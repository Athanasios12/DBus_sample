#ifndef DBUSMETHODREPLY_H
#define DBUSMETHODREPLY_H
#include "DBusArgument.h"
#include <string>
#include <memory>

namespace DBUS
{
    class DBusMethodReply
    {
    public:
        DBusMethodReply();
        DBusMethodReply(DBusArgument::ArgType replyReturnType);
        DBusMethodReply(const DBusMethodReply &other);
        DBusMethodReply(DBusMethodReply &&other);
        DBusMethodReply& operator=(const DBusMethodReply &other);
        DBusMethodReply& operator=(DBusMethodReply &&other);

        ~DBusMethodReply();

        bool operator==(const DBusMethodReply& other) const;

        bool processDBusMsgReply(DBusMessageIter *msgItr);
        //sink - takes dynamicly allocated pointer and takes over it ownership
        //both for smart and raw pointer argument
        bool setRetArg(std::unique_ptr<DBusArgument> &retArg);
        bool setRetArg(DBusArgument *retArg);

        bool isValid() const;
        DBusArgument* getReturn() const;
    private:
        bool m_valid;
        DBusArgument::ArgType m_returnType;
        std::unique_ptr<DBusArgument> m_return;
    };
}
#endif // DBUSMETHODREPLY_H

//Zdefiniuj move i copy contructory dla Container i Arg jako klas
// bazowych i korzystac z nich w klasach pochodnych
