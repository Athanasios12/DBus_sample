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

            bool addMethod(DBusMethod& method)
            {
                bool methodAdded = false;
                if(std::find(m_methods.begin(), m_methods.end(), method) == std::end(m_methods))
                {
                    method.setObjectName(m_name);
                    method.setInterfaceName(m_interfaceName);
                    m_methods.push_back(method);
                    methodAdded = true;
                }
                return methodAdded;
            }

            bool setMethodArg(const std::string &methodName, std::vector<std::unique_ptr<DBusArgument>> &args)
            {
                bool argSet = false;
                auto method = std::find_if(m_methods.begin(), m_methods.end(),
                             [&methodName](const DBusMethod &method)
                            {
                                return (method.getName() == methodName);
                            });
                if(method != std::end(m_methods))
                {
                    bool allArgsSet = true;
                    for(size_t i = 0; i < args.size(); i++)
                    {
                        if(!method->setArg(args[i], i))
                        {
                            allArgsSet = false;
                            break;
                        }
                    }
                    argSet = allArgsSet;
                }
                return argSet;
            }

            bool operator==(const DBusObject& other) const
            {
                return ((other.m_name == m_name) && (other.m_interfaceName == m_interfaceName));
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
