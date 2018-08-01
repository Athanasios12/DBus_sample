#include "DBusInterface.h"
#include <algorithm>

namespace DBUS
{
    DBusInterface::DBusInterface()
    {

    }

    DBusInterface::DBusInterface(const std::string& name):
        m_name(name)
    {

    }

    DBusInterface::~DBusInterface()
    {

    }

    bool DBusInterface::operator==(const DBusInterface& other) const
    {
        return (other.m_name == m_name);
    }

    bool DBusInterface::addObject(DBusInterface::DBusObject &object)
    {
        bool addedObject = false;
        if(std::find(m_objects.begin(), m_objects.end(), object) == std::end(m_objects))
        {
            object.m_interfaceName = m_name;
            m_objects.push_back(object);
            addedObject = true;
        }
        return addedObject;
    }

    std::string DBusInterface::getName() const
    {
        return m_name;
    }

    DBusInterface::DBusObject DBusInterface::getObject(const std::string &name) const
    {
        DBusObject object(name);
        auto interObject = std::find(m_objects.begin(), m_objects.end(), object);
        return *interObject;
    }

    bool DBusInterface::processDBusContainerType(DBusInterface::DBusArgument &containerArg, DBusMessageIter *iterator) const
    {
        bool isEmpty = true;
        size_t numOfElements = dbus_message_iter_get_element_count(iterator);
        if(numOfElements > 0)
        {
            isEmpty = false;
            int type = dbus_message_iter_get_arg_type(iterator);
            uint32_t i = 0;
            while(type != DBUS_TYPE_INVALID)
            {
                DBusArgument arg;
                arg.m_argType = type;
                switch(type)
                {
                case DBUS_TYPE_BYTE:
                    dbus_message_iter_get_basic(iterator, &arg.m_argVal.dByte);
                    break;
                case DBUS_TYPE_BOOLEAN:
                    dbus_message_iter_get_basic(iterator, &arg.m_argVal.dBool);
                    break;
                case DBUS_TYPE_INT16:
                    dbus_message_iter_get_basic(iterator, &arg.m_argVal.dInt16);
                    break;
                case DBUS_TYPE_UINT16:
                    dbus_message_iter_get_basic(iterator, &arg.m_argVal.dUint16);
                    break;
                case DBUS_TYPE_INT32:
                    dbus_message_iter_get_basic(iterator, &arg.m_argVal.dInt32);
                    break;
                case DBUS_TYPE_UINT32:
                    dbus_message_iter_get_basic(iterator, &arg.m_argVal.dUint32);
                    break;
                case DBUS_TYPE_INT64:
                    dbus_message_iter_get_basic(iterator, &arg.m_argVal.dInt64);
                    break;
                case DBUS_TYPE_UINT64:
                    dbus_message_iter_get_basic(iterator, &arg.m_argVal.dUint64);
                    break;
                case DBUS_TYPE_DOUBLE:
                    dbus_message_iter_get_basic(iterator, &arg.m_argVal.dDouble);
                    break;
                case DBUS_TYPE_STRING:
                    dbus_message_iter_get_basic(iterator, &arg.m_argVal.dString);
                    break;
                case DBUS_TYPE_VARIANT:
                case DBUS_TYPE_DICT_ENTRY:
                case DBUS_TYPE_ARRAY:
                case DBUS_TYPE_STRUCT:
                    DBusMessageIter subIterator;
                    dbus_message_iter_recurse(iterator, &subIterator);
                    processDBusContainerType(arg, subiterator);
                    break;
                }
                containerArg.m_argVal.dContainer.push_back(arg);
                dbus_message_iter_next(iterator);
                type = dbus_message_iter_get_arg_type(iterator);
                ++i;
            }
        }
        return isEmpty;
    }

    bool DBusInterface::appendMethodArgs(DBusInterface::DBusMethod &method, DBusMessageIter *iterator) const
    {
        //TDO
        bool processed = true;
        for(auto && arg : method.m_args)
        {
            switch(retArg.m_argType)
            {
            case DBUS_TYPE_BYTE:
                dbus_message_iter_append_basic(iterator, retArg.m_argType, &retArg.m_argVal.dByte);
                break;
            case DBUS_TYPE_BOOLEAN:
                dbus_message_iter_append_basic(iterator, retArg.m_argType, &retArg.m_argVal.dBool);
                break;
            case DBUS_TYPE_INT16:
                dbus_message_iter_append_basic(iterator, retArg.m_argType, &retArg.m_argVal.dInt16);
                break;
            case DBUS_TYPE_UINT16:
                dbus_message_iter_append_basic(iterator, retArg.m_argType, &retArg.m_argVal.dUint16);
                break;
            case DBUS_TYPE_INT32:
                dbus_message_iter_append_basic(iterator, retArg.m_argType, &retArg.m_argVal.dInt32);
                break;
            case DBUS_TYPE_UINT32:
                dbus_message_iter_append_basic(iterator, retArg.m_argType, &retArg.m_argVal.dUint32);
                break;
            case DBUS_TYPE_INT64:
                dbus_message_iter_append_basic(iterator, retArg.m_argType, &retArg.m_argVal.dInt64);
                break;
            case DBUS_TYPE_UINT64:
                dbus_message_iter_append_basic(iterator, retArg.m_argType, &retArg.m_argVal.dUint64);
                break;
            case DBUS_TYPE_DOUBLE:
                dbus_message_iter_append_basic(iterator, retArg.m_argType, &arg.m_argVal.dDouble);
                break;
            case DBUS_TYPE_STRING:
                dbus_message_iter_append_basic(iterator, retArg.m_argType, &arg.m_argVal.dString);
                break;
            case DBUS_TYPE_DICT_ENTRY:
            case DBUS_TYPE_VARIANT:
            case DBUS_TYPE_ARRAY:
            case DBUS_TYPE_STRUCT:
                DBusMessageIter subIter;
                dbus_message_iter_open_container(iterator, retArg.m_argType, NULL, &subIter);
                for(auto & arg : retArg.m_argVal.dContainer)
                {
                    processDBusReply(arg, &subIter);
                }
                dbus_message_iter_close_container(iterator, &subIter);
                break;
            default:
                processed = false;
                break;
            }
        }
        return processed;
    }

    bool DBusInterface::createDBusReply(const DBusInterface::DBusArgument &retArg, DBusMessageIter *iterator) const
    {
        bool replyCreated = true;
        switch(retArg.m_argType)
        {
        case DBUS_TYPE_BYTE:
            dbus_message_iter_append_basic(iterator, retArg.m_argType, &retArg.m_argVal.dByte);
            break;
        case DBUS_TYPE_BOOLEAN:
            dbus_message_iter_append_basic(iterator, retArg.m_argType, &retArg.m_argVal.dBool);
            break;
        case DBUS_TYPE_INT16:
            dbus_message_iter_append_basic(iterator, retArg.m_argType, &retArg.m_argVal.dInt16);
            break;
        case DBUS_TYPE_UINT16:
            dbus_message_iter_append_basic(iterator, retArg.m_argType, &retArg.m_argVal.dUint16);
            break;
        case DBUS_TYPE_INT32:
            dbus_message_iter_append_basic(iterator, retArg.m_argType, &retArg.m_argVal.dInt32);
            break;
        case DBUS_TYPE_UINT32:
            dbus_message_iter_append_basic(iterator, retArg.m_argType, &retArg.m_argVal.dUint32);
            break;
        case DBUS_TYPE_INT64:
            dbus_message_iter_append_basic(iterator, retArg.m_argType, &retArg.m_argVal.dInt64);
            break;
        case DBUS_TYPE_UINT64:
            dbus_message_iter_append_basic(iterator, retArg.m_argType, &retArg.m_argVal.dUint64);
            break;
        case DBUS_TYPE_DOUBLE:
            dbus_message_iter_append_basic(iterator, retArg.m_argType, &arg.m_argVal.dDouble);
            break;
        case DBUS_TYPE_STRING:
            dbus_message_iter_append_basic(iterator, retArg.m_argType, &arg.m_argVal.dString);
            break;
        case DBUS_TYPE_DICT_ENTRY:

        case DBUS_TYPE_VARIANT:
        case DBUS_TYPE_ARRAY:
        case DBUS_TYPE_STRUCT:
            DBusMessageIter subIter;
            dbus_message_iter_open_container(iterator, retArg.m_argType, NULL, &subIter);
            for(auto & arg : retArg.m_argVal.dContainer)
            {
                processDBusReply(arg, &subIter);
            }
            dbus_message_iter_close_container(iterator, &subIter);
            break;
        default:
            replyCreated = false;
            break;
        }
        return replyCreated;
    }

    bool DBusInterface::extractDBusMessageArgData(DBusInterface::DBusMethod &method, DBusMessageIter *argIter) const
    {
        //extract input arguments
        uint16_t numOfMatchedArgs = 0;
        for(auto &arg : method.m_args)
        {
            if(arg.m_type == dbus_message_iter_get_arg_type(argIter))
            {
                switch(arg.m_type)
                {
                case DBUS_TYPE_BYTE:
                    dbus_message_iter_get_basic(argIter, &arg.m_argVal.dByte);
                    break;
                case DBUS_TYPE_BOOLEAN:
                    dbus_message_iter_get_basic(argIter, &arg.m_argVal.dBool);
                    break;
                case DBUS_TYPE_INT16:
                    dbus_message_iter_get_basic(argIter, &arg.m_argVal.dInt16);
                    break;
                case DBUS_TYPE_UINT16:
                    dbus_message_iter_get_basic(argIter, &arg.m_argVal.dUint16);
                    break;
                case DBUS_TYPE_INT32:
                    dbus_message_iter_get_basic(argIter, &arg.m_arg.m_argVal.dInt32);
                    break;
                case DBUS_TYPE_UINT32:
                    dbus_message_iter_get_basic(argIter, &arg.m_argVal.dUint32);
                    break;
                case DBUS_TYPE_INT64:
                    dbus_message_iter_get_basic(argIter, &arg.m_argVal.dInt64);
                    break;
                case DBUS_TYPE_UINT64:
                    dbus_message_iter_get_basic(argIter, &arg.m_argVal.dUint64);
                    break;
                case DBUS_TYPE_DOUBLE:
                    dbus_message_iter_get_basic(argIter, &arg.m_argVal.dDouble);
                    break;
                case DBUS_TYPE_STRING:
                    dbus_message_iter_get_basic(argIter, &arg.m_argVal.dString);
                    break;
                case DBUS_TYPE_VARIANT:
                case DBUS_TYPE_ARRAY:
                case DBUS_TYPE_STRUCT:
                case DBUS_TYPE_DICT_ENTRY:
                    //container types handled separately - recursive calls
                    DBusMessageIter subIter;
                    dbus_message_iter_recurse(argIter, subIter);
                    DBusInterface::processDBusContainerType(arg, subIter);
                    break;
                }
                dbus_message_iter_next(argIter);
                ++numOfMatchedArgs;
            }
        }
        return (numOfMatchedArgs == method.m_args.size());
    }

    bool DBusInterface::processDBusReply(DBusInterface::DBusMethod &method, DBusMessageIter *replyIter) const
    {
        //TDO
    }
}
