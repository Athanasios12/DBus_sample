#include "DBusStruct.h"
#include "DBusArgumentFactory.h"

namespace DBUS
{
    const char STRUCT_START_CHAR = '(';
    const char STRUCT_END_CHAR = ')';

    DBusStruct::DBusStruct():
        DBusContainerArg(ArgType::Struct)
    {

    }

    DBusStruct::DBusStruct(const DBusStruct &other):
        DBusContainerArg(other)
    {

    }

    DBusStruct::DBusStruct(DBusStruct &&other):
        DBusContainerArg(std::forward<DBusStruct>(other))
    {
        if(this != &other)
        {
            m_subArgs = std::move(other.m_subArgs);
        }
    }

    DBusStruct& DBusStruct::operator=(const DBusStruct &other)
    {
        DBusContainerArg::operator=(other);
        return *this;
    }

    DBusStruct& DBusStruct::operator=(DBusStruct &&other)
    {
        DBusContainerArg::operator=(std::forward<DBusStruct>(other));
        return *this;
    }

    DBusStruct::~DBusStruct()
    {

    }

    bool DBusStruct::operator==(const DBusStruct &other) const
    {
        bool equal = false;
        if(m_subArgs.size() == other.m_subArgs.size())
        {
            bool allEqual = true;
            for(size_t i = 0; i < m_subArgs.size(); i++)
            {
                if(m_subArgs[i] != other.m_subArgs[i])
                {
                    allEqual = false;
                    break;
                }
            }
            equal = allEqual;
        }
        return equal;
    }

    bool DBusStruct::addArgument(DBusArgument *arg)
    {
        //container of containers other than dictionary may cause problems, test that
        bool addedNewArg = false;
        if(arg)
        {
            if(arg->getArgType() != ArgType::Invalid)
            {
                auto newArg = DBusArgumentFactory::getArgCopy(arg);
                if(newArg)
                {
                    appendStructSignature(newArg.get());
                    m_subArgs.push_back(std::move(newArg));
                    addedNewArg = true;
                }
            }
        }
        return addedNewArg;
    }

    void DBusStruct::appendStructSignature(DBusArgument *arg)
    {
        if(arg)
        {
            auto structEnd = m_signature.find_last_of(STRUCT_END_CHAR);
            if(structEnd != std::string::npos)
            {
                m_signature.insert(structEnd, arg->getSignature());
            }
        }
    }
}
