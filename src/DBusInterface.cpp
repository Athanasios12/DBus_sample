#include "DBusInterface.h"
#include "DBusMethod.h"
#include "DBusArray.h"
#include <variant>
#include <algorithm>
#include "DBusArgumentFactory.h"
#include <cstring>

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
            //check if object has at least one method otherwise don't add it
            if(!object.m_methods.empty())
            {
                object.m_interfaceName = m_name;
                m_objects.push_back(object);
                addedObject = true;
            }
        }
        return addedObject;
    }

    std::string DBusInterface::getName() const
    {
        return m_name;
    }

    std::optional<DBusInterface::DBusObject> DBusInterface::getObject(const std::string &name) const
    {
        DBusObject object(name);
        auto interObject = std::find(m_objects.begin(), m_objects.end(), object);
        if(interObject != std::end(m_objects))
        {
            return *interObject;
        }
        return {};
    }

    bool DBusInterface::appendArg(DBusArgument *arg, DBusMessageIter *iterator)
    {
        bool argAdded = false;
        //don't forget defining this for array dict. dict entry strict and variant
        if(arg && iterator)
        {
            if(!arg->argIsContainerType())
            {
                void* retValPtr = static_cast<DBusBasicArgument*>(arg)->getArgValuePtr();
                if(retValPtr)
                {
                    if(arg->getArgType() != DBusArgument::ArgType::String)
                    {
                        dbus_message_iter_append_basic(iterator, static_cast<int>(arg->getArgType()), retValPtr);
                    }
                    else
                    {
                        char *string = static_cast<char*>(retValPtr);
                        dbus_message_iter_append_basic(iterator, static_cast<int>(arg->getArgType()), &string);
                    }
                    argAdded = true;
                }
            }
            else
            {
                if(arg->getArgType() != DBusArgument::ArgType::Invalid)
                {
                    DBusMessageIter subIter;
                    DBusContainerArg *cArg = static_cast<DBusContainerArg*>(arg);
                    dbus_message_iter_open_container(iterator, cArg->getArgType(), cArg->getContainerSignature(), &subIter);
                    bool allSubArgsAppended = true;
                    for(auto subArgItr = cArg->getFirstArgItr(); subArgItr != cArg->getLastArgItr(); subArgItr++)
                    {
                        if(!appendArg(subArgItr->get(), &subIter))
                        {
                            allSubArgsAppended = false;
                            break;
                        }
                    }
                    argAdded = allSubArgsAppended;
                    dbus_message_iter_close_container(iterator, &subIter);
                }
            }
        }
        return argAdded;
    }

    bool DBusInterface::checkIfInputArgIsDictionary(DBusArgument::ArgType argType, DBusMessageIter *msgItr)
    {
        bool isDictionary = false;
        std::string argSignature{dbus_message_iter_get_signature(msgItr)};
        //special case for dictionary
        if(argType == DBusArgument::ArgType::Array)
        {
            if(!argSignature.empty())
            {
                auto pos = argSignature.find('{');
                if(pos == 1)
                {
                    isDictionary = true;
                }
            }
        }
        return isDictionary;
    }

    bool DBusInterface::extractDBusBasicArg(DBusBasicArgument &bArg, DBusMessageIter *argIter)
    {
        bool argMatched = false;
        if(bArg.getArgType() != DBusArgument::ArgType::Invalid)
        {
            if(bArg.getArgType() == dbus_message_iter_get_arg_type(argIter))
            {
                DBusBasicValue value;
                dbus_message_iter_get_basic(argIter, &value);
                if(bArg.setArgValue(value))
                {
                    argMatched = true;
                }
            }
        }
        return argMatched;
    }

    bool DBusInterface::processDBusContainerArg(DBusContainerArg *cArg, DBusMessageIter *iterator)
    {
        bool containerProcessed = true;
        if(cArg && iterator)
        {
            //get element type
            DBusMessageIter elementIterator;
            dbus_message_iter_recurse(iterator, &elementIterator);
            auto type = static_cast<DBusArgument::ArgType>(dbus_message_iter_get_arg_type(&elementIterator));
            //special case for dictionary : DBus protocol registers it as ARRAY type
            if(checkIfInputArgIsDictionary(type, &elementIterator))
            {
                type = DBusArgument::ArgType::Dictionary;
            }
            while(type != DBusArgument::ArgType::Invalid)
            {
                bool argExtracted = false;

                auto subArg = DBusArgumentFactory::getArgument(static_cast<DBusArgument::ArgType>(type));
                if(subArg)
                {
                    if(!subArg->argIsContainerType())
                    {
                        DBusBasicArgument *bPtr = static_cast<DBusBasicArgument*>(subArg.get());
                        argExtracted = extractDBusBasicArg(*bPtr, &elementIterator);
                    }
                    else
                    {
                        argExtracted = processDBusContainerArg(static_cast<DBusContainerArg*>(subArg.get()), &elementIterator);
                    }

                    if(argExtracted)
                    {
                        if(!cArg->addArgument(subArg.get()))
                        {
                            argExtracted = false;
                        }

                    }
                }
                if(!argExtracted)
                {
                    containerProcessed = false;
                    break;
                }
                dbus_message_iter_next(&elementIterator);
                type = static_cast<DBusArgument::ArgType>(dbus_message_iter_get_arg_type(&elementIterator));
            }
        }
        return containerProcessed;
    }

    bool DBusInterface::extractDBusMessageArgData(DBusArgument *arg, DBusMessageIter *argIter)
    {
        bool argExtracted = false;
        if(arg && argIter)
        {
            auto argType = arg->getArgType();
            if(argType != DBusArgument::ArgType::Invalid)
            {
                if(argType == dbus_message_iter_get_arg_type(argIter))
                {
                    if(!arg->argIsContainerType())
                    {
                        argExtracted = extractDBusBasicArg(*(static_cast<DBusBasicArgument*>(arg)), argIter);
                    }
                    else
                    {
                        //container types handled separately - recursive calls
                        argExtracted = processDBusContainerArg(static_cast<DBusContainerArg*>(arg), argIter);
                    }
                }
            }
        }
        return argExtracted;
    }
}
