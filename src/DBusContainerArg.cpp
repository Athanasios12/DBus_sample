#include "DBusContainerArg.h"
#include "DBusArgumentFactory.h"
#include "DBusBasicArgument.h"

namespace DBUS
{
    DBusContainerArg::DBusContainerArg()
    {

    }

    DBusContainerArg::DBusContainerArg(ArgType argType):
        DBusArgument(argType)
    {
        m_containerSignature = m_signature;
    }

    DBusContainerArg::DBusContainerArg(const DBusContainerArg &other):
        DBusArgument(other)
    {
        m_containerSignature = other.m_containerSignature;
        m_containedSignature = other.m_containedSignature;
        for(auto && arg : other.m_subArgs)
        {
            if(arg)
            {
                auto argCopy = DBusArgumentFactory::getArgCopy(arg.get());
                m_subArgs.push_back(std::move(argCopy));
            }
        }
    }

    DBusContainerArg::DBusContainerArg(DBusContainerArg &&other):
        DBusArgument(std::forward<DBusContainerArg>(other))
    {
        m_subArgs = std::move(other.m_subArgs);
        m_containerSignature = std::move(other.m_containerSignature);
        m_containedSignature = std::move(other.m_containedSignature);
    }

    DBusContainerArg& DBusContainerArg::operator=(const DBusContainerArg &other)
    {
        if(this != &other)
        {
            m_containerSignature = other.m_containerSignature;
            m_containedSignature = other.m_containedSignature;
            DBusArgument::operator=(other);
            for(auto && arg : other.m_subArgs)
            {
                if(arg)
                {
                    auto argCopy = DBusArgumentFactory::getArgCopy(arg.get());
                    m_subArgs.push_back(std::move(argCopy));
                }
            }            
        }
        return *this;
    }

    DBusContainerArg& DBusContainerArg::operator=(DBusContainerArg &&other)
    {
        if(this != &other)
        {
            DBusArgument::operator=(std::forward<DBusContainerArg>(other));
            m_subArgs = std::move(other.m_subArgs);
            m_containedSignature = std::move(other.m_containedSignature);
            m_containerSignature = std::move(other.m_containerSignature);
        }
        return *this;
    }

    DBusContainerArg::~DBusContainerArg()
    {

    }

    bool DBusContainerArg::operator==(const DBusContainerArg &other) const
    {
        bool equal = false;
        if(DBusArgument::operator ==(other))
        {
            if(m_subArgs.size() == other.m_subArgs.size())
            {
                bool argEqual = true;
                for(size_t i = 0; i < m_subArgs.size(); i++)
                {
                    if(m_subArgs[i] && other.m_subArgs[i])
                    {
                        //solve casting problem, maybe add overload with DBusArgument* as fun parameter for all args
                        if(other.m_subArgs[i].get()->argIsContainerType())
                        {
                            DBusContainerArg *cArg = static_cast<DBusContainerArg*>(other.m_subArgs[i].get());
                            if(!static_cast< DBusContainerArg*>(m_subArgs[i].get())->operator==(*cArg))
                            {
                                argEqual = false;
                                break;
                            }
                        }
                        else
                        {
                            DBusBasicArgument *bArg = static_cast<DBusBasicArgument*>(other.m_subArgs[i].get());
                            if(!static_cast< DBusBasicArgument*>(m_subArgs[i].get())->operator==(*bArg))
                            {
                                argEqual = false;
                                break;
                            }
                        }
                    }
                }
                equal = argEqual;
            }
        }
        return equal;
    }

    bool DBusContainerArg::argIsContainerType() const
    {
        return true;
    }

    void DBusContainerArg::resetArgument()
    {
        DBusArgument::resetArgument();
        m_containedSignature.clear();
        m_subArgs.clear();
    }

    bool DBusContainerArg::resetContainedArgument(std::size_t pos, DBusArgument *newArg)
    {
        bool resetArg = false;
        if(newArg)
        {
            if(pos < m_subArgs.size())
            {
                m_subArgs[pos].reset(newArg);
                resetArg = true;
            }
        }
        return resetArg;
    }

    DBusArgument::ArgType DBusContainerArg::getArgType() const
    {
        return m_argType;
    }

    const char* DBusContainerArg::getContainerSignature() const
    {
        // Used to specify contained signature in dbus_message_iter_open_container()
        // default for struct, dictionary, dict entry, has to overritten by array and variant
        return nullptr;
    }

    DBusContainerArg::SubArgs::iterator DBusContainerArg::getFirstArgItr()
    {
        return m_subArgs.begin();
    }

    DBusContainerArg::SubArgs::iterator DBusContainerArg::getLastArgItr()
    {
        return m_subArgs.end();
    }

    DBusArgument *DBusContainerArg::getArgValueAt(std::size_t pos) const
    {
        DBusArgument *retVal = nullptr;
        if(pos < m_subArgs.size())
        {
            if(m_subArgs[pos])
            {
                retVal = m_subArgs[pos].get();
            }
        }
        return retVal;
    }

    std::size_t DBusContainerArg::getSize() const
    {
        return m_subArgs.size();
    }

    std::string DBusContainerArg::getContainerTypeSignature() const
    {
        return m_containerSignature;
    }

    std::string DBusContainerArg::getContainedSignature() const
    {
        return m_containedSignature;
    }

    DBusArgument::ArgType DBusContainerArg::getContainerType() const
    {
        return m_argType;
    }
}
