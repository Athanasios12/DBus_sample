#include "DBusDictionary.h"
#include "DBusDictEntry.h"

namespace DBUS
{

    DBusDictionary::DBusDictionary():
        DBusContainerArg(ArgType::Dictionary),
        m_initialized{false}
    {
        m_entryType = std::make_pair(ArgType::Invalid, ArgType::Invalid);
    }

    DBusDictionary::DBusDictionary(ArgType keyType, ArgType valType):
        DBusContainerArg(ArgType::Dictionary),
        m_initialized{true}
    {
        m_entryType = std::make_pair(keyType, valType);
        m_containedSignature = DBusDictEntry::createEntrySignature(keyType, valType);
        m_signature += m_containedSignature;
    }

    DBusDictionary::DBusDictionary(const DBusDictionary &other):
        DBusContainerArg(other)
    {
        if(this != &other)
        {
            m_initialized = other.m_initialized;
            m_entryType = other.m_entryType;            
        }
    }

    DBusDictionary::DBusDictionary(DBusDictionary &&other):
        DBusContainerArg(std::forward<DBusDictionary>(other))
    {
        if(this != &other)
        {
            m_initialized = other.m_initialized;
            m_entryType = other.m_entryType;
            other.m_initialized = false;
            other.m_entryType = std::make_pair(ArgType::Invalid, ArgType::Invalid);
            other.m_signature = getArgTypeSignature(ArgType::Dictionary);
        }
    }

    DBusDictionary& DBusDictionary::operator=(const DBusDictionary &other)
    {        
        if(this != &other)
        {
            m_initialized = other.m_initialized;
            m_entryType = other.m_entryType;
            DBusContainerArg::operator=(other);
        }
        return *this;
    }

    DBusDictionary& DBusDictionary::operator=(DBusDictionary &&other)
    {        
        if(this != &other)
        {
            m_initialized = other.m_initialized;
            m_entryType = other.m_entryType;
            other.m_initialized = false;
            other.m_entryType = std::make_pair(ArgType::Invalid, ArgType::Invalid);
            DBusContainerArg::operator=(std::forward<DBusDictionary>(other));
        }
        return *this;
    }

    DBusDictionary::~DBusDictionary()
    {

    }

    bool DBusDictionary::operator==(const DBusDictionary &other) const
    {
        //move this to parent class and call its operator
        bool equal = false;
        if(m_subArgs.size() == other.m_subArgs.size())
        {
            bool allEqual = true;
            for(size_t i = 0; i < m_subArgs.size(); i++)
            {
                if(m_subArgs[i] != other.m_subArgs[i])
                {
                    allEqual = false;
                    break;
                }
            }
            equal = allEqual;
        }
        return equal;
    }

    bool DBusDictionary::addArgument(DBusArgument *arg)
    {
        bool addedNewArg = false;        
        if(arg)
        {
            if(arg->getArgType() == ArgType::Dictionary_Entry)
            {
                auto entry = static_cast<DBusDictEntry*>(arg);
                if(entry->getKeySet() && entry->getValueSet())
                {
                    if(!m_initialized)
                    {
                        m_entryType = std::make_pair(entry->getKeyType(), entry->getValueType());
                        m_containedSignature = entry->getSignature();
                        m_signature += m_containedSignature;
                        m_initialized = true;
                    }
                    if((entry->getKeyType() == m_entryType.first) && (entry->getValueType() == m_entryType.second))
                    {
                        auto newArg = DBusArgumentFactory::getArgCopy(arg);
                        if(newArg)
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

    bool DBusDictionary::setEntryType(ArgType keyType, ArgType valType)
    {
        bool entryTypeSet = false;
        if(!m_initialized)
        {
            //type has not been set yet
            entryTypeSet = (getArgTypeIndex(keyType) >= 0) && (getArgTypeIndex(valType) >= 0);
            if(entryTypeSet)
            {
                m_entryType = std::make_pair(keyType, valType);
                m_containedSignature = DBusDictEntry::createEntrySignature(keyType, valType);
                m_signature += m_containedSignature;
                m_initialized = true;
            }
        }
        return entryTypeSet;
    }

    const char *DBusDictionary::getContainerSignature() const
    {
        const char* retSig = nullptr;
        if(!m_containedSignature.empty())
        {
            retSig = m_containedSignature.c_str();
        }
        return retSig;
    }

    DBusArgument::ArgType DBusDictionary::getArgType() const
    {
        //dictionary is an specified array to dbus protocol, so the type returned by this
        //class is different than its enum type
        return static_cast<ArgType>(DBUS_TYPE_ARRAY);
    }

    std::pair<DBusArgument::ArgType, DBusArgument::ArgType> DBusDictionary::getEntryType() const
    {
        return m_entryType;
    }

    bool DBusDictionary::isInitialized() const
    {
        return m_initialized;
    }

    template<>
    bool DBusDictionary::addEntry(DBusArgument *key, DBusArgument *value)
    {
        bool entryAdded = false;
        if(m_initialized)
        {
        if(key && value)
        {
            if(key->getArgType() == m_entryType.first)
            {
                if(value->getArgType() == m_entryType.second)
                {
                    auto keyArg = DBusArgumentFactory::getArgCopy(key);
                    if(keyArg)
                    {
                        auto valArg = DBusArgumentFactory::getArgCopy(value);
                        if(valArg)
                        {
                            if(!keyArg->argIsContainerType() && !valArg->argIsContainerType())
                            {                                
                                std::unique_ptr<DBusArgument> newEntry{new DBusDictEntry{static_cast<DBusBasicArgument*>(keyArg.release()), static_cast<DBusBasicArgument*>(valArg.release())}};
                                m_subArgs.push_back(std::move(newEntry));
                                entryAdded = true;
                            }
                        }
                    }
                }
            }
        }
        }
        return entryAdded;
    }
}
