/*
    Copyright 2008,2011 Will Stephenson <wstephenson@kde.org>
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

#ifndef NETWORKMANAGERQT_MODEMDEVICE_H
#define NETWORKMANAGERQT_MODEMDEVICE_H

#include "device.h"
#include "networkmanagerqt_export.h"

namespace NetworkManager
{

class ModemDevicePrivate;

/**
 * Represents a generic modem device, generally defined by the modemCapabilities() it exposes and at
 * the current point in time by the currentCapabilities().
 */
class NETWORKMANAGERQT_EXPORT ModemDevice : public Device
{
    Q_OBJECT
public:
    typedef QSharedPointer<ModemDevice> Ptr;
    typedef QList<Ptr> List;
    enum Capability { NoCapability = 0x0, Pots = 0x1, CdmaEvdo = 0x2, GsmUmts = 0x4, Lte = 0x8 };
    Q_DECLARE_FLAGS(Capabilities, Capability)
    explicit ModemDevice(const QString &path, QObject *parent = nullptr);
    explicit ModemDevice(ModemDevicePrivate &dd, QObject *parent = nullptr);
    virtual ~ModemDevice();
    /**
     * Return the type
     */
    virtual Type type() const Q_DECL_OVERRIDE;
    /**
     * The generic family of access technologies the modem supports. Not all capabilities are
     * available at the same time however; some modems require a firmware reload or other
     * reinitialization to switch between eg CDMA/EVDO and GSM/UMTS.
     */
    Capabilities modemCapabilities() const;
    /**
     * The generic family of access technologies the modem currently supports without a firmware
     * reload or reinitialization.
     */
    Capabilities currentCapabilities() const;

Q_SIGNALS:
    /**
     * This signal is emitted when the capabilities of the device change
     */
    void currentCapabilitiesChanged(Capabilities);

private:
    Q_DECLARE_PRIVATE(ModemDevice)
};

Q_DECLARE_OPERATORS_FOR_FLAGS(ModemDevice::Capabilities)

} // namespace NetworkManager

#endif
