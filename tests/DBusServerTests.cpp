#include "gtest/gtest.h"
#include "DBusServer.h"
#include "DBusClient.h"
#include "DBusInterface.h"
#include "DBusArgumentFactory.h"
#include "DBusStruct.h"
#include "DBusMethod.h"
#include "DBusMethodReply.h"
#include "DBusArray.h"
#include "DBusBasicArgument.h"
#include "DBusDictEntry.h"
#include "DBusDictionary.h"
#include "DBusArgumentPack.h"
#include <functional>
#include <thread>
#include <memory>

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

//          DBusMethodReply DBusServerBinding(const std::vector<DBusArgument>& args)
//          {
//              //write server test binding
//          }

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
        using namespace DBUS;
        std::string clientBusName = "in.Radoslaw.Client";
        std::string serverBusName = "in.Radoslaw.Server";
        const std::string methodName{"add_numbers"};
        const std::string objectName{"/in/Radoslaw/adder"};
        const std::string interfaceName{"in.Radoslaw.Interface"};
        //server interface
        DBusInterface::DBusObject object(objectName);
        //just a simple test lambda binding
        std::function<DBusMethodReply(const std::vector<std::unique_ptr<DBusArgument>>&)> printBinding =
                [](const std::vector<std::unique_ptr<DBusArgument>> &args)
        {
            std::cout << "\nAdd numbers called!" << std::endl;
            DBusMethodReply retVal{DBusArgument::ArgType::String};
            std::unique_ptr<DBusArgument> retArg{new DBusBasicArgument{DBusArgument::ArgType::String}};
            static_cast<DBusBasicArgument*>(retArg.get())->setArgValue("Function add_numbers called");
            retVal.setRetArg(retArg);
            return retVal;
        };
        std::vector<DBusArgument::ArgType> bindingArgTypes = {DBusArgument::ArgType::String,
                                                              DBusArgument::ArgType::Byte,
                                                              DBusArgument::ArgType::Array,
                                                              DBusArgument::ArgType::Struct,
                                                              DBusArgument::ArgType::Dictionary,
                                                              DBusArgument::ArgType::Array,
                                                              DBusArgument::ArgType::Array,
                                                              DBusArgument::ArgType::Array};
        DBusMethod method{methodName, printBinding, bindingArgTypes.size(), DBusArgument::ArgType::String};
        method.setBindingArgTypes(bindingArgTypes);
        object.addMethod(method);
        DBusInterface dbusInterface(interfaceName);
        dbusInterface.addObject(object);
        pid_t pid = fork();
        if(pid >= 0)
        {
            if(pid > 0)
            {
                //client
                std::cerr << "In Client" << std::endl;
                DBusClient dbusClient(clientBusName, DBUS_BUS_SYSTEM);
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                bool clientConnected = dbusClient.connect();
                fprintf(stderr, "Client connection %s\n",(clientConnected) ? "success" : "failed");
                DBusArgumentPack methodInputArgs{methodName, objectName, interfaceName};
                //basic arguments
                auto arg = static_cast<DBusBasicArgument*>(methodInputArgs.addNewArgument(DBusArgument::ArgType::Int16));
                arg->setArgValue<dbus_int16_t>(20);
                //change argType and value
                arg->resetArg<const char*>(DBusArgument::ArgType::String, "Hello from Client");
                auto arg1 = static_cast<DBusBasicArgument*>(methodInputArgs.addNewArgument(DBusArgument::ArgType::Byte));
                arg1->setArgValue<uint8_t>(10);
                //array argument
                auto arg2 = static_cast<DBusArray*>(methodInputArgs.addNewArgument(DBusArgument::ArgType::Array));
                arg2->setElementsType(DBusArgument::ArgType::Byte);
                arg2->addArgument<uint8_t>(10);
                arg2->addArgument(static_cast<DBusArgument*>(arg1));
                //struct argument
                auto arg3 = static_cast<DBusStruct*>(methodInputArgs.addNewArgument(DBusArgument::ArgType::Struct));
                arg3->addField(DBusArgument::ArgType::String, "Hello");
                arg3->addArgument(static_cast<DBusArgument*>(arg2));
                //dictionary argument
                auto arg4 = static_cast<DBusDictionary*>(methodInputArgs.addNewArgument(DBusArgument::ArgType::Dictionary));
                arg4->setEntryType(DBusArgument::ArgType::String, DBusArgument::ArgType::Byte);
                arg4->addEntry<const char*, uint8_t>("Entry 0", 86);
                arg4->addEntry<const char*, uint8_t>("Entry 1", 132);
                arg4->addEntry(static_cast<DBusArgument*>(arg), static_cast<DBusArgument*>(arg1));
                //add array of structs
                auto arg5 = static_cast<DBusArray*>(methodInputArgs.addNewArgument(DBusArgument::ArgType::Array));
                arg5->setElementsType(DBusArgument::ArgType::Struct);
                arg5->addArgument(static_cast<DBusArgument*>(arg3));
                //add array of dictionaries
                auto arg6 = static_cast<DBusArray*>(methodInputArgs.addNewArgument(DBusArgument::ArgType::Array));
                arg6->setElementsType(DBusArgument::ArgType::Dictionary);
                arg6->addArgument(static_cast<DBusArgument*>(arg4));
                //add array of arrays
                auto arg7 = static_cast<DBusArray*>(methodInputArgs.addNewArgument(DBusArgument::ArgType::Array));
                arg7->setElementsType(DBusArgument::ArgType::Array);
                arg7->addArgument(static_cast<DBusArgument*>(arg2));
                std::cerr << "Finished argument pack creation" << std::endl;
                //check if all args have been set before method call - add this condition also in call server method, don't send msg if method does not have all args set
                if(methodInputArgs.checkIfAllArgsValid())
                {
                    std::cerr << "Client args valid" << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    DBusMethodReply reply = dbusClient.callServerMethod(serverBusName, methodInputArgs);
                    std::cerr << "\nMethod " << method.getName() << " reply: " << std::endl;
                    std::string retStr{static_cast<char*>(static_cast<DBusBasicArgument*>(reply.getReturn())->getArgValuePtr())};
                    std::cerr << retStr << std::endl;
                    fprintf(stderr, "%s\n",(reply.isValid()) ? "valid" : "invalid");
                }
                //exit(0);
            }
            else
            {
                //server
                DBUS::DBusServer dbusServer(serverBusName, DBUS_BUS_SYSTEM);
                dbusServer.addInterface(dbusInterface);
                dbusServer.connect();
                std::this_thread::sleep_for(std::chrono::milliseconds(50000));
                //EXPECT_EQ(true, dbusServer.checkLastMethodCall(clientBusName, method.getName()));
                exit(0);
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
