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

#ifndef NETWORKMANAGERQT_WIRELESS_SETTING_P_H
#define NETWORKMANAGERQT_WIRELESS_SETTING_P_H

#include <QtCore/QStringList>

namespace NetworkManager
{

class WirelessSettingPrivate
{
public:
    WirelessSettingPrivate();

    QString name;
    QByteArray ssid;
    NetworkManager::WirelessSetting::NetworkMode mode;
    NetworkManager::WirelessSetting::FrequencyBand band;
    quint32 channel;
    QByteArray bssid;
    quint32 rate;
    quint32 txPower;
    QByteArray macAddress;
    QByteArray clonedMacAddress;
    QStringList macAddressBlacklist;
    quint32 mtu;
    QStringList seenBssids;
    QString security;
    bool hidden;
    QString generateMacAddressMask;
    NetworkManager::Setting::MacAddressRandomization macAddressRandomization;
    NetworkManager::WirelessSetting::PowerSave powersave;
};

}

#endif // NETWORKMANAGERQT_WIRELESS_SETTING_P_H

