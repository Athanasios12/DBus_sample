#include "gtest/gtest.h"
#include "DBusDictEntry.h"
#include "DBusBasicArgument.h"
#include "DBusArray.h"
#include "DBusDictionary.h"

using namespace DBUS;

namespace
{
    // The fixture for testing class Foo.
    class DBusDictEntryTest : public ::testing::Test
    {
    protected:
          // You can remove any or all of the following functions if its body
          // is empty.

          DBusDictEntryTest()
          {
            // You can do set-up work for each test here.
          }

          virtual ~DBusDictEntryTest()
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

    TEST_F(DBusDictEntryTest, defaultCtor)
    {
        DBusDictEntry entry;
        EXPECT_EQ(2u, entry.getSize());
        EXPECT_EQ(false, entry.getKeySet());
        EXPECT_EQ(false, entry.getValueSet());
        EXPECT_EQ(DBusArgument::ArgType::Invalid, entry.getKeyType());
        EXPECT_EQ(DBusArgument::ArgType::Invalid, entry.getValueType());
        EXPECT_EQ("{}", std::string{entry.getSignature()});
        EXPECT_EQ(nullptr, entry.getContainerSignature());
    }

    TEST_F(DBusDictEntryTest, ctor_rawPtrArgs)
    {
        DBusBasicArgument key{DBusArgument::ArgType::String};        
        DBusBasicArgument value{DBusArgument::ArgType::Int32};
        key.setArgValue("String Key");
        value.setArgValue(100);
        DBusDictEntry entry{&key, &value};
        EXPECT_EQ(2u, entry.getSize());
        EXPECT_EQ(true, entry.getKeySet());
        EXPECT_EQ(true, entry.getValueSet());
        EXPECT_EQ(DBusArgument::ArgType::String, entry.getKeyType());
        EXPECT_EQ(DBusArgument::ArgType::Int32, entry.getValueType());
        EXPECT_EQ("{si}",std::string{entry.getSignature()});
        EXPECT_EQ(nullptr, entry.getContainerSignature());
    }

    TEST_F(DBusDictEntryTest, ctor_smartPtrArgs)
    {
        std::unique_ptr<DBusArgument> key{new DBusBasicArgument{DBusArgument::ArgType::String}};
        std::unique_ptr<DBusArgument> value{new DBusBasicArgument{DBusArgument::ArgType::Int32}};
        static_cast<DBusBasicArgument*>(key.get())->setArgValue("String Key");
        static_cast<DBusBasicArgument*>(value.get())->setArgValue(100);
        DBusDictEntry entry{key, value};
        EXPECT_EQ(2u, entry.getSize());
        EXPECT_EQ(true, entry.getKeySet());
        EXPECT_EQ(true, entry.getValueSet());
        EXPECT_EQ(DBusArgument::ArgType::String, entry.getKeyType());
        EXPECT_EQ(DBusArgument::ArgType::Int32, entry.getValueType());
        EXPECT_EQ("{si}", std::string{entry.getSignature()});
        EXPECT_EQ(nullptr, entry.getContainerSignature());
        EXPECT_EQ(nullptr, key.get());
        EXPECT_EQ(nullptr, value.get());
    }

    TEST_F(DBusDictEntryTest, copyCtor)
    {
        std::unique_ptr<DBusArgument> key{new DBusBasicArgument{DBusArgument::ArgType::String}};
        std::unique_ptr<DBusArgument> value{new DBusBasicArgument{DBusArgument::ArgType::Int32}};
        static_cast<DBusBasicArgument*>(key.get())->setArgValue("String Key");
        static_cast<DBusBasicArgument*>(value.get())->setArgValue(100);
        DBusDictEntry entry{key, value};
        DBusDictEntry entryCopy{entry};
        EXPECT_EQ(2u, entry.getSize());
        EXPECT_EQ(true, entry.getKeySet());
        EXPECT_EQ(true, entry.getValueSet());
        EXPECT_EQ(DBusArgument::ArgType::String, entry.getKeyType());
        EXPECT_EQ(DBusArgument::ArgType::Int32, entry.getValueType());
        EXPECT_EQ("{si}", std::string{entry.getSignature()});
        EXPECT_EQ(nullptr, entry.getContainerSignature());
        EXPECT_EQ(entry.getSize(), entryCopy.getSize());
        EXPECT_EQ(entry.getKeySet(), entryCopy.getKeySet());
        EXPECT_EQ(entry.getValueSet(), entryCopy.getValueSet());
        EXPECT_EQ(entry.getKeyType(), entryCopy.getKeyType());
        EXPECT_EQ(entry.getValueType(), entryCopy.getValueType());
        EXPECT_EQ(true, strcmp(entry.getSignature(), entryCopy.getSignature()) == 0);
        EXPECT_EQ(nullptr, entryCopy.getContainerSignature());
    }

    TEST_F(DBusDictEntryTest, moveCtor)
    {
        std::unique_ptr<DBusArgument> key{new DBusBasicArgument{DBusArgument::ArgType::String}};
        std::unique_ptr<DBusArgument> value{new DBusBasicArgument{DBusArgument::ArgType::Int32}};
        static_cast<DBusBasicArgument*>(key.get())->setArgValue("String Key");
        static_cast<DBusBasicArgument*>(value.get())->setArgValue(100);
        DBusDictEntry entry{key, value};
        DBusDictEntry entryMove{std::move(entry)};
        EXPECT_EQ(2u, entryMove.getSize());
        EXPECT_EQ(true, entryMove.getKeySet());
        EXPECT_EQ(true, entryMove.getValueSet());
        EXPECT_EQ(DBusArgument::ArgType::String, entryMove.getKeyType());
        EXPECT_EQ(DBusArgument::ArgType::Int32, entryMove.getValueType());
        EXPECT_EQ("{si}", std::string{entryMove.getSignature()});
        EXPECT_EQ(nullptr, entryMove.getContainerSignature());
        //after move
        EXPECT_EQ(0u, entry.getSize());
        EXPECT_EQ(false, entry.getKeySet());
        EXPECT_EQ(false, entry.getValueSet());
        EXPECT_EQ(DBusArgument::ArgType::Invalid, entry.getKeyType());
        EXPECT_EQ(DBusArgument::ArgType::Invalid, entry.getValueType());
        EXPECT_EQ(nullptr, entry.getSignature());
        EXPECT_EQ(nullptr, entry.getContainerSignature());
    }

    TEST_F(DBusDictEntryTest, setKey_rawPtrArg)
    {
        DBusBasicArgument key{DBusArgument::ArgType::String};
        key.setArgValue("String Key");
        DBusDictEntry entry;
        entry.setKey(&key);
        EXPECT_EQ(true, entry.getKeySet());
        EXPECT_EQ(false, entry.getValueSet());
        EXPECT_EQ(DBusArgument::ArgType::String, entry.getKeyType());
    }

    TEST_F(DBusDictEntryTest, setValue_rawPtrArg)
    {
        DBusBasicArgument value{DBusArgument::ArgType::Int32};
        value.setArgValue(100);
        DBusDictEntry entry;
        entry.setValue(&value);
        EXPECT_EQ(true, entry.getValueSet());
        EXPECT_EQ(false, entry.getKeySet());
        EXPECT_EQ(DBusArgument::ArgType::Int32, entry.getValueType());
    }

    TEST_F(DBusDictEntryTest, setKey_smartPtrArg)
    {
        std::unique_ptr<DBusArgument> key{new DBusBasicArgument{DBusArgument::ArgType::String}};
        static_cast<DBusBasicArgument*>(key.get())->setArgValue("String Key");
        DBusDictEntry entry;
        entry.setKey(key);
        EXPECT_EQ(false, entry.getValueSet());
        EXPECT_EQ(true, entry.getKeySet());
        EXPECT_EQ(DBusArgument::ArgType::String, entry.getKeyType());
        EXPECT_EQ("{}", std::string{entry.getSignature()});
    }

    TEST_F(DBusDictEntryTest, setValue_smartPtrArg)
    {
        std::unique_ptr<DBusArgument> value{new DBusBasicArgument{DBusArgument::ArgType::Int32}};
        static_cast<DBusBasicArgument*>(value.get())->setArgValue(100);
        DBusDictEntry entry;
        entry.setValue(value);
        EXPECT_EQ(true, entry.getValueSet());
        EXPECT_EQ(false, entry.getKeySet());
        EXPECT_EQ(DBusArgument::ArgType::Int32, entry.getValueType());
        EXPECT_EQ("{}", std::string{entry.getSignature()});
    }

    TEST_F(DBusDictEntryTest, setValidEntry)
    {
        DBusBasicArgument key{DBusArgument::ArgType::String};
        DBusBasicArgument value{DBusArgument::ArgType::Int32};
        key.setArgValue("String Key");
        value.setArgValue(100);
        DBusDictEntry entry;
        entry.setKey(&key);
        entry.setValue(&value);
        EXPECT_EQ(true, entry.getKeySet());
        EXPECT_EQ(true, entry.getValueSet());
        EXPECT_EQ(DBusArgument::ArgType::String, entry.getKeyType());
        EXPECT_EQ(DBusArgument::ArgType::Int32, entry.getValueType());
        EXPECT_EQ("{si}", std::string{entry.getSignature()});
    }

    TEST_F(DBusDictEntryTest, setInvalidEntry)
    {
        DBusBasicArgument key{DBusArgument::ArgType::String};
        DBusArray value{DBusArgument::ArgType::Int32};
        key.setArgValue("String Key");
        value.addArgument(100);
        DBusDictEntry entry;
        entry.setKey(&key);
        entry.setValue(&value);
        EXPECT_EQ(true, entry.getKeySet());
        EXPECT_EQ(false, entry.getValueSet());
        EXPECT_EQ(DBusArgument::ArgType::String, entry.getKeyType());
        EXPECT_EQ(DBusArgument::ArgType::Invalid, entry.getValueType());
        EXPECT_EQ("{}", std::string{entry.getSignature()});
    }

    TEST_F(DBusDictEntryTest, addArgument)
    {
        DBusBasicArgument key{DBusArgument::ArgType::String};
        key.setArgValue("String Key");
        DBusDictEntry entry;
        EXPECT_EQ(true, entry.addArgument(&key));
        EXPECT_EQ(true, entry.getKeySet());
        EXPECT_EQ(false, entry.getValueSet());
        EXPECT_EQ(DBusArgument::ArgType::String, entry.getKeyType());
        EXPECT_EQ(DBusArgument::ArgType::Invalid, entry.getValueType());
        EXPECT_EQ("{}", std::string{entry.getSignature()});
    }
}
