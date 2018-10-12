#include "DBusServer.h"
#include "DBusBasicArgument.h"
#include "DBusArgumentFactory.h"
#include <utility>
#include <mutex>

namespace
{
    std::mutex m_rxThread_Mutex;
    const uint16_t POLLING_PERIOD = 200; //ms
}

namespace DBUS
{
    DBusServer::DBusServer():
        BusConnection(),
        m_listening(false),
        m_runThread(false)
    {

    }

    DBusServer::DBusServer(const std::string &busName, DBusBusType busType):
        BusConnection(busName, busType),
        m_listening(false),
        m_runThread(false)
    {

    }

    DBusServer::~DBusServer()
    {
        disconnect();
    }

    DBusServer::DBusServer(DBusServer&& other)
    {
        if(this != &other)
        {
            other.disconnect();
            BusConnection::operator=(std::move(other));
        }
    }

    DBusServer &DBusServer::operator=(DBusServer&& other)
    {
        if(this != &other)
        {
            disconnect();
            other.disconnect();
            BusConnection::operator=(std::move(other));
        }
        return *this;
    }

    bool DBusServer::connect()
    {
        if(BusConnection::connect())
        {
            if(!m_rxThread.joinable())
            {
                m_runThread = true;
                m_rxThread = std::thread(&DBUS::DBusServer::pollForMsgs, this);
                m_listening = true;
            }
        }
        return (isConnected() && m_listening);
    }

    bool DBusServer::disconnect()
    {
        if(m_rxThread.joinable())
        {
            m_rxThread_Mutex.lock();
            m_runThread = false;
            m_rxThread_Mutex.unlock();
            m_rxThread.join();
            m_listening = false;
        }
        BusConnection::disconnect();
        return !(isConnected() && m_listening);
    }

    bool DBusServer::checkLastMethodCall(const std::string& clientBusName, const std::string& methodName) const
    {
        bool methodCalled = false;
        if(m_lastMethodCall.first == clientBusName && m_lastMethodCall.second == methodName)
        {
            methodCalled = true;
        }
        return methodCalled;
    }

    void DBusServer::pollForMsgs()
    {
        bool runPolling = true;
        while(runPolling)
        {
            m_rxThread_Mutex.lock();
            runPolling = m_runThread;
            if(runPolling)
            {
                //process incoming messages
                dbus_connection_read_write_dispatch (m_connection, 0);
                DBusMessage *message = dbus_connection_pop_message (m_connection);
                if(message)
                {
                    processMethodCall(message);
                }
            }
            m_rxThread_Mutex.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(POLLING_PERIOD));
        }
    }



    bool DBusServer::processMethodCall(DBusMessage *msg)
    {
        bool methodProcessed = false;
        //search server interfaces for called method
        for(auto && interface : m_interfaceList)
        {
            for(auto && object : interface.m_objects)
            {
                for(auto && method : object.m_methods)
                {
                    if (dbus_message_is_method_call(msg, interface.getName().c_str(), method.getName().c_str()))
                    {
                        //extract input arguments
                        DBusMessageIter argIter;
                        dbus_message_iter_init(msg, &argIter);
                        //extract input arguments
                        if(method.extractMsgInputArguments(&argIter))
                        {
                            //get Client bus name - should be last element of methods args
                            auto clientBusName = DBusArgumentFactory::getArgument(DBusArgument::ArgType::String);
                            if(clientBusName->getArgType() == dbus_message_iter_get_arg_type(&argIter))
                            {
                                if(DBusInterface::extractDBusMessageArgData(clientBusName.get(), &argIter))
                                {
                                    std::string clientName{static_cast<const char*>(static_cast<DBusBasicArgument*>(clientBusName.get())->getArgValuePtr())};
                                    m_lastMethodCall = std::make_pair(clientName, method.getName());
                                    //all arguments extracted, call binding
                                    DBusMethodReply reply = method.callBinding();
                                    //reply to method call if reply requested
                                    if(!dbus_message_get_no_reply(msg))
                                    {
                                        DBusMessage *replyMsg = nullptr;
                                        if(reply.isValid())
                                        {
                                            replyMsg = dbus_message_new_method_return(msg);
                                            if(replyMsg)
                                            {
                                                //create and initialize reply msg iterator
                                                DBusMessageIter replyIter;
                                                dbus_message_iter_init_append(replyMsg, &replyIter);
                                                DBusInterface::appendArg(reply.getReturn(), &replyIter);
                                                //send reply
                                                dbus_connection_send(m_connection, replyMsg, NULL);
                                                methodProcessed = true;
                                            }
                                        }
                                        else
                                        {
                                            std::string errorMsg = std::string("Error in input to method ") + method.getName();
                                            DBusMessage *dbus_error_msg = dbus_message_new_error(msg, DBUS_ERROR_FAILED, errorMsg.c_str());
                                            if (dbus_error_msg)
                                            {
                                                dbus_connection_send(m_connection, dbus_error_msg, NULL);
                                            }
                                            dbus_message_unref(dbus_error_msg);
                                        }
                                        dbus_message_unref(replyMsg);
                                    }
                                }
                            }

                        }
                        break;
                    }
                }
            }
        }
        return methodProcessed;
    }
}

