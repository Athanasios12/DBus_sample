#ifndef DBUSMETHOD_H
#define DBUSMETHOD_H
#include "DBusArgument.h"
#include "DBusMethodReply.h"
#include <vector>
#include <string>
#include <functional>
#include <memory>

namespace DBUS
{
    class DBusMethod
    {
    public:
        typedef std::function<DBusMethodReply(const std::vector<std::unique_ptr<DBusArgument>>&)> dBusMethodBinding;

        DBusMethod();
        DBusMethod(const std::string& name, dBusMethodBinding &binding,std::size_t numOfArgs, DBusArgument::ArgType returnType);
        DBusMethod(const DBusMethod &other);
        DBusMethod(DBusMethod &&other);
        DBusMethod& operator=(const DBusMethod &other);
        DBusMethod& operator=(DBusMethod &&other);

        bool operator==(const DBusMethod& other) const;

        bool checkIfAllArgsSet() const;
        DBusMethodReply callBinding() const;

        bool setArg(std::unique_ptr<DBusArgument> &arg, uint8_t argNum);
        bool setBindingArgTypes(const std::vector<DBusArgument::ArgType> &bindingArgTypes);
        void setBinding(dBusMethodBinding &binding, uint8_t numOfArgs);
        void setName(const std::string &name);
        void setObjectName(const std::string &name);
        void setInterfaceName(const std::string &name);
        
        bool extractMsgInputArguments(DBusMessageIter *msgItr);

        uint8_t getNumOfArgs() const;
        std::string getName() const;
        std::string getObjectName() const;
        std::string getInterfaceName() const;
        DBusArgument::ArgType getReturnType() const;

    private:
        void resizeAndInitArgs(std::size_t newSize);

        bool m_bindingSet;
        std::size_t m_numOfArgs;
        dBusMethodBinding m_binding;
        std::string m_name;
        std::string m_objectName;
        std::string m_interfaceName;
        std::vector<std::unique_ptr<DBusArgument>> m_args;
        std::vector<DBusArgument::ArgType> m_argTypes;
        DBusArgument::ArgType m_returnType;
    };
}
#endif // DBUSMETHOD_H
