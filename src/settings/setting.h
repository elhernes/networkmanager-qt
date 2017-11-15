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

#ifndef NETWORKMANAGERQT_SETTING_H
#define NETWORKMANAGERQT_SETTING_H

#include "../networkmanagerqt_export.h"

#include "../generictypes.h"

#undef signals
#include <NetworkManager/NetworkManager.h>
#define signals Q_SIGNALS

#include <QtCore/QVariantMap>
#include <QtCore/QStringList>
#include <QtCore/QFlags>
#include <QSharedPointer>

#define NM_SETTING_802_1X_SETTING_NAME "802-1x"
#define NM_SETTING_ADSL_SETTING_NAME "adsl"
#define NM_SETTING_BLUETOOTH_SETTING_NAME "bluetooth"
#define NM_SETTING_BOND_SETTING_NAME "bond"
#define NM_SETTING_BRIDGE_PORT_SETTING_NAME "bridge-port"
#define NM_SETTING_BRIDGE_SETTING_NAME "bridge"
#define NM_SETTING_CDMA_SETTING_NAME "cdma"
#define NM_SETTING_CONNECTION_SETTING_NAME "connection"
#define NM_SETTING_DCB_SETTING_NAME "dcb"
#define NM_SETTING_GENERIC_SETTING_NAME "generic"
#define NM_SETTING_GSM_SETTING_NAME "gsm"
#define NM_SETTING_INFINIBAND_SETTING_NAME "infiniband"
#define NM_SETTING_IP4_CONFIG_SETTING_NAME "ipv4"
#define NM_SETTING_IP6_CONFIG_SETTING_NAME "ipv6"
#define NM_SETTING_OLPC_MESH_SETTING_NAME "802-11-olpc-mesh"
#define NM_SETTING_PPP_SETTING_NAME "ppp"
#define NM_SETTING_PPPOE_SETTING_NAME "pppoe"
#define NM_SETTING_SERIAL_SETTING_NAME "serial"
#define NM_SETTING_TEAM_PORT_SETTING_NAME "team-port"
#define NM_SETTING_TEAM_SETTING_NAME "team"
#define NM_SETTING_VLAN_SETTING_NAME "vlan"
#define NM_SETTING_VPN_SETTING_NAME "vpn"
#define NM_SETTING_WIMAX_SETTING_NAME "wimax"
#define NM_SETTING_WIRED_SETTING_NAME "802-3-ethernet"
#define NM_SETTING_WIRELESS_SECURITY_SETTING_NAME "802-11-wireless-security"
#define NM_SETTING_WIRELESS_SETTING_NAME "802-11-wireless"
#define NM_SETTING_NAME "name"

namespace NetworkManager
{

class SettingPrivate;

/**
 * Base class for all kinds of setting
 */
class NETWORKMANAGERQT_EXPORT Setting
{
public:
    typedef QSharedPointer<Setting> Ptr;
    typedef QList<Ptr> List;
    enum SettingType {
        Adsl,
        Cdma,
        Gsm,
        Infiniband,
        Ipv4,
        Ipv6,
        Ppp,
        Pppoe,
        Security8021x,
        Serial,
        Vpn,
        Wired,
        Wireless,
        WirelessSecurity,
        Bluetooth,
        OlpcMesh,
        Vlan,
        Wimax,
        Bond,
        Bridge,
        BridgePort,
        Team,
        Generic,
        Tun
    };

    enum SecretFlagType {
        None = 0,
        AgentOwned = 0x01,
        NotSaved = 0x02,
        NotRequired = 0x04
    };
    Q_DECLARE_FLAGS(SecretFlags, SecretFlagType)

    enum MacAddressRandomization {
        MacAddressRandomizationDefault = 0,
        MacAddressRandomizationNever,
        MacAddressRandomizationAlways
    };

    static QString typeAsString(SettingType type);
    static SettingType typeFromString(const QString &type);

    explicit Setting(SettingType type);
    explicit Setting(const Ptr &setting);
    virtual ~Setting();

    /**
     * @brief Must be reimplemented, default implementation does nothing
     */
    virtual void fromMap(const QVariantMap &map);

    /**
     * @brief Must be reimplemented, default implementationd does nothing
     */
    virtual QVariantMap toMap() const;

    virtual void secretsFromMap(const QVariantMap &map);

    /**
     * @brief secretsFromStringMap is a convenience function
     * to set the secrets from a map of strings.
     * @param map to extract secrets from
     */
    virtual void secretsFromStringMap(const NMStringMap &map);

    virtual QVariantMap secretsToMap() const;

    /**
     * @brief secretsToStringMap is a convenience function
     * to get the secrets to map of strings.
     * @return string map with current secrets
     */
    virtual NMStringMap secretsToStringMap() const;

    virtual QStringList needSecrets(bool requestNew = false) const;

    /**
     * @brief Must be reimplemented, default implementationd does nothing
     */
    virtual QString name() const;

    void setInitialized(bool initialized);

    bool isNull() const;

    void setType(SettingType type);
    SettingType type() const;

protected:
    SettingPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(Setting)
};
Q_DECLARE_OPERATORS_FOR_FLAGS(Setting::SecretFlags)

NETWORKMANAGERQT_EXPORT QDebug operator<<(QDebug dbg, const Setting &setting);

}

#endif // NETWORKMANAGERQT_SETTING_H
