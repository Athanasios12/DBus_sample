#include "DBusArgument.h"
#include "DBusArgumentFactory.h"

namespace DBUS
{
    // Struct; type code 114 'r' is reserved for use in bindings and implementations
    // to represent the general concept of a struct, and must not appear in signatures used on D-Bus
    static const char* DBUS_STRUCT_SIG = "()";
    // Entry in a dict or map (array of key-value pairs). Type code 101 'e' is reserved for use in bindings
    // and implementations to represent the general concept of a dict or dict-entry, and must not appear in signatures used on D-Bus.
    static const char* DBUS_DICT_ENTRY_SIG = "{}";

    DBusArgument::DBusArgument():
        m_argType{ArgType::Invalid},
        m_signature{DBUS_TYPE_INVALID_AS_STRING}
    {

    }

    DBusArgument::DBusArgument(DBusArgument::ArgType argType):
        m_argType{argType}
    {
        m_signature = getArgTypeSignature(m_argType);
    }

    DBusArgument::DBusArgument(const DBusArgument &other)
    {
        if(this != &other)
        {
            m_argType = other.m_argType;
            m_signature = other.m_signature;
        }
    }

    DBusArgument::DBusArgument(DBusArgument &&other)
    {
        if(this != &other)
        {
            m_argType = other.m_argType;
            m_signature = std::move(other.m_signature);
            other.m_argType = ArgType::Invalid;
        }
    }

    DBusArgument& DBusArgument::operator=(const DBusArgument &other)
    {
        if(this != &other)
        {
            m_argType = other.m_argType;
            m_signature = other.m_signature;
        }
        return *this;
    }

    DBusArgument& DBusArgument::operator=(DBusArgument &&other)
    {
        if(this != &other)
        {
            m_argType = other.m_argType;
            m_signature = std::move(other.m_signature);
            other.m_argType = ArgType::Invalid;
        }
        return *this;
    }

    DBusArgument::~DBusArgument()
    {

    }

    int DBusArgument::getArgTypeIndex(ArgType type) const
    {
        int wrongTypeIndex = -1;
        argValType argTypeVariant;
        auto arg = DBusArgumentFactory::getArgument(Byte);
        switch (type)
        {
        case Byte:
            argTypeVariant = static_cast<uint8_t>(0);
            break;
        case UInt16:
            argTypeVariant = static_cast<dbus_uint16_t>(0);
            break;
        case UInt32:
            argTypeVariant = static_cast<dbus_uint32_t>(0);
            break;
        case UInt64:
            argTypeVariant = static_cast<dbus_uint64_t>(0);
            break;
        case Int16:
            argTypeVariant = static_cast<dbus_int16_t>(0);
            break;
        case Int32:
            argTypeVariant = static_cast<dbus_int32_t>(0);
            break;
        case Int64:
            argTypeVariant = static_cast<dbus_int64_t>(0);
            break;
        case Double:
            argTypeVariant = static_cast<double>(0);
            break;
        case Bool:
            argTypeVariant = true;
            break;
        case String:
            argTypeVariant = std::string{};
            break;
        case Array:
        case Struct:
        case Dictionary_Entry:
        case Dictionary:            
            argTypeVariant = arg.get();
            break;
        default:
            return wrongTypeIndex;
        }
        return argTypeVariant.index();
    }

    DBusArgument::ArgType DBusArgument::getArgType() const
    {
        return m_argType;
    }

    const char *DBusArgument::getSignature() const
    {
        return m_signature.c_str();
    }

    std::string DBusArgument::getArgTypeSignature(ArgType argType)
    {
        std::string signature;
        switch (argType)
        {
        case Byte:
            signature = DBUS_TYPE_BYTE_AS_STRING;
            break;
        case UInt16:
            signature = DBUS_TYPE_UINT16_AS_STRING;
            break;
        case UInt32:
            signature = DBUS_TYPE_UINT32_AS_STRING;
            break;
        case UInt64:
            signature = DBUS_TYPE_UINT64_AS_STRING;
            break;
        case Int16:
            signature = DBUS_TYPE_INT16_AS_STRING;
            break;
        case Int32:
            signature = DBUS_TYPE_INT32_AS_STRING;
            break;
        case Int64:
            signature = DBUS_TYPE_INT64_AS_STRING;
            break;
        case Double:
            signature = DBUS_TYPE_DOUBLE_AS_STRING;
            break;
        case Bool:
            signature = DBUS_TYPE_BOOLEAN_AS_STRING;
            break;
        case String:
            signature = DBUS_TYPE_STRING_AS_STRING;
            break;
        case Array:
        case Dictionary:
            signature = DBUS_TYPE_ARRAY_AS_STRING;
            break;
        case Struct:
            signature = DBUS_STRUCT_SIG;
            break;
        case Dictionary_Entry:
            signature = DBUS_DICT_ENTRY_SIG;
            break;
        default:
            break;
        }
        return signature;
    }

    template <>
    DBusArgument::argValType DBusArgument::getSetArgVariant(const char* value) const
    {
        argValType var = std::string{value};
        return var;
    }
}
