#include "gtest/gtest.h"
#include "BusConnection.h"
#include "DBusInterface.h"

namespace
{
    // The fixture for testing class Foo.
    class DBusConnectionTest : public ::testing::Test
    {
        protected:
          // You can remove any or all of the following functions if its body
          // is empty.

          DBusConnectionTest()
          {
            // You can do set-up work for each test here.
          }

          virtual ~DBusConnectionTest()
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

    TEST_F(DBusConnectionTest, defaultCtor)
    {
        DBUS::BusConnection dBusConnection;
        EXPECT_EQ(true, dBusConnection.getBusName().empty());
        EXPECT_EQ(false, dBusConnection.isConnected());
        EXPECT_EQ(true, dBusConnection.getInterfaceList().empty());
        EXPECT_EQ(DBUS_BUS_SYSTEM, dBusConnection.getBusType());
    }

    TEST_F(DBusConnectionTest, ctor)
    {
        DBUS::BusConnection dBusConnection("in.example.bus", DBUS_BUS_SESSION);
        EXPECT_EQ(0, dBusConnection.getBusName().compare("in.example.bus"));
        EXPECT_EQ(false, dBusConnection.isConnected());
        EXPECT_EQ(true, dBusConnection.getInterfaceList().empty());
        EXPECT_EQ(DBUS_BUS_SESSION, dBusConnection.getBusType());
    }

    TEST_F(DBusConnectionTest, moveCtor)
    {
        DBUS::BusConnection dBusConnection("in.example.bus", DBUS_BUS_SESSION);
        DBUS::DBusInterface interface("in.example.interface");
        EXPECT_EQ(true, dBusConnection.addInterface(interface));

        DBUS::BusConnection dBusConnection1(std::move(dBusConnection));

        EXPECT_EQ(true, dBusConnection.getBusName().empty());
        EXPECT_EQ(false, dBusConnection.isConnected());
        EXPECT_EQ(true, dBusConnection.getInterfaceList().empty());
        EXPECT_EQ(DBUS_BUS_SYSTEM, dBusConnection.getBusType());

        EXPECT_EQ(0, dBusConnection1.getBusName().compare("in.example.bus"));
        EXPECT_EQ(false, dBusConnection1.isConnected());
        EXPECT_EQ(false, dBusConnection1.getInterfaceList().empty());
        EXPECT_EQ(0, dBusConnection1.getInterfaceList()[0].getName().compare("in.example.interface"));
        EXPECT_EQ(DBUS_BUS_SESSION, dBusConnection1.getBusType());
    }

    TEST_F(DBusConnectionTest, moveAssignment)
    {
        DBUS::BusConnection dBusConnection("in.example.bus", DBUS_BUS_SESSION);
        DBUS::DBusInterface interface("in.example.interface");
        EXPECT_EQ(true, dBusConnection.addInterface(interface));

        DBUS::BusConnection dBusConnection1("in.example.bus1", DBUS_BUS_SESSION);
        dBusConnection1 = std::move(dBusConnection);

        EXPECT_EQ(true, dBusConnection.getBusName().empty());
        EXPECT_EQ(false, dBusConnection.isConnected());
        EXPECT_EQ(true, dBusConnection.getInterfaceList().empty());
        EXPECT_EQ(DBUS_BUS_SYSTEM, dBusConnection.getBusType());

        EXPECT_EQ(0, dBusConnection1.getBusName().compare("in.example.bus"));
        EXPECT_EQ(false, dBusConnection1.isConnected());
        EXPECT_EQ(false, dBusConnection1.getInterfaceList().empty());
        EXPECT_EQ(0, dBusConnection1.getInterfaceList()[0].getName().compare("in.example.interface"));
        EXPECT_EQ(DBUS_BUS_SESSION, dBusConnection1.getBusType());
    }

    TEST_F(DBusConnectionTest, connect)
    {
        DBUS::BusConnection dBusConnection("in.example.bus", DBUS_BUS_SESSION);
        dBusConnection.connect();
        EXPECT_EQ(true, dBusConnection.isConnected());
        EXPECT_EQ(DBUS_BUS_SESSION, dBusConnection.getBusType());
    }

    TEST_F(DBusConnectionTest, disconnect)
    {
        DBUS::BusConnection dBusConnection("in.example.bus", DBUS_BUS_SESSION);
        dBusConnection.connect();
        EXPECT_EQ(true, dBusConnection.isConnected());
        dBusConnection.disconnect();
        EXPECT_EQ(false, dBusConnection.isConnected());
    }

    TEST_F(DBusConnectionTest, addInterface)
    {
        DBUS::BusConnection dBusConnection("in.example.bus", DBUS_BUS_SESSION);
        DBUS::DBusInterface dbusInterface("in.example.interface");
        dBusConnection.addInterface(dbusInterface);
        auto interfaces = dBusConnection.getInterfaceList();
        EXPECT_EQ(false, interfaces.empty());
        EXPECT_EQ(true, interfaces[0] == dbusInterface);
    }
}
