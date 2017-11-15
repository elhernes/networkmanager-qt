/*
    Copyright 2011 Ilia Kats <ilia-kats@gmx.net>
    Copyright 2013 Daniel Nicoletti <dantti12@gmail.com>
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

#include "activeconnection.h"
#include "activeconnection_p.h"
#include "connection.h"
#include "device.h"
#include "nmdebug.h"
#include "manager.h"
#include "settings.h"

#include <QDBusObjectPath>

#include "manager_p.h"

NetworkManager::ActiveConnectionPrivate::ActiveConnectionPrivate(const QString &dbusPath, ActiveConnection *q)
#ifdef NMQT_STATIC
    : iface(NetworkManagerPrivate::DBUS_SERVICE, dbusPath, QDBusConnection::sessionBus())
#else
    : iface(NetworkManagerPrivate::DBUS_SERVICE, dbusPath, QDBusConnection::systemBus())
#endif
    , dhcp4Config(nullptr)
    , dhcp6Config(nullptr)
    , state(ActiveConnection::Unknown)
    , q_ptr(q)
{
    path = dbusPath;
}

NetworkManager::ActiveConnectionPrivate::~ActiveConnectionPrivate()
{
}

NetworkManager::ActiveConnection::State NetworkManager::ActiveConnectionPrivate::convertActiveConnectionState(uint state)
{
    return (NetworkManager::ActiveConnection::State)state;
}

NetworkManager::ActiveConnection::ActiveConnection(const QString &path, QObject *parent)
    : QObject(parent), d_ptr(new ActiveConnectionPrivate(path, this))
{
    Q_D(ActiveConnection);

    // Get all ActiveConnection's at once
    QVariantMap initialProperties = NetworkManagerPrivate::retrieveInitialProperties(d->iface.staticInterfaceName(), path);
    if (!initialProperties.isEmpty()) {
        d->propertiesChanged(initialProperties);
    }

#ifndef NMQT_STATIC
#if NM_CHECK_VERSION(1, 4, 0)
    QDBusConnection::systemBus().connect(NetworkManagerPrivate::DBUS_SERVICE, d->path, NetworkManagerPrivate::FDO_DBUS_PROPERTIES,
                                         QLatin1String("PropertiesChanged"), d, SLOT(dbusPropertiesChanged(QString,QVariantMap,QStringList)));
#else
    connect(&d->iface, &OrgFreedesktopNetworkManagerConnectionActiveInterface::PropertiesChanged, d, &ActiveConnectionPrivate::propertiesChanged);
#endif
#endif

#ifdef NMQT_STATIC
    connect(&d->iface, &OrgFreedesktopNetworkManagerConnectionActiveInterface::PropertiesChanged, d, &ActiveConnectionPrivate::propertiesChanged);
#endif

#ifndef NMQT_STATIC
    /*
     * Workaround: Re-check connection state before we watch changes in case it gets changed too quickly
     * BUG:352326
     */
    d->recheckProperties();
#endif
}

NetworkManager::ActiveConnection::ActiveConnection(ActiveConnectionPrivate &dd, QObject *parent)
    : QObject(parent), d_ptr(&dd)
{
    Q_D(ActiveConnection);

#ifndef NMQT_STATIC
#if NM_CHECK_VERSION(1, 4, 0)
    QDBusConnection::systemBus().connect(NetworkManagerPrivate::DBUS_SERVICE, d->path, NetworkManagerPrivate::FDO_DBUS_PROPERTIES,
                                         QLatin1String("PropertiesChanged"), d, SLOT(dbusPropertiesChanged(QString,QVariantMap,QStringList)));
#else
    connect(&d->iface, &OrgFreedesktopNetworkManagerConnectionActiveInterface::PropertiesChanged, d, &ActiveConnectionPrivate::propertiesChanged);
#endif
#endif

#ifdef NMQT_STATIC
    connect(&d->iface, &OrgFreedesktopNetworkManagerConnectionActiveInterface::PropertiesChanged, d, &ActiveConnectionPrivate::propertiesChanged);
#endif

#ifndef NMQT_STATIC
    /*
     * Workaround: Re-check connection state before we watch changes in case it gets changed too quickly
     * BUG:352326
     */
    d->recheckProperties();
#endif
}

NetworkManager::ActiveConnection::~ActiveConnection()
{
    delete d_ptr;
}

bool NetworkManager::ActiveConnection::isValid() const
{
    Q_D(const ActiveConnection);
    return !d->connection.isNull();
}

NetworkManager::Connection::Ptr NetworkManager::ActiveConnection::connection() const
{
    Q_D(const ActiveConnection);
    return d->connection;
}

QString NetworkManager::ActiveConnection::path() const
{
    Q_D(const ActiveConnection);
    return d->path;
}

bool NetworkManager::ActiveConnection::default4() const
{
    Q_D(const ActiveConnection);
    return d->default4;
}

bool NetworkManager::ActiveConnection::default6() const
{
    Q_D(const ActiveConnection);
    return d->default6;
}

NetworkManager::Dhcp4Config::Ptr NetworkManager::ActiveConnection::dhcp4Config() const
{
    Q_D(const ActiveConnection);
    if (!d->dhcp4Config && !d->dhcp4ConfigPath.isNull()) {
        d->dhcp4Config = NetworkManager::Dhcp4Config::Ptr(new Dhcp4Config(d->dhcp4ConfigPath), &QObject::deleteLater);
    }
    return d->dhcp4Config;
}

NetworkManager::Dhcp6Config::Ptr NetworkManager::ActiveConnection::dhcp6Config() const
{
    Q_D(const ActiveConnection);
    if (!d->dhcp6Config && !d->dhcp6ConfigPath.isNull()) {
        d->dhcp6Config = NetworkManager::Dhcp6Config::Ptr(new Dhcp6Config(d->dhcp6ConfigPath), &QObject::deleteLater);
    }
    return d->dhcp6Config;
}

NetworkManager::IpConfig NetworkManager::ActiveConnection::ipV4Config() const
{
    Q_D(const ActiveConnection);
    if (!d->ipV4Config.isValid() && !d->ipV4ConfigPath.isNull()) {
        d->ipV4Config.setIPv4Path(d->ipV4ConfigPath);
    }
    return d->ipV4Config;
}

NetworkManager::IpConfig NetworkManager::ActiveConnection::ipV6Config() const
{
    Q_D(const ActiveConnection);
    if (!d->ipV6Config.isValid() && !d->ipV6ConfigPath.isNull()) {
        d->ipV6Config.setIPv6Path(d->ipV6ConfigPath);
    }
    return d->ipV6Config;
}

QString NetworkManager::ActiveConnection::id() const
{
    Q_D(const ActiveConnection);
    return d->id;
}

NetworkManager::ConnectionSettings::ConnectionType NetworkManager::ActiveConnection::type() const
{
    Q_D(const ActiveConnection);
    return NetworkManager::ConnectionSettings::typeFromString(d->type);
}

QString NetworkManager::ActiveConnection::master() const
{
    Q_D(const ActiveConnection);
    return d->master;
}

QString NetworkManager::ActiveConnection::specificObject() const
{
    Q_D(const ActiveConnection);
    return d->specificObject;
}

NetworkManager::ActiveConnection::State NetworkManager::ActiveConnection::state() const
{
    Q_D(const ActiveConnection);
    return d->state;
}

bool NetworkManager::ActiveConnection::vpn() const
{
    Q_D(const ActiveConnection);
    return d->vpn;
}

QString NetworkManager::ActiveConnection::uuid() const
{
    Q_D(const ActiveConnection);
    return d->uuid;
}

QStringList NetworkManager::ActiveConnection::devices() const
{
    Q_D(const ActiveConnection);
    return d->devices;
}

void NetworkManager::ActiveConnectionPrivate::recheckProperties()
{
    Q_Q(ActiveConnection);

    /*
     * Workaround: Re-check connection state before we watch changes in case it gets changed too quickly
     * BUG:352326
     */
    QStringList properties;
    const QDBusObjectPath ip4ConfigObjectPath = iface.ip4Config();
    const QDBusObjectPath ip6ConfigObjectPath = iface.ip6Config();
    const QDBusObjectPath dhcp4ConfigObjectPath = iface.dhcp4Config();
    const QDBusObjectPath dhcp6ConfigObjectPath = iface.dhcp6Config();

    if (state != NetworkManager::ActiveConnectionPrivate::convertActiveConnectionState(iface.state())) {
        properties << QLatin1String("State");
    }

    if (!ip4ConfigObjectPath.path().isNull() && ip4ConfigObjectPath.path() != ipV4ConfigPath) {
        properties << QLatin1String("Ip4Config");
    }

    if (!ip6ConfigObjectPath.path().isNull() && ip6ConfigObjectPath.path() != ipV6ConfigPath) {
        properties << QLatin1String("Ip6Config");
    }

    if (!dhcp4ConfigObjectPath.path().isNull() && dhcp4ConfigObjectPath.path() != dhcp4ConfigPath) {
        properties << QLatin1String("Dhcp4Config");
    }

    if (!dhcp6ConfigObjectPath.path().isNull() && dhcp6ConfigObjectPath.path() != dhcp6ConfigPath) {
        properties << QLatin1String("Dhcp6Config");
    }

    Q_FOREACH (const QString &property, properties) {
        QDBusMessage message = QDBusMessage::createMethodCall(NetworkManager::NetworkManagerPrivate::DBUS_SERVICE,
                            NetworkManager::NetworkManagerPrivate::DBUS_DAEMON_PATH,
                            NetworkManager::NetworkManagerPrivate::FDO_DBUS_PROPERTIES,
                            QLatin1String("Get"));
        message << iface.staticInterfaceName() << property;

        QDBusPendingCall pendingCall = QDBusConnection::systemBus().asyncCall(message);
        QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(pendingCall, this);

        connect(watcher, &QDBusPendingCallWatcher::finished, [watcher, q, this, property] () {
            watcher->deleteLater();
            if (property == QLatin1String("State")) {
                state = NetworkManager::ActiveConnectionPrivate::convertActiveConnectionState(iface.state());
                Q_EMIT q->stateChanged(state);
            }
            if (property == QLatin1String("Ip4Config")) {
                ipV4ConfigPath = iface.ip4Config().path();
                Q_EMIT q->ipV4ConfigChanged();
            } else if (property == QLatin1String("Ip6Config")) {
                ipV6ConfigPath = iface.ip6Config().path();
                Q_EMIT q->ipV6ConfigChanged();
            } else if (property == QLatin1String("Dhcp4Config")) {
                dhcp4ConfigPath = iface.dhcp4Config().path();
                Q_EMIT q->dhcp4ConfigChanged();
            } else if (property == QLatin1String("Dhcp6Config")) {
                dhcp6ConfigPath = iface.dhcp6Config().path();
                Q_EMIT q->dhcp6ConfigChanged();
            }
        });
    }
}

void NetworkManager::ActiveConnectionPrivate::dbusPropertiesChanged(const QString &interfaceName, const QVariantMap &properties, const QStringList &invalidatedProperties)
{
    Q_UNUSED(invalidatedProperties);

    if (interfaceName == QLatin1String("org.freedesktop.NetworkManager.Connection.Active")) {
        propertiesChanged(properties);
    }
}

void NetworkManager::ActiveConnectionPrivate::propertiesChanged(const QVariantMap &properties)
{
    // qCDebug(NMQT) << Q_FUNC_INFO << properties;

    QVariantMap::const_iterator it = properties.constBegin();
    while (it != properties.constEnd()) {
        propertyChanged(it.key(), it.value());
        ++it;
    }
}

void NetworkManager::ActiveConnectionPrivate::propertyChanged(const QString &property, const QVariant &value)
{
    Q_Q(ActiveConnection);

    // qCDebug(NMQT) << property  << " - " << value;

    if (property == QLatin1String("Connection")) {
        connection = NetworkManager::findConnection(qdbus_cast<QDBusObjectPath>(value).path());
        Q_EMIT q->connectionChanged(connection);
        const QString tmpId = connection->settings()->id();
        const QString tmpType = connection->settings()->typeAsString(connection->settings()->connectionType());
        if (tmpId != id) {
            id = tmpId;
            Q_EMIT q->idChanged(id);
        }

        if (tmpType != type) {
            Q_EMIT q->typeChanged(NetworkManager::ConnectionSettings::typeFromString(type));
        }
    } else if (property == QLatin1String("Default")) {
        default4 = value.toBool();
        Q_EMIT q->default4Changed(default4);
    } else if (property == QLatin1String("Default6")) {
        default6 = value.toBool();
        Q_EMIT q->default6Changed(default6);
    } else if (property == QLatin1String("Dhcp4Config")) {
        QDBusObjectPath dhcp4ConfigPathTmp = (value).value<QDBusObjectPath>();
        if (dhcp4ConfigPathTmp.path().isNull()) {
            dhcp4Config.clear();
            dhcp4ConfigPath.clear();
        } else if (!dhcp4Config || dhcp4Config->path() != dhcp4ConfigPathTmp.path()) {
            dhcp4Config.clear();
            dhcp4ConfigPath = dhcp4ConfigPathTmp.path();
        }
        Q_EMIT q->dhcp4ConfigChanged();
    } else if (property == QLatin1String("Dhcp6Config")) {
        QDBusObjectPath dhcp6ConfigPathTmp = (value).value<QDBusObjectPath>();
        if (dhcp6ConfigPathTmp.path().isNull()) {
            dhcp6Config.clear();
            dhcp6ConfigPath.clear();
        } else if (!dhcp6Config || dhcp6Config->path() != dhcp6ConfigPathTmp.path()) {
            dhcp6Config.clear();
            dhcp6ConfigPath = dhcp6ConfigPathTmp.path();
        }
        Q_EMIT q->dhcp6ConfigChanged();
    } else if (property == QLatin1String("Ip4Config")) {
        QDBusObjectPath ip4ConfigObjectPathTmp = (value).value<QDBusObjectPath>();
        if (ip4ConfigObjectPathTmp.path().isNull() || ip4ConfigObjectPathTmp.path() == QLatin1String("/")) {
            ipV4ConfigPath.clear();
        } else {
            ipV4ConfigPath = ip4ConfigObjectPathTmp.path();
        }
        ipV4Config = IpConfig();
        Q_EMIT q->ipV4ConfigChanged();
    } else if (property == QLatin1String("Ip6Config")) {
        QDBusObjectPath ip6ConfigObjectPathTmp = (value).value<QDBusObjectPath>();
        if (ip6ConfigObjectPathTmp.path().isNull() || ip6ConfigObjectPathTmp.path() == QLatin1String("/")) {
            ipV6ConfigPath.clear();
        } else {
            ipV6ConfigPath = ip6ConfigObjectPathTmp.path();
        }
        ipV6Config = IpConfig();
        Q_EMIT q->ipV6ConfigChanged();
    } else if (property == QLatin1String("Id")) {
        id = value.toString();
        Q_EMIT q->idChanged(id);
    } else if (property == QLatin1String("Type")) {
        type = value.toString();
        Q_EMIT q->typeChanged(NetworkManager::ConnectionSettings::typeFromString(type));
    }  else if (property == QLatin1String("Master")) {
        master = qdbus_cast<QDBusObjectPath>(value).path();
        Q_EMIT q->masterChanged(master);
    } else if (property == QLatin1String("SpecificObject")) {
        specificObject = qdbus_cast<QDBusObjectPath>(value).path();
        Q_EMIT q->specificObjectChanged(specificObject);
    } else if (property == QLatin1String("State")) {
        state = NetworkManager::ActiveConnectionPrivate::convertActiveConnectionState(value.toUInt());
        Q_EMIT q->stateChanged(state);
    } else if (property == QLatin1String("Vpn")) {
        vpn = value.toBool();
        Q_EMIT q->vpnChanged(vpn);
    } else if (property == QLatin1String("Uuid")) {
        uuid = value.toString();
        Q_EMIT q->uuidChanged(uuid);
    } else if (property == QLatin1String("Devices")) {
        devices.clear();
        Q_FOREACH (const QDBusObjectPath & path, qdbus_cast< QList<QDBusObjectPath> >(value)) {
            devices.append(path.path());
        }
        Q_EMIT q->devicesChanged();
    } else {
#ifdef WARN_UNHANDLED
        qCWarning(NMQT) << Q_FUNC_INFO << "Unhandled property" << property;
#endif
    }
}
