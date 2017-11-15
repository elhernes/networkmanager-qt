/*
    Copyright 2011 Ilia Kats <ilia-kats@gmx.net>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef NETWORKMANAGERQT_ACTIVECONNECTION_P_H
#define NETWORKMANAGERQT_ACTIVECONNECTION_P_H

#include "activeconnection.h"
#include "dbus/activeconnectioninterface.h"

namespace NetworkManager
{

class ActiveConnectionPrivate : public QObject
{
    Q_OBJECT
public:
    explicit ActiveConnectionPrivate(const QString &, ActiveConnection *q);
    virtual ~ActiveConnectionPrivate();
    static NetworkManager::ActiveConnection::State convertActiveConnectionState(uint);
    NetworkManager::Connection::Ptr connection;
    QString path;
    bool default4;
    bool default6;
    QStringList devices;
    OrgFreedesktopNetworkManagerConnectionActiveInterface iface;
    mutable Dhcp4Config::Ptr dhcp4Config;
    QString dhcp4ConfigPath;
    mutable Dhcp6Config::Ptr dhcp6Config;
    QString dhcp6ConfigPath;
    mutable IpConfig ipV4Config;
    QString ipV4ConfigPath;
    mutable IpConfig ipV6Config;
    QString ipV6ConfigPath;
    QString id;
    QString type;
    QString specificObject;
    ActiveConnection::State state;
    bool vpn;
    QString uuid;
    QString master;

    Q_DECLARE_PUBLIC(ActiveConnection)
    ActiveConnection *q_ptr;

    /*
     * Workaround: Re-check connection state before we watch changes in case it gets changed too quickly
     * BUG:352326
     */
    void recheckProperties();
public:
    /**
     * When subclassing make sure to call the parent class method
     * if the property was not useful to your new class
     */
    virtual void propertyChanged(const QString &property, const QVariant &value);

public Q_SLOTS:
    void propertiesChanged(const QVariantMap &properties);

private Q_SLOTS:
    void dbusPropertiesChanged(const QString &interfaceName, const QVariantMap &properties, const QStringList &invalidatedProperties);
};

}
#endif
