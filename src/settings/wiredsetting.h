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

#ifndef NETWORKMANAGERQT_WIRED_SETTING_H
#define NETWORKMANAGERQT_WIRED_SETTING_H

#include "../networkmanagerqt_export.h"
#include "setting.h"

#include <QtCore/QStringList>

#define NM_SETTING_WIRED_PORT "port"
#define NM_SETTING_WIRED_SPEED "speed"
#define NM_SETTING_WIRED_DUPLEX "duplex"
#define NM_SETTING_WIRED_AUTO_NEGOTIATE "auto-negotiate"
#define NM_SETTING_WIRED_MAC_ADDRESS "mac-address"
#define NM_SETTING_WIRED_CLONED_MAC_ADDRESS "cloned-mac-address"
#define NM_SETTING_WIRED_MAC_ADDRESS_BLACKLIST "mac-address-blacklist"
#define NM_SETTING_WIRED_MTU "mtu"
#define NM_SETTING_WIRED_S390_SUBCHANNELS "s390-subchannels"
#define NM_SETTING_WIRED_S390_NETTYPE "s390-nettype"
#define NM_SETTING_WIRED_S390_OPTIONS "s390-options"

namespace NetworkManager
{

class WiredSettingPrivate;

/**
 * Represents wired setting
 */
class NETWORKMANAGERQT_EXPORT WiredSetting : public Setting
{
public:
    typedef QSharedPointer<WiredSetting> Ptr;
    typedef QList<Ptr> List;
    enum PortType {
        UnknownPort = 0,
        Tp,
        Aui,
        Bnc,
        Mii
    };

    enum DuplexType {
        UnknownDuplexType = 0,
        Half,
        Full
    };

    enum S390Nettype {
        Undefined = 0,
        Qeth,
        Lcs,
        Ctc
    };

    enum WakeOnLanFlag {
        WakeOnLanPhy = 1 << 1,
        WakeOnLanUnicast = 1 << 2,
        WakeOnLanMulticast = 1 << 3,
        WakeOnLanBroadcast = 1 << 4,
        WakeOnLanArp = 1 << 5,
        WakeOnLanMagic = 1 << 6,
        /* Special values */
        WakeOnLanDefault = 1 << 0,
        WakeOnLanIgnore = 1 << 15
    };
    Q_DECLARE_FLAGS(WakeOnLanFlags, WakeOnLanFlag)
    Q_FLAGS(WakeOnLanFlag)

    WiredSetting();
    explicit WiredSetting(const Ptr &other);
    ~WiredSetting();

    QString name() const Q_DECL_OVERRIDE;

    void setPort(PortType port);
    PortType port() const;

    void setSpeed(quint32 speed);
    quint32 speed() const;

    void setDuplexType(DuplexType type);
    DuplexType duplexType() const;

    void setAutoNegotiate(bool autoNegotiate);
    bool autoNegotiate() const;

    QString generateMacAddressMask() const;
    void setGenerateMacAddressMask(const QString& mask);

    void setMacAddress(const QByteArray &address);
    QByteArray macAddress() const;

    void setClonedMacAddress(const QByteArray &address);
    QByteArray clonedMacAddress() const;

    void setMacAddressBlacklist(const QStringList &list);
    QStringList macAddressBlacklist() const;

    void setMtu(quint32 mtu);
    quint32 mtu() const;

    void setS390Subchannels(const QStringList &channels);
    QStringList s390Subchannels() const;

    void setS390NetType(S390Nettype type);
    S390Nettype s390NetType() const;

    void setS390Options(const QMap<QString, QString> &options);
    QMap<QString, QString> s390Options() const;

    WakeOnLanFlags wakeOnLan() const;
    void setWakeOnLan(WakeOnLanFlags wol);

    QString wakeOnLanPassword() const;
    void setWakeOnLanPassword(const QString& password);

    void fromMap(const QVariantMap &setting) Q_DECL_OVERRIDE;

    QVariantMap toMap() const Q_DECL_OVERRIDE;

protected:
    WiredSettingPrivate *d_ptr;

private:
    Q_DECLARE_PRIVATE(WiredSetting)
};

NETWORKMANAGERQT_EXPORT QDebug operator<<(QDebug dbg, const WiredSetting &setting);

Q_DECLARE_OPERATORS_FOR_FLAGS(WiredSetting::WakeOnLanFlags)

}

#endif // NETWORKMANAGERQT_WIRED_SETTING_H
