#include "DBusInterface.h"

#include "DBusMethod.h"
#include "DBusArray.h"
#include <variant>
#include <algorithm>
#include "DBusArgumentFactory.h"

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

    bool DBusInterface::appendArg(DBusArgument *arg, DBusMessageIter *iterator)
    {
        bool argAdded = false;
        //don't forget defining this for array dict. dict entry strict and variant
        if(arg && iterator)
        {
            if(!arg->argIsContainerType())
            {
                auto retValPtr = static_cast<DBusBasicArgument*>(arg)->getArgValuePtr();
                fprintf(stderr, "\n%s\n", (const char*)retValPtr);
                if(retValPtr)
                {
                    dbus_message_iter_append_basic(iterator, static_cast<int>(arg->getArgType()), retValPtr);
                    argAdded = true;
                }
            }
            else
            {
                if(arg->getArgType() != DBusArgument::ArgType::Invalid)
                {
                    DBusMessageIter subIter;
                    DBusContainerArg *cArg = static_cast<DBusContainerArg*>(arg); // wrong cast of dict entry - not child of dbuscontainer arg
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

    bool DBusInterface::extractDBusBasicArg(DBusBasicArgument &bArg, DBusMessageIter *argIter)
    {
        bool argMatched = false;
        if(bArg.getArgType() != DBusArgument::ArgType::Invalid)
        {
            dbus_message_iter_get_basic(argIter, bArg.getArgValuePtr());
            argMatched = true;
        }
        return argMatched;
    }

    bool DBusInterface::processDBusContainerArg(DBusContainerArg *cArg, DBusMessageIter *iterator)
    {
        bool containerProcessed = true;
        if(cArg && iterator)
        {
            size_t numOfElements = dbus_message_iter_get_element_count(iterator);
            if(numOfElements > 0)
            {
                size_t elemNum = 0;
                auto type = dbus_message_iter_get_arg_type(iterator);
                while(type != DBusArgument::ArgType::Invalid)
                {
                    auto subArg = DBusArgumentFactory::getArgument(static_cast<DBusArgument::ArgType>(type));
                    if(subArg.get())
                    {
                        if(!subArg->argIsContainerType())
                        {
                            DBusBasicArgument *bPtr = static_cast<DBusBasicArgument*>(subArg.get());
                            if(extractDBusBasicArg(*bPtr, iterator))
                            {
                                cArg->addArgument(subArg.release());
                            }
                        }
                        else
                        {
                            DBusMessageIter subIterator;
                            dbus_message_iter_recurse(iterator, &subIterator);
                            processDBusContainerArg(static_cast<DBusContainerArg*>(subArg.get()), &subIterator);
                        }
                        ++elemNum;
                    }
                    dbus_message_iter_next(iterator);
                    type = dbus_message_iter_get_arg_type(iterator);
                }
                if(elemNum != numOfElements)
                {
                    containerProcessed = false;
                }
            }
        }
        return containerProcessed;
    }

    bool DBusInterface::extractDBusMessageArgData(DBusArgument *arg, DBusMessageIter *argIter)
    {
        bool argExtracted = false;
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
                    DBusMessageIter subIter;
                    dbus_message_iter_recurse(argIter, &subIter);
                    argExtracted = processDBusContainerArg(static_cast<DBusContainerArg*>(arg), &subIter);
                }                
            }
        }
        return argExtracted;
    }
}
