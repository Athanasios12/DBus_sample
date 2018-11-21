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
        virtual void resetArgument();
        virtual bool resetContainedArgument(std::size_t pos, DBusArgument* newArg);

        virtual ArgType getArgType() const;
        virtual const char* getContainerSignature() const;
        //later have iterator getters as protected, only server, client and interface classes will have access to this
        //for easier handling of data exchange
        SubArgs::iterator getFirstArgItr();
        SubArgs::iterator getLastArgItr();
        //----------------------------------
        DBusArgument* getArgValueAt(std::size_t pos) const;
        std::size_t getSize() const;
        std::string getContainerTypeSignature() const;
        std::string getContainedSignature() const;
        virtual ArgType getContainerType() const;
    protected:
        SubArgs m_subArgs;
        std::string m_containerSignature;
        std::string m_containedSignature;
    };
}

#endif // DBUSCONTAINERARG_H
