#ifndef DBUSARGUMENTFACTORY_H
#define DBUSARGUMENTFACTORY_H
#include "DBusArgument.h"
#include <memory>

namespace DBUS
{
    //Only static methods because this factory is not going to be used otherwise then constructing
    //and returning allocated objects
    class DBusArgumentFactory
    {
    public:
        static std::unique_ptr<DBusArgument> getArgument(DBusArgument::ArgType argType);
        static std::unique_ptr<DBusArgument> getArgCopy(DBusArgument *arg);
    private:
        DBusArgumentFactory()=delete;
        DBusArgumentFactory(const DBusArgumentFactory &other)=delete;
        DBusArgumentFactory& operator=(const DBusArgumentFactory &other)=delete;
    };
}

#endif // DBUSARGUMENTFACTORY_H
