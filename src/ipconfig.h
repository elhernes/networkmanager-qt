/*
    * Copyright 2008,2011 Will Stephenson <wstephenson@kde.org>
    * Copyright 2013 Daniel Nicoletti <dantti12@gmail.com>

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

#ifndef NETWORKMANAGERQT_IPCONFIG_H
#define NETWORKMANAGERQT_IPCONFIG_H

#include "networkmanagerqt_export.h"
#include "ipaddress.h"
#include "iproute.h"

// To prevent signals in glib2 be defined by QT
#include <NetworkManager/NetworkManager.h>
#define signals Q_SIGNALS

#include <QtCore/QStringList>
#include <QNetworkAddressEntry>

namespace NetworkManager
{

/**
 * This class represents IP configuration
 */
class NETWORKMANAGERQT_EXPORT IpConfig
{
public:
    /**
     * Constructs an IP config object with a list of @p addresses, @p nameservers, @p domains and @p routes.
     */
    IpConfig(const IpAddresses &addresses,
             const QList<QHostAddress> &nameservers,
             const QStringList &domains,
             const IpRoutes &routes);

    /**
     * Constructs an empty IpConfig object.
     */
    IpConfig();

    /**
     * Destroys this IpConfig object.
     */
    ~IpConfig();

    /**
     * Constructs an IpConfig object that is a copy of the object @p other.
     */
    IpConfig(const IpConfig &other);

    /**
     * Configure this class using the information on the following @p path
     */
    void setIPv4Path(const QString &path);

    /**
     * Configure this class using the information on the following @p path
     */
    void setIPv6Path(const QString &path);

    /**
     * Returns a list of IP addresses and gateway related to this configuration.
     * Use IpAddress::ip() to access the IP address and IpAddress::gateway()
     * to access the gateway address.
     */
    NetworkManager::IpAddresses addresses() const;

    /**
     * Returns a list of domains related to this configuration.
     */
    QStringList domains() const;

    /**
     * Returns the gateway in use
     *
     * @since 0.9.9.0
     */
    QString gateway() const;

    /**
     * Returns a list of nameservers related to this configuration.
     */
    QList<QHostAddress> nameservers() const;

    /**
     * Returns a list of static routes (not the default gateway) related to this configuration.
     * Use @ref addresses() to retrieve the default gateway.
     */
    IpRoutes routes() const;

    /**
     * Returns a list of DNS searches.
     *
     * @since 0.9.9.0
     */
    QStringList searches() const;

    /**
     * Returns a list of DNS options that modify the behaviour of the DNS resolver.
     * @since 5.14.0
     * @note always returns default constructed QStringList in runtime NM < 1.2.0
     */
    QStringList dnsOptions() const;

    /**
     * Makes a copy of the IpConfig object @p other.
     */
    IpConfig &operator=(const IpConfig &other);

    /**
     * Returns false if the list of IP addresses is empty
     */
    bool isValid() const;

private:
    class Private;
    Private *const d;
};

} // namespace NetworkManager

#endif // NETWORKMANAGERQT_IPCONFIG_H
