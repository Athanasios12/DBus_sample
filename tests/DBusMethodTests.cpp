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
    const std::string clientBusName = "in.Radoslaw.Client";
    const std::string serverBusName = "in.Radoslaw.Server";
    const std::string methodName{"add_numbers"};
    const std::string objectName{"/in/Radoslaw/adder"};
    const std::string interfaceName{"in.Radoslaw.Interface"};

    std::function<DBusMethodReply(const std::vector<std::unique_ptr<DBusArgument>>&)> printBinding =
            [](const std::vector<std::unique_ptr<DBusArgument>> &args)
    {
        //check
        std::cout << "\nAdd numbers called!" << std::endl;
        std::cout << "Number of method input args : " << args.size() << std::endl;
        for(auto && arg : args)
        {
            std::cout << "Arg Type: " << arg->getArgType() << std::endl;

        }
        DBusMethodReply retVal{DBusArgument::ArgType::String};
        std::unique_ptr<DBusArgument> retArg{new DBusBasicArgument{DBusArgument::ArgType::String}};
        static_cast<DBusBasicArgument*>(retArg.get())->setArgValue("Method return");
        retVal.setRetArg(retArg);
        return retVal;
    };

    std::function<DBusMethodReply(const std::vector<std::unique_ptr<DBusArgument>>&)> stringEchoBinding =
            [](const std::vector<std::unique_ptr<DBusArgument>> &args)
    {
        DBusMethodReply retVal{DBusArgument::ArgType::String};
        //chck if only one arg put and if type is string
        if(args.size() == 1)
        {
            if(args[0]->getArgType() == retVal.getReturnType())
            {
                //check if arg is initalized
                if(args[0]->isArgInitlized())
                {
                    auto strArg = static_cast<DBusBasicArgument*>(args[0].get());
                    std::unique_ptr<DBusArgument> retArg{new DBusBasicArgument{DBusArgument::ArgType::String}};
                    static_cast<DBusBasicArgument*>(retArg.get())->setArgValue(static_cast<char*>(strArg->getArgValuePtr()));
                    retVal.setRetArg(retArg);
                }
            }
        }
        return retVal;
    };

    // The fixture for testing class Foo.
    class DBusMethodTest : public ::testing::Test
    {
        protected:
          // You can remove any or all of the following functions if its body
          // is empty.

          DBusMethodTest()
          {
            // You can do set-up work for each test here.
          }

          virtual ~DBusMethodTest()
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

    TEST_F(DBusMethodTest, defaultCtor)
    {
        DBusMethod dbusMethod{methodName};
        EXPECT_EQ(false, dbusMethod.bindingIsSet());
        EXPECT_EQ(0u, dbusMethod.getNumOfArgs());
        EXPECT_EQ(methodName, dbusMethod.getName());
        EXPECT_EQ(true, dbusMethod.getObjectName().empty());
        EXPECT_EQ(true, dbusMethod.getInterfaceName().empty());
        EXPECT_EQ(DBusArgument::ArgType::Invalid, dbusMethod.getReturnType());
    }

    TEST_F(DBusMethodTest, ctor)
    {
        std::vector<DBusArgument::ArgType> bindingArgTypes = {DBusArgument::ArgType::String};
        DBusArgument::ArgType methodReturnType = DBusArgument::ArgType::String;
        DBusMethod dbusMethod{methodName, printBinding, bindingArgTypes.size(), methodReturnType};
        EXPECT_EQ(true, dbusMethod.bindingIsSet());
        EXPECT_EQ(1u, dbusMethod.getNumOfArgs());
        EXPECT_EQ(methodName, dbusMethod.getName());
        EXPECT_EQ(true, dbusMethod.getObjectName().empty());
        EXPECT_EQ(true, dbusMethod.getInterfaceName().empty());
        EXPECT_EQ(methodReturnType, dbusMethod.getReturnType());
    }

    TEST_F(DBusMethodTest, setArg_bindingIsNotSet)
    {
        DBusMethod dbusMethod{methodName};
        EXPECT_EQ(false, dbusMethod.bindingIsSet());
        EXPECT_EQ(0u, dbusMethod.getNumOfArgs());
        DBusBasicArgument arg{DBusArgument::ArgType::Int32};
        EXPECT_EQ(true, arg.setArgValue(static_cast<dbus_int32_t>(100)));

        EXPECT_EQ(false, dbusMethod.setArg(&arg, 0));
    }

    TEST_F(DBusMethodTest, setArg_argSizeIsZero)
    {
        DBusArgument::ArgType methodReturnType = DBusArgument::ArgType::String;
        DBusMethod dbusMethod{methodName, printBinding, 0u, methodReturnType};
        EXPECT_EQ(true, dbusMethod.bindingIsSet());
        EXPECT_EQ(0u, dbusMethod.getNumOfArgs());
        DBusBasicArgument arg{DBusArgument::ArgType::Int32};
        EXPECT_EQ(true, arg.setArgValue(static_cast<dbus_int32_t>(100)));

        EXPECT_EQ(false, dbusMethod.setArg(&arg, 0));
    }


    TEST_F(DBusMethodTest, setArg_wrongArgType)
    {
        std::vector<DBusArgument::ArgType> bindingArgTypes = {DBusArgument::ArgType::String};
        DBusArgument::ArgType methodReturnType = DBusArgument::ArgType::String;
        DBusMethod dbusMethod{methodName, printBinding, bindingArgTypes.size(), methodReturnType};
        EXPECT_EQ(true, dbusMethod.bindingIsSet());
        EXPECT_EQ(1u, dbusMethod.getNumOfArgs());
        DBusBasicArgument arg{DBusArgument::ArgType::Int32};
        EXPECT_EQ(true, arg.setArgValue(static_cast<dbus_int32_t>(100)));

        EXPECT_EQ(false, dbusMethod.setArg(&arg, 0));
    }

    TEST_F(DBusMethodTest, setArg_argIsNotInitialized)
    {
        std::vector<DBusArgument::ArgType> bindingArgTypes = {DBusArgument::ArgType::String};
        DBusArgument::ArgType methodReturnType = DBusArgument::ArgType::String;
        DBusMethod dbusMethod{methodName, printBinding, bindingArgTypes.size(), methodReturnType};
        dbusMethod.setBindingArgTypes(bindingArgTypes);
        EXPECT_EQ(true, dbusMethod.bindingIsSet());
        EXPECT_EQ(1u, dbusMethod.getNumOfArgs());
        DBusBasicArgument arg{DBusArgument::ArgType::String};

        EXPECT_EQ(false, dbusMethod.setArg(&arg, 0));
    }

    TEST_F(DBusMethodTest, setArg_success)
    {
        std::vector<DBusArgument::ArgType> bindingArgTypes = {DBusArgument::ArgType::String};
        DBusArgument::ArgType methodReturnType = DBusArgument::ArgType::String;
        DBusMethod dbusMethod{methodName, stringEchoBinding, bindingArgTypes.size(), methodReturnType};
        dbusMethod.setBindingArgTypes(bindingArgTypes);
        EXPECT_EQ(true, dbusMethod.bindingIsSet());
        EXPECT_EQ(1u, dbusMethod.getNumOfArgs());
        DBusBasicArgument arg{DBusArgument::ArgType::String};
        EXPECT_EQ(true, arg.setArgValue("String"));

        EXPECT_EQ(true, dbusMethod.setArg(&arg, 0));
        auto reply = dbusMethod.callBinding();
        auto retArg = static_cast<DBusBasicArgument*>(reply.getReturn());
        EXPECT_NE(nullptr, retArg);
        EXPECT_EQ(true, retArg->getArgType() == DBusArgument::ArgType::String);
        EXPECT_EQ(true, strcmp(static_cast<char*>(retArg->getArgValuePtr()), static_cast<char*>(arg.getArgValuePtr())) == 0);
    }

    TEST_F(DBusMethodTest, setBindingArgTypes_bindingNotSet)
    {
        DBusMethod dbusMethod{methodName};

        EXPECT_EQ(false, dbusMethod.setBindingArgTypes({DBusArgument::ArgType::String}));
        EXPECT_EQ(false,dbusMethod.methodArgTypesSet());
    }

    TEST_F(DBusMethodTest, setBindingArgTypes_bindingArgTypesSizeDoesNotMatchArgNumber)
    {
        DBusMethod dbusMethod{methodName, stringEchoBinding, 4, DBusArgument::ArgType::String};

        EXPECT_EQ(false, dbusMethod.setBindingArgTypes({DBusArgument::ArgType::String}));
        EXPECT_EQ(false,dbusMethod.methodArgTypesSet());
    }

    TEST_F(DBusMethodTest, setBindingArgTypes_Success)
    {
        DBusMethod dbusMethod{methodName, stringEchoBinding, 1, DBusArgument::ArgType::String};

        EXPECT_EQ(true, dbusMethod.setBindingArgTypes({DBusArgument::ArgType::String}));
        EXPECT_EQ(true, dbusMethod.methodArgTypesSet());
    }

    TEST_F(DBusMethodTest, extractMsgInputArguments_allArgNotExtracted)
    {

    }

    TEST_F(DBusMethodTest, extractMsgInputArguments_Success)
    {

    }

    TEST_F(DBusMethodTest, callBinding_AllArgsAreNotSet)
    {

    }

    TEST_F(DBusMethodTest, callBinding_ReplyInvalid)
    {

    }

    TEST_F(DBusMethodTest, callBinding_validReply)
    {

    }

    TEST_F(DBusMethodTest, copyCtor)
    {

    }

    TEST_F(DBusMethodTest, moveCtor)
    {

    }
}
