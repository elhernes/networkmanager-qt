/*
    Copyright 2011-2013 Lamarque V. Souza <lamarque@kde.org>
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

#ifndef NETWORKMANAGERQT_DHCP6CONFIG_H
#define NETWORKMANAGERQT_DHCP6CONFIG_H

#include "generictypes.h"

#include "networkmanagerqt_export.h"

#include <QtCore/QStringList>
#include <QSharedPointer>

namespace NetworkManager
{
class Dhcp6ConfigPrivate;

/**
 * This class represents dhcp4 configuration
 */
class NETWORKMANAGERQT_EXPORT Dhcp6Config: public QObject
{
    Q_OBJECT
public:
    typedef QSharedPointer<Dhcp6Config> Ptr;
    typedef QList<Ptr> List;

    explicit Dhcp6Config(const QString &path, QObject *owner = nullptr);
    ~Dhcp6Config();

    QString path() const;

    QVariantMap options() const;

    QString optionValue(const QString &key) const;

Q_SIGNALS:
    void optionsChanged(const QVariantMap &);

private:
    Q_DECLARE_PRIVATE(Dhcp6Config)

    Dhcp6ConfigPrivate *const d_ptr;
};
} // namespace NetworkManager

#endif // NETWORKMANAGERQT_DHCP6CONFIG_H
