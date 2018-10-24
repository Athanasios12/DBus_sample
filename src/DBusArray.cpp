#include "DBusArray.h"

namespace DBUS
{

    DBusArray::DBusArray():
        DBusContainerArg(ArgType::Array),
        m_elemType(ArgType::Invalid)
    {

    }

    DBusArray::DBusArray(ArgType argType):
        DBusContainerArg(ArgType::Array),
        m_elemType(argType)
    {
        m_containedSignature = getArgTypeSignature(m_elemType);
        m_signature += m_containedSignature;
    }

    DBusArray::DBusArray(const DBusArray &other):
        DBusContainerArg(other)
    {
        m_elemType = other.m_elemType;
        m_elemTypeSet = other.m_elemTypeSet;
    }

    DBusArray::DBusArray(DBusArray &&other):
        DBusContainerArg(std::forward<DBusArray>(other))
    {
        m_elemType = other.m_elemType;
        m_elemTypeSet = other.m_elemTypeSet;
        other.m_elemTypeSet = false;
        other.m_elemType = ArgType::Invalid;
    }

    DBusArray& DBusArray::operator=(const DBusArray &other)
    {
        if(this != &other)
        {
            m_elemType = other.m_elemType;
            m_elemTypeSet = other.m_elemTypeSet;
            DBusContainerArg::operator=(other);
        }
        return *this;
    }

    DBusArray& DBusArray::operator=(DBusArray &&other)
    {
        if(this != &other)
        {
            m_elemType = other.m_elemType;
            m_elemTypeSet = other.m_elemTypeSet;
            other.m_elemType = ArgType::Invalid;
            other.m_elemTypeSet = false;
            DBusContainerArg::operator=(std::forward<DBusArray>(other));
        }
        return *this;
    }

    DBusArray::~DBusArray()
    {

    }

    bool DBusArray::operator==(const DBusArray &other) const
    {
        bool equal = false;
        if(m_elemType == other.m_elemType)
        {
            equal = DBusContainerArg::operator==(other);
        }
        return equal;
    }

    bool DBusArray::addArgument(DBusArgument *arg)
    {
        //container of containers other than dictionary may cause problems, test that
        bool addedNewArg = false;
        if(arg)
        {
            if(m_elemTypeSet)
            {
                if(arg->getArgType() != ArgType::Invalid)
                {
                    if(arg->getArgType() == m_elemType)
                    {
                        auto newArg = DBusArgumentFactory::getArgCopy(arg);
                        if(newArg)
                        {
                            if(containedSignatureMatch(newArg.get()))
                            {
                                m_subArgs.push_back(std::move(newArg));
                                addedNewArg = true;
                            }
                        }

                    }
                }
            }
        }
        return addedNewArg;
    }

    bool DBusArray::setElementsType(ArgType argType)
    {
        bool setElemType = false;
        if(argType != ArgType::Invalid)
        {
            if(!m_elemTypeSet) // otherwise specify explicitly by calling resetContainer and then set type
            {
                // elem type has not been set yet
                setElemType = (getArgTypeIndex(argType) >= 0);
                if(setElemType)
                {
                    m_elemType = argType;
                    m_elemTypeSet = true;
                    m_containedSignature = getArgTypeSignature(argType);
                    m_signature = getArgTypeSignature(ArgType::Array) + m_containedSignature;
                }
            }
        }
        return setElemType;
    }

    void DBusArray::resetArgument()
    {
        DBusContainerArg::resetArgument();
        m_elemType = ArgType::Invalid;
        m_elemTypeSet = false;
    }

    const char *DBusArray::getContainerSignature() const
    {
        const char *retPtr = nullptr;
        if(!m_containedSignature.empty())
        {
            retPtr = m_containedSignature.c_str();
        }
        return retPtr;
    }

    DBusArgument::ArgType DBusArray::getElemType() const
    {
        return m_elemType;
    }

    bool DBusArray::isElementTypeSet() const
    {
        return m_elemTypeSet;
    }

    bool DBusArray::containedSignatureMatch(DBusArgument *arg)
    {
        bool sigMatch = true;
        if(arg)
        {
            if(m_subArgs.size() == 0)
            {
                m_signature += arg->getSignature();
                m_containedSignature = arg->getSignature();
            }
            else if(arg->getSignature() != m_containedSignature)
            {
                sigMatch = false;
            }
        }
        return sigMatch;
    }
}
