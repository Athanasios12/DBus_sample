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
        if(this != &other)
        {
            m_valid = other.m_valid;
            if(other.m_return)
            {
                m_return.reset(DBusArgumentFactory::getArgCopy(other.m_return.get()).release());
            }
            else
            {
                m_return.reset(nullptr);
            }
        }
    }

    DBusMethodReply::DBusMethodReply(DBusMethodReply &&other)
    {
        if(this != &other)
        {
            m_valid = other.m_valid;
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
    }

    DBusMethodReply& DBusMethodReply::operator=(const DBusMethodReply &other)
    {
        if(this != &other)
        {
            m_valid = other.m_valid;
            if(other.m_return)
            {
                m_return.reset(DBusArgumentFactory::getArgCopy(other.m_return.get()).release());
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
        return (other.m_return.get() == m_return.get());
    }

    bool DBusMethodReply::processDBusMsgReply(DBusMessageIter *msgItr)
    {
        if(m_return)
        {
            //get reply return from message using passed iterator
            m_valid = DBusInterface::extractDBusMessageArgData(m_return.get(), msgItr);
        }
        return m_valid;
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
                m_return.reset(retArg);
                m_valid = true;
                argSet = true;
                retArg = nullptr;
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
