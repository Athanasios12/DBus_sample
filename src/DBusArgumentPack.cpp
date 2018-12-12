#include "DBusArgumentPack.h"
#include "DBusArgumentFactory.h"
#include "DBusInterface.h"

namespace DBUS
{

    DBusArgumentPack::DBusArgumentPack(const std::string &methodName, const std::string &objectName, const std::string &interfaceName):
        m_isInitialized{true},
        m_methodName{methodName},
        m_objectName{objectName},
        m_interfaceName{interfaceName}
    {

    }

    DBusArgumentPack::DBusArgumentPack(const DBusArgumentPack &other)
    {
        if(this != &other)
        {
            m_isInitialized = other.m_isInitialized;
            m_requestReply = other.m_requestReply;
            m_args.clear();
            for(auto && arg : other.m_args)
            {
                if(arg)
                {
                    auto argCopy = DBusArgumentFactory::getArgCopy(arg.get());
                    m_args.push_back(std::move(argCopy));
                }
            }
            m_methodName = other.m_methodName;
            m_objectName = other.m_objectName;
            m_interfaceName = other.m_interfaceName;
        }
    }

    DBusArgumentPack::DBusArgumentPack(DBusArgumentPack &&other)
    {
        if(this != &other)
        {
            m_isInitialized = other.m_isInitialized;
            m_requestReply = other.m_requestReply;
            m_args = std::move(other.m_args);
            m_methodName = std::move(other.m_methodName);
            m_objectName = std::move(other.m_objectName);
            m_interfaceName = std::move(other.m_interfaceName);
            other.m_isInitialized = false;
            other.m_requestReply = false;
        }
    }

    DBusArgumentPack& DBusArgumentPack::operator=(const DBusArgumentPack &other)
    {
        if(this != &other)
        {
            m_isInitialized = other.m_isInitialized;
            m_requestReply = other.m_requestReply;
            m_args.clear();
            for(auto && arg : other.m_args)
            {
                if(arg)
                {
                    auto argCopy = DBusArgumentFactory::getArgCopy(arg.get());
                    m_args.push_back(std::move(argCopy));
                }
            }
            m_methodName = other.m_methodName;
            m_objectName = other.m_objectName;
            m_interfaceName = other.m_interfaceName;
        }
        return *this;
    }

    DBusArgumentPack& DBusArgumentPack::operator=(DBusArgumentPack &&other)
    {
        if(this != &other)
        {
            m_isInitialized = other.m_isInitialized;
            m_requestReply = other.m_requestReply;
            m_args = std::move(other.m_args);
            m_methodName = std::move(other.m_methodName);
            m_objectName = std::move(other.m_objectName);
            m_interfaceName = std::move(other.m_interfaceName);
            other.m_isInitialized = false;
            other.m_requestReply = false;
        }
        return *this;
    }

    bool DBusArgumentPack::operator==(const DBusArgumentPack &other) const
    {
        return (m_isInitialized == other.m_isInitialized) &&
                (m_requestReply == other.m_requestReply) &&
                (m_methodName == other.m_methodName) &&
                (m_objectName == other.m_objectName) &&
                (m_interfaceName == other.m_interfaceName) &&
                (m_args == other.m_args);

    }

    DBusArgument *DBusArgumentPack::addNewArgument(DBusArgument::ArgType argType)
    {
        DBusArgument *retArgPtr = nullptr;
        auto newArg = DBusArgumentFactory::getArgument(argType);
        if(newArg)
        {
            retArgPtr = newArg.get();
            m_args.push_back(std::move(newArg));
        }
        return retArgPtr;
    }

    bool DBusArgumentPack::setArg(std::unique_ptr<DBusArgument> &arg, std::size_t argNum)
    {
        bool argSet = false;
        if(argNum < m_args.size())
        {
            if(arg)
            {
                m_args[argNum] = std::move(arg);
                argSet = true;
            }
        }
        return argSet;
    }

    bool DBusArgumentPack::removeArg(std::size_t argNum)
    {
        bool argRemoved = false;
        if(argNum < m_args.size())
        {
            m_args.erase(m_args.begin() + argNum);
            argRemoved = true;
        }
        return  argRemoved;
    }

    bool DBusArgumentPack::appendArgsToDBusMsg(DBusMessageIter *msgItr) const
    {
        bool processed = true;
        for(auto && arg : m_args)
        {            
            if(!DBusInterface::appendArg(arg.get(), msgItr))
            {
                processed = false;
                break;
            }
        }
        return processed;
    }

    bool DBusArgumentPack::checkIfAllArgsValid() const
    {
        bool valid = true;
        for(auto && arg : m_args)
        {
            if(!arg)
            {
                valid = false;
                break;
            }
        }
        return valid && (m_args.size() > 0);
    }

    void DBusArgumentPack::setMethodName(const std::string &name)
    {
        m_methodName = name;
    }

    void DBusArgumentPack::setObjectName(const std::string &name)
    {
        m_objectName = name;
    }

    void DBusArgumentPack::setInterfaceName(const std::string &name)
    {
        m_interfaceName = name;
    }

    void DBusArgumentPack::setMethodReturnType(DBusArgument::ArgType returnType)
    {
        m_methodReturnType = returnType;
    }

    void DBusArgumentPack::setRequestReply(bool requestReply)
    {
        m_requestReply = requestReply;
    }

    std::string DBusArgumentPack::getMethodName() const
    {
        return m_methodName;
    }

    std::string DBusArgumentPack::getObjectName() const
    {
        return m_objectName;
    }

    std::string DBusArgumentPack::getInterfaceName() const
    {
        return m_interfaceName;
    }

    bool DBusArgumentPack::getRequestReply() const
    {
       return m_requestReply;
    }

    std::size_t DBusArgumentPack::getNumOfArgs() const
    {
        return m_args.size();
    }

    DBusArgument::ArgType DBusArgumentPack::getReturnType() const
    {
        return m_methodReturnType;
    }

}
