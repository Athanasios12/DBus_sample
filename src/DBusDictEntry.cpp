#include "DBusDictEntry.h"
#include "DBusArgumentFactory.h"

namespace DBUS
{
    const char DICT_ENTRY_START_CHAR = '{';
    const char DICT_ENTRY_END_CHAR = '}';
    const size_t KEY_IDX = 0;
    const size_t VALUE_IDX = 1;
    const size_t DICT_ENTRY_SIZE = 2;

    //Add check for basic non container type for key and value

    void DBusDictEntry::initializeEntryArgs()
    {
        m_subArgs.resize(std::size_t(DICT_ENTRY_SIZE));
    }

    DBusDictEntry::DBusDictEntry():
        DBusContainerArg(ArgType::Dictionary_Entry)
    {
        initializeEntryArgs();
    }

    DBusDictEntry::DBusDictEntry(DBusArgument *key, DBusArgument *value):
        DBusContainerArg(ArgType::Dictionary_Entry)
    {
        initializeEntryArgs();
        setKey(key);
        setValue(value);
    }

    DBusDictEntry::DBusDictEntry(std::unique_ptr<DBusArgument> &key, std::unique_ptr<DBusArgument> &value):
         DBusContainerArg(ArgType::Dictionary_Entry)
    {
        initializeEntryArgs();
        setKey(key);
        setValue(value);
    }

    DBusDictEntry::DBusDictEntry(const DBusDictEntry &other):
        DBusContainerArg{other}
    {
        m_keySet = other.m_keySet;
        m_valSet = other.m_valSet;
    }

    DBusDictEntry::DBusDictEntry(DBusDictEntry &&other):
        DBusContainerArg(std::forward<DBusDictEntry>(other))
    {
        m_keySet = other.m_keySet;
        m_valSet = other.m_valSet;
        other.m_keySet = false;
        other.m_valSet = false;
    }

    DBusDictEntry& DBusDictEntry::operator=(const DBusDictEntry &other)
    {
        if(this != &other)
        {
            DBusContainerArg::operator=(other);
            m_keySet = other.m_keySet;
            m_valSet = other.m_valSet;
        }
        return *this;
    }

    DBusDictEntry& DBusDictEntry::operator=(DBusDictEntry &&other)
    {
        if(this != &other)
        {
            DBusContainerArg::operator=(std::forward<DBusDictEntry>(other));
            m_keySet = other.m_keySet;
            m_valSet = other.m_valSet;
            other.m_keySet = false;
            other.m_valSet = false;
        }
        return *this;
    }

    DBusDictEntry::~DBusDictEntry()
    {

    }

    bool DBusDictEntry::addArgument(DBusArgument *arg)
    {
        bool addedNewArg = false;
        if(arg)
        {
            if(!arg->argIsContainerType())
            {
                if(!m_keySet)
                {
                    m_subArgs[KEY_IDX] = DBusArgumentFactory::getArgCopy(arg);
                    m_keySet = true;
                    addedNewArg = true;
                }
                else if(!m_valSet)
                {
                    m_subArgs[VALUE_IDX] = DBusArgumentFactory::getArgCopy(arg);
                    m_valSet = true;
                    addedNewArg = true;
                }
                if(addedNewArg && m_keySet && m_valSet)
                {
                    setEntrySignature();
                }
                //else both key and val has been set, use setkey, setval instead
            }
        }
        return addedNewArg;
    }


    bool DBusDictEntry::setKey(std::unique_ptr<DBusArgument> &key)
    {
        bool keyValid = false;
        if(key)
        {
            //dictionary entry can have only basic types no containers allowed
            if(key->getArgType() != ArgType::Invalid && !key->argIsContainerType())
            {
                if(key->isArgInitlized())
                {
                    m_subArgs[KEY_IDX] = std::move(key);
                    keyValid = true;
                    m_keySet = true;
                    if(m_valSet)
                    {
                        setEntrySignature();
                    }
                }
            }
        }
        return keyValid;
    }

    bool DBusDictEntry::setValue(std::unique_ptr<DBusArgument> &value)
    {
        bool valueValid = false;
        if(value)
        {
            //dictionary entry can have only basic types no containers allowed
            if(value->getArgType() != ArgType::Invalid && !value->argIsContainerType())
            {
                if(value->isArgInitlized())
                {
                    m_subArgs[VALUE_IDX] = std::move(value);
                    valueValid = true;
                    m_valSet = true;
                    if(m_keySet)
                    {
                        setEntrySignature();
                    }
                }
            }
        }
        return valueValid;
    }

    bool DBusDictEntry::setKey(DBusArgument *key)
    {
        bool keyValid = false;
        if(key)
        {
            //dictionary entry can have only basic types no containers allowed
            if(key->getArgType() != ArgType::Invalid && !key->argIsContainerType())
            {
                if(key->isArgInitlized())
                {
                    m_subArgs[KEY_IDX] = std::move(DBusArgumentFactory::getArgCopy(key));
                    keyValid = true;
                    m_keySet = true;
                    if(m_valSet)
                    {
                        setEntrySignature();
                    }
                }
            }
        }
        return keyValid;
    }

    bool DBusDictEntry::setValue(DBusArgument *value)
    {
        bool valueValid = false;
        if(value)
        {
            //dictionary entry can have only basic types no containers allowed
            if(value->getArgType() != ArgType::Invalid && !value->argIsContainerType())
            {
                if(value->isArgInitlized())
                {
                    m_subArgs[VALUE_IDX] = std::move(DBusArgumentFactory::getArgCopy(value));
                    valueValid = true;
                    m_valSet = true;
                    if(m_keySet)
                    {
                        setEntrySignature();
                    }
                }
            }
        }
        return valueValid;
    }

    DBusArgument::ArgType DBusDictEntry::getKeyType() const
    {
        auto type = ArgType::Invalid;
        if(m_keySet)
        {
            type = m_subArgs[KEY_IDX]->getArgType();
        }
        return type;
    }

    DBusArgument::ArgType DBusDictEntry::getValueType() const
    {
        auto type = ArgType::Invalid;
        if(m_valSet)
        {
            type = m_subArgs[VALUE_IDX]->getArgType();
        }
        return type;
    }

    bool DBusDictEntry::getKeySet() const
    {
        return m_keySet;
    }

    bool DBusDictEntry::getValueSet() const
    {
        return m_valSet;
    }

    void DBusDictEntry::setEntrySignature()
    {
        auto entryEnd = m_signature.find_last_of(DICT_ENTRY_END_CHAR);
        if(entryEnd != std::string::npos)
        {
            if(m_keySet && m_valSet)
            {
                if(m_subArgs[KEY_IDX] && m_subArgs[VALUE_IDX])
                {
                    m_signature.insert(entryEnd, m_subArgs[KEY_IDX]->getSignature());
                    entryEnd = m_signature.find_last_of(DICT_ENTRY_END_CHAR);
                    m_signature.insert(entryEnd, m_subArgs[VALUE_IDX]->getSignature());
                    m_argIsInitalized = true;
                }
            }
        }
    }

    std::string DBusDictEntry::createEntrySignature(ArgType key, ArgType value)
    {
        std::string signature;
        auto keyString = getArgTypeSignature(key);
        auto valueString = getArgTypeSignature(value);
        if(!keyString.empty() && !valueString.empty())
        {
            signature = DICT_ENTRY_START_CHAR + keyString + valueString + DICT_ENTRY_END_CHAR;
        }
        return signature;
    }

}
