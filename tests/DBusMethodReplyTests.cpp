#include "gtest/gtest.h"
#include "DBusMethodReply.h"

using namespace DBUS;
namespace
{
    // The fixture for testing class Foo.
    class DBusMethodReplyTest : public ::testing::Test
    {
        protected:
          // You can remove any or all of the following functions if its body
          // is empty.

          DBusMethodReplyTest()
          {
            // You can do set-up work for each test here.
          }

          virtual ~DBusMethodReplyTest()
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

    TEST_F(DBusMethodReplyTest, defaultCtor)
    {

    }

    TEST_F(DBusMethodReplyTest, ctor)
    {

    }

    TEST_F(DBusMethodReplyTest, processDBusMsgReply_invalidReply)
    {

    }

    TEST_F(DBusMethodReplyTest, processDBusMsgReply_replyIsValid)
    {

    }

    TEST_F(DBusMethodReplyTest, setRetArg_ReturnTypeIsWrong)
    {

    }

    TEST_F(DBusMethodReplyTest, setRetArg_argIsNull)
    {

    }

    TEST_F(DBusMethodReplyTest, copyCtor)
    {

    }

    TEST_F(DBusMethodReplyTest, moveCtor)
    {

    }

}
