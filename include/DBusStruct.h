#ifndef DBUSSTRUCT_H
#define DBUSSTRUCT_H
#include "DBusContainerArg.h"
#include "DBusBasicArgument.h"
#include "DBusArgumentFactory.h"
#include <memory>
#include <vector>

namespace DBUS
{
    class DBusStruct : public DBusContainerArg
    {
    public:
        DBusStruct();
        DBusStruct(const DBusStruct &other);
        DBusStruct(DBusStruct &&other);
        DBusStruct& operator=(const DBusStruct &other);
        DBusStruct& operator=(DBusStruct &&other);
        virtual ~DBusStruct();

        bool operator==(const DBusStruct &other) const;

        template<typename Val>
        bool addField(ArgType type, Val value);
        bool addArgument(DBusArgument *arg);
    private:
        void appendStructSignature(DBusArgument *arg);
    };

    template<typename Val>
    bool DBusStruct::addField(ArgType type, Val value)
    {
        bool addedNewArg = false;
        if(type != ArgType::Invalid)
        {
            //check if arg type matches value type
            argValType argVariant = value;
            if(static_cast<int>(argVariant.index()) == getArgTypeIndex(type))
            {
                std::unique_ptr<DBusArgument> arg{new DBusBasicArgument{type}};
                if(arg)
                {
                    appendStructSignature(arg.get());
                    static_cast<DBusBasicArgument*>(arg.get())->setArgValue(value);
                    m_subArgs.push_back(std::move(arg));
                    addedNewArg = true;
                    m_argIsInitalized = true;
                }
            }
        }
        return addedNewArg;
    }
}

#endif // DBUSSTRUCT_H
