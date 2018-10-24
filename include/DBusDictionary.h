#ifndef DBUSDICTIONARY_H
#define DBUSDICTIONARY_H
#include "DBusContainerArg.h"
#include "DBusArgumentFactory.h"
#include "DBusBasicArgument.h"
#include "DBusDictEntry.h"
#include <vector>
#include <memory>
#include <utility>

namespace DBUS
{
    class DBusDictionary : public DBusContainerArg
    {
    public:
        DBusDictionary();
        DBusDictionary(ArgType keyType, ArgType valType);
        DBusDictionary(const DBusDictionary &other);
        DBusDictionary(DBusDictionary &&other);
        DBusDictionary& operator=(const DBusDictionary &other);
        DBusDictionary& operator=(DBusDictionary &&other);
        virtual ~DBusDictionary();

        bool operator==(const DBusDictionary &other) const;

        template<typename Key, typename Value>
        bool addEntry(Key key, Value value);
        bool addArgument(DBusArgument* arg);
        bool setEntryType(ArgType keyType, ArgType valType);
        const char* getContainerSignature() const final;

        ArgType getArgType() const;
        std::pair<ArgType, ArgType> getEntryType() const;
        bool isInitialized() const;
    private:
        bool  m_initialized;
        std::pair<ArgType, ArgType> m_entryType;
    };

    template<typename Key, typename Value>
    bool DBusDictionary::addEntry(Key key, Value value)
    {
        bool entryAdded = false;
        if(m_initialized)
        {
            //check if types match
            argValType keyVariant{};
            auto keyIdx = setArgVariant(keyVariant, key);
            argValType valVariant{};
            auto valIdx = setArgVariant(valVariant, value);
            //fprintf(stderr, "\nKey index : %d\nValue index: %d\n", keyVariant.index(), valVariant.index());
            if(static_cast<int>(keyIdx) == getArgTypeIndex(m_entryType.first))
            {
                if(static_cast<int>(valIdx) == getArgTypeIndex(m_entryType.second))
                {
                    std::unique_ptr<DBusArgument> keyArg{new DBusBasicArgument{m_entryType.first}};
                    if(keyArg)
                    {
                        if(static_cast<DBusBasicArgument*>(keyArg.get())->setArgValue(key))
                        {
                            //key matches the entry type
                            std::unique_ptr<DBusArgument> valArg{new DBusBasicArgument{m_entryType.second}};
                            if(valArg)
                            {
                                //check if value matches entry type
                                if(static_cast<DBusBasicArgument*>(valArg.get())->setArgValue<decltype(value)>(value))
                                {
                                    std::unique_ptr<DBusArgument> newEntry{new DBusDictEntry{keyArg, valArg}};
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

#endif // DBUSDICTIONARY_H
