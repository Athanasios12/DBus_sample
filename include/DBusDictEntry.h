#ifndef DBUSDICTENTRY_H
#define DBUSDICTENTRY_H
#include "DBusContainerArg.h"
#include <memory>

namespace DBUS
{
    class DBusDictEntry : public DBusContainerArg
    {
    public:
        DBusDictEntry();
        explicit DBusDictEntry(std::unique_ptr<DBusArgument> &key, std::unique_ptr<DBusArgument> &value);
        explicit DBusDictEntry(DBusArgument *key, DBusArgument *value);
        DBusDictEntry(const DBusDictEntry &other);
        DBusDictEntry(DBusDictEntry &&other);
        DBusDictEntry& operator=(const DBusDictEntry &other);
        DBusDictEntry& operator=(DBusDictEntry &&other);
        ~DBusDictEntry();

        bool addArgument(DBusArgument* arg);
        static std::string createEntrySignature(ArgType key, ArgType value);
        //maybe later add option of changing the entry type after initalization - arg reset

        //take over managing underlying pointers and reset the passed arguments
        bool setKey(std::unique_ptr<DBusArgument> &key);
        bool setValue(std::unique_ptr<DBusArgument> &value);
        bool setKey(DBusArgument *key);
        bool setValue(DBusArgument *value);

        ArgType getKeyType() const;
        ArgType getValueType() const;
        bool getKeySet() const;
        bool getValueSet() const;
    private:
        void setEntrySignature();
        void initializeEntryArgs();

        bool m_keySet{false};
        bool m_valSet{false};

    };
}

#endif // DBUSDICTENTRY_H
