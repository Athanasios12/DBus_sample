#ifndef DBUSCLIENT_H
#define DBUSCLIENT_H
#include "BusConnection.h"

namespace DBUS
{
    class DBusClient : public BusConnection
    {
    public:
        DBusClient();
        DBusClient(const std::string& busName, DBusBusType busType);
        ~DBusClient();
        DBusClient& operator=(const DBusServer& other) = delete;
        DBusClient(const DBusServer& other) = delete;
        DBusClient(DBusClient &&other);
        DBusClient& operator=(DBusServer&& other);

        bool connect();
        bool disconnect();

        DBusInterface::DBusMethodReply callServerMethod(const std::string &serverBusName,
                                                        const std::string &interface,
                                                        const std::string &object,
                                                        DBusInterface::DBusMethod &method);

    private:

    };
}

#endif // DBUSCLIENT_H
