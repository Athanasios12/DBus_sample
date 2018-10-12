#include "DBusDictEntry.h"
#include "DBusArgumentFactory.h"

namespace DBUS
{
    const char DICT_ENTRY_START_CHAR = '{';
    const char DICT_ENTRY_END_CHAR = '}';

    void DBusDictEntry::initializeEntryArgs()
    {
        m_subArgs.resize(std::size_t(2));
    }

    DBusDictEntry::DBusDictEntry():
        DBusContainerArg(ArgType::Dictionary_Entry),
        m_key(nullptr),
        m_value(nullptr)
    {
        initializeEntryArgs();
    }

    DBusDictEntry::DBusDictEntry(std::unique_ptr<DBusBasicArgument> &key, std::unique_ptr<DBusBasicArgument> &value):
         DBusContainerArg(ArgType::Dictionary_Entry)
    {
        initializeEntryArgs();
        setKey(key);
        setValue(value);
        setEntrySignature();
    }

    DBusDictEntry::DBusDictEntry(const DBusDictEntry &other):
        DBusContainerArg{other}
    {
        if(this != &other)
        {
            initializeEntryArgs();
            auto keyCopy = DBusArgumentFactory::getArgCopy(other.m_key.get());
            auto valueCopy = DBusArgumentFactory::getArgCopy(other.m_value.get());
            m_key.reset(static_cast<DBusBasicArgument*>(keyCopy.release()));
            m_value.reset(static_cast<DBusBasicArgument*>(valueCopy.release()));
            setEntrySignature();
        }
    }

    DBusDictEntry::DBusDictEntry(DBusDictEntry &&other):
        DBusContainerArg(std::forward<DBusDictEntry>(other))
    {

    }

    DBusDictEntry& DBusDictEntry::operator=(const DBusDictEntry &other)
    {
        if(this != &other)
        {
            DBusContainerArg::operator=(other);
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
            //dokonczyc przerabianie dict entry - constructory operator=& i &&,
            //addArgument - dodanie kontrolowane klucza i wartosci, max 2 elementy,
            //add Argument nie moze dodawac jesli zostaly ustawione, wtedy nalezy uzyc setkey i setvalue
            //zamiast tego. msubargs ma max rozmiar 2 - zdefiniuj jao const lokalny global
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
            if(!m_keySet)
            {
                if(arg->getArgType())
            }
            else if(!m_valSet)
            {

            }
        }
        return addedNewArg;
    }


    bool DBusDictEntry::setKey(std::unique_ptr<DBusArgument> &key)
    {
        bool keyValid = false;
        if(key.get())
        {
            m_key = std::move(key);
            keyValid = true;
        }
        return keyValid;
    }

    bool DBusDictEntry::setValue(std::unique_ptr<DBusArgument> &value)
    {
        bool valueValid = false;
        if(value.get())
        {
            m_value = std::move(value);
            valueValid = true;
        }
        return valueValid;
    }

    bool DBusDictEntry::argIsContainerType() const
    {
        return true;
    }

    DBusBasicArgument* DBusDictEntry::getKey()
    {
        return m_key.get();
    }

    DBusBasicArgument* DBusDictEntry::getValue()
    {
        return m_value.get();
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
                }
            }
        }
    }

}
