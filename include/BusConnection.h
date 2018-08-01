#ifndef BusConnection_H
#define BusConnection_H
#include <dbus/dbus.h>
#include <string>
#include <vector>
#include <DBusInterface.h>

namespace DBUS
{
    class BusConnection
    {
    public:
        BusConnection();
        BusConnection(const std::string& busName, DBusBusType busType);
        virtual ~BusConnection();
        BusConnection& operator=(const BusConnection& other) = delete;
        BusConnection(const BusConnection& other) = delete;
        BusConnection(BusConnection&& other);
        BusConnection& operator=(BusConnection&& other);

        virtual bool connect();
        virtual bool disconnect();
        bool addInterface(const DBusInterface& interface);

        std::string getBusName() const;
        DBusBusType getBusType() const;
        std::vector<DBusInterface> getInterfaceList() const;
        bool isConnected() const;
    private:
        std::string m_busName;
        DBusBusType m_busType;
        std::vector<DBusInterface> m_interfaceList;
        DBusConnection *m_connection;
        bool m_connected;
    };
}
#endif // BusConnection_H
