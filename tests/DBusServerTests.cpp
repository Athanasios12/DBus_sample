#include "gtest/gtest.h"
#include "DBusServer.h"
#include "DBusClient.h"
#include "DBusInterface.h"
#include <thread>

namespace
{
    // The fixture for testing class Foo.
    class DBusServerTest : public ::testing::Test
    {
        protected:
          // You can remove any or all of the following functions if its body
          // is empty.

          DBusServerTest()
          {
            // You can do set-up work for each test here.
          }

          virtual ~DBusServerTest()
          {
            // You can do clean-up work that doesn't throw exceptions here.
          }

          // If the constructor and destructor are not enough for setting up
          // and cleaning up each test, you can define the following methods:

          virtual void SetUp()
          {
            // Code here will be called immediately after the constructor (right
            // before each test).


          }

          virtual void TearDown()
          {
            // Code here will be called immediately after each test (right
            // before the destructor).
          }

    };

    TEST_F(DBusServerTest, defaultCtor)
    {
        DBUS::DBusServer dbusServer;
        EXPECT_EQ(true, dbusServer.getBusName().empty());
        EXPECT_EQ(false, dbusServer.isConnected());
        EXPECT_EQ(true, dbusServer.getInterfaceList().empty());
        EXPECT_EQ(DBUS_BUS_SYSTEM, dbusServer.getBusType());
    }

    TEST_F(DBusServerTest, ctor)
    {
        DBUS::DBusServer dbusServer("in.example.bus", DBUS_BUS_SESSION);
        EXPECT_EQ(0, dbusServer.getBusName().compare("in.example.bus"));
        EXPECT_EQ(false, dbusServer.isConnected());
        EXPECT_EQ(true, dbusServer.getInterfaceList().empty());
        EXPECT_EQ(DBUS_BUS_SESSION, dbusServer.getBusType());
    }

    TEST_F(DBusServerTest, moveCtor)
    {
        DBUS::DBusServer dbusServer("in.example.bus", DBUS_BUS_SESSION);
        DBUS::DBusInterface interface("in.example.interface");
        EXPECT_EQ(true, dbusServer.addInterface(interface));

        DBUS::DBusServer dbusServer1(std::move(dbusServer));

        EXPECT_EQ(true, dbusServer.getBusName().empty());
        EXPECT_EQ(false, dbusServer.isConnected());
        EXPECT_EQ(true, dbusServer.getInterfaceList().empty());
        EXPECT_EQ(DBUS_BUS_SYSTEM, dbusServer.getBusType());

        EXPECT_EQ(0, dbusServer1.getBusName().compare("in.example.bus"));
        EXPECT_EQ(false, dbusServer1.isConnected());
        EXPECT_EQ(false, dbusServer1.getInterfaceList().empty());
        EXPECT_EQ(0, dbusServer1.getInterfaceList()[0].getName().compare("in.example.interface"));
        EXPECT_EQ(DBUS_BUS_SESSION, dbusServer1.getBusType());
    }

    TEST_F(DBusServerTest, moveAssignment)
    {
        DBUS::DBusServer dbusServer("in.example.bus", DBUS_BUS_SESSION);
        DBUS::DBusInterface interface("in.example.interface");
        EXPECT_EQ(true, dbusServer.addInterface(interface));

        DBUS::DBusServer dbusServer1("in.example.bus1", DBUS_BUS_SESSION);
        dbusServer1 = std::move(dbusServer);

        EXPECT_EQ(true, dbusServer.getBusName().empty());
        EXPECT_EQ(false, dbusServer.isConnected());
        EXPECT_EQ(true, dbusServer.getInterfaceList().empty());
        EXPECT_EQ(DBUS_BUS_SYSTEM, dbusServer.getBusType());

        EXPECT_EQ(0, dbusServer1.getBusName().compare("in.example.bus"));
        EXPECT_EQ(false, dbusServer1.isConnected());
        EXPECT_EQ(false, dbusServer1.getInterfaceList().empty());
        EXPECT_EQ(0, dbusServer1.getInterfaceList()[0].getName().compare("in.example.interface"));
        EXPECT_EQ(DBUS_BUS_SESSION, dbusServer1.getBusType());
    }

    TEST_F(DBusServerTest, connect)
    {
        DBUS::DBusServer dbusServer("in.example.bus", DBUS_BUS_SESSION);
        dbusServer.connect();
        EXPECT_EQ(true, dbusServer.isConnected());
        EXPECT_EQ(DBUS_BUS_SESSION, dbusServer.getBusType());
    }

    TEST_F(DBusServerTest, disconnect)
    {
        DBUS::DBusServer dbusServer("in.example.bus", DBUS_BUS_SESSION);
        dbusServer.connect();
        EXPECT_EQ(true, dbusServer.isConnected());
        dbusServer.disconnect();
        EXPECT_EQ(false, dbusServer.isConnected());
    }
    const char SERVER_CONNECTION_NAME[] = "in.Radoslaw.Server";
    const char CLIENT_CONNECTION_NAME[] = "in.Radoslaw.Client";
    const char MSG_OBJECT[] = "/in/Radoslaw/Object";
    const char MSG_INTERFACE[] = "in.Radoslaw.Interface";
    TEST_F(DBusServerTest, addInterface)
    {
        DBUS::DBusServer dbusServer("in.example.bus", DBUS_BUS_SESSION);
        DBUS::DBusInterface dbusInterface("in.example.interface");
        dbusServer.addInterface(dbusInterface);
        auto interfaces = dbusServer.getInterfaceList();
        EXPECT_EQ(false, interfaces.empty());
        EXPECT_EQ(true, interfaces[0] == dbusInterface);
    }

    TEST_F(DBusServerTest, receiveMethodCall)
    {
        using namespace DBUS::DBusInterface;
        pid_t pid = fork();
        std::string clientBusName = "in.example.client";
        std::string serverBusName = "in.example.server";
        //server interface
        DBusObject object("in/example/object");
        DBusMethod method("print");
        std::function<DBusMethodReply(std::vector<DBusArgument>)> printBinding= [](std::vector<DBusArgument> args){std::cerr << "\nServer method called \n" << endl};
        method.m_binding = printBinding;
        object.addMethod(method);
        DBUS::DBusInterface dbusInterface("in.example.interface");
        dbusInterface.addObject(object);
        if(pid >= 0)
        {
            if(pid == 0)
            {
                //client
                DBUS::DBusClient dbusClient(clientBusName, DBUS_BUS_SESSION);
                dbusClient.connect();
                dbusClient.addInterface(interface);
                DBUS::DBusInterface::DBusMethodReply reply = dbusClient.callServerMethod(serverBusName, interface, object, method);
                std::cerr << "\nMethod " << method.m_name << " call " << reply.m_id << std::endl;
                exit(0);
            }
            else
            {
                //server
                DBUS::DBusServer dbusServer(serverBusName, DBUS_BUS_SESSION);
                dbusServer.connect();
                dbusServer.addInterface(interface);
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                EXPECT_EQ(true, dbusServer.checkLastMethodCall(clientBusName, method));
            }
        }
    }

    TEST_F(DBusServerTest, receiveBroadcastSignal)
    {
        DBUS::DBusServer dbusServer("in.example.bus", DBUS_BUS_SESSION);
        dbusServer.connect();
        EXPECT_EQ(true, dbusServer.isConnected());
        dbusServer.disconnect();
        EXPECT_EQ(false, dbusServer.isConnected());
    }

    TEST_F(DBusServerTest, broadcastMsg)
    {
        DBUS::DBusServer dbusServer("in.example.bus", DBUS_BUS_SESSION);
        dbusServer.connect();
        EXPECT_EQ(true, dbusServer.isConnected());
        dbusServer.disconnect();
        EXPECT_EQ(false, dbusServer.isConnected());
    }
}
