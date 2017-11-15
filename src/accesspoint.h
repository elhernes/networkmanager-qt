/*
    Copyright 2008 Will Stephenson <wstephenson@kde.org>
    Copyright 2011-2013 Lamarque V. Souza <lamarque@kde.org>
    Copyright 2013 Jan Grulich <jgrulich@redhat.com>

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

#ifndef NETWORKMANAGERQT_ACCESSPOINT_H
#define NETWORKMANAGERQT_ACCESSPOINT_H

#include "networkmanagerqt_export.h"

#include <NetworkManager/NetworkManager.h>

#include <QObject>
#include <QSharedPointer>
#include <QVariantMap>

namespace NetworkManager
{

class AccessPointPrivate;

/**
 * Represents an access point
 */
class NETWORKMANAGERQT_EXPORT AccessPoint : public QObject
{
    Q_OBJECT
public:
    typedef QSharedPointer<AccessPoint> Ptr;
    typedef QList<Ptr> List;
    /**
     * The access point's current operating mode
     */
    enum OperationMode {
        Unknown = 0, /**< not associated with a network */
        Adhoc, /**< part of an adhoc network */
        Infra, /**< a station in an infrastructure wireless network */
        ApMode /**< access point in an infrastructure network */
    };
    /**
     * General capabilities of an access point
     */
    enum Capability {
        None = 0x0, /**< Null capability - says nothing about the access point */
        Privacy = 0x1 /**< Access point supports privacy measures */
    };
    /**
     * Flags describing the access point's capabilities according to WPA (Wifi Protected Access)
     */
    enum WpaFlag { PairWep40 = 0x1, PairWep104 = 0x2, PairTkip = 0x4, PairCcmp = 0x8,
                   GroupWep40 = 0x10, GroupWep104 = 0x20, GroupTkip = 0x40, GroupCcmp = 0x80,
                   KeyMgmtPsk = 0x100, KeyMgmt8021x = 0x200
                 };
    Q_DECLARE_FLAGS(Capabilities, Capability)
    Q_FLAG(Capabilities)
    Q_DECLARE_FLAGS(WpaFlags, WpaFlag)
    Q_FLAG(WpaFlags)
    explicit AccessPoint(const QString &path, QObject *parent = nullptr);
    virtual ~AccessPoint();

    /**
     * @return path of the access point
     */
    QString uni() const;
    /**
     * @return capabilities of an access point
     */
    Capabilities capabilities() const;
    /**
     * @return flags describing the access point's capabilities according to WPA (Wifi Protected Access).
     * @see WpaFlag
     */
    AccessPoint::WpaFlags wpaFlags() const;
    /**
     * @return Flags describing the access point's capabilities according to the RSN (Robust Secure Network) protocol.
     * @see WpaFlag
     */
    AccessPoint::WpaFlags rsnFlags() const;
    /**
     * @return The Service Set Identifier identifying the access point.
     */
    QString ssid() const;
    /**
     * @return raw SSID, encoded as a byte array
     */
    QByteArray rawSsid() const;
    /**
     * @return The radio channel frequency in use by the access point, in MHz.
     */
    uint frequency() const;
    /**
     * @return The hardware address (BSSID) of the access point.
     */
    QString hardwareAddress() const;
    /**
     * @return The maximum bitrate this access point is capable of, in kilobits/second (Kb/s).
     */
    uint maxBitRate() const;
    /**
     * @return Describes the operating mode of the access point.
     */
    OperationMode mode() const;
    /**
     * @return The current signal quality of the access point, in percent.
     */
    int signalStrength() const;
    /**
     * @return The timestamp (in CLOCK_BOOTTIME seconds) for the last time the access point
     * was found in scan results. A value of -1 means the access point has never been found in scan results.
     * @since 5.14.0
     * @note always returns -1 in runtime NM < 1.0.6
     */
    int lastSeen() const;

    /**
     * Helper method to convert wire representation of operation @p mode to enum
     */
    static OperationMode convertOperationMode(uint mode);

Q_SIGNALS:
    /**
     * This signal is emitted when the signal strength of this network has changed.
     *
     * @param strength the new signal strength value for this network
     */
    void signalStrengthChanged(int strength);

    /**
     * This signal is emitted when the bitrate of this network has changed.
     *
     * @param bitrate the new bitrate value for this network
     */
    void bitRateChanged(int bitrate);

    /**
     * This signal is emitted when the capabilities of this network have changed.
     *
     * @param caps the new capabilities
     */
    void capabilitiesChanged(AccessPoint::Capabilities caps);

    /**
     * This signal is emitted when the WPA flags in use by this access point change
     *
     * @param flags the new flags
     */
    void wpaFlagsChanged(AccessPoint::WpaFlags flags);

    /**
     * This signal is emitted when the RSN(WPA2) flags in use by this access point change
     *
     * @param flags the new flags
     */
    void rsnFlagsChanged(AccessPoint::WpaFlags flags);
    /**
     * This signal is emitted when the ssid of this Access Point changes
     *
     * @param ssid the new SSID
     */
    void ssidChanged(const QString &ssid);

    /**
     * This signal is emitted when the frequency used by this Access Point changes
     *
     * @param frequency the new frequency
     */
    void frequencyChanged(uint frequency);

    /**
     * This signal is emitted when the timestamp for the last time the access point was found
     * in scan results changes
     *
     * @param lastSeen the timestamp for the last time the access point was found in scan results.
     * @since 5.14.0
     * @see lastSeen
     * @note never emitted in runtime NM < 1.0.6
     */
    void lastSeenChanged(int lastSeen);

private:
    Q_DECLARE_PRIVATE(AccessPoint)

    AccessPointPrivate *const d_ptr;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(AccessPoint::WpaFlags)

}
#endif

