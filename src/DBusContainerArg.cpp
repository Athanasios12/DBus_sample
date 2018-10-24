#include "DBusContainerArg.h"
#include "DBusArgumentFactory.h"

namespace DBUS
{
    DBusContainerArg::DBusContainerArg()
    {

    }

    DBusContainerArg::DBusContainerArg(ArgType argType):
        DBusArgument(argType)
    {

    }

    DBusContainerArg::DBusContainerArg(const DBusContainerArg &other):
        DBusArgument(other)
    {
        for(auto && arg : other.m_subArgs)
        {
            if(arg)
            {
                auto argCopy = DBusArgumentFactory::getArgCopy(arg.get());
                m_subArgs.push_back(std::move(argCopy));
            }
        }
        m_containedSignature = other.m_containedSignature;
    }

    DBusContainerArg::DBusContainerArg(DBusContainerArg &&other):
        DBusArgument(std::forward<DBusContainerArg>(other))
    {
        if(this != &other)
        {
            m_subArgs = std::move(other.m_subArgs);
            m_containedSignature = std::move(other.m_containedSignature);
        }
    }

    DBusContainerArg& DBusContainerArg::operator=(const DBusContainerArg &other)
    {
        if(this != &other)
        {
            DBusArgument::operator=(other);
            for(auto && arg : other.m_subArgs)
            {
                if(arg)
                {
                    auto argCopy = DBusArgumentFactory::getArgCopy(arg.get());
                    m_subArgs.push_back(std::move(argCopy));
                }
            }
            m_containedSignature = other.m_containedSignature;
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
        }
        return *this;
    }

    DBusContainerArg::~DBusContainerArg()
    {

    }

    bool DBusContainerArg::operator==(const DBusContainerArg &other) const
    {
        //just checks if each shared pointer has the same address as other
        return m_subArgs == other.m_subArgs;
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

    std::size_t DBusContainerArg::getSize() const
    {
        return m_subArgs.size();
    }
}
