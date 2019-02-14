
/*
 *
 *     add-server.c: server program, receives message,
 *                   adds numbers in message and 
 *                   gives back result to client
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include <dbus/dbus.h>
#include <dbus/dbus-glib-lowlevel.h>
#include <glib/gprintf.h>
#include <gio/gio.h>
/*
const char *const INTERFACE_NAME = "in.softprayog.dbus_example";
const char *const SERVER_BUS_NAME = "in.softprayog.add_server";
const char *const OBJECT_PATH_NAME = "/in/softprayog/adder";
const char *const METHOD_NAME = "add_numbers";
*/
const char *const INTERFACE_NAME = "in.Radoslaw.Interface";
const char *const SERVER_BUS_NAME = "in.Radoslaw.Server";
const char *const CLIENT_BUS_NAME = "in.Radoslaw.Client";
const char *const SERVER_OBJECT_PATH_NAME = "/in/Radoslaw/adder";
const char *const METHOD_NAME = "add_numbers";


const char *server_introspection_xml =
        DBUS_INTROSPECT_1_0_XML_DOCTYPE_DECL_NODE
        "<node>\n"

        "  <interface name='org.freedesktop.DBus.Introspectable'>\n"
        "    <method name='Introspect'>\n"
        "      <arg name='data' type='s' direction='out' />\n"
        "    </method>\n"
        "  </interface>\n"

        "  <interface name='org.freedesktop.DBus.Properties'>\n"
        "    <method name='Get'>\n"
        "      <arg name='interface' type='s' direction='in' />\n"
        "      <arg name='property'  type='s' direction='in' />\n"
        "      <arg name='value'     type='s' direction='out' />\n"
        "    </method>\n"
        "    <method name='GetAll'>\n"
        "      <arg name='interface'  type='s'     direction='in'/>\n"
        "      <arg name='properties' type='a{sv}' direction='out'/>\n"
        "    </method>\n"
        "  </interface>\n"

        "  <interface name='org.example.TestInterface'>\n"
        "    <property name='Version' type='s' access='read' />\n"
        "    <method name='Ping' >\n"
        "      <arg type='s' direction='out' />\n"
        "    </method>\n"
        "    <method name='Echo'>\n"
        "      <arg name='string' direction='in' type='s'/>\n"
        "      <arg type='s' direction='out' />\n"
        "    </method>\n"
        "    <method name='EmitSignal'>\n"
        "    </method>\n"
        "    <method name='Quit'>\n"
        "    </method>\n"
        "    <signal name='OnEmitSignal'>\n"
        "    </signal>"
        "  </interface>\n"

        "</node>\n";

DBusError dbus_error;
GMainLoop *mainloop;
void print_dbus_error (char *str);
bool isinteger (char *ptr);

DBusHandlerResult server_message_handler(DBusConnection *conn, DBusMessage *message, void *data)
{
    DBusHandlerResult result = DBUS_HANDLER_RESULT_NOT_YET_HANDLED;
    DBusMessage *reply = NULL;
    DBusError err;
    bool quit = false;

    fprintf(stderr, "Got D-Bus request: %s.%s on %s\n",
            dbus_message_get_interface(message),
            dbus_message_get_member(message),
            dbus_message_get_path(message));
    if (dbus_message_is_method_call(message, "org.example.TestInterface", "Ping"))
    {
        fprintf(stderr, "\nMethod ping called by client\n");
        const char *pong = "Pong";

        if (reply = dbus_message_new_method_return(message))
        {
            dbus_message_append_args(reply,
                                 DBUS_TYPE_STRING, &pong,
                                 DBUS_TYPE_INVALID);
        }
    }
    else if (dbus_message_is_method_call(message, "org.example.TestInterface", "Quit"))
    {
        reply = dbus_message_new_method_return(message);
        quit  = true;
    }
    if(reply)
    {
        if(dbus_connection_send(conn, reply, NULL))
        {
            fprintf(stderr, "\nServer sent response\n");
            result = DBUS_HANDLER_RESULT_HANDLED;
        }
        dbus_message_unref (reply);
        if(quit)
        {
            fprintf(stderr, "Server exiting...\n");
            g_main_loop_quit(mainloop);
        }
    }
    return result;
}

void dbusClient()
{
    //client
    DBusConnection *conn;
    int ret;

    dbus_error_init (&dbus_error);

    conn = dbus_bus_get (DBUS_BUS_SYSTEM, &dbus_error);

    if (dbus_error_is_set (&dbus_error))
        print_dbus_error ("dbus_bus_get");

    if (!conn)
        exit (1);
    char input [80];
    sleep(1);
    printf ("Please type two numbers: ");
    while (fgets (input, 78, stdin) != NULL)
    {
        // Get a well known name
        while (1)
        {
            ret = dbus_bus_request_name (conn, CLIENT_BUS_NAME, 0, &dbus_error);
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
        }

        DBusMessage *request;
        sleep(1);
        if ((request = dbus_message_new_method_call (SERVER_BUS_NAME, SERVER_OBJECT_PATH_NAME,
                           INTERFACE_NAME, METHOD_NAME)) == NULL)
        {
            fprintf (stderr, "Error in dbus_message_new_method_call\n");
            exit (1);
        }

        DBusMessageIter iter;
        dbus_message_iter_init_append (request, &iter);
        char *ptr = input;
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

        if (dbus_bus_release_name (conn, CLIENT_BUS_NAME, &dbus_error) == -1) {
             fprintf (stderr, "Error in dbus_bus_release_name\n");
             exit (1);
        }

        printf ("Please type two numbers: ");
    }
    dbus_connection_unref(conn);
    dbus_bus_release_name(conn, CLIENT_BUS_NAME, NULL);
}

void dbusClient2()
{
    //client
    DBusConnection *conn;
    int ret;

    dbus_error_init (&dbus_error);

    conn = dbus_bus_get (DBUS_BUS_SYSTEM, &dbus_error);

    if (dbus_error_is_set (&dbus_error))
        print_dbus_error ("dbus_bus_get");

    if (!conn)
        exit (1);
    char input [80];
    sleep(1);
    printf ("Please type two numbers: ");
    // Get a well known name
    while (1)
    {
        ret = dbus_bus_request_name (conn, CLIENT_BUS_NAME, 0, &dbus_error);
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
    }

    DBusMessage *request;
    if ((request = dbus_message_new_method_call (SERVER_BUS_NAME, SERVER_OBJECT_PATH_NAME,
                       INTERFACE_NAME, METHOD_NAME)) == NULL)
    {
        fprintf (stderr, "Error in dbus_message_new_method_call\n");
        exit (1);
    }

    DBusMessageIter iter;
    dbus_message_iter_init_append (request, &iter);
    const char *ptr = "10 44";
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

    dbus_pending_call_unref(pending_return);

    char *s;
    if (dbus_message_get_args (reply, &dbus_error, DBUS_TYPE_STRING, &s, DBUS_TYPE_INVALID))
    {
        printf ("%s\n", s);
    }
    else
    {
         fprintf (stderr, "Did not get arguments in reply\n");
         exit (1);
    }
    dbus_message_unref (reply);

    if (dbus_bus_release_name (conn, CLIENT_BUS_NAME, &dbus_error) == -1)
    {
         fprintf (stderr, "Error in dbus_bus_release_name\n");
         exit (1);
    }
    dbus_connection_unref(conn);
    dbus_bus_release_name(conn, CLIENT_BUS_NAME, NULL);
}

void dbusServer()
{
    DBusConnection *conn;
    int ret;

    dbus_error_init (&dbus_error);

    conn = dbus_bus_get (DBUS_BUS_SYSTEM, &dbus_error);

    if (dbus_error_is_set (&dbus_error))
        print_dbus_error ("dbus_bus_get");

    if (!conn)
        exit (1);
    //server
    // Get a well known name
    ret = dbus_bus_request_name (conn, SERVER_BUS_NAME, DBUS_NAME_FLAG_DO_NOT_QUEUE, &dbus_error);

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

        if (dbus_message_is_method_call (message, INTERFACE_NAME, METHOD_NAME))
        {
            char *s;
            char *str1 = NULL, *str2 = NULL;
            const char space [4] = " \n\t";
            int i, j;
            bool error = false;

            if (dbus_message_get_args (message, &dbus_error, DBUS_TYPE_STRING, &s, DBUS_TYPE_INVALID))
            {
                printf ("%s", s);
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

                    if (!dbus_connection_send (conn, reply, NULL))
                    {
                        fprintf (stderr, "Error in dbus_connection_send\n");
                        exit (1);
                    }

                    dbus_connection_flush (conn);

                    dbus_message_unref (reply);
                    dbus_connection_unref(conn);
                    dbus_bus_release_name(conn, SERVER_BUS_NAME, NULL);
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


void dbusServer2(DBusConnection *conn)
{
    int ret;

    dbus_error_init (&dbus_error);

    conn = dbus_bus_get (DBUS_BUS_SESSION, &dbus_error);

    if (dbus_error_is_set (&dbus_error))
        print_dbus_error ("dbus_bus_get");

    if (!conn)
        exit (1);
    //server
    // Get a well known name
    DBusObjectPathVTable server_vtable;
    server_vtable.message_function = server_message_handler;
    ret = dbus_bus_request_name(conn, "org.example.TestServer", DBUS_NAME_FLAG_REPLACE_EXISTING , &dbus_error);

    if (dbus_error_is_set (&dbus_error))
        print_dbus_error ("dbus_bus_get");
    if (!dbus_connection_register_object_path(conn, "/org/example/TestObject", &server_vtable, NULL))
    {
        fprintf(stderr, "Failed to request name on bus: %s\n", dbus_error.message);
        exit(1);
    }

    mainloop = g_main_loop_new(NULL, false);
    /* Set up the DBus connection to work in a GLib event loop */
    dbus_connection_setup_with_g_main(conn, NULL);
    /* Start the glib event loop */
    g_main_loop_run(mainloop);
}

void test_Ping(GDBusProxy *proxy)
{
        GVariant *result;
        GError *error = NULL;
        const gchar *str;

        g_printf("Calling Ping()...\n");
        result = g_dbus_proxy_call_sync(proxy,
                                        "Ping",
                                        NULL,
                                        G_DBUS_CALL_FLAGS_NONE,
                                        -1,
                                        NULL,
                                        &error);
        g_assert_no_error(error);
        g_variant_get(result, "(&s)", &str);
        g_printf("The server answered: '%s'\n", str);
        g_variant_unref(result);
}

void test_Quit(GDBusProxy *proxy)
{
        GVariant *result;
        GError *error = NULL;

        g_printf("Calling method Quit()...\n");
        result = g_dbus_proxy_call_sync(proxy,
                                        "Quit",
                                        NULL,
                                        G_DBUS_CALL_FLAGS_NONE,
                                        -1,
                                        NULL,
                                        &error);
        g_assert_no_error(error);
        g_variant_unref(result);
}

void dbusClient3(bool quit = false)
{
    GDBusProxy *proxy;
    GDBusConnection *conn;
    GError *error = NULL;
    const char *version;
    GVariant *variant;

    conn = g_bus_get_sync(G_BUS_TYPE_SESSION, NULL, &error);
    g_assert_no_error(error);

    proxy = g_dbus_proxy_new_sync(conn,
                                  G_DBUS_PROXY_FLAGS_NONE,
                                  NULL,				/* GDBusInterfaceInfo */
                                  "org.example.TestServer",		/* name */
                                  "/org/example/TestObject",	/* object path */
                                  "org.example.TestInterface",	/* interface */
                                  NULL,
                                  &error);
    g_assert_no_error(error);

    /* read the version property of the interface */
//    variant = g_dbus_proxy_get_cached_property(proxy, "Version");
//    g_assert(variant != NULL);
//    g_variant_get(variant, "s", &version);
//    g_variant_unref(variant);
//    printf("Testing server interface v%s\n", version);

    /* Test all server methods */
    test_Ping(proxy);
    sleep(1);
    if(quit)
    {
        test_Quit(proxy);
    }

    g_object_unref(proxy);
    g_object_unref(conn);
}

int main (int argc, char **argv)
{
    pid_t pid = fork();
    if(pid >= 0)
    {
        if(pid == 0)
        {
            //client
            printf("\n-----Started first Client ----\n");
            dbusClient2();
            printf("\n-----First Client Finished successfully-----\n");
            sleep(5);
            printf("\n-----Started second Client ----\n");
            dbusClient2();
            printf("\n-----Second Client Finished successfully-----\n");
            exit(0);
        }
        else
        {
            dbusServer();
            sleep(10);
        }
    }
    dbus_error_free(&dbus_error);
}


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
