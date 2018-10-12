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
    private:
        bool  m_initialized;
        std::pair<ArgType, ArgType> m_entryType;
    };

    template<typename Key, typename Value>
    bool DBusDictionary::addEntry(Key key, Value value)
    {
        bool entryAdded = false;
        //check if types match
        argValType keyVariant;
        argValType valVariant;
        setArgVariant(keyVariant, key);
        setArgVariant(valVariant, value);
        fprintf(stderr, "\nKey index : %d\nValue index: %d\n", keyVariant.index(), valVariant.index());
        if(static_cast<int>(keyVariant.index()) == getArgTypeIndex(m_entryType.first))
        {
            if(static_cast<int>(valVariant.index()) == getArgTypeIndex(m_entryType.second))
            {
                auto keyArg = std::make_unique<DBusBasicArgument>(DBusBasicArgument{m_entryType.first});
                if(keyArg)
                {
                    if(keyArg->setArgValue(key))
                    {
                        //key matches the entry type
                        auto valArg = std::make_unique<DBusBasicArgument>(DBusBasicArgument{m_entryType.second});
                        if(valArg)
                        {
                            //check if value matches entry type
                            if(valArg->setArgValue<decltype(value)>(value))
                            {
                                std::unique_ptr<DBusArgument> newEntry{new DBusDictEntry{keyArg, valArg}};
                                if(m_subArgs.size() == 0)
                                {
                                    m_containedSignature = newEntry->getSignature();
                                }
                                m_subArgs.push_back(std::move(newEntry));
                                entryAdded = true;
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
