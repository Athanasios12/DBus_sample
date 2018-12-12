#include "DBusBasicArgument.h"
#include <memory>
#include <cstring>

namespace DBUS
{
    DBusBasicArgument::DBusBasicArgument()
    {

    }

    DBusBasicArgument::DBusBasicArgument(ArgType argType):
        DBusArgument(argType)
    {

    }

    DBusBasicArgument::DBusBasicArgument(const DBusBasicArgument &other):
        DBusArgument(other)
    {
        initializeArgValue(other);
    }

    DBusBasicArgument::DBusBasicArgument(DBusBasicArgument &&other):
        DBusArgument(std::forward<DBusBasicArgument>(other))
    {
        m_arg = std::move(other.m_arg);
        other.m_argType = ArgType::Invalid;
    }

    DBusBasicArgument& DBusBasicArgument::operator=(const DBusBasicArgument &other)
    {
        if(this != &other)
        {
            DBusArgument::operator=(other);
            initializeArgValue(other);
        }
        return *this;
    }

    DBusBasicArgument& DBusBasicArgument::operator=(DBusBasicArgument &&other)
    {
        if(this != &other)
        {
            DBusArgument::operator=(std::forward<DBusBasicArgument>(other));
            m_arg = std::move(other.m_arg);
            other.m_argType = ArgType::Invalid;
        }
        return *this;
    }

    DBusBasicArgument::~DBusBasicArgument()
    {

    }

    bool DBusBasicArgument::operator==(const DBusBasicArgument &other) const
    {
        bool equal = false;
        if(DBusArgument::operator ==(other))
        {
            //because of special case for comparing strings - have to use strcmp instead of normal comparison
            if(m_argType != ArgType::String)
            {
                equal = m_arg == other.m_arg;
            }
            else
            {
               auto strPtr = static_cast<const char*>(std::get<std::unique_ptr<char[]>>(m_arg).get());
               auto strPtr_Other = static_cast<const char*>(std::get<std::unique_ptr<char[]>>(other.m_arg).get());
               if(strPtr && strPtr_Other)
               {
                    equal = strcmp(strPtr, strPtr_Other) == 0;
               }
            }
        }
        return equal;
    }

    bool DBusBasicArgument::setArgValue(const char *value)
    {
        return setArgValue(const_cast<char*>(value));
    }

    bool DBusBasicArgument::setArgValue(char *value)
    {
        bool argSet = false;
        if(m_argType == ArgType::String)
        {
            if(value)
            {
                std::size_t strSize = strlen(value) + 1;
                std::unique_ptr<char[]> data{new char[strSize]};
                if(data)
                {
                    strcpy(data.get(), value);
                    m_arg = std::move(data);
                    m_argIsInitalized = true;
                    argSet = true;
                }
            }
        }
        return argSet;
    }

    bool DBusBasicArgument::setArgValue(DBusBasicValue value)
    {
        bool argSet = true;
        switch(m_argType)
        {
        case DBusArgument::ArgType::Byte:
            m_arg = value.byt;
            break;
        case DBusArgument::ArgType::Int16:
            m_arg = value.i16;
            break;
        case DBusArgument::ArgType::UInt16:
            m_arg = value.u16;
            break;
        case DBusArgument::ArgType::Int32:
            m_arg = value.i32;
            break;
        case DBusArgument::ArgType::Bool:
            m_arg = value.bool_val;
            break;
        case DBusArgument::ArgType::UInt32:
            m_arg = value.u32;
            break;
        case DBusArgument::ArgType::Int64:
            m_arg = value.i64;
            break;
        case DBusArgument::ArgType::UInt64:
            m_arg = value.u64;
            break;
        case DBusArgument::ArgType::Double:
            m_arg = value.dbl;
            break;
        case DBusArgument::ArgType::String:
            if(value.str)
            {
                std::size_t strSize = strlen(value.str) + 1;
                std::unique_ptr<char[]> data{new char[strSize]};
                strcpy(data.get(), value.str);
                m_arg = std::move(data);
            }
            else
            {
                argSet = false;
            }
            break;
        default:
            argSet = false;
            break;
        }
        m_argIsInitalized = argSet;
        return argSet;
    }

    void* DBusBasicArgument::getArgValuePtr()
    {
        void *retPtr = nullptr;
        if(m_argType != ArgType::Invalid && m_argIsInitalized)
        {
            switch(m_argType)
            {
            case DBusArgument::ArgType::Byte:
                retPtr = &(std::get<uint8_t>(m_arg));
                break;            
            case DBusArgument::ArgType::Int16:
                retPtr = &(std::get<dbus_int16_t>(m_arg));
                break;
            case DBusArgument::ArgType::UInt16:
                retPtr = &(std::get<dbus_uint16_t>(m_arg));
                break;
            case DBusArgument::ArgType::Int32:
                retPtr = &(std::get<dbus_int32_t>(m_arg));
                break;
            case DBusArgument::ArgType::Bool:
            case DBusArgument::ArgType::UInt32:
                retPtr = &(std::get<dbus_uint32_t>(m_arg));
                break;
            case DBusArgument::ArgType::Int64:
                retPtr = &(std::get<dbus_int64_t>(m_arg));
                break;
            case DBusArgument::ArgType::UInt64:
                retPtr = &(std::get<dbus_uint64_t>(m_arg));
                break;
            case DBusArgument::ArgType::Double:
                retPtr = &(std::get<double>(m_arg));
                break;
            case DBusArgument::ArgType::String:                
                retPtr = std::get<std::unique_ptr<char[]>>(m_arg).get();
                break;
            default:
                break;
            }
        }
        return retPtr;
    }

    bool DBusBasicArgument::argIsContainerType() const
    {
        return false;
    }

    void DBusBasicArgument::initializeArgValue(const DBusBasicArgument &arg)
    {
        if(arg.m_argType == m_argType)
        {
            if(arg.m_argIsInitalized)
            {
                const char* dataPtr = nullptr;
                switch(m_argType)
                {
                case DBusArgument::ArgType::Byte:
                    m_arg = std::get<uint8_t>(arg.m_arg);
                    break;
                case DBusArgument::ArgType::Int16:
                    m_arg = std::get<dbus_int16_t>(arg.m_arg);
                    break;
                case DBusArgument::ArgType::UInt16:
                    m_arg = std::get<dbus_uint16_t>(arg.m_arg);
                    break;
                case DBusArgument::ArgType::Int32:
                    m_arg = std::get<dbus_int32_t>(arg.m_arg);
                    break;
                case DBusArgument::ArgType::Bool:
                case DBusArgument::ArgType::UInt32:
                    m_arg = std::get<dbus_uint32_t>(arg.m_arg);
                    break;
                case DBusArgument::ArgType::Int64:
                    m_arg = std::get<dbus_int64_t>(arg.m_arg);
                    break;
                case DBusArgument::ArgType::UInt64:
                    m_arg = std::get<dbus_uint64_t>(arg.m_arg);
                    break;
                case DBusArgument::ArgType::Double:
                    m_arg = std::get<double>(arg.m_arg);
                    break;
                case DBusArgument::ArgType::String:
                    dataPtr = std::get<std::unique_ptr<char[]>>(arg.m_arg).get();
                    if(dataPtr)
                    {
                        std::size_t strSize = strlen(dataPtr) + 1;
                        std::unique_ptr<char[]> data{new char[strSize]};
                        strcpy(data.get(), dataPtr);
                        m_arg = std::move(data);
                    }
                    else
                    {
                        m_argIsInitalized = false;
                    }
                default:
                    break;
                }
            }
        }
    }
}
