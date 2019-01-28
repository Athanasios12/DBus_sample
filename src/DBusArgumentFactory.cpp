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
        case DBusArgument::ArgType::Variant:
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
        switch(arg->getArgType())
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
            argCopy.reset(new DBusBasicArgument{*(static_cast<DBusBasicArgument*>(arg))});
            break;
        case DBusArgument::ArgType::Variant:
            break;
        case DBusArgument::ArgType::Array:
            argCopy.reset(new DBusArray{*(static_cast<DBusArray*>(arg))});
            break;
        case DBusArgument::ArgType::Struct:
            argCopy.reset(new DBusStruct{*(static_cast<DBusStruct*>(arg))});
            break;
        case DBusArgument::ArgType::Dictionary:
            argCopy.reset(new DBusDictionary{*(static_cast<DBusDictionary*>(arg))});
            break;
        case DBusArgument::ArgType::Dictionary_Entry:
            argCopy.reset(new DBusDictEntry{*(static_cast<DBusDictEntry*>(arg))});
            break;
        }
        return argCopy;
    }

    bool DBusArgumentFactory::checkIfArgsEqual(DBusArgument *arg1, DBusArgument *arg2)
    {
        bool equal = arg1->getArgType() == arg2->getArgType();
        if(equal)
        {
            switch(arg1->getArgType())
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
                equal = *static_cast<DBusBasicArgument*>(arg1) == *static_cast<DBusBasicArgument*>(arg2);
                break;
            case DBusArgument::ArgType::Array:
                equal = *static_cast<DBusArray*>(arg1) == *static_cast<DBusArray*>(arg2);
                break;
            case DBusArgument::ArgType::Struct:
                equal = *static_cast<DBusStruct*>(arg1) == *static_cast<DBusStruct*>(arg2);
                break;
            case DBusArgument::ArgType::Dictionary:
                equal = *static_cast<DBusDictionary*>(arg1) == *static_cast<DBusDictionary*>(arg2);
                break;
            case DBusArgument::ArgType::Dictionary_Entry:
                equal = *static_cast<DBusDictEntry*>(arg1) == *static_cast<DBusDictEntry*>(arg2);
                break;
            default:
                equal = false;
            }
        }
        return equal;
    }


}
