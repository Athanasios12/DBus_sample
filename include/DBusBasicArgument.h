#ifndef DBUSBASICARGUMENT_H
#define DBUSBASICARGUMENT_H
#include "DBusArgument.h"
#include <optional>

namespace DBUS
{
    class DBusBasicArgument : public DBusArgument
    {
    public:

        DBusBasicArgument();
        DBusBasicArgument(ArgType argType);
        DBusBasicArgument(const DBusBasicArgument &other);
        DBusBasicArgument(DBusBasicArgument &&other);
        DBusBasicArgument& operator=(const DBusBasicArgument &other);
        DBusBasicArgument& operator=(DBusBasicArgument &&other);
        ~DBusBasicArgument();

        bool operator==(const DBusBasicArgument& other) const;

        template<typename T>
        bool setArgValue(T value);

        template<typename T>
        bool resetArg(ArgType argType, T value);

        void* getArgValuePtr();
        bool argIsContainerType() const;
    private:
        argValType m_arg;
    };

    template<typename T>
    bool DBusBasicArgument::setArgValue(T value)
    {
        bool argSet = false;
        auto index = getArgTypeIndex(m_argType);        
        auto argVariant = getSetArgVariant(value);
        if(index == static_cast<decltype(index)>(argVariant.index()))
        {
            m_arg = value;
            argSet = true;
        }
        return argSet;
    }

    template<typename T>
    bool DBusBasicArgument::resetArg(ArgType argType, T value)
    {
        bool argReset = false;
        auto index = getArgTypeIndex(argType);        
        if(index >= 0)
        {
            auto argVariant = getSetArgVariant(value);
            if(index == static_cast<decltype(index)>(argVariant.index()))
            {
                m_argType = argType;
                m_arg = argVariant;
                m_signature = getArgTypeSignature(argType);
                argReset = true;
            }
        }
        return argReset;
    }
}

#endif // DBUSBASICARGUMENT_H
