#ifndef DBUSARGUMENT_H
#define DBUSARGUMENT_H
#include <dbus/dbus.h>
#include <variant>
#include <cstdint>
#include <string>
#include <optional>
#include <memory>

namespace DBUS
{
    class DBusArgument
    {
    public:
        typedef std::variant<   dbus_uint16_t,
                                dbus_int16_t,
                                dbus_uint32_t,
                                dbus_int32_t,
                                dbus_uint64_t,
                                dbus_int64_t,
                                double,
                                uint8_t,
                                std::unique_ptr<char[]>,
                                DBusArgument*> argValType;

        enum ArgType
        {
            Dictionary          = 0xFF, // also an array but all elements are of dict entry type
            UInt16              = DBUS_TYPE_UINT16,
            UInt32              = DBUS_TYPE_UINT32,
            UInt64              = DBUS_TYPE_UINT64,
            Int16               = DBUS_TYPE_INT16,
            Int32               = DBUS_TYPE_INT32,
            Int64               = DBUS_TYPE_INT64,
            Double              = DBUS_TYPE_DOUBLE,
            Bool                = DBUS_TYPE_BOOLEAN,
            Byte                = DBUS_TYPE_BYTE,
            String              = DBUS_TYPE_STRING,
            Array               = DBUS_TYPE_ARRAY,
            Struct              = DBUS_TYPE_STRUCT,
            Variant             = DBUS_TYPE_VARIANT,
            Dictionary_Entry    = DBUS_TYPE_DICT_ENTRY,
            Invalid             = DBUS_TYPE_INVALID
        };              

        DBusArgument();
        DBusArgument(ArgType argType);
        DBusArgument(const DBusArgument &other);
        DBusArgument(DBusArgument &&other);
        DBusArgument& operator=(const DBusArgument &other);
        DBusArgument& operator=(DBusArgument &&other);
        virtual ~DBusArgument();

        bool operator==(const DBusArgument &other) const;

        virtual void resetArgument();        
        virtual ArgType getArgType() const;
        virtual const char* getSignature() const;
        int getArgTypeIndex(ArgType type) const;
        virtual bool argIsContainerType() const = 0;
        static std::string getArgTypeSignature(ArgType argType);
        bool isArgInitalized() const;
    protected:
        ArgType m_argType;
        bool m_argIsInitalized{false};
        std::string m_signature;
    };
}
#endif // DBUSARGUMENT_H
