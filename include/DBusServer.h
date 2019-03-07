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
        DBusServer(const std::string& busName, DBusBusType busType, int timeout = 0);
        ~DBusServer();
        DBusServer& operator=(const DBusServer& other) = delete;
        DBusServer(const DBusServer& other) = delete;
        DBusServer(DBusServer&& other);
        DBusServer& operator=(DBusServer&& other);

        bool connect();
        bool disconnect();

        bool checkLastMethodCall(const std::string& clientBusName, const std::string &methodName) const;

        bool isServerRunning() const;
    private:
        void pollForMsgs();
        bool processMethodCall(DBusMessage *msg);

        std::thread m_rxThread;
        std::pair<std::string, std::string> m_lastMethodCall; // clientBus name and method name
        bool m_listening;
        bool m_runThread;
        int m_readMsgTimeout;
    };
}

#endif // DBUSSERVER_H
