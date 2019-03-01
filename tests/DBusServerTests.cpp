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

using namespace DBUS;
namespace
{
    // Those names are defined in /etc/dbus-1/system.d/in.Radoslaw.Client.conf , in.Radoslaw.Server.conf
    // To use system bus these configuration files are needed to be created at specified directory
//    const std::string clientBusName = "in.Radoslaw.Client";
//    const std::string serverBusName = "in.Radoslaw.Server";
//    const std::string methodName{"add_numbers"};
//    const std::string objectName{"/in/Radoslaw/adder"};
//    const std::string interfaceName{"in.Radoslaw.Interface"};




    // The fixture for testing class Foo.
    class DBusServerTest : public ::testing::Test
    {
    protected:
        // You can remove any or all of the following functions if its body
        // is empty.

        DBusServerTest()
        {
            // You can do set-up work for each test here.
            //basic arguments
            auto arg = static_cast<DBusBasicArgument*>(methodInputArgs.addNewArgument(DBusArgument::ArgType::String));
            arg->setArgValue("Hello from Client");;
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

        struct DBusTestSettings
        {
            std::string clientBusName;
            std::string serverBusName;
            std::string methodName;
            std::string objectName;
            std::string interfaceName;
        };
        DBusArgumentPack methodInputArgs;
        const DBusTestSettings systemBusSettings{ "in.Radoslaw.Client",
                                                  "in.Radoslaw.Server",
                                                  "add_numbers",
                                                  "/in/Radoslaw/adder",
                                                  "in.Radoslaw.Interface"
                                                };

        const std::vector<DBusTestSettings> sessionBusSettings{ {
                                                                "org.example.TestClient",
                                                                "org.example.TestServer",
                                                                "add_numbers",
                                                                "/org/example/TestObject",
                                                                "org.example.TestInterface"
                                                                }
                                                              };
        const std::function<DBusMethodReply(const std::vector<std::unique_ptr<DBusArgument>>&)> printBinding =
                [this](const std::vector<std::unique_ptr<DBusArgument>> &args)
        {
            std::cout << "\nAdd numbers called!" << std::endl;
            std::cout << "Number of method input args : " << args.size() << std::endl;
            size_t argNum = 0;
            for(auto && arg : args)
            {
                EXPECT_NE(nullptr, arg);
                if(arg)
                {
                    std::cout << "Arg Type: " << arg->getArgType() << std::endl;
                    bool equal = DBusArgumentFactory::checkIfArgsEqual(methodInputArgs.getInputArg(argNum), arg.get());
                    fprintf(stdout, "\nArgument transmit %s\n------\n", (equal) ? "success" : "failed");
                    EXPECT_EQ(true, equal);
                }
                else
                {
                    break;
                }
                ++argNum;
            }
            DBusMethodReply retVal{DBusArgument::ArgType::String};
            std::unique_ptr<DBusArgument> retArg{new DBusBasicArgument{DBusArgument::ArgType::String}};
            static_cast<DBusBasicArgument*>(retArg.get())->setArgValue("Function add_numbers called");
            retVal.setRetArg(retArg);

            return retVal;
        };
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
        //server interface        
        std::vector<DBusArgument::ArgType> bindingArgTypes = {DBusArgument::ArgType::String,
                                                              DBusArgument::ArgType::Byte,
                                                              DBusArgument::ArgType::Array,
                                                              DBusArgument::ArgType::Struct,
                                                              DBusArgument::ArgType::Dictionary,
                                                              DBusArgument::ArgType::Array,
                                                              DBusArgument::ArgType::Array,
                                                              DBusArgument::ArgType::Array};

        DBusInterface dbusInterface(systemBusSettings.interfaceName);
        DBusInterface::DBusObject object(systemBusSettings.objectName);
        DBusMethod method{systemBusSettings.methodName, printBinding, bindingArgTypes.size(), DBusArgument::ArgType::String};
        method.setBindingArgTypes(bindingArgTypes);
        object.addMethod(std::move(method));
        dbusInterface.addObject(object);
        pid_t pid = fork();
        if(pid >= 0)
        {
            if(pid == 0)
            {
                //client
                std::cerr << "In Client" << std::endl;
                DBusClient dbusClient(systemBusSettings.clientBusName, DBUS_BUS_SYSTEM);
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                bool clientConnected = dbusClient.connect();
                fprintf(stderr, "Client connection %s\n",(clientConnected) ? "success" : "failed");
                //check if all args have been set before method call - add this condition also in call server method, don't send msg if method does not have all args set
                methodInputArgs.setInterfaceName(systemBusSettings.interfaceName);
                methodInputArgs.setObjectName(systemBusSettings.objectName);
                methodInputArgs.setMethodName(systemBusSettings.methodName);
                methodInputArgs.setMethodReturnType(method.getReturnType());
                if(methodInputArgs.checkIfAllArgsValid())
                {
                    std::cerr << "Client args valid" << std::endl;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    DBusMethodReply reply = dbusClient.callServerMethod(systemBusSettings.serverBusName, methodInputArgs);
                    std::cerr << "\nMethod " << systemBusSettings.methodName << " reply: " << std::endl;
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
                exit(0);
            }
            else
            {
                //server
                DBUS::DBusServer dbusServer(systemBusSettings.serverBusName, DBUS_BUS_SYSTEM, 1000);
                dbusServer.addInterface(dbusInterface);
                dbusServer.connect();
                std::this_thread::sleep_for(std::chrono::milliseconds(5000));
                EXPECT_EQ(true, dbusServer.checkLastMethodCall(systemBusSettings.clientBusName, systemBusSettings.methodName));
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
