/*
    Copyright 2012-2014 Jan Grulich <jgrulich@redhat.com>

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

#ifndef NETWORKMANAGERQT_MACVLAN_DEVICE_P_H
#define NETWORKMANAGERQT_MACVLAN_DEVICE_P_H

#include "device_p.h"
#include "macvlandevice.h"
#include "manager_p.h"
#include "dbus/macvlandeviceinterface.h"

namespace NetworkManager
{

class MacVlanDevicePrivate: public DevicePrivate
{
    Q_OBJECT
public:
    MacVlanDevicePrivate(const QString &path, MacVlanDevice *q);
    virtual ~MacVlanDevicePrivate();

    OrgFreedesktopNetworkManagerDeviceMacvlanInterface iface;
    QString mode;
    bool noPromisc;
    QString parent;

    Q_DECLARE_PUBLIC(MacVlanDevice)
protected:
    /**
     * When subclassing make sure to call the parent class method
     * if the property was not useful to your new class
     */
    virtual void propertyChanged(const QString &property, const QVariant &value) Q_DECL_OVERRIDE;
};

}

#endif
