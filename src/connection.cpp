/*
    Copyright 2008,2009 Will Stephenson <wstephenson@kde.org>
    Copyright 2011 Ilia Kats <ilia-kats@gmx.net>
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

#include "connection_p.h"

#undef signals
#include <NetworkManager/NetworkManager.h>
#define signals Q_SIGNALS

#include <QDBusConnection>
#include <QDBusPendingReply>
#include <QDBusPendingCallWatcher>

#include "nmdebug.h"

NetworkManager::ConnectionPrivate::ConnectionPrivate(const QString &path, Connection *q)
#ifdef NMQT_STATIC
    : iface(NetworkManagerPrivate::DBUS_SERVICE, path, QDBusConnection::sessionBus())
#else
    : iface(NetworkManagerPrivate::DBUS_SERVICE, path, QDBusConnection::systemBus())
#endif
    , q_ptr(q)
{ }

NetworkManager::Connection::Connection(const QString &path, QObject *parent)
    : QObject(parent)
    , d_ptr(new ConnectionPrivate(path, this))
{
    Q_D(Connection);

    qDBusRegisterMetaType<NMVariantMapMap>();
    QDBusReply<NMVariantMapMap> reply = d->iface.GetSettings();
    if (reply.isValid()) {
        d->updateSettings(reply.value());
    } else {
        d->updateSettings();
    }
    d->path = path;
    //qCDebug(NMQT) << m_connection;

    connect(&d->iface, &OrgFreedesktopNetworkManagerSettingsConnectionInterface::Updated, d, &ConnectionPrivate::onConnectionUpdated);
    connect(&d->iface, &OrgFreedesktopNetworkManagerSettingsConnectionInterface::Removed, d, &ConnectionPrivate::onConnectionRemoved);
    d->unsaved = d->iface.unsaved();
#if NM_CHECK_VERSION(1, 4, 0)
    QDBusConnection::systemBus().connect(NetworkManagerPrivate::DBUS_SERVICE, d->path, NetworkManagerPrivate::FDO_DBUS_PROPERTIES,
                                         QLatin1String("PropertiesChanged"), d, SLOT(dbusPropertiesChanged(QString,QVariantMap,QStringList)));
#else
    connect(&d->iface, &OrgFreedesktopNetworkManagerSettingsConnectionInterface::PropertiesChanged, d, &ConnectionPrivate::onPropertiesChanged);
#endif
}

NetworkManager::Connection::~Connection()
{
    delete d_ptr;
}

bool NetworkManager::Connection::isValid() const
{
    Q_D(const Connection);
    return d->iface.isValid();
}

QString NetworkManager::Connection::uuid() const
{
    Q_D(const Connection);
    return d->uuid;
}

QString NetworkManager::Connection::name() const
{
    Q_D(const Connection);
    return d->id;
}

bool NetworkManager::Connection::isUnsaved() const
{
    Q_D(const Connection);
    return d->unsaved;
}

NetworkManager::ConnectionSettings::Ptr NetworkManager::Connection::settings()
{
    Q_D(Connection);

    if (d->connection.isNull()) {
        d->connection = ConnectionSettings::Ptr(new ConnectionSettings(d->settings));
    }
    return d->connection;
}

QDBusPendingReply<NMVariantMapMap> NetworkManager::Connection::secrets(const QString &setting)
{
    Q_D(Connection);
    return d->iface.GetSecrets(setting);
}

QDBusPendingReply<> NetworkManager::Connection::update(const NMVariantMapMap &settings)
{
    Q_D(Connection);
    return d->iface.Update(settings);
}

QDBusPendingReply<> NetworkManager::Connection::updateUnsaved(const NMVariantMapMap &settings)
{
    Q_D(Connection);
    return d->iface.UpdateUnsaved(settings);
}

QDBusPendingReply<> NetworkManager::Connection::save()
{
    Q_D(Connection);
    return d->iface.Save();
}

QDBusPendingReply<> NetworkManager::Connection::clearSecrets()
{
    Q_D(Connection);
    return d->iface.ClearSecrets();
}

QDBusPendingReply<> NetworkManager::Connection::remove()
{
    Q_D(Connection);
    return d->iface.Delete();
}

QString NetworkManager::Connection::path() const
{
    Q_D(const Connection);
    return d->path;
}

void NetworkManager::ConnectionPrivate::onConnectionUpdated()
{
    Q_Q(Connection);
    QDBusReply<NMVariantMapMap> reply = iface.GetSettings();
    if (reply.isValid()) {
        updateSettings(reply.value());
    } else {
        updateSettings();
    }
    Q_EMIT q->updated();
}

void NetworkManager::ConnectionPrivate::onConnectionRemoved()
{
    Q_Q(Connection);
    QString tmpPath = path;
    updateSettings();
    Q_EMIT q->removed(tmpPath);
}

void NetworkManager::ConnectionPrivate::dbusPropertiesChanged(const QString &interfaceName, const QVariantMap &properties, const QStringList &invalidatedProperties)
{
    Q_UNUSED(invalidatedProperties);
    if (interfaceName == QLatin1String("org.freedesktop.NetworkManager.Settings.Connection")) {
        onPropertiesChanged(properties);
    }
}

void NetworkManager::ConnectionPrivate::onPropertiesChanged(const QVariantMap &properties)
{
    Q_Q(Connection);
    QVariantMap::const_iterator it = properties.constBegin();
    while (it != properties.constEnd()) {
        const QString property = it.key();
        if (property == QLatin1String("Unsaved")) {
            unsaved = it->toBool();
            Q_EMIT q->unsavedChanged(unsaved);
        } else {
#ifdef WARN_UNHANDLED
            qCWarning(NMQT) << Q_FUNC_INFO << "Unhandled property" << property;
#endif
        }
        ++it;
    }
}

void NetworkManager::ConnectionPrivate::updateSettings(const NMVariantMapMap &newSettings)
{
    settings = newSettings;
    if (settings.contains(QLatin1String(NM_SETTING_CONNECTION_SETTING_NAME))) {
        QVariantMap connectionSetting = settings.value(QLatin1String(NM_SETTING_CONNECTION_SETTING_NAME));
        if (connectionSetting.contains(QLatin1String(NM_SETTING_CONNECTION_UUID))) {
            uuid = connectionSetting.value(QLatin1String(NM_SETTING_CONNECTION_UUID)).toString();
        }
        if (connectionSetting.contains(QLatin1String(NM_SETTING_CONNECTION_ID))) {
            id = connectionSetting.value(QLatin1String(NM_SETTING_CONNECTION_ID)).toString();
        }
    } else if (newSettings.isEmpty()) {
        uuid.clear();
        id.clear();
    }
    connection.clear();
}
