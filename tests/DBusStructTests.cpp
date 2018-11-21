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
    class DBusStructTest : public ::testing::Test
    {
    protected:
          // You can remove any or all of the following functions if its body
          // is empty.

          DBusStructTest()
          {
            // You can do set-up work for each test here.
          }

          virtual ~DBusStructTest()
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

    TEST_F(DBusStructTest, defaultCtor)
    {
        DBusStruct dbStruct;
        EXPECT_EQ(0u, dbStruct.getSize());
        EXPECT_EQ(DBusArgument::ArgType::Struct, dbStruct.getArgType());
        EXPECT_EQ(std::string{"()"}, std::string{dbStruct.getSignature()});
        EXPECT_EQ(true, dbStruct.getContainedSignature().empty());
        EXPECT_EQ(nullptr, dbStruct.getContainerSignature());
    }

    TEST_F(DBusStructTest, addField_valid)
    {
        DBusStruct dbStruct;
        EXPECT_EQ(true, dbStruct.addField(DBusArgument::ArgType::String, "String field"));
        EXPECT_EQ(true, dbStruct.addField(DBusArgument::ArgType::Int32, 90));
        EXPECT_EQ(2u, dbStruct.getSize());
        std::string expectedSig = std::string{"("} + std::string{DBUS_TYPE_STRING_AS_STRING} +
                                   std::string{DBUS_TYPE_INT32_AS_STRING} + std::string{")"};
        EXPECT_EQ(expectedSig, std::string{dbStruct.getSignature()});
        EXPECT_EQ(std::string{DBUS_TYPE_STRING_AS_STRING} + std::string{DBUS_TYPE_INT32_AS_STRING},
                  dbStruct.getContainedSignature());
        auto firstArgPtr = static_cast<DBusBasicArgument*>(dbStruct.getArgValueAt(0));
        auto secondArgPtr = static_cast<DBusBasicArgument*>(dbStruct.getArgValueAt(1));
        //error z rzutem char* na stringa, sprawdzic tworzenie basic arga
        EXPECT_NE(nullptr, firstArgPtr);
        EXPECT_NE(nullptr, secondArgPtr);
        EXPECT_EQ(DBusArgument::ArgType::String, firstArgPtr->getArgType());
        EXPECT_EQ(DBusArgument::ArgType::Int32, secondArgPtr->getArgType());
        EXPECT_EQ(std::string{"String field"}, std::string{static_cast<char*>(firstArgPtr->getArgValuePtr())});
        EXPECT_EQ(90, *(static_cast<dbus_int32_t*>(secondArgPtr->getArgValuePtr())));
    }

    TEST_F(DBusStructTest, addField_nonMatchingTypeAndValue)
    {
        DBusStruct dbStruct;
        EXPECT_EQ(false, dbStruct.addField(DBusArgument::ArgType::String, 20));
        EXPECT_EQ(0u, dbStruct.getSize());
        EXPECT_EQ(std::string{"()"}, std::string{dbStruct.getSignature()});
        EXPECT_EQ(true, dbStruct.getContainedSignature().empty());
        EXPECT_EQ(nullptr, dbStruct.getContainerSignature());
    }

    TEST_F(DBusStructTest, addArgument_valid)
    {
        DBusStruct dbStruct;
        DBusBasicArgument field0{DBusArgument::ArgType::String};
        EXPECT_EQ(true, field0.setArgValue("String field"));
        DBusBasicArgument field1{DBusArgument::ArgType::Int32};
        EXPECT_EQ(true, field1.setArgValue(90));

        EXPECT_EQ(true, dbStruct.addArgument(static_cast<DBusArgument*>(&field0)));
        EXPECT_EQ(true, dbStruct.addArgument(static_cast<DBusArgument*>(&field1)));
        EXPECT_EQ(2u, dbStruct.getSize());
        std::string expectedSig = std::string{"("} + std::string{DBUS_TYPE_STRING_AS_STRING} +
                                   std::string{DBUS_TYPE_INT32_AS_STRING} + std::string{")"};
        EXPECT_EQ(expectedSig, std::string{dbStruct.getSignature()});
        EXPECT_EQ(std::string{DBUS_TYPE_STRING_AS_STRING} + std::string{DBUS_TYPE_INT32_AS_STRING},
                  dbStruct.getContainedSignature());
        //check if args added with proper values
        auto firstArgPtr = static_cast<DBusBasicArgument*>(dbStruct.getArgValueAt(0));
        auto secondArgPtr = static_cast<DBusBasicArgument*>(dbStruct.getArgValueAt(1));
        EXPECT_NE(nullptr, firstArgPtr);
        EXPECT_NE(nullptr, secondArgPtr);
        EXPECT_EQ(DBusArgument::ArgType::String, firstArgPtr->getArgType());
        EXPECT_EQ(DBusArgument::ArgType::Int32, secondArgPtr->getArgType());
        EXPECT_EQ(std::string{"String field"}, std::string{static_cast<char*>(firstArgPtr->getArgValuePtr())});
        EXPECT_EQ(90, *(static_cast<dbus_int32_t*>(secondArgPtr->getArgValuePtr())));
    }

    TEST_F(DBusStructTest, addArgument_invalid)
    {
        //trying to add uninitialized arg
        DBusStruct dbStruct;
        DBusBasicArgument invalidArg{};
        EXPECT_EQ(false, dbStruct.addArgument(static_cast<DBusArgument*>(&invalidArg)));
        EXPECT_EQ(0u, dbStruct.getSize());
        EXPECT_EQ(std::string{"()"}, std::string{dbStruct.getSignature()});
        EXPECT_EQ(true, dbStruct.getContainedSignature().empty());
        EXPECT_EQ(nullptr, dbStruct.getContainerSignature());
    }

    TEST_F(DBusStructTest, copyCtor)
    {
        DBusStruct dbStruct;
        dbStruct.addField(DBusArgument::ArgType::String, "String field");
        dbStruct.addField(DBusArgument::ArgType::Int32, 78);
        DBusStruct dbStructCopy{dbStruct};
        //original
        EXPECT_EQ(2u, dbStruct.getSize());
        std::string expectedSig = std::string{"("} + std::string{DBUS_TYPE_STRING_AS_STRING} +
                                   std::string{DBUS_TYPE_INT32_AS_STRING} + std::string{")"};
        EXPECT_EQ(expectedSig, std::string{dbStruct.getSignature()});
        EXPECT_EQ(std::string{DBUS_TYPE_STRING_AS_STRING} + std::string{DBUS_TYPE_INT32_AS_STRING},
                  dbStruct.getContainedSignature());
        //copy
        EXPECT_EQ(dbStruct.getSize(), dbStructCopy.getSize());
        EXPECT_EQ(true, strcmp(dbStruct.getSignature(), dbStructCopy.getSignature()) == 0);
        EXPECT_EQ(dbStruct.getContainedSignature(), dbStructCopy.getContainedSignature());
    }

    TEST_F(DBusStructTest, moveCtor)
    {
        DBusStruct dbStruct;
        dbStruct.addField(DBusArgument::ArgType::String, "String field");
        dbStruct.addField(DBusArgument::ArgType::Int32, 78);
        DBusStruct dbStructMove{std::move(dbStruct)};
        //move
        EXPECT_EQ(2u, dbStructMove.getSize());
        std::string expectedSig = std::string{"("} + std::string{DBUS_TYPE_STRING_AS_STRING} +
                                   std::string{DBUS_TYPE_INT32_AS_STRING} + std::string{")"};
        EXPECT_EQ(expectedSig, std::string{dbStructMove.getSignature()});
        EXPECT_EQ(std::string{DBUS_TYPE_STRING_AS_STRING} + std::string{DBUS_TYPE_INT32_AS_STRING},
                  dbStructMove.getContainedSignature());
        //original
        EXPECT_EQ(0u, dbStruct.getSize());
        EXPECT_EQ(DBusArgument::ArgType::Struct, dbStruct.getArgType());
        EXPECT_EQ(std::string{"()"}, std::string{dbStruct.getSignature()});
        EXPECT_EQ(true, dbStruct.getContainedSignature().empty());
        EXPECT_EQ(nullptr, dbStruct.getContainerSignature());
    }

}
