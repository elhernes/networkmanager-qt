/*
 * This file was generated by qdbusxml2cpp version 0.7
 * Command line was: qdbusxml2cpp -m -p nm-access-pointinterface /home/ilia/libQtNetworkManager/libQtNetworkManager/dbus/introspection/nm-access-point.xml
 *
 * qdbusxml2cpp is Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
 *
 * This is an auto-generated file.
 * This file may have been hand-edited. Look for HAND-EDIT comments
 * before re-generating it.
 */

#include "nm-access-pointinterface.h"

/*
 * Implementation of interface class OrgFreedesktopNetworkManagerAccessPointInterface
 */

OrgFreedesktopNetworkManagerAccessPointInterface::OrgFreedesktopNetworkManagerAccessPointInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

OrgFreedesktopNetworkManagerAccessPointInterface::~OrgFreedesktopNetworkManagerAccessPointInterface()
{
}


#include "nm-access-pointinterface.moc"
