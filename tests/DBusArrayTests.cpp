#include "gtest/gtest.h"
#include "DBusBasicArgument.h"
#include "DBusArray.h"
#include "DBusStruct.h"
#include <utility>
#include <memory>

using namespace DBUS;

namespace
{
    // The fixture for testing class Foo.
    class DBusArrayTest : public ::testing::Test
    {
    protected:
          // You can remove any or all of the following functions if its body
          // is empty.

          DBusArrayTest()
          {
            // You can do set-up work for each test here.
          }

          virtual ~DBusArrayTest()
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

    TEST_F(DBusArrayTest, defaultCtor)
    {
        DBusArray array;
        EXPECT_EQ(0u, array.getSize());
        EXPECT_EQ(DBusArgument::ArgType::Array, array.getArgType());
        EXPECT_EQ(DBusArgument::ArgType::Invalid, array.getElemType());
        EXPECT_EQ(DBUS_TYPE_ARRAY_AS_STRING, std::string{array.getSignature()});
        EXPECT_EQ(nullptr, array.getContainerSignature());
    }

    TEST_F(DBusArrayTest, ctor)
    {
        DBusArray array{DBusArgument::ArgType::String};
        EXPECT_EQ(0u, array.getSize());
        EXPECT_EQ(DBusArgument::ArgType::Array, array.getArgType());
        EXPECT_EQ(DBusArgument::ArgType::String, array.getElemType());
        EXPECT_EQ(std::string{DBUS_TYPE_ARRAY_AS_STRING} + std::string{DBUS_TYPE_STRING_AS_STRING}, std::string{array.getSignature()});
        EXPECT_EQ(DBUS_TYPE_STRING_AS_STRING, std::string{array.getContainerSignature()});
    }

    TEST_F(DBusArrayTest, copyCtor)
    {
        DBusArray array{DBusArgument::ArgType::String};
        DBusBasicArgument strArg{DBusArgument::ArgType::String};
        EXPECT_EQ(true, array.addArgument(static_cast<DBusArgument*>(&strArg)));
        DBusArray arrayCopy{array};
        //original
        EXPECT_EQ(1u, array.getSize());
        EXPECT_EQ(DBusArgument::ArgType::Array, array.getArgType());
        EXPECT_EQ(DBusArgument::ArgType::String, array.getElemType());
        EXPECT_EQ(std::string{DBUS_TYPE_ARRAY_AS_STRING} + std::string{DBUS_TYPE_STRING_AS_STRING}, std::string{array.getSignature()});
        EXPECT_EQ(DBUS_TYPE_STRING_AS_STRING, std::string{array.getContainerSignature()});
        //copy
        EXPECT_EQ(array.getSize(), arrayCopy.getSize());
        EXPECT_EQ(array.getArgType(), arrayCopy.getArgType());
        EXPECT_EQ(array.getElemType(), arrayCopy.getElemType());
        EXPECT_EQ(true, strcmp(array.getSignature(), arrayCopy.getSignature()) == 0);
        EXPECT_EQ(true, strcmp(array.getContainerSignature(), arrayCopy.getContainerSignature()) == 0);
    }

    TEST_F(DBusArrayTest, moveCtor)
    {
        DBusArray array{DBusArgument::ArgType::String};
        DBusBasicArgument strArg{DBusArgument::ArgType::String};
        array.addArgument(&strArg);
        DBusArray arrayMove{std::move(array)};
        //move
        EXPECT_EQ(1u, arrayMove.getSize());
        EXPECT_EQ(DBusArgument::ArgType::Array, arrayMove.getArgType());
        EXPECT_EQ(DBusArgument::ArgType::String, arrayMove.getElemType());
        EXPECT_EQ(std::string{DBUS_TYPE_ARRAY_AS_STRING} + std::string{DBUS_TYPE_STRING_AS_STRING}, std::string{arrayMove.getSignature()});
        EXPECT_EQ(DBUS_TYPE_STRING_AS_STRING, arrayMove.getContainerSignature());
        //original
        EXPECT_EQ(0u, array.getSize());
        EXPECT_EQ(DBusArgument::ArgType::Array, array.getArgType());
        EXPECT_EQ(DBusArgument::ArgType::Invalid, array.getElemType());
        EXPECT_EQ(DBUS_TYPE_ARRAY_AS_STRING, std::string{array.getSignature()});
        EXPECT_EQ(nullptr, array.getContainerSignature());
    }

    TEST_F(DBusArrayTest, addArgument_notInitialized)
    {
        //added arg not initialized arg
        DBusBasicArgument notInitArg{};
        DBusArray array{DBusArgument::ArgType::String};
        EXPECT_EQ(false, array.addArgument(&notInitArg));
        EXPECT_EQ(0u, array.getSize());
        EXPECT_EQ(DBusArgument::ArgType::Array, array.getArgType());
        EXPECT_EQ(DBusArgument::ArgType::String, array.getElemType());
        EXPECT_EQ(std::string{DBUS_TYPE_ARRAY_AS_STRING} + std::string{DBUS_TYPE_STRING_AS_STRING}, std::string{array.getSignature()});
        EXPECT_EQ(DBUS_TYPE_STRING_AS_STRING, std::string{array.getContainerSignature()});
    }

    TEST_F(DBusArrayTest, addArgument_wrongType)
    {
        //added arg of invalid type
        DBusBasicArgument wrongTypeArg{DBusArgument::ArgType::Byte};
        DBusArray array{DBusArgument::ArgType::String};
        EXPECT_EQ(false, array.addArgument(&wrongTypeArg));
        EXPECT_EQ(0u, array.getSize());
        EXPECT_EQ(DBusArgument::ArgType::Array, array.getArgType());
        EXPECT_EQ(DBusArgument::ArgType::String, array.getElemType());
        EXPECT_EQ(std::string{DBUS_TYPE_ARRAY_AS_STRING} + std::string{DBUS_TYPE_STRING_AS_STRING}, std::string{array.getSignature()});
        EXPECT_EQ(DBUS_TYPE_STRING_AS_STRING, std::string{array.getContainerSignature()});
    }

    TEST_F(DBusArrayTest, addArgument_basicArg)
    {
        //array of basic arg type args - > string, int, etc.
        DBusBasicArgument strArg{DBusArgument::ArgType::String};
        strArg.setArgValue("Elem 0");
        DBusArray array{DBusArgument::ArgType::String};
        EXPECT_EQ(true, array.addArgument(&strArg));
        EXPECT_EQ(true, array.addArgument("Elem 1"));
        EXPECT_EQ(2u, array.getSize());
        EXPECT_EQ(DBusArgument::ArgType::Array, array.getArgType());
        EXPECT_EQ(DBusArgument::ArgType::String, array.getElemType());
        EXPECT_EQ(std::string{DBUS_TYPE_ARRAY_AS_STRING} + std::string{DBUS_TYPE_STRING_AS_STRING}, std::string{array.getSignature()});
        EXPECT_EQ(DBUS_TYPE_STRING_AS_STRING, std::string{array.getContainerSignature()});
    }

    TEST_F(DBusArrayTest, addArgument_arrayArg)
    {
        //array of arrays
        DBusBasicArgument strArg{DBusArgument::ArgType::String};
        strArg.setArgValue("Elem 0");
        DBusArray subArray{DBusArgument::ArgType::String};
        subArray.addArgument(&strArg);
        subArray.addArgument("Elem 1");
        DBusArray array{DBusArgument::ArgType::Array};
        array.addArgument(&array);
        EXPECT_EQ(1u, array.getSize());
        EXPECT_EQ(DBusArgument::ArgType::Array, array.getArgType());
        EXPECT_EQ(DBusArgument::ArgType::Array, array.getElemType());
        EXPECT_EQ(std::string{DBUS_TYPE_ARRAY_AS_STRING} + std::string{subArray.getSignature()}, std::string{array.getSignature()});
        EXPECT_EQ(std::string{subArray.getSignature()}, std::string{array.getContainerSignature()});
    }

    TEST_F(DBusArrayTest, addArgument_structArg)
    {
        //array of structs
    }

    TEST_F(DBusArrayTest, addArgument_dictionaryArg)
    {
        //array of dictionaries
    }

    TEST_F(DBusArrayTest, editArrayElement)
    {
        //change array element properties
        DBusBasicArgument intArg{DBusArgument::ArgType::Int32};
        intArg.setArgValue(-100);
        DBusArray array{DBusArgument::ArgType::Int32};
        EXPECT_EQ(true,array.addArgument(static_cast<DBusArgument*>(&intArg)));
        EXPECT_EQ(true,array.addArgument(52));
        auto arrItr = array.getFirstArgItr();
        EXPECT_EQ(DBusArgument::ArgType::Int32, (*arrItr)->getArgType());
        //change this - get Ptr to element of array not get ietrator - ugly as hell
        auto intPtr1 = static_cast<dbus_int32_t*>(static_cast<DBusBasicArgument*>((*arrItr).get())->getArgValuePtr());
        auto intPtr2 = static_cast<dbus_int32_t*>(static_cast<DBusBasicArgument*>((*(++arrItr)).get())->getArgValuePtr());
        EXPECT_EQ(true, intPtr1 != nullptr);
        EXPECT_EQ(true, intPtr2 != nullptr);
        EXPECT_EQ(-100, *intPtr1);
        EXPECT_EQ(52, *intPtr2);
    }
}
