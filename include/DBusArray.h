#ifndef DBUSARRAY_H
#define DBUSARRAY_H
#include "DBusContainerArg.h"
#include "DBusBasicArgument.h"
#include "DBusArgumentFactory.h"
#include <vector>
#include <memory>
//Array must hold a complete type so it can have basic types and structs, dictionaries with the same content types - ai, a((i)), a
namespace DBUS
{
    class DBusArray : public DBusContainerArg
    {
    public:
        DBusArray();
        DBusArray(ArgType argType);
        DBusArray(const DBusArray &other);
        DBusArray(DBusArray &&other);
        DBusArray& operator=(const DBusArray &other);
        DBusArray& operator=(DBusArray &&other);
        virtual ~DBusArray();

        bool operator==(const DBusArray &other) const;

        template<typename Arg>
        bool addArgument(Arg newElem);
        bool addArgument(DBusArgument *arg);
        bool setElementsType(ArgType argType);
        const char* getContainerSignature() const final;
    private:
        bool containedSignatureMatch(DBusArgument *arg);
        ArgType m_elemType;
    };

    template<typename Arg>
    bool DBusArray::addArgument(Arg newElem)
    {
        bool addedNewArg = false;
        if(m_elemType != ArgType::Invalid)
        {
            //check if arg type match
            argValType argVariant = newElem;
            if(static_cast<int>(argVariant.index()) == getArgTypeIndex(m_elemType))
            {
                //check if contained signature match
                std::unique_ptr<DBusArgument> arg{new DBusBasicArgument{m_elemType}};
                if(arg)
                {
                    if(containedSignatureMatch(arg.get()))
                    {
                        static_cast<DBusBasicArgument*>(arg.get())->setArgValue(newElem);
                        m_subArgs.push_back(std::move(arg));
                    }
                }
            }
        }
        return addedNewArg;
    }
}

#endif // DBUSARRAY_H
