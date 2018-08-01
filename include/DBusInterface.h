#ifndef DBUSINTERFACE_H
#define DBUSINTERFACE_H
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include  <dbus/dbus.h>

namespace DBUS
{
    class DBusInterface
    {
    public:
        struct DBusArgument
        {
            union Dbus_Type
            {
                dbus_uint16_t   dUint16;
                dbus_int16_t    dInt16;
                dbus_uint32_t   dUint32;
                dbus_int32_t    dInt32;
                dbus_uint64_t   dUint64;
                dbus_int64_t    dInt64;
                double          dDouble;
                uint8_t         dByte;
                dbus_bool_t     dBool;
                char*           dString;
                std::vector<DBusArgument> dContainer; //array, object or dictionary
            };

            Dbus_Type m_argVal;
            int m_argType;
            DBusArgument():
                m_argType(DBUS_TYPE_INVALID)
            {

            }

            bool operator==(const DBusArgument& other) const
            {
                return ((other.m_argType == m_argType) && (other.dUint64 == dUint64));
            }
        };

        struct DBusMethodReply
        {
            uint32_t m_id;
            std::string m_serverName;
            DBusArgument m_return;
            bool m_valid;

            DBusMethodReply():
                m_valid(false)
            {

            }

            bool operator==(const DBusMethodReply& other) const
            {
                return (other.m_id == m_id);
            }


        };

        struct DBusMethod
        {
        public:
            std::string m_name;
            std::string m_objectName;
            std::string m_interfaceName;
            std::vector<DBusArgument> m_args;

            DBusMethod()
            {

            }

            DBusMethod(const std::string& name):
                m_name(name)
            {

            }

            bool operator==(const DBusMethod& other) const
            {
                return (other.m_name == m_name);
            }

            bool argCheck()
            {
                bool valid = true;
                for (auto && arg : m_args)
                {
                    if(DBUS_TYPE_INVALID == arg.m_argType)
                    {
                        valid = false;
                        break;
                    }
                }
                return valid;
            }

            DBusMethodReply callBinding()
            {
                DBusMethodReply reply;
                reply.valid = false;
                //check if all arguments are valid
                if(argCheck())
                {
                    //call binding
                    reply = m_binding(m_args);
                }
                return reply;
            }

        private:
            std::function<DBusMethodReply(std::vector<DBusArgument>)> m_binding;
        };

        struct DBusObject
        {
            std::string m_name;
            std::string m_interfaceName;
            std::vector<DBusMethod> m_methods;
            DBusObject(const std::string& name):
                m_name(name)
            {

            }

            bool addMethod(DBusMethod& method)
            {
                bool methodAdded = false;
                if(std::find(m_methods.begin(), m_methods.end(), method) == std::end(m_methods))
                {
                    method.m_objectName = m_name;
                    m_methods.push_back(method);
                    methodAdded = true;
                }
                return methodAdded;
            }

            bool operator==(const DBusObject& other) const
            {
                return (other.m_name == m_name);
            }
        };

        DBusInterface();
        DBusInterface(const std::string& name);
        ~DBusInterface();

        bool operator==(const DBusInterface& other) const;
        //public methods
        bool addObject(DBusObject &object);
        //getters
        std::string getName() const;
        DBusObject getObject(const std::string &name) const;
        //static methods
        static bool processDBusContainerType(const DBusInterface::DBusArgument &containerArg, DBusMessageIter *iterator) const;
        static bool appendMethodArgs(DBUS::DBusInterface::DBusMethod &method, DBusMessageIter *iterator) const;
        static bool createDBusReply(const DBusInterface::DBusArgument &retArg, DBusMessageIter *iterator) const;
        static bool extractDBusMessageArgData(DBusInterface::DBusMethod &method, DBusMessageIter *argIter) const;
    private:
        std::string m_name;
        std::vector<DBusObject> m_objects;
    };
}
#endif // DBUSINTERFACE_H
