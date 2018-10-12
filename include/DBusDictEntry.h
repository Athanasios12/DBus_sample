#ifndef DBUSDICTENTRY_H
#define DBUSDICTENTRY_H
#include "DBusContainerArg.h"
#include "DBusBasicArgument.h"
#include <memory>

namespace DBUS
{
    class DBusDictEntry : public DBusContainerArg
    {
    public:
        DBusDictEntry();
        DBusDictEntry(std::unique_ptr<DBusArgument> &key, std::unique_ptr<DBusArgument> &value);
        DBusDictEntry(const DBusDictEntry &other);
        DBusDictEntry(DBusDictEntry &&other);
        DBusDictEntry& operator=(const DBusDictEntry &other);
        DBusDictEntry& operator=(DBusDictEntry &&other);
        ~DBusDictEntry();

        bool addArgument(DBusArgument* arg);

        //take over managing underlying pointers and reset the passed arguments
        bool setKey(std::unique_ptr<DBusArgument> &key);
        bool setValue(std::unique_ptr<DBusArgument> &value);
    private:
        void setEntrySignature();
        void initializeEntryArgs();

        bool m_keySet{false};
        bool m_valSet{false};
    };
}

#endif // DBUSDICTENTRY_H
