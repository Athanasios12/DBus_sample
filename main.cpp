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
#include "DBusClient.h"
#include "DBusServer.h"
#include "DBusArgumentPack.h"

using namespace DBUS;

const char SERVER_CONNECTION_NAME[] = "in.Radoslaw.Server";
const char CLIENT_CONNECTION_NAME[] = "in.Radoslaw.Client";
const char MSG_OBJECT[] = "/in/Radoslaw/Object";
const char MSG_INTERFACE[] = "in.Radoslaw.Interface";

struct DBusTestSettings
{
    std::string clientBusName;
    std::string serverBusName;
    std::string methodName;
    std::string objectName;
    std::string interfaceName;
};
const std::vector<DBusTestSettings> sessionBusSettings{ {"org.example.TestClient2",
                                                        "org.example.TestServer",
                                                        "add_numbers",
                                                        "/org/example/TestObject",
                                                        "org.example.TestInterface"}
                                                      };

const std::function<DBusMethodReply(const std::vector<std::unique_ptr<DBusArgument>>&)> printBinding =
        [](const std::vector<std::unique_ptr<DBusArgument>> &args)
{
    std::cout << "\nAdd numbers called!" << std::endl;
    std::cout << "Number of method input args : " << args.size() << std::endl;
    for(auto && arg : args)
    {
        if(arg)
        {
            std::cout << "Arg Type: " << arg->getArgType() << std::endl;
        }
    }
    DBusMethodReply retVal{DBusArgument::ArgType::String};
    std::unique_ptr<DBusArgument> retArg{new DBusBasicArgument{DBusArgument::ArgType::String}};
    static_cast<DBusBasicArgument*>(retArg.get())->setArgValue("Function add_numbers called");
    retVal.setRetArg(retArg);
    return retVal;
};

DBusError dbus_error;
bool isinteger (char *ptr)
{

    if (*ptr == '+' || *ptr == '-')
        ptr++;

    while (*ptr) {
        if (!isdigit ((int) *ptr++))
            return false;
    }

    return true;
}

void print_dbus_error (char *str)
{
    fprintf (stderr, "%s: %s\n", str, dbus_error.message);
    dbus_error_free (&dbus_error);
}

void dbusServer3()
{
    DBusConnection *conn;
    int ret;

    dbus_error_init (&dbus_error);

    conn = dbus_bus_get (DBUS_BUS_SESSION, &dbus_error);

    if (dbus_error_is_set (&dbus_error))
        print_dbus_error ("dbus_bus_get");

    if (!conn)
        exit (1);
    //server
    // Get a well known name
    ret = dbus_bus_request_name (conn, "org.example.TestServer", DBUS_NAME_FLAG_DO_NOT_QUEUE, &dbus_error);

    if (dbus_error_is_set (&dbus_error))
        print_dbus_error ("dbus_bus_get");

    if (ret != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER)
    {
        fprintf (stderr, "Dbus: not primary owner, ret = %d\n", ret);
        exit (1);
    }
    while (1)
    {
        // Block for msg from client
        if (!dbus_connection_read_write_dispatch (conn, -1))
        {
            fprintf (stderr, "Not connected now.\n");
            exit (1);
        }
        sleep(1);
        DBusMessage *message;

        if ((message = dbus_connection_pop_message (conn)) == NULL)
        {
            fprintf (stderr, "Did not get message\n");
            continue;
        }
        else
        {
            printf("\nServer received message\n");
        }

        if (dbus_message_is_method_call (message, "org.example.TestInterface", "add_numbers"))
        {
            printf("\nServer method called\n");
            char *s;
            char *str1 = NULL, *str2 = NULL;
            const char space [4] = " \n\t";
            int i, j;
            bool error = false;

            if (dbus_message_get_args (message, &dbus_error, DBUS_TYPE_STRING, &s, DBUS_TYPE_INVALID))
            {
                printf ("\nMethod called with args : %s\n", s);
                // Validate received message
                str1 = strtok (s, space);
                if (str1)
                    str2 = strtok (NULL, space);

                if (isinteger (str1))
                    i = atoi (str1);
                else
                    error = true;
                if (isinteger (str2))
                    j = atoi (str2);
                else
                    error = true;
                if (!error)
                {
                    // send reply
                    DBusMessage *reply;
                    char answer [40];

                    sprintf (answer, "Sum is %d", i + j);
                    if ((reply = dbus_message_new_method_return (message)) == NULL)
                    {
                        fprintf (stderr, "Error in dbus_message_new_method_return\n");
                        exit (1);
                    }

                    DBusMessageIter iter;
                    dbus_message_iter_init_append (reply, &iter);
                    char *ptr = answer;
                    if (!dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &ptr))
                    {
                        fprintf (stderr, "Error in dbus_message_iter_append_basic\n");
                        exit (1);
                    }
                    printf("\nSending reply\n");
                    if (!dbus_connection_send (conn, reply, NULL))
                    {
                        fprintf (stderr, "Error in dbus_connection_send\n");
                        exit (1);
                    }

                    dbus_connection_flush (conn);

                    dbus_message_unref (reply);
                    dbus_connection_unref(conn);
                    dbus_bus_release_name(conn, "org.example.TestServer", NULL);
                    break;
                }
                else // There was an error
                {
                    DBusMessage *dbus_error_msg;
                    char error_msg [] = "Error in input";
                    if ((dbus_error_msg = dbus_message_new_error (message, DBUS_ERROR_FAILED, error_msg)) == NULL)
                    {
                         fprintf (stderr, "Error in dbus_message_new_error\n");
                         exit (1);
                    }

                    if (!dbus_connection_send (conn, dbus_error_msg, NULL))
                    {
                        fprintf (stderr, "Error in dbus_connection_send\n");
                        exit (1);
                    }

                    dbus_connection_flush (conn);

                    dbus_message_unref (dbus_error_msg);
                }
            }
            else
            {
                print_dbus_error ("Error getting message");
            }
        }
    }
}

void dbusClient4()
{
    //client
    DBusConnection *conn;
    int ret;

    dbus_error_init (&dbus_error);

    conn = dbus_bus_get (DBUS_BUS_SESSION, &dbus_error);

    if (dbus_error_is_set (&dbus_error))
        print_dbus_error ("dbus_bus_get");

    if (!conn)
        exit (1);
    char input [80];
    //sleep(1);
    printf ("Please type two numbers: ");
    while (fgets (input, 78, stdin) != NULL)
    {
        // Get a well known name
        while (1)
        {
            ret = dbus_bus_request_name (conn, "org.example.TestClient", DBUS_NAME_FLAG_DO_NOT_QUEUE , &dbus_error);
            if (ret == DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER)
               break;

            if (ret == DBUS_REQUEST_NAME_REPLY_IN_QUEUE)
            {
               fprintf (stderr, "Waiting for the bus ... \n");
               sleep (1);
               continue;
            }
            if (dbus_error_is_set (&dbus_error))
               print_dbus_error ("dbus_bus_get");
            printf("\nDidn't get dbus name\n");
        }

        DBusMessage *request;
        sleep(1);
        if ((request = dbus_message_new_method_call ("org.example.TestServer", "/org/example/TestObject",
                           "org.example.TestInterface", "add_numbers")) == NULL)
        {
            fprintf (stderr, "Error in dbus_message_new_method_call\n");
            exit (1);
        }

        DBusMessageIter iter;
        dbus_message_iter_init_append (request, &iter);
        char *ptr = input;
        printf("\nClient method call input args : %s\n", ptr);
        if (!dbus_message_iter_append_basic (&iter, DBUS_TYPE_STRING, &ptr))
        {
            fprintf (stderr, "Error in dbus_message_iter_append_basic\n");
            exit (1);
        }
        DBusPendingCall *pending_return;
        if (!dbus_connection_send_with_reply (conn, request, &pending_return, -1))
        {
            fprintf (stderr, "Error in dbus_connection_send_with_reply\n");
            exit (1);
        }

        if (pending_return == NULL)
        {
            fprintf (stderr, "pending return is NULL");
            exit (1);
        }
        dbus_connection_flush (conn);

        dbus_message_unref (request);

        dbus_pending_call_block (pending_return);
        DBusMessage *reply;
        if ((reply = dbus_pending_call_steal_reply (pending_return)) == NULL) {
            fprintf (stderr, "Error in dbus_pending_call_steal_reply");
            exit (1);
        }

        dbus_pending_call_unref	(pending_return);

        char *s;
        if (dbus_message_get_args (reply, &dbus_error, DBUS_TYPE_STRING, &s, DBUS_TYPE_INVALID))
        {
            printf ("%s\n", s);
            break;
        }
        else
        {
             fprintf (stderr, "Did not get arguments in reply\n");
             exit (1);
        }
        dbus_message_unref (reply);
        printf("\nReleasing client name\n");
        if (dbus_bus_release_name (conn, "test.method.caller", &dbus_error) == -1) {
             fprintf (stderr, "Error in dbus_bus_release_name\n");
             exit (1);
        }

        printf ("Please type two numbers: ");
    }
    dbus_connection_unref(conn);
}

void myClient()
{
    DBusArgumentPack methodInputArgs{sessionBusSettings[0].methodName, sessionBusSettings[0].objectName, sessionBusSettings[0].interfaceName};
    auto arg = static_cast<DBusBasicArgument*>(methodInputArgs.addNewArgument(DBusArgument::ArgType::Byte));
    arg->setArgValue<uint8_t>(10);

    DBusClient dbusClient(sessionBusSettings[0].clientBusName, DBUS_BUS_SESSION);
    bool clientConnected = dbusClient.connect();
    fprintf(stderr, "\nClient connection %s\n",(clientConnected) ? "success" : "failed");
    //check if all args have been set before method call - add this condition also in call server method, don't send msg if method does not have all args set
    if(methodInputArgs.checkIfAllArgsValid())
    {
        std::cerr << "Client args valid" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        DBusMethodReply reply = dbusClient.callServerMethod(sessionBusSettings[0].serverBusName, methodInputArgs);
        std::cerr << "\nMethod " << sessionBusSettings[0].methodName << " reply: " << std::endl;
        auto retArg = static_cast<DBusBasicArgument*>(reply.getReturn());
        if(retArg)
        {
            auto retPtr = *static_cast<const char**>(retArg->getArgValuePtr());
            if(retPtr)
            {
                std::string retStr{retPtr};
                std::cerr << retStr << std::endl;
            }
        }
        fprintf(stderr, "%s\n",(reply.isValid()) ? "valid" : "invalid");
    }
}

void myServer(DBUS::DBusServer &dbusServer)
{
    DBusInterface::DBusObject object(sessionBusSettings[0].objectName);
    std::vector<DBusArgument::ArgType> bindingArgTypes = {DBusArgument::ArgType::Byte};
    DBusMethod method{sessionBusSettings[0].methodName, printBinding, bindingArgTypes.size(), DBusArgument::ArgType::String};
    method.setBindingArgTypes(bindingArgTypes);
    object.addMethod(std::move(method));
    DBusInterface dbusInterface(sessionBusSettings[0].interfaceName);
    dbusInterface.addObject(object);

    dbusServer.addInterface(dbusInterface);
    dbusServer.connect();
}

int main(int argv, char **argc)
{
    pid_t pid = fork();
    if(pid >= 0)
    {
        if(pid > 0)
        {
            //client
            printf("\n-----Started first Client ----\n");
            sleep(1);
            myClient();
            printf("\n-----First Client Finished successfully-----\n");
            exit(0);
        }
        else
        {
            printf("\nStarted server:\n");
            DBUS::DBusServer dbusServer(sessionBusSettings[0].serverBusName, DBUS_BUS_SESSION);
            myServer(dbusServer);
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            printf("\nEnded server:\n");
        }
    }
    return 0;
}

