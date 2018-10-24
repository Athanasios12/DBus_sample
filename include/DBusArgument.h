#ifndef DBUSARGUMENT_H
#define DBUSARGUMENT_H
#include <dbus/dbus.h>
#include <variant>
#include <cstdint>
#include <string>
#include <optional>

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
                                bool,
                                double,
                                uint8_t,
                                char*,//tried with std::string - sigfaults??
                                DBusArgument*> argValType;

        enum ArgType
        {
            Dictionary          = 0, // also an array but all elements are of dict entry type            
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

        virtual void resetArgument();

        template <typename Val>
        auto setArgVariant(argValType &var, Val value) const
        {
            var = value;
            return var.index();
        }

        virtual ArgType getArgType() const;
        virtual const char* getSignature() const;
        int getArgTypeIndex(ArgType type) const;
        virtual bool argIsContainerType() const = 0;
    protected:
        static std::string getArgTypeSignature(ArgType argType);
        ArgType m_argType;
        std::string m_signature;
    };
}
#endif // DBUSARGUMENT_H
