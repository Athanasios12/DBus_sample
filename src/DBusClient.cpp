#include "DBusClient.h"
#include "DBusArgumentFactory.h"
#include "DBusBasicArgument.h"

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

    DBusMethodReply DBusClient::callServerMethod(const std::string &serverBusName,
                                                 const DBusArgumentPack &methodInputArgs)
    {
        DBusMethodReply reply{methodInputArgs.getReturnType()};
        DBusMessage *request = dbus_message_new_method_call(serverBusName.c_str(),
                                                            methodInputArgs.getObjectName().c_str(),
                                                            methodInputArgs.getInterfaceName().c_str(),
                                                            methodInputArgs.getMethodName().c_str());
        if(request)
        {
            DBusMessageIter iter;
            dbus_message_iter_init_append(request, &iter);
            //checks if all method args are set with correct values, otherwise does not proceed will server comm
            if(methodInputArgs.appendArgsToDBusMsg(&iter))
            {
                //append client bus name at the end of the message
                DBusBasicArgument clientNameArg{DBusArgument::ArgType::String};
                clientNameArg.setArgValue(m_busName.c_str());
                DBusInterface::appendArg(&clientNameArg, &iter);
                //send with reply request
                DBusPendingCall *pending_return = nullptr;
                if(dbus_connection_send_with_reply(m_connection, request, &pending_return, 2000))
                {
                    if(pending_return)
                    {
                        dbus_pending_call_block(pending_return);
                        DBusMessage *replyMsg = dbus_pending_call_steal_reply(pending_return);
                        if(replyMsg)
                        {
                            DBusMessageIter replyItr;
                            dbus_message_iter_init(replyMsg, &replyItr);
                            reply.processDBusMsgReply(&replyItr);
                            dbus_message_unref(replyMsg);
                        }
                    }
                }
                dbus_pending_call_unref(pending_return);
            }
        }
        dbus_message_unref(request);
        return reply;
    }

}
