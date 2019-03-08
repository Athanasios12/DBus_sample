#include "DBusMethodReply.h"
#include "DBusArgumentFactory.h"
#include "DBusInterface.h"

namespace DBUS
{
    //DBUS Method Call Reply
    DBusMethodReply::DBusMethodReply():
        m_valid(false),
        m_return(nullptr)
    {

    }

    DBusMethodReply::DBusMethodReply(DBusArgument::ArgType replyReturnType):
        m_valid(false),
        m_returnType(replyReturnType)
    {
        m_return = std::move(DBusArgumentFactory::getArgument(replyReturnType));
    }

    DBusMethodReply::DBusMethodReply(const DBusMethodReply &other)
    {
        m_valid = other.m_valid;
        m_returnType = other.m_returnType;
        if(other.m_return)
        {
            m_return.reset(DBusArgumentFactory::getArgCopy(other.m_return.get()).release());
        }
        else
        {
            m_return.reset(nullptr);
        }
    }

    DBusMethodReply::DBusMethodReply(DBusMethodReply &&other)
    {
        m_valid = other.m_valid;
        m_returnType = other.m_returnType;
        other.m_returnType = DBusArgument::ArgType::Invalid;
        other.m_valid = false;
        if(other.m_return)
        {
            m_return = std::move(other.m_return);
            other.m_return.reset(nullptr);
        }
        else
        {
            m_return.reset(nullptr);
        }
    }

    DBusMethodReply& DBusMethodReply::operator=(const DBusMethodReply &other)
    {
        if(this != &other)
        {
            m_valid = other.m_valid;
            m_returnType = other.m_returnType;
            if(other.m_return)
            {
                m_return = std::move(DBusArgumentFactory::getArgCopy(other.m_return.get()));
            }
            else
            {
                m_return.reset(nullptr);
            }
        }
        return *this;
    }

    DBusMethodReply& DBusMethodReply::operator=(DBusMethodReply &&other)
    {
        if(this != &other)
        {
            m_valid = other.m_valid;
            other.m_valid = false;
            m_returnType = other.m_returnType;
            other.m_returnType = DBusArgument::ArgType::Invalid;
            if(other.m_return)
            {
                m_return = std::move(other.m_return);
                other.m_return.reset(nullptr);
            }
            else
            {
                m_return.reset(nullptr);
            }
        }
        return *this;
    }

    DBusMethodReply::~DBusMethodReply()
    {

    }

    bool DBusMethodReply::operator==(const DBusMethodReply& other) const
    {
        bool equal = true;
        equal &= other.m_returnType == m_returnType;
        equal &= other.m_valid == m_valid;
        if(equal && m_return && other.m_return)
        {
            //if both not null and other memebers the same
            equal = DBusArgumentFactory::checkIfArgsEqual(m_return.get(), other.m_return.get());
        }
        return equal;
    }

    bool DBusMethodReply::processDBusMsgReply(DBusMessageIter *msgItr)
    {
        bool msgProcessed = false;
        if(msgItr)
        {
            auto retArg = std::move(DBusArgumentFactory::getArgument(static_cast<DBusArgument::ArgType>(dbus_message_iter_get_arg_type(msgItr))));
            //get reply return from message using passed iterator
            m_valid = DBusInterface::extractDBusMessageArgData(retArg.get(), msgItr);
            if(retArg)
            {
                m_return = std::move(retArg);
                m_returnType = m_return->getArgType();
                msgProcessed = m_valid;
            }
        }
        return msgProcessed;
    }

    bool DBusMethodReply::setRetArg(std::unique_ptr<DBusArgument> &retArg)
    {
        bool argSet = false;
        if(retArg)
        {
            if(retArg->getArgType() == m_returnType)
            {
                m_return = std::move(retArg);
                m_valid = true;
                argSet = true;
            }
        }
        return argSet;
    }

    bool DBusMethodReply::setRetArg(DBusArgument *retArg)
    {
        bool argSet = false;
        if(retArg)
        {
            if(retArg->getArgType() == m_returnType)
            {
                m_return = std::move(DBusArgumentFactory::getArgCopy(retArg));
                m_valid = true;
                argSet = true;
            }
        }
        return argSet;
    }

    bool DBusMethodReply::isValid() const
    {
        return m_valid;
    }

    DBusArgument* DBusMethodReply::getReturn() const
    {
        return m_return.get();
    }

    DBusArgument::ArgType DBusMethodReply::getReturnType() const
    {
        return m_returnType;
    }
}
