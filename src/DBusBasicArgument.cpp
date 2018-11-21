#include "DBusBasicArgument.h"

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
        m_arg = other.m_arg;
    }

    DBusBasicArgument::DBusBasicArgument(DBusBasicArgument &&other):
        DBusArgument(std::forward<DBusBasicArgument>(other))
    {
        m_arg = std::move(other.m_arg);
    }

    DBusBasicArgument& DBusBasicArgument::operator=(const DBusBasicArgument &other)
    {
        if(this != &other)
        {
            DBusArgument::operator=(other);
            m_arg = other.m_arg;
        }
        return *this;
    }

    DBusBasicArgument& DBusBasicArgument::operator=(DBusBasicArgument &&other)
    {
        if(this != &other)
        {
            DBusArgument::operator=(std::forward<DBusBasicArgument>(other));
            m_arg = std::move(other.m_arg);
        }
        return *this;
    }

    DBusBasicArgument::~DBusBasicArgument()
    {

    }

    bool DBusBasicArgument::operator==(const DBusBasicArgument &other) const
    {
        return ((other.m_arg == m_arg) && (other.m_argType == m_argType));
    }

    void* DBusBasicArgument::getArgValuePtr()
    {
        void *retPtr = nullptr;
        if(m_argType != ArgType::Invalid && m_argSet)
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
                retPtr = (void*)const_cast<char*>(std::get<const char*>(m_arg));
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
}
