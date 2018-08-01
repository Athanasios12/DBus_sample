#include "DBusClient.h"

namespace DBUS
{
    DBusClient::DBusClient():
        BusConnection()
    {

    }

    DBusClient::DBusClient(const std::string &busName, DBusBusType busType):
        BusConnection(busName, busType)
    {

    }

    DBusClient::~DBusClient()
    {

    }

    DBusClient::DBusClient(DBusClient &&other):
        BusConnection(static_cast<BusConnection&&>(other))
    {

    }

    DBusClient &DBusClient::operator=(DBusClient &&other)
    {
        DBusClient& retVal = static_cast<DBusClient&>(BusConnection::operator=(static_cast<BusConnection&&>(other)));
        return retVal;
    }

    bool DBusClient::connect()
    {
        return BusConnection::connect();
    }

    bool DBusClient::disconnect()
    {
        return BusConnection::disconnect();
    }

    bool DBusClient::processDbusReply(const DBUS::DBusInterface::DBusMethod &method, DBusMessageIter *iterator)
    {
        //placeholder
        char *s;
        if (dbus_message_get_args (reply, &dbus_error, DBUS_TYPE_STRING, &s, DBUS_TYPE_INVALID)) {
            printf ("%s\n", s);
        }
        else
        {
             fprintf (stderr, "Did not get arguments in reply\n");
             exit (1);
        }
        return true;
    }

    DBusInterface::DBusMethodReply DBusClient::callServerMethod(const std::string &serverBusName,
                                                                const std::string &interface,
                                                                const std::string &object,
                                                                DBusInterface::DBusMethod &method)
    {
        DBusInterface::DBusMethodReply reply;
        DBusMessage *request = dbus_message_new_method_call(serverBusName.c_str(), object.c_str(), interface.c_str(), method.m_name.c_str());
        if(request)
        {
            DBusMessageIter iter;
            dbus_message_iter_init_append(request, &iter);
            if(DBusInterface::appendMethodArgs(method, &iter))
            {
                DBusPendingCall *pending_return = dbus_connection_send_with_reply(m_connection, request, &pending_return, -1);
                if(pending_return)
                {
                    dbus_pending_call_block(pending_return);
                    DBusMessage *replyMsg = dbus_pending_call_steal_reply(pending_return);
                    if(replyMsg)
                    {
                        DBusMessageIter replyItr;
                        dbus_message_iter_init(replyMsg, &replyItr);
                        DBusInterface::processDBusReply(method, replyItr);
                        dbus_message_unref(replyMsg);
                    }
                    dbus_pending_call_unref(pending_return);
                }
            }
            dbus_message_unref(request);
        }
    }

}
