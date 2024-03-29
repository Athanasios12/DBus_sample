#include "BusConnection.h"
#include <algorithm>

namespace DBUS
{
    BusConnection::BusConnection():
        m_busType(DBUS_BUS_SYSTEM),
        m_connection(nullptr),
        m_connected(false)
    {

    }

    BusConnection::BusConnection(const std::string &busName, DBusBusType busType):
        m_busName(busName),
        m_busType(busType),
        m_connection(nullptr),
        m_connected(false)
    {

    }

    BusConnection::~BusConnection()
    {
        disconnect();
    }

    BusConnection::BusConnection(BusConnection&& other)
    {
        m_interfaceList = std::move(other.m_interfaceList);
        m_busName = other.m_busName;
        m_busType = other.m_busType;
        m_connection = other.m_connection;
        m_connected = other.m_connected;
        other.m_busName.clear();
        other.m_busType = DBUS_BUS_SYSTEM;
        other.m_connection = nullptr;
        other.m_connected = false;
    }

    BusConnection& BusConnection::operator=(BusConnection&& other)
    {
        if(this != &other)
        {
            disconnect();
            m_interfaceList = std::move(other.m_interfaceList);
            m_busName = other.m_busName;
            m_busType = other.m_busType;
            m_connection = other.m_connection;
            m_connected = other.m_connected;
            other.m_busName.clear();
            other.m_busType = DBUS_BUS_SYSTEM;
            other.m_connection = nullptr;
            other.m_connected = false;
        }
        return *this;
    }

    bool BusConnection::connect()
    {
        if(!m_connected)
        {
            DBusConnection *connection = dbus_bus_get(m_busType, NULL);
            if(connection)
            {
                auto ret = dbus_bus_request_name(connection, m_busName.c_str(), DBUS_NAME_FLAG_DO_NOT_QUEUE, NULL);
                if(DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER == ret)
                {
                    m_connected = true;
                    m_connection = connection;
                }
            }
        }
        return m_connected;
    }

    bool BusConnection::disconnect()
    {
        if(m_connected && m_connection)
        {
            dbus_connection_unref(m_connection);
            dbus_bus_release_name(m_connection, m_busName.c_str(), NULL);
            m_connected = false;
        }
        return !m_connected;
    }

    bool BusConnection::addInterface(const DBusInterface &interface)
    {
        bool addedInterface = false;
        if(std::find(m_interfaceList.begin(), m_interfaceList.end(), interface) == std::end(m_interfaceList))
        {
            addedInterface = true;
            m_interfaceList.push_back(interface);
        }
        return addedInterface;
    }

    std::string BusConnection::getBusName() const
    {
        return m_busName;
    }

    DBusBusType BusConnection::getBusType() const
    {
        return m_busType;
    }

    std::vector<DBusInterface> BusConnection::getInterfaceList() const
    {
        return m_interfaceList;
    }

    bool BusConnection::isConnected() const
    {
        return m_connected;
    }

}
