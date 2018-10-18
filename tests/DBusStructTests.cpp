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
//        DBusStruct dbStruct;
//        EXPECT_EQ(0u, dbStruct.getSize());
//        EXPECT_EQ(std::make_pair(DBusArgument::ArgType::Invalid, DBusArgument::ArgType::Invalid), dbStruct.getEntryType());
//        EXPECT_EQ(false, dbStruct.isInitialized());
//        EXPECT_EQ("a", std::string{dbStruct.getSignature()});
//        EXPECT_EQ(nullptr, dbStruct.getContainerSignature());
    }

//    TEST_F(DBusStructTest, ctor)
//    {
//        DBusStruct dbStruct{DBusArgument::ArgType::String, DBusArgument::ArgType::Int32};
//        EXPECT_EQ(0u, dbStruct.getSize());
//        EXPECT_EQ(std::make_pair(DBusArgument::ArgType::String, DBusArgument::ArgType::Int32), dbStruct.getEntryType());
//        EXPECT_EQ(true, dbStruct.isInitialized());
//        EXPECT_EQ("a{si}", std::string{dbStruct.getSignature()});
//        EXPECT_EQ(true, dbStruct.getContainerSignature() != nullptr);
//        EXPECT_EQ("{si}", std::string{dbStruct.getContainerSignature()});
//    }

//    TEST_F(DBusStructTest, copyCtor)
//    {
//        DBusStruct dbStruct;
//        DBusBasicArgument key{DBusArgument::ArgType::String};
//        DBusBasicArgument value{DBusArgument::ArgType::Int32};
//        dbStruct.setEntryType(key.getArgType(), value.getArgType());
//        dbStruct.addEntry<const char*, dbus_int32_t>("Key", 10);
//        dbStruct.addEntry<DBusArgument*, DBusArgument*>(&key, &value);
//        DBusStruct dbStructCopy{dbStruct};
//        //original
//        EXPECT_EQ(2u, dbStructCopy.getSize());
//        EXPECT_EQ(std::make_pair(DBusArgument::ArgType::String, DBusArgument::ArgType::Int32), dbStructCopy.getEntryType());
//        EXPECT_EQ(true, dbStructCopy.isInitialized());
//        EXPECT_EQ("a{si}", std::string{dbStructCopy.getSignature()});
//        EXPECT_EQ("{si}", std::string{dbStructCopy.getContainerSignature()});
//        //copy
//        EXPECT_EQ(dbStructCopy.getSize(), dbStruct.getSize());
//        EXPECT_EQ(dbStructCopy.getEntryType(), dbStruct.getEntryType());
//        EXPECT_EQ(dbStructCopy.isInitialized(), dbStruct.isInitialized());
//        EXPECT_EQ(true, strcmp(dbStruct.getSignature(), dbStructCopy.getSignature()) == 0);
//        EXPECT_EQ(true, strcmp(dbStruct.getContainerSignature(), dbStructCopy.getContainerSignature()) == 0);
//    }

//    TEST_F(DBusStructTest, moveCtor)
//    {
//        DBusStruct dbStruct;
//        DBusBasicArgument key{DBusArgument::ArgType::String};
//        DBusBasicArgument value{DBusArgument::ArgType::Int32};
//        dbStruct.setEntryType(key.getArgType(), value.getArgType());
//        dbStruct.addEntry<const char*, dbus_int32_t>("Key", 10);
//        dbStruct.addEntry<DBusArgument*, DBusArgument*>(&key, &value);
//        DBusStruct dbStructMove{std::move(dbStruct)};
//        //move
//        EXPECT_EQ(2u, dbStructMove.getSize());
//        EXPECT_EQ(std::make_pair(DBusArgument::ArgType::String, DBusArgument::ArgType::Int32), dbStructMove.getEntryType());
//        EXPECT_EQ(true, dbStructMove.isInitialized());
//        EXPECT_EQ("a{si}", std::string{dbStructMove.getSignature()});
//        EXPECT_EQ("{si}", std::string{dbStructMove.getContainerSignature()});
//        //original
//        EXPECT_EQ(0u, dbStruct.getSize());
//        EXPECT_EQ(std::make_pair(DBusArgument::ArgType::Invalid, DBusArgument::ArgType::Invalid), dbStruct.getEntryType());
//        EXPECT_EQ(false, dbStruct.isInitialized());
//        EXPECT_EQ("a", std::string{dbStruct.getSignature()});
//        EXPECT_EQ(nullptr, dbStruct.getContainerSignature());
//    }

//    TEST_F(DBusStructTest, addEntry_valid)
//    {
//        DBusStruct dbStruct;
//        DBusBasicArgument key{DBusArgument::ArgType::String};
//        DBusBasicArgument value{DBusArgument::ArgType::Int32};
//        dbStruct.setEntryType(key.getArgType(), value.getArgType());

//        bool addedEntries = dbStruct.addEntry<const char*, dbus_int32_t>("Key", 10);
//        addedEntries &= dbStruct.addEntry<DBusArgument*, DBusArgument*>(&key, &value);

//        EXPECT_EQ(true, addedEntries);
//        EXPECT_EQ(2u, dbStruct.getSize());
//        EXPECT_EQ(std::make_pair(DBusArgument::ArgType::String, DBusArgument::ArgType::Int32), dbStruct.getEntryType());
//        EXPECT_EQ(true, dbStruct.isInitialized());
//        EXPECT_EQ("a{si}", std::string{dbStruct.getSignature()});
//        EXPECT_EQ("{si}", std::string{dbStruct.getContainerSignature()});
//    }

//    TEST_F(DBusStructTest, addEntry_invalid)
//    {
//        DBusStruct dbStruct;
//        DBusBasicArgument key{DBusArgument::ArgType::String};
//        DBusBasicArgument value{DBusArgument::ArgType::Int32};
//        dbStruct.setEntryType(key.getArgType(), value.getArgType());

//        bool addedEntries = dbStruct.addEntry<double, bool>(10.9, true);
//        addedEntries &= dbStruct.addEntry<DBusArgument*, DBusArgument*>(&key, &value);
//        EXPECT_EQ(false, addedEntries);
//        EXPECT_EQ(1u, dbStruct.getSize());
//    }

//    TEST_F(DBusStructTest, addArgument_valid)
//    {
//        DBusStruct dbStruct;
//        DBusBasicArgument key{DBusArgument::ArgType::String};
//        DBusBasicArgument value{DBusArgument::ArgType::Int32};
//        DBusdbStructEntry entry{&key, &value};
//        dbStruct.setEntryType(entry.getKeyType(), entry.getValueType());
//        bool argAdded = dbStruct.addArgument(&entry);
//        EXPECT_EQ(true, argAdded);
//        EXPECT_EQ(1u, dbStruct.getSize());
//        EXPECT_EQ(true, dbStruct.isInitialized());
//        EXPECT_EQ("a{si}", std::string{dbStruct.getSignature()});
//        EXPECT_EQ("{si}", std::string{dbStruct.getContainerSignature()});
//    }

//    TEST_F(DBusStructTest, addArgument_invalid)
//    {
//        DBusStruct dbStruct;
//        DBusBasicArgument string{DBusArgument::ArgType::String};
//        dbStruct.setEntryType(DBusArgument::ArgType::String, DBusArgument::ArgType::Int32);
//        bool argAdded = dbStruct.addArgument(&string);
//        EXPECT_EQ(false, argAdded);
//        EXPECT_EQ(0u, dbStruct.getSize());
//        EXPECT_EQ(true, dbStruct.isInitialized());
//        EXPECT_EQ("a{si}", std::string{dbStruct.getSignature()});
//        EXPECT_EQ("{si}", std::string{dbStruct.getContainerSignature()});
//    }

}
