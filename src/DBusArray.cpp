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

    }

    DBusArray::DBusArray(const DBusArray &other):
        DBusContainerArg(other)
    {
        if(this != &other)
        {
            m_elemType = other.m_elemType;
        }
    }

    DBusArray::DBusArray(DBusArray &&other):
        DBusContainerArg(std::forward<DBusArray>(other))
    {
        if(this != &other)
        {
            m_elemType = other.m_elemType;
            other.m_elemType = ArgType::Invalid;
        }
    }

    DBusArray& DBusArray::operator=(const DBusArray &other)
    {
        if(this != &other)
        {
            m_elemType = other.m_elemType;
            DBusContainerArg::operator=(other);
        }
        return *this;
    }

    DBusArray& DBusArray::operator=(DBusArray &&other)
    {
        if(this != &other)
        {
            m_elemType = other.m_elemType;
            other.m_elemType = ArgType::Invalid;
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
        return addedNewArg;
    }

    bool DBusArray::setElementsType(ArgType argType)
    {
        bool setElemType = false;
        if(m_elemType == ArgType::Invalid)
        {
            // elem type has not been set yet
            setElemType = (getArgTypeIndex(argType) >= 0);
            if(setElemType)
            {
                m_elemType = argType;
            }
        }
        return setElemType;
    }

    const char *DBusArray::getContainerSignature() const
    {
        return m_containedSignature.c_str();
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
