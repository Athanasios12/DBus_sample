#ifndef DBUSSERVER_H
#define DBUSSERVER_H
#include "BusConnection.h"
#include <thread>
#include <utility>

namespace DBUS
{
    class DBusServer : public BusConnection
    {
    public:
        DBusServer();
        DBusServer(const std::string& busName, DBusBusType busType);
        ~DBusServer();
        DBusServer& operator=(const DBusServer& other) = delete;
        DBusServer(const DBusServer& other) = delete;
        DBusServer(DBusServer&& other);
        DBusServer& operator=(DBusServer&& other);

        bool connect();
        bool disconnect();

        bool checkLastMethodCall(const std::string& clientBusName, const DBusInterface::DBusMethod& method) const;
    private:
        void pollForMsgs();
        void processMethodCall(DBusMessage *msg);

        std::thread m_rxThread;
        std::pair<std::string, DBusInterface::DBusMethod> m_lastMethodCall;
        bool m_listening;
    };
}

#endif // DBUSSERVER_H
