#ifndef DBUSINTERFACE_H
#define DBUSINTERFACE_H
#include <vector>
#include <string>
#include <dbus/dbus.h>
#include <functional>
#include "DBusMethod.h"
#include "DBusMethodReply.h"
#include "DBusArgument.h"
#include "DBusBasicArgument.h"
#include "DBusContainerArg.h"
#include <optional>

namespace DBUS
{
    class DBusInterface
    {
    public:
        struct DBusObject
        {
            std::string m_name;
            std::string m_interfaceName;
            std::vector<DBusMethod> m_methods;
            DBusObject(const std::string& name):
                m_name(name)
            {

            }

            bool addMethod(DBusMethod&& method)
            {
                bool methodAdded = false;
                if(method.bindingIsSet())
                {
                    if(std::find(m_methods.begin(), m_methods.end(), method) == std::end(m_methods))
                    {
                        method.setObjectName(m_name);
                        method.setInterfaceName(m_interfaceName);
                        m_methods.push_back(std::move(method));
                        methodAdded = true;
                    }
                }
                return methodAdded;
            }

            bool operator==(const DBusObject& other) const
            {
                return ((other.m_name == m_name) && (m_methods == other.m_methods));
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
        std::optional<DBusObject> getObject(const std::string &name) const;

        //static methods
        static bool processDBusContainerArg(DBusContainerArg *containerArg, DBusMessageIter *iterator);
        static bool extractDBusBasicArg(DBusBasicArgument &bArg, DBusMessageIter *argIter);
        static bool extractDBusMessageArgData(DBusArgument *arg, DBusMessageIter *argIter);
        static bool appendArg(DBusArgument *arg, DBusMessageIter *iterator);

        std::vector<DBusObject> m_objects;//make private and instead provide iterators
    private:
        std::string m_name;
    };
}
#endif // DBUSINTERFACE_H
