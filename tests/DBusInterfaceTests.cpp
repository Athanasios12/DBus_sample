#include "gtest/gtest.h"
#include <dbus/dbus.h>
#include "DBusInterface.h"
#include "DBusArray.h"
#include "DBusDictionary.h"
#include "DBusStruct.h"

using namespace DBUS;
namespace
{
    const std::string clientBusName{"in.Radoslaw.Client"};
    const std::string serverBusName{"in.Radoslaw.Server"};
    const std::string methodName{"add_numbers"};
    const std::string objectName{"/in/Radoslaw/adder"};
    const std::string interfaceName{"in.Radoslaw.Interface"};

    // The fixture for testing class Foo.
    class DBusInterfaceTest : public ::testing::Test
    {
        protected:
          // You can remove any or all of the following functions if its body
          // is empty.

          DBusInterfaceTest()
          {
            // You can do set-up work for each test here.
          }

          virtual ~DBusInterfaceTest()
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


    // apend args to message - appendArg
    TEST_F(DBusInterfaceTest, appendArg_ArgNotInitialized)
    {
        DBusInterface interface{interfaceName};
        DBusMessage *msg = dbus_message_new_method_call(serverBusName.c_str(),
                                                        objectName.c_str(),
                                                        interfaceName.c_str(),
                                                        methodName.c_str());
        DBusMessageIter msgItr;
        dbus_message_iter_init_append(msg, &msgItr);
        DBusBasicArgument arg{DBusArgument::ArgType::Bool};
        EXPECT_EQ(false, interface.appendArg(&arg, &msgItr));
    }

    TEST_F(DBusInterfaceTest, appendArg_argIsNull)
    {
        DBusInterface interface{interfaceName};
        DBusMessage *msg = dbus_message_new_method_call(serverBusName.c_str(),
                                                        objectName.c_str(),
                                                        interfaceName.c_str(),
                                                        methodName.c_str());
        DBusMessageIter msgItr;
        dbus_message_iter_init_append(msg, &msgItr);
        EXPECT_EQ(false, interface.appendArg(nullptr, &msgItr));
    }

    TEST_F(DBusInterfaceTest, appendArg_iteratorIsNull)
    {
        DBusInterface interface{interfaceName};
        DBusMessage *msg = dbus_message_new_method_call(serverBusName.c_str(),
                                                        objectName.c_str(),
                                                        interfaceName.c_str(),
                                                        methodName.c_str());
        DBusMessageIter msgItr;
        dbus_message_iter_init_append(msg, &msgItr);
        DBusBasicArgument arg{DBusArgument::ArgType::Bool};
        arg.setArgValue<dbus_bool_t>(true);
        EXPECT_EQ(false, interface.appendArg(&arg, nullptr));
    }

    TEST_F(DBusInterfaceTest, appendArg_2ArgsBoolString)
    {
        DBusInterface interface{interfaceName};
        DBusMessage *msg = dbus_message_new_method_call(serverBusName.c_str(),
                                                        objectName.c_str(),
                                                        interfaceName.c_str(),
                                                        methodName.c_str());
        DBusMessageIter msgItr;
        dbus_message_iter_init_append(msg, &msgItr);
        DBusBasicArgument boolArg{DBusArgument::ArgType::Bool};
        boolArg.setArgValue<dbus_bool_t>(true);
        DBusBasicArgument stringArg{DBusArgument::ArgType::String};
        stringArg.setArgValue("String");
        EXPECT_EQ(true, interface.appendArg(&boolArg, &msgItr));
        EXPECT_EQ(true, interface.appendArg(&stringArg, &msgItr));
    }

    TEST_F(DBusInterfaceTest, appendArg_dictionary)
    {
        DBusInterface interface{interfaceName};
        DBusMessage *msg = dbus_message_new_method_call(serverBusName.c_str(),
                                                        objectName.c_str(),
                                                        interfaceName.c_str(),
                                                        methodName.c_str());
        DBusMessageIter msgItr;
        dbus_message_iter_init_append(msg, &msgItr);
        DBusDictionary dictArg{DBusArgument::ArgType::String, DBusArgument::ArgType::Int32};
        dictArg.addEntry("String", 100);
        EXPECT_EQ(true, interface.appendArg(&dictArg, &msgItr));
    }

    // extractDBusBasicArg
    TEST_F(DBusInterfaceTest, extractDBusBasicArg_InvalidArgType)
    {
        DBusInterface interface{interfaceName};
        DBusMessage *msg = dbus_message_new_method_call(serverBusName.c_str(),
                                                        objectName.c_str(),
                                                        interfaceName.c_str(),
                                                        methodName.c_str());
        DBusMessageIter msgItr;
        dbus_message_iter_init(msg, &msgItr);
        DBusBasicArgument arg;
        EXPECT_EQ(false, interface.extractDBusBasicArg(arg, &msgItr));
    }

    TEST_F(DBusInterfaceTest, extractDBusBasicArg_Success)
    {
        DBusInterface interface{interfaceName};
        DBusMessage *msg = dbus_message_new_method_call(serverBusName.c_str(),
                                                        objectName.c_str(),
                                                        interfaceName.c_str(),
                                                        methodName.c_str());
        DBusMessageIter msgInItr;
        dbus_message_iter_init_append(msg, &msgInItr);
        DBusBasicArgument inArg{DBusArgument::ArgType::Int32};
        dbus_int32_t val = 100;
        inArg.setArgValue(val);
        EXPECT_EQ(true, interface.appendArg(&inArg, &msgInItr));
        //msg appended now extract it
        DBusMessageIter msgOutItr;
        dbus_message_iter_init(msg, &msgOutItr);
        DBusBasicArgument outArg{DBusArgument::ArgType::Int32};
        EXPECT_EQ(true, interface.extractDBusBasicArg(outArg, &msgOutItr));
        EXPECT_EQ(*static_cast<dbus_int32_t*>(inArg.getArgValuePtr()), *static_cast<dbus_int32_t*>(outArg.getArgValuePtr()));
    }

    // processDBusContainerArg
    TEST_F(DBusInterfaceTest, processDBusContainerArg_wrongArrayElementType)
    {
        DBusInterface interface{interfaceName};
        DBusMessage *msg = dbus_message_new_method_call(serverBusName.c_str(),
                                                        objectName.c_str(),
                                                        interfaceName.c_str(),
                                                        methodName.c_str());
        DBusMessageIter msgInItr;
        dbus_message_iter_init_append(msg, &msgInItr);
        DBusArray arrayArg{DBusArgument::ArgType::String};
        arrayArg.addArgument("String");
        EXPECT_EQ(true, interface.appendArg(&arrayArg, &msgInItr));
        //msg appended now extract it
        DBusMessageIter msgOutItr;
        dbus_message_iter_init(msg, &msgOutItr);
        DBusArray arrayOutArg{DBusArgument::ArgType::Int32};
        EXPECT_EQ(false, interface.processDBusContainerArg(&arrayOutArg, &msgOutItr));
        EXPECT_EQ(true, arrayArg != arrayOutArg);

    }

    TEST_F(DBusInterfaceTest, processDBusContainerArg_wrongDictionaryEntryType)
    {
        DBusInterface interface{interfaceName};
        DBusMessage *msg = dbus_message_new_method_call(serverBusName.c_str(),
                                                        objectName.c_str(),
                                                        interfaceName.c_str(),
                                                        methodName.c_str());
        DBusMessageIter msgInItr;
        dbus_message_iter_init_append(msg, &msgInItr);
        DBusDictionary dictArg{DBusArgument::ArgType::String, DBusArgument::ArgType::Int32};
        dictArg.addEntry("String", 100);
        EXPECT_EQ(true, interface.appendArg(&dictArg, &msgInItr));
        //msg appended now extract it
        DBusMessageIter msgOutItr;
        dbus_message_iter_init(msg, &msgOutItr);
        DBusDictionary dictOutArg{DBusArgument::ArgType::Double, DBusArgument::ArgType::Int32};
        EXPECT_EQ(false, interface.processDBusContainerArg(&dictOutArg, &msgOutItr));
        EXPECT_EQ(true, dictArg != dictOutArg);
    }

    TEST_F(DBusInterfaceTest, processDBusContainerArg_Success_ArrayArg)
    {
        DBusInterface interface{interfaceName};
        DBusMessage *msg = dbus_message_new_method_call(serverBusName.c_str(),
                                                        objectName.c_str(),
                                                        interfaceName.c_str(),
                                                        methodName.c_str());
        DBusMessageIter msgInItr;
        dbus_message_iter_init_append(msg, &msgInItr);
        DBusArray arrayArg{DBusArgument::ArgType::String};
        arrayArg.addArgument("String");
        EXPECT_EQ(true, interface.appendArg(&arrayArg, &msgInItr));
        //msg appended now extract it
        DBusMessageIter msgOutItr;
        dbus_message_iter_init(msg, &msgOutItr);
        DBusArray arrayOutArg{DBusArgument::ArgType::String};
        EXPECT_EQ(true, interface.processDBusContainerArg(&arrayOutArg, &msgOutItr));
        EXPECT_EQ(true, arrayArg == arrayOutArg);
    }

    TEST_F(DBusInterfaceTest, processDBusContainerArg_Success_DictionaryArg)
    {
        DBusInterface interface{interfaceName};
        DBusMessage *msg = dbus_message_new_method_call(serverBusName.c_str(),
                                                        objectName.c_str(),
                                                        interfaceName.c_str(),
                                                        methodName.c_str());
        DBusMessageIter msgInItr;
        dbus_message_iter_init_append(msg, &msgInItr);
        DBusDictionary dictArg{DBusArgument::ArgType::String, DBusArgument::ArgType::Int32};
        dictArg.addEntry("String", 100);
        EXPECT_EQ(true, interface.appendArg(&dictArg, &msgInItr));
        //msg appended now extract it
        DBusMessageIter msgOutItr;
        dbus_message_iter_init(msg, &msgOutItr);
        DBusDictionary dictOutArg{DBusArgument::ArgType::String, DBusArgument::ArgType::Int32};
        EXPECT_EQ(true, interface.processDBusContainerArg(&dictOutArg, &msgOutItr));
        EXPECT_EQ(true, dictArg == dictOutArg);
    }

    TEST_F(DBusInterfaceTest, processDBusContainerArg_Success_StructArg)
    {
        DBusInterface interface{interfaceName};
        DBusMessage *msg = dbus_message_new_method_call(serverBusName.c_str(),
                                                        objectName.c_str(),
                                                        interfaceName.c_str(),
                                                        methodName.c_str());
        DBusMessageIter msgInItr;
        dbus_message_iter_init_append(msg, &msgInItr);
        DBusStruct structArg;
        structArg.addField(DBusArgument::ArgType::String, "String");
        structArg.addField(DBusArgument::ArgType::Bool, static_cast<dbus_bool_t>(true));
        EXPECT_EQ(true, interface.appendArg(&structArg, &msgInItr));
        //msg appended now extract it
        DBusMessageIter msgOutItr;
        dbus_message_iter_init(msg, &msgOutItr);
        DBusStruct structOutArg;
        EXPECT_EQ(true, interface.processDBusContainerArg(&structOutArg, &msgOutItr));
        EXPECT_EQ(true, structOutArg == structArg);
    }

    // extractDBusMessageArgData
    TEST_F(DBusInterfaceTest, extractDBusMessageArgData_Success_argIsAContainer)
    {
        DBusInterface interface{interfaceName};
        DBusMessage *msg = dbus_message_new_method_call(serverBusName.c_str(),
                                                        objectName.c_str(),
                                                        interfaceName.c_str(),
                                                        methodName.c_str());
        DBusMessageIter msgInItr;
        dbus_message_iter_init_append(msg, &msgInItr);
        DBusStruct structArg;
        structArg.addField(DBusArgument::ArgType::String, "String");
        EXPECT_EQ(true, interface.appendArg(&structArg, &msgInItr));
        //msg appended now extract it
        DBusMessageIter msgOutItr;
        dbus_message_iter_init(msg, &msgOutItr);
        DBusStruct structOutArg;
        EXPECT_EQ(true, interface.extractDBusMessageArgData(&structOutArg, &msgOutItr));
        EXPECT_EQ(true, structOutArg == structArg);
    }

    TEST_F(DBusInterfaceTest, extractDBusMessageArgData_Success_argIsBasicType)
    {
        DBusInterface interface{interfaceName};
        DBusMessage *msg = dbus_message_new_method_call(serverBusName.c_str(),
                                                        objectName.c_str(),
                                                        interfaceName.c_str(),
                                                        methodName.c_str());
        DBusMessageIter msgInItr;
        dbus_message_iter_init_append(msg, &msgInItr);
        DBusBasicArgument stringArg{DBusArgument::ArgType::String};
        stringArg.setArgValue("String");
        EXPECT_EQ(true, interface.appendArg(&stringArg, &msgInItr));
        //msg appended now extract it
        DBusMessageIter msgOutItr;
        dbus_message_iter_init(msg, &msgOutItr);
        DBusBasicArgument stringOutArg{DBusArgument::ArgType::String};
        EXPECT_EQ(true, interface.extractDBusMessageArgData(&stringOutArg, &msgOutItr));
        EXPECT_EQ(true, stringOutArg == stringArg);
    }

    TEST_F(DBusInterfaceTest, copyCtor)
    {

    }

    TEST_F(DBusInterfaceTest, moveCtor)
    {

    }

}
