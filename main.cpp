#include <iostream>
#include <dbus/dbus-glib.h>
#include <dbus/dbus.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>

const char SERVER_CONNECTION_NAME[] = "in.Radoslaw.Server";
const char CLIENT_CONNECTION_NAME[] = "in.Radoslaw.Client";
const char MSG_OBJECT[] = "/in/Radoslaw/Object";
const char MSG_INTERFACE[] = "in.Radoslaw.Interface";

bool connectToSessionDBus(DBusConnection* &conn, DBusError *error)
{
    bool connected = true;

    dbus_error_init(error);
    conn = dbus_bus_get(DBUS_BUS_SYSTEM, error);
    if(!conn)
    {
        std::cerr << error->name << ": " << error->message << std::endl;
        connected = false;
    }
    return connected;
}

bool aquireDBusService(DBusConnection* &connection, DBusError *error, const char* busName)
{
    bool nameAquired = true;
    auto ret = dbus_bus_request_name(connection, busName, DBUS_NAME_FLAG_REPLACE_EXISTING , error);
    //check if service after call is the primary owner of specified name connection
    //otherwise the name request failed
    if(DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret)
    {
        nameAquired = false;
        if(dbus_error_is_set(error))
        {
            std::cerr << error->name << ": " << error->message << std::endl;
        }
    }
    return nameAquired;
}

bool broadcastToDBus(DBusConnection* connection, const char* msgObject, const char* msgInterface, const char* sigName)
{
    bool signalSent = false;
    DBusMessage* msg;
    DBusMessageIter args;

    // create a signal and check for errors
    msg = dbus_message_new_signal(msgObject, msgInterface, sigName);
    // append arguments onto signal
    dbus_message_iter_init_append(msg, &args);
    if(nullptr != msg)
    {
        char* msgStr = static_cast<char*>(malloc(100));
        while(true)
        {
            std::cout << "Type message to send : " << std::endl;
            fgets(msgStr, 100, stdin);
            printf("\nYour message : %s\n", msgStr);
            msg = dbus_message_new_signal(msgObject, msgInterface, sigName);
            // append arguments onto signal
            dbus_message_iter_init_append(msg, &args);
            if(dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &msgStr))
            {
                // send the message and flush the connection
                if(dbus_connection_send(connection, msg, NULL))
                {
                    // free the message
                    dbus_message_unref(msg);
                }
                else
                {
                    std::cerr << "Out Of Memory!" << std::endl;
                }
            }
            else
            {
                std::cerr << "Out Of Memory!" << std::endl;
            }
            if(strcmp(msgStr, "q") == 0)
            {
                dbus_connection_flush(connection);
                dbus_message_unref(msg);
                signalSent = true;
                break;
            }
            usleep(250000);
        }
    }
    else
    {
        std::cerr << "Msg is NULL" << std::endl;
    }
    //dbus_message_unref(msg);
    return signalSent;
}

bool receiveMsgFromDBus(DBusConnection *connection, DBusError *err, const char* interface, const char* sigName)
{
    bool msgReceived = false;
    char *sigvalue = nullptr;
    DBusMessageIter args;

    // add a rule for which messages we want to see
    std::string matchRule = std::string{"type='signal',interface='"} + std::string{interface} + std::string{"'"};
    dbus_bus_add_match(connection, matchRule.c_str(), err); // see signals from the given interface
    dbus_connection_flush(connection);
    if (dbus_error_is_set(err))
    {
        std::cerr << "Msg is NULL!" << std::endl;
    }
    //loop unitl message is read successfully
    while (true)
    {
        //blocking read of the next available message
        dbus_connection_read_write(connection, 0);
        auto msg = dbus_connection_pop_message(connection);
        // loop again if we haven't read a message
        if (NULL != msg)
        {
            // check if the message is a signal from the correct interface and with the correct name
            if (dbus_message_is_signal(msg, interface, sigName))
            {
                // read the parameters
                if (!dbus_message_iter_init(msg, &args))
                {
                    std::cerr << "Message has no arguments!" << std::endl;
                }
                else if (DBUS_TYPE_STRING != dbus_message_iter_get_arg_type(&args))
                {
                    std::cerr << "Argument is not string!" << std::endl;
                }
                else
                {
                    dbus_message_iter_get_basic(&args, &sigvalue);
                    printf("Got Signal with value %s\n", sigvalue);
                    if(strcmp(sigvalue, "q") == 0)
                    {
                        msgReceived = true;
                        printf("\nStopped communitaction\n");
                        // free the message
                        dbus_message_unref(msg);
                        break;
                    }
                }
            }

        }
        usleep(250000);
    }
    return msgReceived;
}

int main(int argv, char **argc)
{
    DBusError err;
    DBusConnection *connection = nullptr;
    if(argv > 1)
    {
        if(strcmp(argc[1], "Client") == 0)
        {
            //client
            assert(connectToSessionDBus(connection, &err));
            assert(aquireDBusService(connection, &err, CLIENT_CONNECTION_NAME));
            std::thread rxThread(receiveMsgFromDBus, connection, &err, MSG_INTERFACE, "Test");
            assert(broadcastToDBus(connection, MSG_OBJECT, MSG_INTERFACE, "Test"));
            rxThread.join();
            dbus_error_free(&err);
        }
        else if(strcmp(argc[1], "Server") == 0)
        {
            //server
            assert(connectToSessionDBus(connection, &err));
            assert(aquireDBusService(connection, &err, SERVER_CONNECTION_NAME));
            std::thread rxThread(receiveMsgFromDBus, connection, &err, MSG_INTERFACE, "Test");
            //assert(broadcastToDBus(connection, MSG_OBJECT, MSG_INTERFACE, "Test"));
            rxThread.join();
            dbus_error_free(&err);
        }
    }
    return 0;
}

