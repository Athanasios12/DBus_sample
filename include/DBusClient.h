#ifndef DBUSCLIENT_H
#define DBUSCLIENT_H
#include "BusConnection.h"
#include "DBusArgumentPack.h"

namespace DBUS
{
    class DBusClient : public BusConnection
    {
    public:
        DBusClient();
        DBusClient(const std::string& busName, DBusBusType busType);
        ~DBusClient();
        DBusClient& operator=(const DBusClient& other) = delete;
        DBusClient(const DBusClient& other) = delete;
        DBusClient(DBusClient &&other);
        DBusClient& operator=(DBusClient&& other);

        bool connect();
        bool disconnect();

        DBusMethodReply callServerMethod(const std::string &serverBusName,
                                         const DBusArgumentPack &methodInputArgs);

    };
}

#endif // DBUSCLIENT_H
