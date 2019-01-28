#include "gtest/gtest.h"
#include "DBusMethodReply.h"
#include "DBusArgumentPack.h"
#include "DBusBasicArgument.h"

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
        DBusMethodReply reply{};
        EXPECT_EQ(nullptr, reply.getReturn());
        EXPECT_EQ(false, reply.isValid());
        EXPECT_EQ(DBusArgument::ArgType::Invalid, reply.getReturnType());
    }

    TEST_F(DBusMethodReplyTest, ctor)
    {
        DBusMethodReply reply{DBusArgument::ArgType::String};
        EXPECT_EQ(true, reply.getReturn() != nullptr);
        EXPECT_EQ(false, reply.isValid());
        EXPECT_EQ(DBusArgument::ArgType::String, reply.getReturnType());
    }

    TEST_F(DBusMethodReplyTest, processDBusMsgReply_invalidReply_RetArgNotInitialized)
    {
        //add input arguments
        DBusArgumentPack argPack{"Test", "/test/signal/Object", "test.signal.Type"};
        auto stringArg = static_cast<DBusBasicArgument*>(argPack.addNewArgument(DBusArgument::ArgType::String));
        //create reply msg
        DBusMessage *replyMsg = dbus_message_new_signal("/test/signal/Object","test.signal.Type","Test");
        DBusMessageIter txIter;
        dbus_message_iter_init_append(replyMsg, &txIter);
        argPack.appendArgsToDBusMsg(&txIter);
        //extract reply from dbus msg
        DBusMessageIter rxIter;
        dbus_message_iter_init(replyMsg, &rxIter);
        DBusMethodReply reply{DBusArgument::ArgType::String};
        reply.processDBusMsgReply(&rxIter);
        auto retArg = static_cast<DBusBasicArgument*>(reply.getReturn());
        EXPECT_EQ(false, retArg->isArgInitalized());
        EXPECT_EQ(false, reply.isValid());
    }

    TEST_F(DBusMethodReplyTest, processDBusMsgReply_replyIsValid)
    {
        //add input arguments
        DBusArgumentPack argPack{"Test", "/test/signal/Object", "test.signal.Type"};
        auto stringArg = static_cast<DBusBasicArgument*>(argPack.addNewArgument(DBusArgument::ArgType::String));
        stringArg->setArgValue("String reply");
        //create reply msg
        DBusMessage *replyMsg = dbus_message_new_signal("/test/signal/Object","test.signal.Type","Test");
        DBusMessageIter txIter;
        dbus_message_iter_init_append(replyMsg, &txIter);
        argPack.appendArgsToDBusMsg(&txIter);
        //extract reply from dbus msg
        DBusMessageIter rxIter;
        dbus_message_iter_init(replyMsg, &rxIter);
        DBusMethodReply reply{DBusArgument::ArgType::String};
        reply.processDBusMsgReply(&rxIter);
        auto retArg = static_cast<DBusBasicArgument*>(reply.getReturn());
        EXPECT_EQ(true, retArg->isArgInitalized());
        EXPECT_EQ(true, reply.isValid());
        EXPECT_EQ(*stringArg, *retArg);
    }

    TEST_F(DBusMethodReplyTest, setRetArg_ReturnTypeIsWrong)
    {
        DBusMethodReply reply{DBusArgument::ArgType::String};
        DBusBasicArgument intArg{DBusArgument::ArgType::Int32};
        intArg.setArgValue(100);
        EXPECT_EQ(false, reply.setRetArg(&intArg));
        EXPECT_EQ(false, reply.isValid());
    }

    TEST_F(DBusMethodReplyTest, setRetArg_argIsNull)
    {
        DBusMethodReply reply{DBusArgument::ArgType::String};
        EXPECT_EQ(false, reply.setRetArg(nullptr));
        EXPECT_EQ(false, reply.isValid());
    }

    TEST_F(DBusMethodReplyTest, setRetArg_success)
    {
        DBusMethodReply reply{DBusArgument::ArgType::Int32};
        DBusBasicArgument intArg{DBusArgument::ArgType::Int32};
        intArg.setArgValue(100);
        EXPECT_EQ(true, reply.setRetArg(&intArg));
        EXPECT_EQ(true, reply.isValid());
    }

    TEST_F(DBusMethodReplyTest, equalOperator_repliesAreTheSame)
    {
        DBusMethodReply reply{DBusArgument::ArgType::Int32};
        DBusBasicArgument intArg{DBusArgument::ArgType::Int32};
        intArg.setArgValue(100);
        reply.setRetArg(&intArg);
        auto replyCopy{reply};
        EXPECT_EQ(true, replyCopy == reply);
    }

    TEST_F(DBusMethodReplyTest, equalOperator_repliesAreDifferent)
    {
        DBusMethodReply reply{DBusArgument::ArgType::String};
        DBusBasicArgument intArg{DBusArgument::ArgType::Int32};
        intArg.setArgValue(100);
        DBusBasicArgument boolArg{DBusArgument::ArgType::Bool};
        boolArg.setArgValue(true);
        DBusMethodReply replyOther{DBusArgument::ArgType::Bool};
        replyOther.setRetArg(&boolArg);
        EXPECT_EQ(false, replyOther == reply);
    }

    TEST_F(DBusMethodReplyTest, copyCtor)
    {
        DBusMethodReply reply{DBusArgument::ArgType::Int32};
        DBusBasicArgument intArg{DBusArgument::ArgType::Int32};
        intArg.setArgValue(100);
        reply.setRetArg(&intArg);
        auto replyCopy{reply};
        auto retArg = static_cast<DBusBasicArgument*>(reply.getReturn());
        auto retArgCopy = static_cast<DBusBasicArgument*>(replyCopy.getReturn());
        EXPECT_EQ(*retArg, *retArgCopy);
        EXPECT_EQ(reply.isValid(), replyCopy.isValid());
        EXPECT_EQ(reply.getReturnType(), replyCopy.getReturnType());
    }

    TEST_F(DBusMethodReplyTest, moveCtor)
    {
        DBusMethodReply reply{DBusArgument::ArgType::Int32};
        DBusBasicArgument intArg{DBusArgument::ArgType::Int32};
        intArg.setArgValue(100);
        reply.setRetArg(&intArg);
        auto replyMove{std::move(reply)};
        auto retArgMove = static_cast<DBusBasicArgument*>(replyMove.getReturn());
        EXPECT_EQ(intArg, *retArgMove);
        EXPECT_EQ(true, replyMove.isValid());
        EXPECT_EQ(DBusArgument::ArgType::Int32, replyMove.getReturnType());
        //original after move
        EXPECT_EQ(nullptr, reply.getReturn());
        EXPECT_EQ(false, reply.isValid());
        EXPECT_EQ(DBusArgument::ArgType::Invalid, reply.getReturnType());
    }

}
