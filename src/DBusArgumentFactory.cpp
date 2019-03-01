#include "DBusArgumentFactory.h"
#include "DBusArray.h"
#include "DBusBasicArgument.h"
#include "DBusDictionary.h"
#include "DBusStruct.h"
//Think about handling Variant type
namespace DBUS
{

    std::unique_ptr<DBusArgument> DBusArgumentFactory::getArgument(DBusArgument::ArgType argType)
    {
        std::unique_ptr<DBusArgument> arg{nullptr};
        switch(argType)
        {
        case DBusArgument::ArgType::Byte:
        case DBusArgument::ArgType::Bool:
        case DBusArgument::ArgType::Int16:
        case DBusArgument::ArgType::UInt16:
        case DBusArgument::ArgType::Int32:
        case DBusArgument::ArgType::UInt32:
        case DBusArgument::ArgType::Int64:
        case DBusArgument::ArgType::UInt64:
        case DBusArgument::ArgType::Double:
        case DBusArgument::ArgType::String:
            arg.reset(new DBusBasicArgument{argType});
            break;
        case DBusArgument::ArgType::Array:
            arg.reset(new DBusArray{});
            break;
        case DBusArgument::ArgType::Struct:
            arg.reset(new DBusStruct{});
            break;
        case DBusArgument::ArgType::Dictionary:
            arg.reset(new DBusDictionary{});
            break;
        case DBusArgument::ArgType::Dictionary_Entry:
            arg.reset(new DBusDictEntry{});
            break;
        }
        return arg;
    }

    std::unique_ptr<DBusArgument> DBusArgumentFactory::getArgCopy(DBusArgument *arg)
    {        
        std::unique_ptr<DBusArgument> argCopy{nullptr};
        if(arg)
        {
            if(!arg->argIsContainerType())
            {
                argCopy.reset(new DBusBasicArgument{*(static_cast<DBusBasicArgument*>(arg))});
            }
            else
            {
                DBusContainerArg *cArg = static_cast<DBusContainerArg*>(arg);
                switch(cArg->getContainerType())
                {
                case DBusArgument::ArgType::Array:
                    argCopy.reset(new DBusArray{*(static_cast<DBusArray*>(cArg))});
                    break;
                case DBusArgument::ArgType::Struct:
                    argCopy.reset(new DBusStruct{*(static_cast<DBusStruct*>(cArg))});
                    break;
                case DBusArgument::ArgType::Dictionary:
                    argCopy.reset(new DBusDictionary{*(static_cast<DBusDictionary*>(cArg))});
                    break;
                case DBusArgument::ArgType::Dictionary_Entry:
                    argCopy.reset(new DBusDictEntry{*(static_cast<DBusDictEntry*>(cArg))});
                    break;
                }
            }
        }
        return argCopy;
    }

    bool DBusArgumentFactory::checkIfArgsEqual(const DBusArgument *arg1, const DBusArgument *arg2)
    {
        bool equal = false;
        if(arg1 && arg2)
        {
            if(arg1->getArgType() && arg2->getArgType())
            {
                if(!arg1->argIsContainerType())
                {
                    equal = *static_cast<const DBusBasicArgument*>(arg1) == *static_cast<const DBusBasicArgument*>(arg2);
                }
                else
                {
                    auto *cArg1 = static_cast<const DBusContainerArg*>(arg1);
                    auto *cArg2 = static_cast<const DBusContainerArg*>(arg2);
                    if(cArg1->getContainerType() == cArg2->getContainerType())
                    {
                        switch(cArg1->getContainerType())
                        {
                        case DBusArgument::ArgType::Array:
                            equal = *static_cast<const DBusArray*>(cArg1) == *static_cast<const DBusArray*>(cArg2);
                            break;
                        case DBusArgument::ArgType::Struct:
                            equal = *static_cast<const DBusStruct*>(cArg1) == *static_cast<const DBusStruct*>(cArg2);
                            break;
                        case DBusArgument::ArgType::Dictionary:
                            equal = *static_cast<const DBusDictionary*>(cArg1) == *static_cast<const DBusDictionary*>(cArg2);
                            break;
                        case DBusArgument::ArgType::Dictionary_Entry:
                            equal = *static_cast<const DBusDictEntry*>(cArg1) == *static_cast<const DBusDictEntry*>(cArg2);
                            break;
                        }
                    }
                }
            }
        }
        return equal;
    }


}
