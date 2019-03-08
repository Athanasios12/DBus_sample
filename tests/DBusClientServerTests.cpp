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
    struct DBusTestSettings
    {
        std::string clientBusName;
        std::string serverBusName;
        std::string methodName;
        std::string objectName;
        std::string interfaceName;
    };
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
    // The fixture for testing class Foo.
    class DBusClientServerTest : public ::testing::Test
    {
    public:
        static void SetUpTestSuite() //googletest stup function override
        {
            //Setup input arguments pack
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

            //setup server connection
            dbusSystemBusServer = DBUS::DBusServer(systemBusSettings.serverBusName, DBUS_BUS_SYSTEM);
        }

        static DBusArgumentPack methodInputArgs;
        static DBUS::DBusServer dbusSystemBusServer;
    protected:

        DBusClientServerTest()
        {

        }

        virtual ~DBusClientServerTest()
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

        const std::string methodReturn{"Function add_numbers called"};
        //Server method binding
        const std::function<DBusMethodReply(const std::vector<std::unique_ptr<DBusArgument>>&)> printBinding =
                [this](const std::vector<std::unique_ptr<DBusArgument>> &args)
        {
            size_t argNum = 0;
            DBusContainerArg *cArg = nullptr;
            DBusBasicArgument *bArg = nullptr;
            for(auto && arg : args)
            {
                EXPECT_NE(nullptr, arg);
                if(arg)
                {
                    if(arg->argIsContainerType())
                    {
                        cArg = static_cast<DBusContainerArg*>(arg.get());
                    }
                    else
                    {
                        bArg = static_cast<DBusBasicArgument*>(arg.get());
                    }
                    bool equal = DBusArgumentFactory::checkIfArgsEqual(methodInputArgs.getInputArg(argNum), arg.get());
                    EXPECT_TRUE(equal);
                }
                else
                {
                    break;
                }
                ++argNum;
            }
            DBusMethodReply retVal{DBusArgument::ArgType::String};
            std::unique_ptr<DBusArgument> retArg{new DBusBasicArgument{DBusArgument::ArgType::String}};
            static_cast<DBusBasicArgument*>(retArg.get())->setArgValue(methodReturn.c_str());
            retVal.setRetArg(retArg);
            return retVal;
        };
    };

    DBusArgumentPack DBusClientServerTest::methodInputArgs;
    DBUS::DBusServer DBusClientServerTest::dbusSystemBusServer;

    TEST_F(DBusClientServerTest, defaultCtor)
    {
        DBUS::DBusServer dbusServer;
        EXPECT_EQ(true, dbusServer.getBusName().empty());
        EXPECT_EQ(false, dbusServer.isConnected());
        EXPECT_EQ(true, dbusServer.getInterfaceList().empty());
        EXPECT_EQ(DBUS_BUS_SYSTEM, dbusServer.getBusType());
    }

    TEST_F(DBusClientServerTest, ctor)
    {
        DBUS::DBusServer dbusServer("in.example.bus", DBUS_BUS_SESSION);
        EXPECT_EQ(0, dbusServer.getBusName().compare("in.example.bus"));
        EXPECT_EQ(false, dbusServer.isConnected());
        EXPECT_EQ(true, dbusServer.getInterfaceList().empty());
        EXPECT_EQ(DBUS_BUS_SESSION, dbusServer.getBusType());
    }

    TEST_F(DBusClientServerTest, moveCtor)
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

    TEST_F(DBusClientServerTest, moveAssignment)
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

    TEST_F(DBusClientServerTest, connect)
    {
        DBUS::DBusServer dbusServer("in.example.bus", DBUS_BUS_SESSION);
        dbusServer.connect();
        EXPECT_EQ(true, dbusServer.isConnected());
        EXPECT_EQ(DBUS_BUS_SESSION, dbusServer.getBusType());
    }

    TEST_F(DBusClientServerTest, disconnect)
    {
        DBUS::DBusServer dbusServer("in.example.bus", DBUS_BUS_SESSION);
        dbusServer.connect();
        EXPECT_EQ(true, dbusServer.isConnected());
        dbusServer.disconnect();
        EXPECT_EQ(false, dbusServer.isConnected());
    }

    TEST_F(DBusClientServerTest, addInterface)
    {
        DBUS::DBusServer dbusServer("in.example.bus", DBUS_BUS_SESSION);
        DBUS::DBusInterface dbusInterface("in.example.interface");
        dbusServer.addInterface(dbusInterface);
        auto interfaces = dbusServer.getInterfaceList();
        EXPECT_EQ(false, interfaces.empty());
        EXPECT_EQ(true, interfaces[0] == dbusInterface);
    }

    TEST_F(DBusClientServerTest, receiveMethodCall)
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
            if(pid > 0)
            {
                //client
                DBusClient dbusClient(systemBusSettings.clientBusName, DBUS_BUS_SYSTEM);
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                dbusClient.connect();
                //check if all args have been set before method call - add this condition also in call server method, don't send msg if method does not have all args set
                methodInputArgs.setInterfaceName(systemBusSettings.interfaceName);
                methodInputArgs.setObjectName(systemBusSettings.objectName);
                methodInputArgs.setMethodName(systemBusSettings.methodName);
                methodInputArgs.setMethodReturnType(method.getReturnType());
                if(methodInputArgs.checkIfAllArgsValid())
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    DBusMethodReply reply = dbusClient.callServerMethod(systemBusSettings.serverBusName, methodInputArgs);
                    EXPECT_TRUE(reply.isValid());
                    auto retArg = static_cast<DBusBasicArgument*>(reply.getReturn());
                    EXPECT_NE(nullptr, retArg);
                    if(retArg)
                    {
                        auto retPtr = static_cast<const char*>(retArg->getArgValuePtr());
                        if(retPtr)
                        {
                            std::string retStr{retPtr};
                            EXPECT_EQ(methodReturn, retStr);
                        }
                    }
                }                
            }
            else
            {
                //server
                dbusSystemBusServer.addInterface(dbusInterface);
                dbusSystemBusServer.connect();
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                EXPECT_EQ(true, dbusSystemBusServer.checkLastMethodCall(systemBusSettings.clientBusName, systemBusSettings.methodName));
                exit(0);
            }
        }
    }

    TEST_F(DBusClientServerTest, receiveBroadcastSignal)
    {
        DBUS::DBusServer dbusServer("in.example.bus", DBUS_BUS_SESSION);
        dbusServer.connect();
        EXPECT_EQ(true, dbusServer.isConnected());
        dbusServer.disconnect();
        EXPECT_EQ(false, dbusServer.isConnected());
    }

    TEST_F(DBusClientServerTest, broadcastMsg)
    {
        DBUS::DBusServer dbusServer("in.example.bus", DBUS_BUS_SESSION);
        dbusServer.connect();
        EXPECT_EQ(true, dbusServer.isConnected());
        dbusServer.disconnect();
        EXPECT_EQ(false, dbusServer.isConnected());
    }
}
