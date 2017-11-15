/*
    Copyright 2012-2013  Jan Grulich <jgrulich@redhat.com>

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

#ifndef NETWORKMANAGERQT_CONNECTION_SETTINGS_P_H
#define NETWORKMANAGERQT_CONNECTION_SETTINGS_P_H

#include "setting.h"

#include <QtCore/QHash>
#include <QtCore/QString>
#include <QtCore/QDateTime>

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

namespace NetworkManager
{

class ConnectionSettingsPrivate
{
public:
    Q_DECLARE_PUBLIC(ConnectionSettings)

    explicit ConnectionSettingsPrivate(ConnectionSettings *q);

    void addSetting(const NetworkManager::Setting::Ptr &setting);
    void clearSettings();
    void initSettings(NMBluetoothCapabilities bt_cap);
    void initSettings(const NetworkManager::ConnectionSettings::Ptr &connectionSettings);

    QString name;
    QString id;
    QString uuid;
    QString interfaceName;
    NetworkManager::ConnectionSettings::ConnectionType type;
    QHash<QString, QString> permissions;
    bool autoconnect;
    QDateTime timestamp;
    bool readOnly;
    QString zone;
    QString master;
    QString slaveType;
    QStringList secondaries;
    quint32 gatewayPingTimeout;
    int autoconnectPriority;
    int autoconnectRetries;
    NetworkManager::ConnectionSettings::AutoconnectSlaves autoconnectSlaves;
    NetworkManager::ConnectionSettings::Lldp lldp;
    NetworkManager::ConnectionSettings::Metered metered;
    QString stableId;
    Setting::List settings;

    ConnectionSettings *q_ptr;
};

}

#endif //  NETWORKMANAGERQT_CONNECTION_SETTINGS_P_H
