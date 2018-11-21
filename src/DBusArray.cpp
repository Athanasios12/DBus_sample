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
            if(arg->getArgType() != ArgType::Invalid)
            {
                if(arg->isArgInitlized())
                {
                    //special case for dictionary - because it type return is different than container type
                    //dictionary is special array of entries in DBus protocol
                    bool elemIsMatchingDictionary = false;
                    if(arg->argIsContainerType())
                    {
                        auto cArg = static_cast<DBusContainerArg*>(arg);
                        if((cArg->getContainerType() == m_elemType) && (cArg->getArgType() != m_elemType))
                        {
                            elemIsMatchingDictionary = true;
                        }
                    }
                    if(arg->getArgType() == m_elemType || elemIsMatchingDictionary)
                    {
                        auto newArg = DBusArgumentFactory::getArgCopy(arg);
                        if(newArg)
                        {
                            if(containedSignatureMatch(newArg.get()))
                            {
                                m_subArgs.push_back(std::move(newArg));
                                addedNewArg = true;
                                m_argIsInitalized = true;
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
        bool sigMatch = false;
        if(arg)
        {
            if(!arg->argIsContainerType())
            {
                if(arg->getSignature() == m_containedSignature && m_elemType != ArgType::Invalid)
                {
                    sigMatch = true;
                }
            }
            else
            {
                auto containerArg = static_cast<DBusContainerArg*>(arg);
                if(containerArg->getContainerTypeSignature() == m_containedSignature ||
                   containerArg->getSignature() == m_containedSignature)
                {
                    std::string elemSig{containerArg->getSignature()};
                    if(!m_elemTypeSet)
                    {
                        m_signature = m_containerSignature + elemSig;
                        m_containedSignature = elemSig;
                        m_elemTypeSet = true;
                    }
                    if(m_signature == m_containerSignature + elemSig)
                    {
                        sigMatch = true;
                    }
                }
            }
        }
        return sigMatch;
    }
}
