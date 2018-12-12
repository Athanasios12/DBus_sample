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
        bool setArgValue(const char* value);
        bool setArgValue(char* value);
        bool setArgValue(DBusBasicValue value);

        template<typename T>
        bool resetArg(ArgType argType, T value);

        void* getArgValuePtr();
        bool argIsContainerType() const;
    private:
        void initializeArgValue(const DBusBasicArgument &arg);
        argValType m_arg;
    };

    template<typename T>
    bool DBusBasicArgument::setArgValue(T value)
    {
        bool argSet = false;
        if(m_argType != ArgType::Invalid)
        {
            int index = getArgTypeIndex(m_argType);
            argValType argVariant = value;
            if(static_cast<int>(argVariant.index()) == index)
            {
                m_arg =  value;
                m_argIsInitalized = true;
                argSet = true;
            }
        }
        return argSet;
    }

    template<typename T>
    bool DBusBasicArgument::resetArg(ArgType argType, T value)
    {
        bool argReset = false;
        int index = getArgTypeIndex(argType);
        if(index >= 0)
        {
            argValType argVariant = value;
            if(static_cast<int>(argVariant.index()) == index)
            {
                m_argType = argType;
                m_arg = argVariant;
                m_signature = getArgTypeSignature(argType);
                argReset = true;
                m_argIsInitalized = true;
            }
        }
        return argReset;
    }
}

#endif // DBUSBASICARGUMENT_H
