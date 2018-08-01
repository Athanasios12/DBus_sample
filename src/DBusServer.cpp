#include "DBusServer.h"
#include <utility>
#include <mutex>

namespace
{
    std::mutex m_rxThread_Mutex;
    bool m_runThread;
    const uint16_t POLLING_PERIOD = 200; //ms
}

namespace DBUS
{
    DBusServer::DBusServer():
        BusConnection(),
        m_runThread(false)
    {

    }

    DBusServer::DBusServer(const std::string &busName, DBusBusType busType):
        BusConnection(busName, busType),
        m_runThread(false)
    {

    }

    DBusServer::~DBusServer()
    {
        disconnect();
    }

    DBusServer::DBusServer(DBusServer&& other):
    {
        if(this != &other)
        {
            disconnect();
            other.disconnect();
            BusConnection(static_cast<BusConnection&&>(other));
        }
    }

    DBusServer &DBusServer::operator=(DBusServer&& other)
    {
        DBusServer& retVal = static_cast<DBusServer&>(BusConnection::operator=(static_cast<BusConnection&&>(other)));
        return retVal;
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
        return m_connected && m_listening;
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
        return !(m_connected && m_listening);
    }

    bool DBusServer::checkLastMethodCall(const std::string& clientBusName, const DBusInterface::DBusMethod& method) const
    {
        bool methodCalled = false;
        if(m_lastMethodCall.first == clientBusName && m_lastMethodCall.second == method)
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
                dbus_connection_read_write_dispatch (conn, 0);
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



    void DBusServer::processMethodCall(DBusMessage *msg)
    {
        bool methodProcessed = false;
        //search server interfaces for called method
        for(auto && interface : m_interfaceList)
        {
            for(auto && object : interface.m_objects)
            {
                for(auto && method : object.m_methods)
                {
                    if (dbus_message_is_method_call(msg, interface.m_name.c_str(), method.m_name.c_str()))
                    {
                        //extract input arguments
                        DBusMessageIter argIter;
                        dbus_message_iter_init(msg, &argIter);
                        if(DBusInterface::extractDBusMessageArgData(method, &argIter))
                        {
                            //all arguments extracted, call binding
                            DBusInterface::DBusMethodReply reply = method.callBinding();
                            //reply to method call if reply requested
                            if(!dbus_message_get_no_reply(msg))
                            {
                                DBusMessage *replyMsg = nullptr;
                                if(reply.m_valid)
                                {
                                    replyMsg= dbus_message_new_method_return(msg);
                                    if(replyMsg)
                                    {
                                        //create and initialize reply msg iterator
                                        DBusMessageIter replyIter;
                                        dbus_message_iter_init_append(replyMsg, &replyIter);
                                        if(reply.m_valid)
                                        {
                                            DBusInterface::createDBusReply(reply.m_return, &replyIter);
                                            //send reply
                                            dbus_connection_send(m_connection, replyMsg, NULL);
                                            methodProcessed = true;
                                        }
                                    }
                                }
                                else
                                {
                                    std::string errorMsg = std::string("Error in input to method ") + method.m_name;
                                    dbus_error_msg = dbus_message_new_error(msg, DBUS_ERROR_FAILED, errorMsg);
                                    if (dbus_error_msg)
                                    {
                                        dbus_connection_send(m_connection, dbus_error_msg, NULL);
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

