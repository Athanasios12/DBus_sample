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
        EXPECT_EQ(DBUS_TYPE_ARRAY_AS_STRING, std::string{dict.getSignature()});
        EXPECT_EQ(true, dict.getContainedSignature().empty());
    }

    TEST_F(DBusDictionaryTest, ctor)
    {
        DBusDictionary dict{DBusArgument::ArgType::String, DBusArgument::ArgType::Int32};
        EXPECT_EQ(0u, dict.getSize());
        EXPECT_EQ(std::make_pair(DBusArgument::ArgType::String, DBusArgument::ArgType::Int32), dict.getEntryType());
        EXPECT_EQ(true, dict.isInitialized());
        auto expectedSig = std::string{"{"} + std::string{DBUS_TYPE_STRING_AS_STRING} +
                           std::string{DBUS_TYPE_INT32_AS_STRING} + std::string{"}"};
        EXPECT_EQ(std::string{DBUS_TYPE_ARRAY_AS_STRING} + expectedSig, std::string{dict.getSignature()});
        EXPECT_EQ(expectedSig, dict.getContainedSignature());
    }    

    TEST_F(DBusDictionaryTest, addEntry_valid)
    {
        DBusDictionary dict;
        DBusBasicArgument key{DBusArgument::ArgType::String};        
        DBusBasicArgument value{DBusArgument::ArgType::Byte};
        key.setArgValue("String");
        value.setArgValue(static_cast<uint8_t>(10));
        dict.setEntryType(key.getArgType(), value.getArgType());

        bool addedEntries = dict.addEntry("Key", static_cast<uint8_t>(10));
        addedEntries &= dict.addEntry(static_cast<DBusArgument*>(&key), static_cast<DBusArgument*>(&value));
        EXPECT_EQ(true, addedEntries);
        EXPECT_EQ(2u, dict.getSize());
        EXPECT_EQ(std::make_pair(DBusArgument::ArgType::String, DBusArgument::ArgType::Byte), dict.getEntryType());
        EXPECT_EQ(true, dict.isInitialized());
        auto expectedSig = std::string{"{"} + std::string{DBUS_TYPE_STRING_AS_STRING} +
                           std::string{DBUS_TYPE_BYTE_AS_STRING} + std::string{"}"};
        EXPECT_EQ(std::string{DBUS_TYPE_ARRAY_AS_STRING} + expectedSig, std::string{dict.getSignature()});
        EXPECT_EQ(expectedSig, dict.getContainedSignature());
    }

    TEST_F(DBusDictionaryTest, addEntry_invalid_EntryArgsValuesNotSet)
    {
        DBusDictionary dict;
        DBusBasicArgument key{DBusArgument::ArgType::String};
        DBusBasicArgument value{DBusArgument::ArgType::Int32};
        dict.setEntryType(key.getArgType(), value.getArgType());

        bool addedEntry = dict.addEntry(static_cast<DBusArgument*>(&key), static_cast<DBusArgument*>(&value));
        EXPECT_EQ(false, addedEntry);
        EXPECT_EQ(0u, dict.getSize());
        auto expectedSig = std::string{"{"} + std::string{DBUS_TYPE_STRING_AS_STRING} +
                           std::string{DBUS_TYPE_INT32_AS_STRING} + std::string{"}"};
        EXPECT_EQ(std::string{DBUS_TYPE_ARRAY_AS_STRING} + expectedSig, std::string{dict.getSignature()});
        EXPECT_EQ(expectedSig, dict.getContainedSignature());
    }

    TEST_F(DBusDictionaryTest, addEntry_invalid_DifferentEntryType)
    {
        DBusDictionary dict;
        DBusBasicArgument key{DBusArgument::ArgType::String};
        DBusBasicArgument value{DBusArgument::ArgType::Byte};
        EXPECT_EQ(true, key.setArgValue("String"));
        EXPECT_EQ(true, value.setArgValue(static_cast<uint8_t>(10)));
        dict.setEntryType(DBusArgument::ArgType::Double, DBusArgument::ArgType::Double);

        bool addedEntry = dict.addEntry(static_cast<DBusArgument*>(&key), static_cast<DBusArgument*>(&value));
        EXPECT_EQ(false, addedEntry);
        EXPECT_EQ(0u, dict.getSize());
        auto expectedSig = std::string{"{"} + std::string{DBUS_TYPE_DOUBLE_AS_STRING} +
                           std::string{DBUS_TYPE_DOUBLE_AS_STRING} + std::string{"}"};
        EXPECT_EQ(std::string{DBUS_TYPE_ARRAY_AS_STRING} + expectedSig, std::string{dict.getSignature()});
        EXPECT_EQ(expectedSig, dict.getContainedSignature());
    }

    TEST_F(DBusDictionaryTest, addArgument_invalid_ArgIsNotDictEntry)
    {
        DBusDictionary dict;
        DBusBasicArgument string{DBusArgument::ArgType::String};
        dict.setEntryType(DBusArgument::ArgType::String, DBusArgument::ArgType::Int32);
        bool argAdded = dict.addArgument(&string);
        EXPECT_EQ(false, argAdded);
        EXPECT_EQ(0u, dict.getSize());
        EXPECT_EQ(false, dict.isArgInitalized());
        auto expectedSig = std::string{"{"} + std::string{DBUS_TYPE_STRING_AS_STRING} +
                           std::string{DBUS_TYPE_INT32_AS_STRING} + std::string{"}"};
        EXPECT_EQ(std::string{DBUS_TYPE_ARRAY_AS_STRING} + expectedSig, std::string{dict.getSignature()});
        EXPECT_EQ(expectedSig, dict.getContainedSignature());
    }

    TEST_F(DBusDictionaryTest, addArgument_invalid_DictEntryIsNotInitialized)
    {
        DBusDictionary dict;
        DBusDictEntry entry;
        dict.setEntryType(DBusArgument::ArgType::String, DBusArgument::ArgType::Int32);
        bool argAdded = dict.addArgument(&entry);
        EXPECT_EQ(false, argAdded);
        EXPECT_EQ(0u, dict.getSize());
        EXPECT_EQ(false, dict.isArgInitalized());
        auto expectedSig = std::string{"{"} + std::string{DBUS_TYPE_STRING_AS_STRING} +
                           std::string{DBUS_TYPE_INT32_AS_STRING} + std::string{"}"};
        EXPECT_EQ(std::string{DBUS_TYPE_ARRAY_AS_STRING} + expectedSig, std::string{dict.getSignature()});
        EXPECT_EQ(expectedSig, dict.getContainedSignature());
    }

    TEST_F(DBusDictionaryTest, addArgument_valid)
    {
        DBusDictionary dict;
        DBusBasicArgument key{DBusArgument::ArgType::String};
        DBusBasicArgument value{DBusArgument::ArgType::Int32};
        EXPECT_EQ(true, key.setArgValue("String"));
        EXPECT_EQ(true, value.setArgValue(10));
        DBusDictEntry entry{&key, &value};
        dict.setEntryType(entry.getKeyType(), entry.getValueType());
        bool argAdded = dict.addArgument(&entry);
        EXPECT_EQ(true, argAdded);
        EXPECT_EQ(1u, dict.getSize());
        EXPECT_EQ(true, dict.isInitialized());
        auto expectedSig = std::string{"{"} + std::string{DBUS_TYPE_STRING_AS_STRING} +
                           std::string{DBUS_TYPE_INT32_AS_STRING} + std::string{"}"};
        EXPECT_EQ(std::string{DBUS_TYPE_ARRAY_AS_STRING} + expectedSig, std::string{dict.getSignature()});
        EXPECT_EQ(expectedSig, dict.getContainedSignature());
    }

    TEST_F(DBusDictionaryTest, copyCtor)
    {
        DBusDictionary dict;
        DBusBasicArgument key{DBusArgument::ArgType::String};
        DBusBasicArgument value{DBusArgument::ArgType::Int32};
        EXPECT_EQ(true, key.setArgValue("String"));
        EXPECT_EQ(true, value.setArgValue(10));
        dict.setEntryType(key.getArgType(), value.getArgType());
        dict.addEntry<const char*, dbus_int32_t>("Key", 10);
        dict.addEntry<DBusArgument*, DBusArgument*>(&key, &value);
        DBusDictionary dictCopy{dict};
        //original
        EXPECT_EQ(2u, dict.getSize());
        EXPECT_EQ(std::make_pair(DBusArgument::ArgType::String, DBusArgument::ArgType::Int32), dict.getEntryType());
        auto expectedSig = std::string{"{"} + std::string{DBUS_TYPE_STRING_AS_STRING} +
                           std::string{DBUS_TYPE_INT32_AS_STRING} + std::string{"}"};
        EXPECT_EQ(std::string{DBUS_TYPE_ARRAY_AS_STRING} + expectedSig, std::string{dict.getSignature()});
        EXPECT_EQ(expectedSig, dict.getContainedSignature());
        //copy
        EXPECT_EQ(dictCopy.getSize(), dict.getSize());
        EXPECT_EQ(dictCopy.getEntryType(), dict.getEntryType());
        EXPECT_EQ(dictCopy.isInitialized(), dict.isInitialized());
        EXPECT_EQ(true, strcmp(dict.getSignature(), dictCopy.getSignature()) == 0);
        EXPECT_EQ(dict.getContainedSignature(), dictCopy.getContainedSignature());
    }

    TEST_F(DBusDictionaryTest, moveCtor)
    {
        DBusDictionary dict;
        DBusBasicArgument key{DBusArgument::ArgType::String};
        DBusBasicArgument value{DBusArgument::ArgType::Int32};
        EXPECT_EQ(true, key.setArgValue("String"));
        EXPECT_EQ(true, value.setArgValue(10));
        dict.setEntryType(key.getArgType(), value.getArgType());
        dict.addEntry<const char*, dbus_int32_t>("Key", 10);
        dict.addEntry<DBusArgument*, DBusArgument*>(&key, &value);
        DBusDictionary dictMove{std::move(dict)};
        //move
        EXPECT_EQ(2u, dictMove.getSize());
        EXPECT_EQ(std::make_pair(DBusArgument::ArgType::String, DBusArgument::ArgType::Int32), dictMove.getEntryType());
        EXPECT_EQ(true, dictMove.isInitialized());
        auto expectedSig = std::string{"{"} + std::string{DBUS_TYPE_STRING_AS_STRING} +
                           std::string{DBUS_TYPE_INT32_AS_STRING} + std::string{"}"};
        EXPECT_EQ(std::string{DBUS_TYPE_ARRAY_AS_STRING} + expectedSig, std::string{dictMove.getSignature()});
        EXPECT_EQ(expectedSig, dictMove.getContainedSignature());
        //original
        EXPECT_EQ(0u, dict.getSize());
        EXPECT_EQ(std::make_pair(DBusArgument::ArgType::Invalid, DBusArgument::ArgType::Invalid), dict.getEntryType());
        EXPECT_EQ(false, dict.isInitialized());
        EXPECT_EQ(DBUS_TYPE_ARRAY_AS_STRING, std::string{dict.getSignature()});
        EXPECT_EQ(true, dict.getContainedSignature().empty());
    }

}
