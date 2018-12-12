#include "gtest/gtest.h"
#include "DBusBasicArgument.h"
#include "DBusArray.h"
#include "DBusStruct.h"
#include "DBusDictionary.h"
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

    TEST_F(DBusArrayTest, addArgument_notInitialized)
    {
        //added arg not initialized arg
        DBusBasicArgument notInitArg{};
        DBusArray array{DBusArgument::ArgType::String};
        EXPECT_EQ(false, array.addArgument(static_cast<DBusArgument*>(&notInitArg)));
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
        EXPECT_EQ(false, array.addArgument(static_cast<DBusArgument*>(&wrongTypeArg)));
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
        EXPECT_EQ(true, array.addArgument(static_cast<DBusArgument*>(&strArg)));
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
        subArray.addArgument(static_cast<DBusArgument*>(&strArg));
        subArray.addArgument("Elem 1");
        DBusArray array{DBusArgument::ArgType::Array};
        array.addArgument(static_cast<DBusArgument*>(&subArray));
        EXPECT_EQ(1u, array.getSize());
        EXPECT_EQ(DBusArgument::ArgType::Array, array.getArgType());
        EXPECT_EQ(DBusArgument::ArgType::Array, array.getElemType());
        EXPECT_EQ(std::string{DBUS_TYPE_ARRAY_AS_STRING} + std::string{subArray.getSignature()}, std::string{array.getSignature()});
        EXPECT_EQ(std::string{subArray.getSignature()}, std::string{array.getContainerSignature()});
    }

    TEST_F(DBusArrayTest, addArgument_structArg)
    {
        //array of structs
        DBusStruct subStruct{};
        subStruct.addField(DBusArgument::ArgType::Bool, false);
        subStruct.addField(DBusArgument::ArgType::Double, 234.56);

        DBusArray array{DBusArgument::ArgType::Struct};
        EXPECT_EQ(true, array.addArgument(static_cast<DBusArgument*>(&subStruct)));
        EXPECT_EQ(1u, array.getSize());
        EXPECT_EQ(DBusArgument::ArgType::Array, array.getArgType());
        EXPECT_EQ(DBusArgument::ArgType::Struct, array.getElemType());
        EXPECT_EQ(std::string{DBUS_TYPE_ARRAY_AS_STRING} + std::string{subStruct.getSignature()}, std::string{array.getSignature()});
        EXPECT_EQ(std::string{subStruct.getSignature()}, std::string{array.getContainerSignature()});
    }

    TEST_F(DBusArrayTest, addArgument_structArg_2DifferentStructsError)
    {
        //first struct
        DBusStruct subStruct{};
        subStruct.addField(DBusArgument::ArgType::Bool, false);
        subStruct.addField(DBusArgument::ArgType::Double, 234.56);
        //second different struct - for array to hold structs they have to have the same field types and number - Dbus protocol requirements
        DBusStruct subStructDiff{};
        subStructDiff.addField(DBusArgument::ArgType::String, "String field");
        subStructDiff.addField(DBusArgument::ArgType::UInt32, 20);

        DBusArray array{DBusArgument::ArgType::Struct};
        EXPECT_EQ(true, array.addArgument(static_cast<DBusArgument*>(&subStruct)));
        EXPECT_EQ(false, array.addArgument(static_cast<DBusArgument*>(&subStructDiff)));
        EXPECT_EQ(1u, array.getSize());
        EXPECT_EQ(DBusArgument::ArgType::Array, array.getArgType());
        EXPECT_EQ(DBusArgument::ArgType::Struct, array.getElemType());
        EXPECT_EQ(std::string{DBUS_TYPE_ARRAY_AS_STRING} + std::string{subStruct.getSignature()}, std::string{array.getSignature()});
        EXPECT_EQ(std::string{subStruct.getSignature()}, std::string{array.getContainerSignature()});
    }

    TEST_F(DBusArrayTest, addArgument_dictionaryArg)
    {
        //array of dictionaries
        DBusDictionary subDict{DBusArgument::ArgType::String, DBusArgument::ArgType::Int32};
        subDict.addEntry("Entry 0", 80);
        subDict.addEntry("Entry 1", -8);

        DBusArray array{DBusArgument::ArgType::Dictionary};
        EXPECT_EQ(true, array.addArgument(static_cast<DBusArgument*>(&subDict)));
        EXPECT_EQ(1u, array.getSize());
        EXPECT_EQ(DBusArgument::ArgType::Array, array.getArgType());
        EXPECT_EQ(DBusArgument::ArgType::Dictionary, array.getElemType());
        EXPECT_EQ(std::string{DBUS_TYPE_ARRAY_AS_STRING} + std::string{subDict.getSignature()}, std::string{array.getSignature()});
        EXPECT_EQ(std::string{subDict.getSignature()}, std::string{array.getContainerSignature()});
    }

    TEST_F(DBusArrayTest, addArgument_dictionaryArg_2DifferentDictionariesError)
    {
        //first dictionary
        DBusDictionary subDict{DBusArgument::ArgType::String, DBusArgument::ArgType::Int32};
        subDict.addEntry("Entry 0", 80);
        subDict.addEntry("Entry 1", -8);
        //second with different entry type
        DBusDictionary subDictDiff{DBusArgument::ArgType::UInt32, DBusArgument::ArgType::Bool};
        subDictDiff.addEntry(40, true);
        subDictDiff.addEntry(0, false);

        DBusArray array{DBusArgument::ArgType::Dictionary};
        EXPECT_EQ(true, array.addArgument(static_cast<DBusArgument*>(&subDict)));
        EXPECT_EQ(false, array.addArgument(static_cast<DBusArgument*>(&subDictDiff)));
        EXPECT_EQ(1u, array.getSize());
        EXPECT_EQ(DBusArgument::ArgType::Array, array.getArgType());
        EXPECT_EQ(DBusArgument::ArgType::Dictionary, array.getElemType());
        EXPECT_EQ(std::string{DBUS_TYPE_ARRAY_AS_STRING} + std::string{subDict.getSignature()}, std::string{array.getSignature()});
        EXPECT_EQ(std::string{subDict.getSignature()}, std::string{array.getContainerSignature()});
    }

    TEST_F(DBusArrayTest, editArrayElement)
    {
        //change array element properties
        DBusBasicArgument intArg{DBusArgument::ArgType::Int32};
        intArg.setArgValue(-100);
        DBusArray array{DBusArgument::ArgType::Int32};
        EXPECT_EQ(true,array.addArgument(static_cast<DBusArgument*>(&intArg)));
        EXPECT_EQ(true,array.addArgument(52));
        //change this - get Ptr to element of array not get iterator - ugly as hell
        auto firstArgPtr = static_cast<DBusBasicArgument*>(array.getArgValueAt(0));
        auto secondArgPtr = static_cast<DBusBasicArgument*>(array.getArgValueAt(1));
        EXPECT_NE(nullptr, firstArgPtr);
        EXPECT_NE(nullptr, secondArgPtr);
        EXPECT_EQ(DBusArgument::ArgType::Int32, firstArgPtr->getArgType());
        EXPECT_EQ(DBusArgument::ArgType::Int32, secondArgPtr->getArgType());
        auto firstArgValue = static_cast<dbus_int32_t*>(firstArgPtr->getArgValuePtr());
        auto secondArgValue = static_cast<dbus_int32_t*>(secondArgPtr->getArgValuePtr());
        EXPECT_NE(nullptr, firstArgValue);
        EXPECT_NE(nullptr, secondArgValue);
        EXPECT_EQ(-100, *firstArgValue);
        EXPECT_EQ(52, *secondArgValue);
    }

    TEST_F(DBusArrayTest, copyCtor)
    {
        DBusArray array{DBusArgument::ArgType::String};
        DBusBasicArgument strArg{DBusArgument::ArgType::String};
        strArg.setArgValue("String");
        EXPECT_EQ(true, array.addArgument(static_cast<DBusArgument*>(&strArg)));
        DBusArray arrayCopy{array};
        //original
        EXPECT_EQ(1u, array.getSize());
        EXPECT_EQ(DBusArgument::ArgType::Array, array.getArgType());
        EXPECT_EQ(DBusArgument::ArgType::String, array.getElemType());
        auto expectedArraySignature = std::string{DBUS_TYPE_ARRAY_AS_STRING} + std::string{DBUS_TYPE_STRING_AS_STRING};
        EXPECT_EQ(expectedArraySignature, std::string{array.getSignature()});
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
        strArg.setArgValue("String");
        array.addArgument(static_cast<DBusArgument*>(&strArg));
        DBusArray arrayMove{std::move(array)};
        //move
        EXPECT_EQ(1u, arrayMove.getSize());
        EXPECT_EQ(DBusArgument::ArgType::Array, arrayMove.getArgType());
        EXPECT_EQ(DBusArgument::ArgType::String, arrayMove.getElemType());
        EXPECT_EQ(std::string{DBUS_TYPE_ARRAY_AS_STRING} + std::string{DBUS_TYPE_STRING_AS_STRING}, std::string{arrayMove.getSignature()});
        EXPECT_EQ(DBUS_TYPE_STRING_AS_STRING, std::string{arrayMove.getContainerSignature()});
        //original
        EXPECT_EQ(0u, array.getSize());
        EXPECT_EQ(DBusArgument::ArgType::Array, array.getArgType());
        EXPECT_EQ(DBusArgument::ArgType::Invalid, array.getElemType());
        EXPECT_EQ(nullptr, array.getSignature());
        EXPECT_EQ(nullptr, array.getContainerSignature());
    }
}
