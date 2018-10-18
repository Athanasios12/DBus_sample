#ifndef DBUSCONTAINERARG_H
#define DBUSCONTAINERARG_H
#include "DBusArgument.h"
#include <vector>
#include <memory>

namespace DBUS
{
    class DBusContainerArg : public DBusArgument
    {
        typedef std::vector<std::unique_ptr<DBusArgument>> SubArgs;
    public:

        DBusContainerArg();
        DBusContainerArg(ArgType argType);
        DBusContainerArg(const DBusContainerArg &other);
        DBusContainerArg(DBusContainerArg &&other);
        DBusContainerArg& operator=(const DBusContainerArg &other);
        DBusContainerArg& operator=(DBusContainerArg &&other);
        virtual ~DBusContainerArg();

        bool operator==(const DBusContainerArg &other) const;

        bool argIsContainerType() const;
        virtual bool addArgument(DBusArgument* arg) = 0;        

        virtual ArgType getArgType() const;
        virtual const char* getContainerSignature() const;
        SubArgs::iterator getFirstArgItr();
        SubArgs::iterator getLastArgItr();
        std::size_t getSize() const;
    protected:
        SubArgs m_subArgs;
        std::string m_containedSignature;
    };
}

#endif // DBUSCONTAINERARG_H
