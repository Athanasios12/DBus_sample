#ifndef DBUSARGUMENTPACK_H
#define DBUSARGUMENTPACK_H
#include "DBusArgument.h"
#include <string>
#include <vector>
#include <memory>

namespace DBUS
{
    class DBusArgumentPack
    {
    public:

        DBusArgumentPack() = default;
        DBusArgumentPack(const std::string &methodName, const std::string &objectName, const std::string &interfaceName);
        DBusArgumentPack(const DBusArgumentPack &other);
        DBusArgumentPack(DBusArgumentPack &&other);
        DBusArgumentPack& operator=(const DBusArgumentPack &other);
        DBusArgumentPack& operator=(DBusArgumentPack &&other);

        bool operator==(const DBusArgumentPack& other) const;

        DBusArgument* addNewArgument(DBusArgument::ArgType argType);
        bool setArg(std::unique_ptr<DBusArgument> &arg, std::size_t argNum);
        bool removeArg(std::size_t argNum);
        bool appendArgsToDBusMsg(DBusMessageIter *msgItr) const;
        bool checkIfAllArgsValid() const;

        void setMethodName(const std::string &name);
        void setObjectName(const std::string &name);
        void setInterfaceName(const std::string &name);
        void setMethodReturnType(DBusArgument::ArgType returnType);
        void setRequestReply(bool requestReply);

        std::string getMethodName() const;
        std::string getObjectName() const;
        std::string getInterfaceName() const;
        bool getRequestReply() const;
        std::size_t getNumOfArgs() const;
        DBusArgument::ArgType getReturnType() const;
        const DBusArgument *getInputArg(size_t argNum) const;
    private:
        bool m_isInitialized{false};
        bool m_requestReply{false};
        std::string m_methodName;
        std::string m_objectName;
        std::string m_interfaceName;
        DBusArgument::ArgType m_methodReturnType;
        std::vector<std::unique_ptr<DBusArgument>> m_args;

    };
}
#endif // DBUSARGUMENTPACK_H
