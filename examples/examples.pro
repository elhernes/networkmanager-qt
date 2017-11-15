TARGET=nmqt
TEMPLATE=app

INSTALL_PATH=/Volumes/Data/xyz

INCLUDEPATH+=$${INSTALL_PATH}/include

QT += dbus network
LIBS+=-L$${INSTALL_PATH}/lib -lNetworkManagerQt

SOURCES=main.cpp
