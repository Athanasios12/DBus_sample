#include "gtest/gtest.h"
#include "DBusBasicArgument.h"
#include <utility>
#include <memory>

using namespace DBUS;

namespace
{
    // The fixture for testing class Foo.
    class DBusBasicArgumentTest : public ::testing::Test
    {
    protected:
          // You can remove any or all of the following functions if its body
          // is empty.

          DBusBasicArgumentTest()
          {
            // You can do set-up work for each test here.
          }

          virtual ~DBusBasicArgumentTest()
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

    TEST_F(DBusBasicArgumentTest, defaultCtor)
    {
        DBusBasicArgument bArg;
        EXPECT_EQ(false, bArg.argIsContainerType());
        EXPECT_EQ(DBusArgument::ArgType::Invalid, bArg.getArgType());
        EXPECT_EQ(nullptr, bArg.getArgValuePtr());
        EXPECT_EQ(nullptr, bArg.getSignature());
    }

    TEST_F(DBusBasicArgumentTest, ctor)
    {
        DBusBasicArgument bArg{DBusArgument::ArgType::String};
        EXPECT_EQ(false, bArg.argIsContainerType());
        EXPECT_EQ(DBusArgument::ArgType::String, bArg.getArgType());
        EXPECT_EQ(nullptr, bArg.getArgValuePtr());
        EXPECT_EQ(DBUS_TYPE_STRING_AS_STRING, std::string{bArg.getSignature()});
    }    

    TEST_F(DBusBasicArgumentTest, setArgValue_UInt16)
    {
        DBusBasicArgument bArg{DBusArgument::ArgType::UInt16};
        dbus_uint16_t uint16_val = 100;

        EXPECT_EQ(true, bArg.setArgValue<dbus_uint16_t>(uint16_val));

        void* retVal = bArg.getArgValuePtr();
        EXPECT_EQ(true, bArg.getArgValuePtr() != nullptr);
        EXPECT_EQ(uint16_val, *(static_cast<dbus_uint16_t*>(retVal)));
    }

    TEST_F(DBusBasicArgumentTest, setArgValue_UInt32)
    {
        DBusBasicArgument bArg{DBusArgument::ArgType::UInt32};
        dbus_uint32_t uint32_val = 100;

        EXPECT_EQ(true, bArg.setArgValue<dbus_uint32_t>(uint32_val));

        void* retVal = bArg.getArgValuePtr();
        EXPECT_EQ(true, bArg.getArgValuePtr() != nullptr);
        EXPECT_EQ(uint32_val, *(static_cast<dbus_uint32_t*>(retVal)));
    }

    TEST_F(DBusBasicArgumentTest, setArgValue_UInt64)
    {
        DBusBasicArgument bArg{DBusArgument::ArgType::UInt64};
        dbus_uint64_t uint64_val = 100;

        EXPECT_EQ(true, bArg.setArgValue<dbus_uint64_t>(uint64_val));

        void* retVal = bArg.getArgValuePtr();
        EXPECT_EQ(true, bArg.getArgValuePtr() != nullptr);
        EXPECT_EQ(uint64_val, *(static_cast<dbus_uint64_t*>(retVal)));
    }

    TEST_F(DBusBasicArgumentTest, setArgValue_Int16)
    {
        DBusBasicArgument bArg{DBusArgument::ArgType::Int16};
        dbus_int16_t int16_val = -100;

        EXPECT_EQ(true, bArg.setArgValue<dbus_int16_t>(int16_val));

        void* retVal = bArg.getArgValuePtr();
        EXPECT_EQ(true, bArg.getArgValuePtr() != nullptr);
        EXPECT_EQ(int16_val, *(static_cast<dbus_int16_t*>(retVal)));
    }

    TEST_F(DBusBasicArgumentTest, setArgValue_Int32)
    {
        DBusBasicArgument bArg{DBusArgument::ArgType::Int32};
        dbus_int32_t int32_val = -100;

        EXPECT_EQ(true, bArg.setArgValue<dbus_int32_t>(int32_val));

        void* retVal = bArg.getArgValuePtr();
        EXPECT_EQ(true, bArg.getArgValuePtr() != nullptr);
        EXPECT_EQ(int32_val, *(static_cast<dbus_int32_t*>(retVal)));
    }

    TEST_F(DBusBasicArgumentTest, setArgValue_Int64)
    {
        DBusBasicArgument bArg{DBusArgument::ArgType::Int64};
        dbus_int64_t int64_val = -100;

        EXPECT_EQ(true, bArg.setArgValue<dbus_int64_t>(int64_val));

        void* retVal = bArg.getArgValuePtr();
        EXPECT_EQ(true, bArg.getArgValuePtr() != nullptr);
        EXPECT_EQ(int64_val, *(static_cast<dbus_int64_t*>(retVal)));
    }

    TEST_F(DBusBasicArgumentTest, setArgValue_Double)
    {
        DBusBasicArgument bArg{DBusArgument::ArgType::Double};
        double double_val = -100.1;

        EXPECT_EQ(true, bArg.setArgValue<double>(double_val));

        void* retVal = bArg.getArgValuePtr();
        EXPECT_EQ(true, bArg.getArgValuePtr() != nullptr);
        EXPECT_EQ(double_val, *(static_cast<double*>(retVal)));
    }

    TEST_F(DBusBasicArgumentTest, setArgValue_Bool)
    {
        DBusBasicArgument bArg{DBusArgument::ArgType::Bool};
        dbus_bool_t bool_val = true;

        EXPECT_EQ(true, bArg.setArgValue(bool_val));

        void* retVal = bArg.getArgValuePtr();
        EXPECT_EQ(true, bArg.getArgValuePtr() != nullptr);
        EXPECT_EQ(bool_val, *(static_cast<dbus_bool_t*>(retVal)));
    }

    TEST_F(DBusBasicArgumentTest, setArgValue_Byte)
    {
        DBusBasicArgument bArg{DBusArgument::ArgType::Byte};
        uint8_t byte_val = true;

        EXPECT_EQ(true, bArg.setArgValue<uint8_t>(byte_val));

        void* retVal = bArg.getArgValuePtr();
        EXPECT_EQ(true, bArg.getArgValuePtr() != nullptr);
        EXPECT_EQ(byte_val, *(static_cast<uint8_t*>(retVal)));
    }

    TEST_F(DBusBasicArgumentTest, setArgValue_String)
    {
        DBusBasicArgument bArg{DBusArgument::ArgType::String};
        const char *cstr = "Hello";

        EXPECT_EQ(true, bArg.setArgValue(cstr));

        void* retVal = bArg.getArgValuePtr();
        EXPECT_EQ(true, bArg.getArgValuePtr() != nullptr);
        EXPECT_EQ(true, strcmp(cstr, static_cast<char*>(retVal)) == 0);
    }

    TEST_F(DBusBasicArgumentTest, copyCtor)
    {
        DBusBasicArgument bArg{DBusArgument::ArgType::String};
        const char *cstr = "Hello";
        EXPECT_EQ(true, bArg.setArgValue(cstr));
        DBusBasicArgument bArgCopy{bArg};
        //original
        EXPECT_EQ(DBusArgument::ArgType::String, bArg.getArgType());
        EXPECT_EQ(true, strcmp(cstr, static_cast<char*>(bArg.getArgValuePtr())) == 0);
        EXPECT_EQ(DBUS_TYPE_STRING_AS_STRING, std::string{bArg.getSignature()});
        //copy
        EXPECT_EQ(bArgCopy.getArgType(), bArg.getArgType());
        EXPECT_EQ(true, strcmp(static_cast<char*>(bArg.getArgValuePtr()),
                  static_cast<char*>(bArgCopy.getArgValuePtr())) == 0);
        EXPECT_EQ(std::string{bArg.getSignature()}, std::string{bArgCopy.getSignature()});
    }

    TEST_F(DBusBasicArgumentTest, moveCtor)
    {
        DBusBasicArgument bArg{DBusArgument::ArgType::String};
        const char *cstr = "Hello";
        EXPECT_EQ(true, bArg.setArgValue(cstr));
        DBusBasicArgument bArgMove{std::move(bArg)};
        //original
        EXPECT_EQ(DBusArgument::ArgType::Invalid, bArg.getArgType());
        EXPECT_EQ(nullptr, bArg.getArgValuePtr());
        EXPECT_EQ(nullptr, bArg.getSignature());
        //move
        EXPECT_EQ(DBusArgument::ArgType::String, bArgMove.getArgType());
        EXPECT_EQ(true, strcmp(cstr, static_cast<char*>(bArgMove.getArgValuePtr())) == 0);
        EXPECT_EQ(DBUS_TYPE_STRING_AS_STRING, std::string{bArgMove.getSignature()});
    }
}
