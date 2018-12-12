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
        bool operator!=(const DBusStruct &other) const;

        template<typename Val>
        bool addField(ArgType type, Val value);
        bool addArgument(DBusArgument *arg);
        void setParentStruct(DBusStruct *parentStruct);
    private:
        void appendStructSignature(DBusArgument *arg);
        DBusStruct *m_parentContainer{nullptr};
    };

    template<typename Val>
    bool DBusStruct::addField(ArgType type, Val value)
    {
        bool addedNewArg = false;
        //if struct has a parent container, forbidd adding new fields, because
        //that would need dynamic update of parent container signature
        if(m_parentContainer == nullptr)
        {
            if(type != ArgType::Invalid)
            {
                //check if arg type matches value type
                std::unique_ptr<DBusArgument> arg{new DBusBasicArgument{type}};
                if(arg)
                {
                    if(static_cast<DBusBasicArgument*>(arg.get())->setArgValue(value))
                    {
                        appendStructSignature(arg.get());
                        m_subArgs.push_back(std::move(arg));
                        addedNewArg = true;
                        m_argIsInitalized = true;
                    }
                }
            }
        }
        return addedNewArg;
    }
}

#endif // DBUSSTRUCT_H
