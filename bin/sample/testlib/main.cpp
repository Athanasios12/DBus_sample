#include "DBusBasicArgument.h"
#include "DBusServer.h"
#include <vector>

using namespace DBUS;

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

//const std::function<DBusMethodReply(const std::vector<std::unique_ptr<DBusArgument>>&)> printBinding =
//        [](const std::vector<std::unique_ptr<DBusArgument>> &args)
//{
//    std::cout << "\nAdd numbers called!" << std::endl;
//    std::cout << "Number of method input args : " << args.size() << std::endl;
//    for(auto && arg : args)
//    {
//        if(arg)
//        {
//            std::cout << "Arg Type: " << arg->getArgType() << std::endl;
//        }
//    }
//    DBusMethodReply retVal{DBusArgument::ArgType::String};
//    std::unique_ptr<DBusArgument> retArg{new DBusBasicArgument{DBusArgument::ArgType::String}};
//    static_cast<DBusBasicArgument*>(retArg.get())->setArgValue("Function add_numbers called");
//    retVal.setRetArg(retArg);
//    return retVal;
//};

//void myClient()
//{
//    DBusArgumentPack methodInputArgs{sessionBusSettings[0].methodName, sessionBusSettings[0].objectName, sessionBusSettings[0].interfaceName};
//    auto arg = static_cast<DBusBasicArgument*>(methodInputArgs.addNewArgument(DBusArgument::ArgType::String));
//    arg->setArgValue("10 20");

//    DBusClient dbusClient(sessionBusSettings[0].clientBusName, DBUS_BUS_SESSION);
//    bool clientConnected = dbusClient.connect();
//    fprintf(stderr, "\nClient connection %s\n",(clientConnected) ? "success" : "failed");
//    //check if all args have been set before method call - add this condition also in call server method, don't send msg if method does not have all args set
//    if(methodInputArgs.checkIfAllArgsValid())
//    {
//        std::cerr << "Client args valid" << std::endl;
//        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//        DBusMethodReply reply = dbusClient.callServerMethod(sessionBusSettings[0].serverBusName, methodInputArgs);
//        std::cerr << "\nMethod " << sessionBusSettings[0].methodName << " reply: " << std::endl;
//        auto retArg = static_cast<DBusBasicArgument*>(reply.getReturn());
//        if(retArg)
//        {
//            auto retPtr = *static_cast<const char**>(retArg->getArgValuePtr());
//            if(retPtr)
//            {
//                std::string retStr{retPtr};
//                std::cerr << retStr << std::endl;
//            }
//        }
//        fprintf(stderr, "%s\n",(reply.isValid()) ? "valid" : "invalid");
//    }
//}

//void myServer(DBUS::DBusServer &dbusServer)
//{
//    DBusInterface::DBusObject object(sessionBusSettings[0].objectName);
//    std::vector<DBusArgument::ArgType> bindingArgTypes = {DBusArgument::ArgType::String};
//    DBusMethod method{sessionBusSettings[0].methodName, printBinding, bindingArgTypes.size(), DBusArgument::ArgType::String};
//    method.setBindingArgTypes(bindingArgTypes);
//    object.addMethod(std::move(method));
//    DBusInterface dbusInterface(sessionBusSettings[0].interfaceName);
//    dbusInterface.addObject(object);

//    dbusServer.addInterface(dbusInterface);
//    dbusServer.connect();
//}

//int main(int argv, char **argc)
//{
//    pid_t pid = fork();
//    if(pid >= 0)
//    {
//        if(pid == 0)
//        {
//            //client
//            printf("\n-----Started Client ----\n");
//            sleep(1);
//            myClient();
//            printf("\n-----Client Finished successfully-----\n");
//            exit(0);
//        }
//        else
//        {
//            printf("\nStarted server:\n");
//            DBUS::DBusServer dbusServer(sessionBusSettings[0].serverBusName, DBUS_BUS_SESSION);
//            myServer(dbusServer);
//            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
//            printf("\nServer terminated\n");
//        }
//    }
//    return 0;
//}
int main()
{
    DBUS::DBusBasicArgument arg;
    DBUS::DBusServer dbusServer(sessionBusSettings[0].serverBusName, DBUS_BUS_SESSION);
    return 0;
}

