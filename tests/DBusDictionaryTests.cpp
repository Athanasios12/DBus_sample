#include "gtest/gtest.h"
#include "DBusBasicArgument.h"
#include "DBusDictEntry.h"
#include "DBusDictionary.h"
#include <utility>
#include <memory>

using namespace DBUS;

namespace
{
    // The fixture for testing class Foo.
    class DBusDictionaryTest : public ::testing::Test
    {
    protected:
          // You can remove any or all of the following functions if its body
          // is empty.

          DBusDictionaryTest()
          {
            // You can do set-up work for each test here.
          }

          virtual ~DBusDictionaryTest()
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

    TEST_F(DBusDictionaryTest, defaultCtor)
    {
        DBusDictionary dict;
        EXPECT_EQ(0u, dict.getSize());
        EXPECT_EQ(std::make_pair(DBusArgument::ArgType::Invalid, DBusArgument::ArgType::Invalid), dict.getEntryType());
        EXPECT_EQ(false, dict.isInitialized());
        EXPECT_EQ("a", std::string{dict.getSignature()});
        EXPECT_EQ(nullptr, dict.getContainerSignature());
    }

    TEST_F(DBusDictionaryTest, ctor)
    {
        DBusDictionary dict{DBusArgument::ArgType::String, DBusArgument::ArgType::Int32};
        EXPECT_EQ(0u, dict.getSize());
        EXPECT_EQ(std::make_pair(DBusArgument::ArgType::String, DBusArgument::ArgType::Int32), dict.getEntryType());
        EXPECT_EQ(true, dict.isInitialized());
        EXPECT_EQ("a{si}", std::string{dict.getSignature()});
        EXPECT_EQ(true, dict.getContainerSignature() != nullptr);
        EXPECT_EQ("{si}", std::string{dict.getContainerSignature()});
    }

    TEST_F(DBusDictionaryTest, copyCtor)
    {
        DBusDictionary dict;
        DBusBasicArgument key{DBusArgument::ArgType::String};
        DBusBasicArgument value{DBusArgument::ArgType::Int32};
        dict.setEntryType(key.getArgType(), value.getArgType());
        dict.addEntry<const char*, dbus_int32_t>("Key", 10);
        dict.addEntry<DBusArgument*, DBusArgument*>(&key, &value);
        DBusDictionary dictCopy{dict};
        //original
        EXPECT_EQ(2u, dictCopy.getSize());
        EXPECT_EQ(std::make_pair(DBusArgument::ArgType::String, DBusArgument::ArgType::Int32), dictCopy.getEntryType());
        EXPECT_EQ(true, dictCopy.isInitialized());
        EXPECT_EQ("a{si}", std::string{dictCopy.getSignature()});
        EXPECT_EQ("{si}", std::string{dictCopy.getContainerSignature()});
        //copy
        EXPECT_EQ(dictCopy.getSize(), dict.getSize());
        EXPECT_EQ(dictCopy.getEntryType(), dict.getEntryType());
        EXPECT_EQ(dictCopy.isInitialized(), dict.isInitialized());
        EXPECT_EQ(true, strcmp(dict.getSignature(), dictCopy.getSignature()) == 0);
        EXPECT_EQ(true, strcmp(dict.getContainerSignature(), dictCopy.getContainerSignature()) == 0);
    }

    TEST_F(DBusDictionaryTest, moveCtor)
    {
        DBusDictionary dict;
        DBusBasicArgument key{DBusArgument::ArgType::String};
        DBusBasicArgument value{DBusArgument::ArgType::Int32};
        dict.setEntryType(key.getArgType(), value.getArgType());
        dict.addEntry<const char*, dbus_int32_t>("Key", 10);
        dict.addEntry<DBusArgument*, DBusArgument*>(&key, &value);
        DBusDictionary dictMove{std::move(dict)};
        //move
        EXPECT_EQ(2u, dictMove.getSize());
        EXPECT_EQ(std::make_pair(DBusArgument::ArgType::String, DBusArgument::ArgType::Int32), dictMove.getEntryType());
        EXPECT_EQ(true, dictMove.isInitialized());
        EXPECT_EQ("a{si}", std::string{dictMove.getSignature()});
        EXPECT_EQ("{si}", std::string{dictMove.getContainerSignature()});
        //original
        EXPECT_EQ(0u, dict.getSize());
        EXPECT_EQ(std::make_pair(DBusArgument::ArgType::Invalid, DBusArgument::ArgType::Invalid), dict.getEntryType());
        EXPECT_EQ(false, dict.isInitialized());
        EXPECT_EQ("a", std::string{dict.getSignature()});
        EXPECT_EQ(nullptr, dict.getContainerSignature());
    }

    TEST_F(DBusDictionaryTest, addEntry_valid)
    {
        DBusDictionary dict;
        DBusBasicArgument key{DBusArgument::ArgType::String};
        DBusBasicArgument value{DBusArgument::ArgType::Int32};
        dict.setEntryType(key.getArgType(), value.getArgType());

        bool addedEntries = dict.addEntry<const char*, dbus_int32_t>("Key", 10);
        addedEntries &= dict.addEntry<DBusArgument*, DBusArgument*>(&key, &value);

        EXPECT_EQ(true, addedEntries);
        EXPECT_EQ(2u, dict.getSize());
        EXPECT_EQ(std::make_pair(DBusArgument::ArgType::String, DBusArgument::ArgType::Int32), dict.getEntryType());
        EXPECT_EQ(true, dict.isInitialized());
        EXPECT_EQ("a{si}", std::string{dict.getSignature()});
        EXPECT_EQ("{si}", std::string{dict.getContainerSignature()});
    }

    TEST_F(DBusDictionaryTest, addEntry_invalid)
    {
        DBusDictionary dict;
        DBusBasicArgument key{DBusArgument::ArgType::String};
        DBusBasicArgument value{DBusArgument::ArgType::Int32};
        dict.setEntryType(key.getArgType(), value.getArgType());

        bool addedEntries = dict.addEntry<double, bool>(10.9, true);
        addedEntries &= dict.addEntry<DBusArgument*, DBusArgument*>(&key, &value);
        EXPECT_EQ(false, addedEntries);
        EXPECT_EQ(1u, dict.getSize());
    }

    TEST_F(DBusDictionaryTest, addArgument_valid)
    {
        DBusDictionary dict;
        DBusBasicArgument key{DBusArgument::ArgType::String};
        DBusBasicArgument value{DBusArgument::ArgType::Int32};
        DBusDictEntry entry{&key, &value};
        dict.setEntryType(entry.getKeyType(), entry.getValueType());
        bool argAdded = dict.addArgument(&entry);
        EXPECT_EQ(true, argAdded);
        EXPECT_EQ(1u, dict.getSize());
        EXPECT_EQ(true, dict.isInitialized());
        EXPECT_EQ("a{si}", std::string{dict.getSignature()});
        EXPECT_EQ("{si}", std::string{dict.getContainerSignature()});
    }

    TEST_F(DBusDictionaryTest, addArgument_invalid)
    {
        DBusDictionary dict;
        DBusBasicArgument string{DBusArgument::ArgType::String};
        dict.setEntryType(DBusArgument::ArgType::String, DBusArgument::ArgType::Int32);
        bool argAdded = dict.addArgument(&string);
        EXPECT_EQ(false, argAdded);
        EXPECT_EQ(0u, dict.getSize());
        EXPECT_EQ(true, dict.isInitialized());
        EXPECT_EQ("a{si}", std::string{dict.getSignature()});
        EXPECT_EQ("{si}", std::string{dict.getContainerSignature()});
    }

}
