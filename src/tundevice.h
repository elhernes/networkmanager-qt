/*
    Copyright 2013 Lukáš Tinkl <ltinkl@redhat.com>
    Copyright 2014 Jan Grulich <jgrulich@redhat.com>

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

#ifndef NETWORKMANAGERQT_TUN_DEVICE_H
#define NETWORKMANAGERQT_TUN_DEVICE_H

#include "device.h"
#include "networkmanagerqt_export.h"

namespace NetworkManager
{

class TunDevicePrivate;

/**
 * A tun device interface
 */
class NETWORKMANAGERQT_EXPORT TunDevice : public Device
{
    Q_OBJECT
    Q_PROPERTY(qlonglong owner READ owner NOTIFY ownerChanged)
    Q_PROPERTY(qlonglong group READ group NOTIFY groupChanged)
    Q_PROPERTY(QString mode READ mode NOTIFY modeChanged)
    Q_PROPERTY(bool multiQueue READ multiQueue NOTIFY multiQueueChanged)
    Q_PROPERTY(bool noPi READ noPi NOTIFY noPiChanged)
    Q_PROPERTY(bool vnetHdr READ vnetHdr NOTIFY vnetHdrChanged)
    Q_PROPERTY(QString hwAddress READ hwAddress NOTIFY hwAddressChanged)

public:
    typedef QSharedPointer<TunDevice> Ptr;
    typedef QList<Ptr> List;
    explicit TunDevice(const QString &path, QObject *parent = nullptr);
    virtual ~TunDevice();

    virtual Type type() const Q_DECL_OVERRIDE;

    /**
     * The uid of the tunnel owner, or -1 if it has no owner.
     */
    qlonglong owner() const;
    /**
     * The gid of the tunnel group, or -1 if it has no owner.
     */
    qlonglong group() const;
    /**
     * The tunnel mode, either "tun" or "tap".
     */
    QString mode() const;
    /**
     * The tunnel's "TUN_TAP_MQ" flag; true if callers can connect to the tap device multiple times, for multiple send/receive queues.
     */
    bool multiQueue() const;
    /**
     * The tunnel's "TUN_NO_PI" flag; true if no protocol info is prepended to the tunnel packets.
     */
    bool noPi() const;
    /**
     * The tunnel's "TUN_VNET_HDR" flag; true if the tunnel packets include a virtio network header.
     */
    bool vnetHdr() const;
    /**
     * Hardware address of the device.
     * @note returns empty address in runtime NM < 1.2.0
     */
    QString hwAddress() const;

Q_SIGNALS:
    /**
     * Emitted when the uid of the tunnel owner has changed
     */
    void ownerChanged(qlonglong owner);
    /**
     * Emitted when the gid of the tunnel group has changed
     */
    void groupChanged(qlonglong group);
    /**
     * Emitted when the tunnel mode has changed
     */
    void modeChanged(const QString &mode);
    /**
     * Emitted when the tunnel's "TUN_TAP_MQ" flag has changed
     */
    void multiQueueChanged(bool multiQueue);
    /**
     * Emitted when the tunnel's "TUN_NO_PI" flag has changed
     */
    void noPiChanged(bool noPi);
    /**
     * Emitted when the tunnel's "TUN_VNET_HDR" flag has changed
     */
    void vnetHdrChanged(bool vnetHdr);
    /**
     * Emitted when the hardware address of the device has changed
     * @note never emitted in runtime NM < 1.2.0
     */
    void hwAddressChanged(const QString &hwAddress);

private:
    Q_DECLARE_PRIVATE(TunDevice)
};

}

#endif
