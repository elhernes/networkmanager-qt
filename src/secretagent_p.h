/*
    Copyright 2011 Ilia Kats <ilia-kats@gmx.net>

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

#ifndef NETWORKMANAGERQT_SECRETAGENT_P_H
#define NETWORKMANAGERQT_SECRETAGENT_P_H

#include "dbus/agentmanagerinterface.h"
#include "dbus/secretagentadaptor.h"

#include <QObject>

namespace NetworkManager
{
class SecretAgent;
class SecretAgentPrivate
{
    Q_DECLARE_PUBLIC(SecretAgent)
public:
    explicit SecretAgentPrivate(const QString &, SecretAgent *parent = nullptr);
    virtual ~SecretAgentPrivate();
private Q_SLOTS:
    void registerAgent();
private:
    SecretAgent *q_ptr;
    SecretAgentAdaptor agent;
    OrgFreedesktopNetworkManagerAgentManagerInterface agentManager;
    QDBusServiceWatcher watcher;
    QString agentId;
};
}

#endif // NETWORKMANAGERQT_SECRETAGENT_P_H
