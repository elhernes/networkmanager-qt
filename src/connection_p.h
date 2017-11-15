/*
    Copyright 2008,2009 Will Stephenson <wstephenson@kde.org>
    Copyright 2011-2013 Lamarque V. Souza <lamarque@kde.org>
    Copyright 2013-2014 Jan Grulich <jgrulich@redhat.com>

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

#ifndef NETWORKMANAGERQT_SETTINGS_CONNECTION_P_H
#define NETWORKMANAGERQT_SETTINGS_CONNECTION_P_H

#include "connection.h"
#include "device.h"
#include "manager_p.h"
#include "dbus/connectioninterface.h"
#include "generictypes.h"

//from NetworkManager/nm-setting-connection.h, but that sucks in glib and other shit
#define NM_SETTING_CONNECTION_ID             "id"
#define NM_SETTING_CONNECTION_UUID           "uuid"
#define NM_SETTING_CONNECTION_INTERFACE_NAME "interface-name"
#define NM_SETTING_CONNECTION_TYPE           "type"
#define NM_SETTING_CONNECTION_AUTOCONNECT    "autoconnect"
#define NM_SETTING_CONNECTION_TIMESTAMP      "timestamp"
#define NM_SETTING_CONNECTION_READ_ONLY      "read-only"
#define NM_SETTING_CONNECTION_PERMISSIONS    "permissions"
#define NM_SETTING_CONNECTION_ZONE           "zone"
#define NM_SETTING_CONNECTION_MASTER         "master"
#define NM_SETTING_CONNECTION_SLAVE_TYPE     "slave-type"
#define NM_SETTING_CONNECTION_SECONDARIES    "secondaries"
#define NM_SETTING_CONNECTION_GATEWAY_PING_TIMEOUT "gateway-ping-timeout"

class QDBusPendingCallWatcher;

namespace NetworkManager
{

class ConnectionPrivate : public QObject
{
    Q_OBJECT
public:
    ConnectionPrivate(const QString &path, Connection *q);

    void updateSettings(const NMVariantMapMap &newSettings = NMVariantMapMap());
    bool unsaved;
    QString uuid;
    QString id;
    NMVariantMapMap settings;
    ConnectionSettings::Ptr connection;
    QString path;
    OrgFreedesktopNetworkManagerSettingsConnectionInterface iface;

    Q_DECLARE_PUBLIC(Connection)
    Connection *q_ptr;
private Q_SLOTS:
    void onConnectionUpdated();
    void onConnectionRemoved();
    void dbusPropertiesChanged(const QString &interfaceName, const QVariantMap &properties, const QStringList &invalidatedProperties);
    void onPropertiesChanged(const QVariantMap &properties);
};

}

#endif
