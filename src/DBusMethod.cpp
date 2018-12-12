#include "DBusMethod.h"
#include "DBusArgumentFactory.h"
#include "DBusInterface.h"

namespace DBUS
{
    void DBusMethod::resizeAndInitArgs(std::size_t newSize)
    {
        m_args.clear();
        m_args.resize(newSize);
        for(auto && arg : m_args)
        {
            arg = nullptr;
        }
    }

    DBusMethod::DBusMethod(const std::string& name):
        m_bindingSet{false},
        m_numOfArgs{0},
        m_returnType{DBusArgument::ArgType::Invalid},
        m_bindingArgTypesSet{false},
        m_name{name}
    {

    }

    DBusMethod::DBusMethod(const std::string& name, dBusMethodBinding &binding, std::size_t numOfArgs, DBusArgument::ArgType returnType):
        m_bindingSet(true),
        m_numOfArgs(numOfArgs),
        m_binding(binding),
        m_name(name),
        m_returnType(returnType)

    {
        m_bindingArgTypesSet = !(numOfArgs > 0);
        resizeAndInitArgs(numOfArgs);
    }

    DBusMethod::DBusMethod(const DBusMethod &other)
    {
        if(this != &other)
        {
            m_bindingSet = other.m_bindingSet;
            m_numOfArgs = other.m_numOfArgs;
            resizeAndInitArgs(other.m_numOfArgs);
            for(std::size_t i = 0; i < m_numOfArgs; i++)
            {
                if(other.m_args[i])
                {
                    auto argCopy = DBusArgumentFactory::getArgCopy(other.m_args[i].get());
                    m_args[i] = std::move(argCopy);
                }
            }
            m_argTypes = other.m_argTypes;
            m_binding = other.m_binding;
            m_name = other.m_name;
            m_objectName = other.m_objectName;
            m_interfaceName = other.m_interfaceName;
            m_returnType = other.m_returnType;
        }
    }

    DBusMethod::DBusMethod(DBusMethod &&other)
    {
        if(this != &other)
        {
            m_bindingSet = other.m_bindingSet;
            m_args = std::move(other.m_args);
            m_argTypes = std::move(other.m_argTypes);
            m_numOfArgs = other.m_numOfArgs;
            other.m_numOfArgs = 0;
            m_binding = other.m_binding;
            m_name = std::move(other.m_name);
            m_objectName = std::move(other.m_objectName);
            m_interfaceName = std::move(other.m_interfaceName);
            m_returnType = other.m_returnType;
            other.m_returnType = DBusArgument::ArgType::Invalid;
        }
    }

    DBusMethod& DBusMethod::operator=(const DBusMethod &other)
    {
        if(this != &other)
        {
            m_bindingSet = other.m_bindingSet;
            m_numOfArgs = other.m_numOfArgs;
            resizeAndInitArgs(other.m_numOfArgs);
            for(std::size_t i = 0; i < m_numOfArgs; i++)
            {
                if(other.m_args[i])
                {
                    auto argCopy = DBusArgumentFactory::getArgCopy(other.m_args[i].get());
                    m_args[i] = std::move(argCopy);
                }
            }
            m_argTypes = other.m_argTypes;
            m_binding = other.m_binding;
            m_name = other.m_name;
            m_objectName = other.m_objectName;
            m_interfaceName = other.m_interfaceName;
            m_returnType = other.m_returnType;
        }
        return *this;
    }

    DBusMethod& DBusMethod::operator=(DBusMethod &&other)
    {
        if(this != &other)
        {
            m_bindingSet = other.m_bindingSet;
            m_args = std::move(other.m_args);
            m_argTypes = std::move(other.m_argTypes);
            m_numOfArgs = other.m_numOfArgs;
            other.m_numOfArgs = 0;
            m_binding = other.m_binding;
            m_name = std::move(other.m_name);
            m_objectName = std::move(other.m_objectName);
            m_interfaceName = std::move(other.m_interfaceName);
            m_returnType = other.m_returnType;
            other.m_returnType = DBusArgument::ArgType::Invalid;
        }
        return *this;
    }

    bool DBusMethod::operator==(const DBusMethod& other) const
    {
        return (other.m_name == m_name);
    }

    bool DBusMethod::checkIfAllArgsSet() const
    {
        bool valid = true;
        for (auto && arg : m_args)
        {
            if(DBusArgument::ArgType::Invalid == arg->getArgType())
            {
                valid = false;
                break;
            }
        }
        return valid;
    }

    bool DBusMethod::setArg(std::unique_ptr<DBusArgument> &arg, std::size_t argNum)
    {
        return setArg(arg.get(), argNum);
    }

    bool DBusMethod::setArg(DBusArgument *arg, std::size_t argNum)
    {
        bool argSet = false;
        if(m_bindingSet && m_bindingArgTypesSet)
        {
            if(argNum < m_numOfArgs)
            {
                //check argument type before assigning it to it
                if(arg)
                {
                    if(arg->isArgInitlized())
                    {
                        if(arg->getArgType() == m_argTypes[argNum])
                        {
                            auto argCopy = DBusArgumentFactory::getArgCopy(arg);
                            if(argCopy)
                            {
                                m_args[argNum] = std::move(argCopy);
                                argSet = true;
                            }
                        }
                    }
                }
            }
        }
        return argSet;
    }

    bool DBusMethod::setBindingArgTypes(const std::vector<DBusArgument::ArgType> &bindingArgTypes)
    {
        bool argTypesSet = false;
        if(m_bindingSet)
        {
            if(m_args.size() == bindingArgTypes.size())
            {
                m_argTypes = bindingArgTypes;
                argTypesSet = true;
                m_bindingArgTypesSet = true;
            }
        }
        return argTypesSet;
    }

    DBusMethodReply DBusMethod::callBinding() const
    {
        DBusMethodReply reply;
        //check if all arguments are valid
        if(checkIfAllArgsSet())
        {
            //call binding
            reply = m_binding(m_args);
        }
        return reply;
    }

    std::size_t DBusMethod::getNumOfArgs() const
    {
        return m_numOfArgs;
    }

    void DBusMethod::setBinding(dBusMethodBinding &binding, std::size_t numOfArgs, DBusArgument::ArgType returnType)
    {
        m_binding = binding;
        m_numOfArgs = numOfArgs;        
        m_bindingSet = true;
        m_returnType = returnType;
        resizeAndInitArgs(numOfArgs);
        m_bindingArgTypesSet = !(numOfArgs > 0);

    }

    std::string DBusMethod::getName() const
    {
        return m_name;
    }

    std::string DBusMethod::getObjectName() const
    {
        return m_objectName;
    }

    std::string DBusMethod::getInterfaceName() const
    {
        return m_interfaceName;
    }

    DBusArgument::ArgType DBusMethod::getReturnType() const
    {
        return m_returnType;
    }

    bool DBusMethod::bindingIsSet() const
    {
        return m_bindingSet;
    }

    bool DBusMethod::methodArgTypesSet() const
    {
        return m_bindingArgTypesSet;
    }

    void DBusMethod::setName(const std::string &name)
    {
        m_name = name;
    }

    void DBusMethod::setObjectName(const std::string &name)
    {
        m_objectName = name;
    }

    void DBusMethod::setInterfaceName(const std::string &name)
    {
        m_interfaceName = name;
    }

    bool DBusMethod::extractMsgInputArguments(DBusMessageIter *msgItr)
    {
        bool extractedArgs = false;
        if(m_bindingSet && m_bindingArgTypesSet && m_returnType != DBusArgument::ArgType::Invalid)
        {
            uint16_t numOfMatchedArgs = 0;
            for(auto && arg : m_args)
            {
                if(arg->getArgType() == dbus_message_iter_get_arg_type(msgItr))
                {
                    if(DBusInterface::extractDBusMessageArgData(arg.get(), msgItr))
                    {
                        ++numOfMatchedArgs;
                    }
                }
                dbus_message_iter_next(msgItr);
            }
            extractedArgs = (numOfMatchedArgs == m_args.size());
        }
        return extractedArgs;
    }
}
