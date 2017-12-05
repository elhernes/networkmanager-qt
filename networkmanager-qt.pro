TARGET=NetworkManagerQt
TEMPLATE=lib

QT += dbus network
CONFIG+=shared_and_static link_pkgconfig
PKGCONFIG=libnm

INCLUDEPATH=$${PWD}/src

#DEFINES+=WARN_UNHANDLED

optional_modules+=wireless
optional_modules+=wired
#optional_modules+=adsl # broken
#optional_modules+=team # broken
#optional_modules+=wimax # broken 
#optional_modules+=gsm # broken 
#optional_modules+=ppp # broken 
optional_modules+=ppoe
optional_modules+=serial
optional_modules+=tun
optional_modules+=bridge
optional_modules+=vlan
optional_modules+=modem
optional_modules+=bond
optional_modules+=bluetooth
#optional_modules+=infiniband # broken
optional_modules+=cdma
# optional_modules+=olpcmesh # broken

##################################################
# wireless
SRC_wireless= \
    $${PWD}/src/settings/wirelesssetting.cpp \
    $${PWD}/src/settings/wirelesssecuritysetting.cpp \
    $${PWD}/src/dbus/wirelessdeviceinterface.cpp \
    $${PWD}/src/wirelessnetwork.cpp \
    $${PWD}/src/wirelessdevice.cpp

HDR_wireless= \
    $${PWD}/src/settings/wirelesssecuritysetting.h \
    $${PWD}/src/settings/wirelesssetting.h \
    $${PWD}/src/wirelessnetwork.h \
    $${PWD}/src/wirelessdevice.h \
    $${PWD}/src/dbus/wirelessdeviceinterface.h

pHDR_wireless= \
    $${PWD}/src/settings/wirelesssetting_p.h \
    $${PWD}/src/settings/wirelesssecuritysetting_p.h \
    $${PWD}/src/wirelessnetwork_p.h \
    $${PWD}/src/wirelessdevice_p.h \

DEF_wireless=WITH_WIRELESS

##################################################
# wired
SRC_wired=\
    $${PWD}/src/settings/wiredsetting.cpp \
    $${PWD}/src/wireddevice.cpp \
    $${PWD}/src/dbus/wireddeviceinterface.cpp

HDR_wired=\
    $${PWD}/src/wireddevice.h \
    $${PWD}/src/dbus/wireddeviceinterface.h \
    $${PWD}/src/settings/wiredsetting.h

pHDR_wired=\
    $${PWD}/src/settings/wiredsetting_p.h \
    $${PWD}/src/wireddevice_p.h

DEF_wired=WITH_WIRED

##################################################
# adsl - broken

SRC_adsl=\
    $${PWD}/src/adsldevice.cpp \
    $${PWD}/src/settings/adslsetting.cpp \
    $${PWD}/src/dbus/adsldeviceinterface.cpp

HDR_adsl=\
    $${PWD}/src/settings/adslsetting.h \
    $${PWD}/src/dbus/adsldeviceinterface.h \
    $${PWD}/src/adsldevice.h
pHDR_adsl=\
    $${PWD}/src/settings/adslsetting_p.h \
    $${PWD}/src/adsldevice_p.h

DEF_adsl=WITH_ADSL

##################################################
# team - broken
SRC_team=\
    $${PWD}/src/settings/teamsetting.cpp \
    $${PWD}/src/dbus/teamdeviceinterface.cpp \
    $${PWD}/src/teamdevice.cpp

HDR_team=\
    $${PWD}/src/settings/teamsetting.h \
    $${PWD}/src/dbus/teamdeviceinterface.h \
    $${PWD}/src/teamdevice.h
pHDR_team=\
    $${PWD}/src/settings/teamsetting_p.h \
    $${PWD}/src/teamdevice_p.h

DEF_team=WITH_TEAM

##################################################
# wimax

SRC_wimax=\
    $${PWD}/src/settings/wimaxsetting.cpp \
    $${PWD}/src/dbus/wimaxnspinterface.cpp \
    $${PWD}/src/dbus/wimaxdeviceinterface.cpp \
    $${PWD}/src/wimaxnsp.cpp \
    $${PWD}/src/wimaxdevice.cpp

HDR_wimax=\
    $${PWD}/src/settings/wimaxsetting.h \
    $${PWD}/src/dbus/wimaxnspinterface.h \
    $${PWD}/src/dbus/wimaxdeviceinterface.h \
    $${PWD}/src/wimaxdevice.h \
    $${PWD}/src/wimaxnsp.h
pHDR_wimax=\
    $${PWD}/src/settings/wimaxsetting_p.h \
    $${PWD}/src/wimaxnsp_p.h \
    $${PWD}/src/wimaxdevice_p.h

DEF_wimax=WITH_WIMAX

##################################################
# gsm

SRC_gsm=\
    $${PWD}/src/settings/gsmsetting.cpp

HDR_gsm=\
    $${PWD}/src/settings/gsmsetting.h

pHDR_gsm=\
    $${PWD}/src/settings/gsmsetting_p.h

DEF_gsm=WITH_GSM

##################################################
# ppp - broken

SRC_ppp=\
    $${PWD}/src/settings/pppsetting.cpp
    $${PWD}/src/dbus/pppinterface.cpp

HDR_ppp=\
    $${PWD}/src/dbus/pppinterface.h \
    $${PWD}/src/settings/pppsetting.h
pHDR_ppp=\
    $${PWD}/src/settings/pppsetting_p.h \

DEF_ppp=WITH_PPP

##################################################
# ppoe

SRC_ppoe=\
    $${PWD}/src/settings/pppoesetting.cpp

HDR_ppoe=\
    $${PWD}/src/settings/pppoesetting.h
pHDR_ppoe=\
    $${PWD}/src/settings/pppoesetting_p.h

DEF_ppoe=WITH_PPOE

##################################################
# serial
SRC_serial=\
    $${PWD}/src/settings/serialsetting.cpp \

HDR_serial=\
    $${PWD}/src/settings/serialsetting.h
pHDR_serial=\
    $${PWD}/src/settings/serialsetting_p.h

DEF_serial=WITH_SERIAL

##################################################
# tun

SRC_tun=\
    $${PWD}/src/settings/tunsetting.cpp \
    $${PWD}/src/dbus/tundeviceinterface.cpp \
    $${PWD}/src/tundevice.cpp

HDR_tun=\
    $${PWD}/src/settings/tunsetting.h \
    $${PWD}/src/dbus/tundeviceinterface.h \
    $${PWD}/src/tundevice.h

pHDR_tun=\
    $${PWD}/src/settings/tunsetting_p.h \
    $${PWD}/src/tundevice_p.h \

DEF_tun=WITH_TUN

##################################################
# bridge
SRC_bridge=\
    $${PWD}/src/settings/bridgesetting.cpp \
    $${PWD}/src/settings/bridgeportsetting.cpp \
    $${PWD}/src/dbus/bridgedeviceinterface.cpp \
    $${PWD}/src/bridgedevice.cpp
    
HDR_bridge=\
    $${PWD}/src/settings/bridgesetting.h \
    $${PWD}/src/settings/bridgeportsetting.h \
    $${PWD}/src/dbus/bridgedeviceinterface.h \
    $${PWD}/src/bridgedevice.h
pHDR_bridge=\
    $${PWD}/src/settings/bridgesetting_p.h \
    $${PWD}/src/settings/bridgeportsetting_p.h \
    $${PWD}/src/bridgedevice_p.h \

DEF_bridge=WITH_BRIDGE

##################################################
# vlan
SRC_vlan=\
    $${PWD}/src/vlandevice.cpp \
    $${PWD}/src/dbus/vlandeviceinterface.cpp \
    $${PWD}/src/settings/vlansetting.cpp
	
HDR_vlan=\
    $${PWD}/src/settings/vlansetting.h \
    $${PWD}/src/dbus/vlandeviceinterface.h \
    $${PWD}/src/vlandevice.h
pHDR_vlan=\
    $${PWD}/src/settings/vlansetting_p.h \
    $${PWD}/src/vlandevice_p.h \

DEF_vlan=WITH_VLAN

##################################################
# modem
SRC_modem=\
    $${PWD}/src/dbus/modemdeviceinterface.cpp \
    $${PWD}/src/modemdevice.cpp

HDR_modem=\
    $${PWD}/src/dbus/modemdeviceinterface.h \
    $${PWD}/src/modemdevice.h
pHDR_modem=\
    $${PWD}/src/modemdevice_p.h

DEF_modem=WITH_MODEM

##################################################
# bond
SRC_bond=\
    $${PWD}/src/settings/bondsetting.cpp \
    $${PWD}/src/dbus/bonddeviceinterface.cpp \
    $${PWD}/src/bonddevice.cpp

HDR_bond=\
    $${PWD}/src/settings/bondsetting.h \
    $${PWD}/src/dbus/bonddeviceinterface.h \
    $${PWD}/src/bonddevice.h
pHDR_bond=\
    $${PWD}/src/bonddevice_p.h
    $${PWD}/src/settings/bondsetting_p.h \

DEF_bond=WITH_BOND

##################################################
# bluetooth
SRC_bluetooth=\
    $${PWD}/src/settings/bluetoothsetting.cpp \
    $${PWD}/src/dbus/bluetoothdeviceinterface.cpp \
    $${PWD}/src/bluetoothdevice.cpp

HDR_bluetooth=\
    $${PWD}/src/settings/bluetoothsetting.h \
    $${PWD}/src/dbus/bluetoothdeviceinterface.h \
    $${PWD}/src/bluetoothdevice.h
pHDR_bluetooth=\
    $${PWD}/src/settings/bluetoothsetting_p.h \
    $${PWD}/src/bluetoothdevice_p.h

DEF_bluetooth=WITH_BLUETOOTH

##################################################
# infiniband -broken
SRC_infiniband=\
    $${PWD}/src/settings/infinibandsetting.cpp \
    $${PWD}/src/dbus/infinibanddeviceinterface.cpp \
    $${PWD}/src/infinibanddevice.cpp

HDR_infiniband=\
    $${PWD}/src/settings/infinibandsetting.h \
    $${PWD}/src/dbus/infinibanddeviceinterface.h \
    $${PWD}/src/infinibanddevice.h
pHDR_infiniband=\
    $${PWD}/src/settings/infinibandsetting_p.h \
    $${PWD}/src/infinibanddevice_p.h

DEF_infiniband=WITH_INFINIBAND

##################################################
# cdma

SRC_cdma=\
    $${PWD}/src/settings/cdmasetting.cpp

HDR_cdma=\
    $${PWD}/src/settings/cdmasetting.h \
    $${PWD}/src/settings/cdmasetting.h
pHDR_cdma=\
    $${PWD}/src/settings/cdmasetting_p.h \

DEF_cdma=WITH_CDMA

##################################################
#  olpcmesh
SRC_olpcmesh=\
    $${PWD}/src/olpcmeshdevice.cpp \
    $${PWD}/src/settings/olpcmeshsetting.cpp \
    $${PWD}/src/dbus/olpcmeshdeviceinterface.cpp

HDR_olpcmesh=\
    $${PWD}/src/settings/olpcmeshsetting.h \
    $${PWD}/src/dbus/olpcmeshdeviceinterface.h \
    $${PWD}/src/olpcmeshdevice.h

pHDR_olpcmesh=\
    $${PWD}/src/olpcmeshdevice_p.h \
    $${PWD}/src/settings/olpcmeshsetting_p.h

DEF_olpcmesh=WITH_OLPCMESH

###################################################
##  xxx
#SRC_xxx=\
#HDR_=\
#pHDR_xxx=\
#DEF_xxx

SOURCES_settings=\
    $${PWD}/src/settings/setting.cpp \
    $${PWD}/src/settings/connectionsettings.cpp \
    $${PWD}/src/settings/security8021xsetting.cpp \
    $${PWD}/src/settings/ipv6setting.cpp \
    $${PWD}/src/settings/genericsetting.cpp \
    $${PWD}/src/settings/vpnsetting.cpp \
    $${PWD}/src/settings/ipv4setting.cpp \

#    $${PWD}/src/settings/template.cpp \
#    $${PWD}/src/settings/template_p.h \
#    $${PWD}/src/settings/template.h \

HEADERS_settings=\
    $${PWD}/src/settings/vpnsetting.h \
    $${PWD}/src/settings/genericsetting.h \
    $${PWD}/src/settings/security8021xsetting_p.h \
    $${PWD}/src/settings/connectionsettings.h \
    $${PWD}/src/settings/ipv6setting.h \
    $${PWD}/src/settings/connectionsettings_p.h \
    $${PWD}/src/settings/security8021xsetting.h \
    $${PWD}/src/settings/ipv6setting_p.h \
    $${PWD}/src/settings/ipv4setting.h \
    $${PWD}/src/settings/ipv4setting_p.h \
    $${PWD}/src/settings/vpnsetting_p.h \
    $${PWD}/src/settings/setting.h \
    $${PWD}/src/settings/genericsetting_p.h \

SOURCES_dbus=\
    $${PWD}/src/dbus/checkpointinterface.cpp \
    $${PWD}/src/dbus/vethdeviceinterface.cpp \
    $${PWD}/src/dbus/vpnconnectioninterface.cpp \
    $${PWD}/src/dbus/devicestatisticsinterface.cpp \
    $${PWD}/src/dbus/gredeviceinterface.cpp \
    $${PWD}/src/dbus/dnsmanagerinterface.cpp \
    $${PWD}/src/dbus/genericdeviceinterface.cpp \
    $${PWD}/src/dbus/accesspointinterface.cpp \
    $${PWD}/src/dbus/activeconnectioninterface.cpp \
    $${PWD}/src/dbus/secretagentadaptor.cpp \
    $${PWD}/src/dbus/macsecdeviceinterface.cpp \
    $${PWD}/src/dbus/ip4configinterface.cpp \
    $${PWD}/src/dbus/settingsinterface.cpp \
    $${PWD}/src/dbus/dhcp6configinterface.cpp \
    $${PWD}/src/dbus/agentmanagerinterface.cpp \
    $${PWD}/src/dbus/iptunneldeviceinterface.cpp \
    $${PWD}/src/dbus/ip6configinterface.cpp \
    $${PWD}/src/dbus/networkmanagerinterface.cpp \
    $${PWD}/src/dbus/dhcp4configinterface.cpp \
    $${PWD}/src/dbus/vxlandeviceinterface.cpp \
    $${PWD}/src/dbus/connectioninterface.cpp \
    $${PWD}/src/dbus/deviceinterface.cpp \
    $${PWD}/src/dbus/vpnplugininterface.cpp \
    $${PWD}/src/dbus/macvlandeviceinterface.cpp

HEADERS_dbus=\
    $${PWD}/src/dbus/vpnplugininterface.h \
    $${PWD}/src/dbus/networkmanagerinterface.h \
    $${PWD}/src/dbus/secretagentadaptor.h \
    $${PWD}/src/dbus/accesspointinterface.h \
    $${PWD}/src/dbus/gredeviceinterface.h \
    $${PWD}/src/dbus/vpnconnectioninterface.h \
    $${PWD}/src/dbus/ip4configinterface.h \
    $${PWD}/src/dbus/dhcp4configinterface.h \
    $${PWD}/src/dbus/devicestatisticsinterface.h \
    $${PWD}/src/dbus/macsecdeviceinterface.h \
    $${PWD}/src/dbus/vethdeviceinterface.h \
    $${PWD}/src/dbus/activeconnectioninterface.h \
    $${PWD}/src/dbus/agentmanagerinterface.h \
    $${PWD}/src/dbus/checkpointinterface.h \
    $${PWD}/src/dbus/iptunneldeviceinterface.h \
    $${PWD}/src/dbus/vxlandeviceinterface.h \
    $${PWD}/src/dbus/settingsinterface.h \
    $${PWD}/src/dbus/dnsmanagerinterface.h \
    $${PWD}/src/dbus/genericdeviceinterface.h \
    $${PWD}/src/dbus/connectioninterface.h \
    $${PWD}/src/dbus/macvlandeviceinterface.h \
    $${PWD}/src/dbus/deviceinterface.h \
    $${PWD}/src/dbus/ip6configinterface.h \
    $${PWD}/src/dbus/dhcp6configinterface.h \

SOURCES_src= \
    $${PWD}/src/device.cpp \
    $${PWD}/src/ipconfig.cpp \
    $${PWD}/src/iproute.cpp \
    $${PWD}/src/manager.cpp \

HEADERS_src= \
    $${PWD}/src/device.h \
    $${PWD}/src/device_p.h \
    $${PWD}/src/ipconfig.h \
    $${PWD}/src/iproute.h \
    $${PWD}/src/manager_p.h \
    $${PWD}/src/manager.h \

SOURCES_src+= \
    $${PWD}/src/vpnconnection.cpp \
    $${PWD}/src/utils.cpp \
    $${PWD}/src/dhcp6config.cpp \
    $${PWD}/src/vpnplugin.cpp \
    $${PWD}/src/vethdevice.cpp \
    $${PWD}/src/gredevice.cpp \
    $${PWD}/src/ipaddress.cpp \
    $${PWD}/src/activeconnection.cpp \
    $${PWD}/src/secretagent.cpp \
    $${PWD}/src/devicestatistics.cpp \
    $${PWD}/src/dhcp4config.cpp \
    $${PWD}/src/genericdevice.cpp \
    $${PWD}/src/macvlandevice.cpp \
    $${PWD}/src/iptunneldevice.cpp \
    $${PWD}/src/generictypes.cpp \
    $${PWD}/src/connection.cpp \
    $${PWD}/src/settings.cpp \
    $${PWD}/src/accesspoint.cpp

HEADERS_src+= \
    $${PWD}/src/connection.h \
    $${PWD}/src/iptunneldevice.h \
    $${PWD}/src/vethdevice_p.h \
    $${PWD}/src/utils.h \
    $${PWD}/src/gredevice.h \
    $${PWD}/src/vpnconnection_p.h \
    $${PWD}/src/dhcp6config_p.h \
    $${PWD}/src/devicestatistics.h \
    $${PWD}/src/ipaddress.h \
    $${PWD}/src/genericdevice.h \
    $${PWD}/src/settings.h \
    $${PWD}/src/macvlandevice.h \
    $${PWD}/src/activeconnection_p.h \
    $${PWD}/src/gredevice_p.h \
    $${PWD}/src/vpnplugin.h \
    $${PWD}/src/secretagent.h \
    $${PWD}/src/nmdebug.h \
    $${PWD}/src/accesspoint.h \
    $${PWD}/src/macvlandevice_p.h \
    $${PWD}/src/macros.h \
    $${PWD}/src/dhcp4config_p.h \
    $${PWD}/src/genericdevice_p.h \
    $${PWD}/src/generictypes.h \
    $${PWD}/src/devicestatistics_p.h \
    $${PWD}/src/secretagent_p.h \
    $${PWD}/src/dhcp4config.h \
    $${PWD}/src/activeconnection.h \
    $${PWD}/src/settings_p.h \
    $${PWD}/src/accesspoint_p.h \
    $${PWD}/src/vethdevice.h \
    $${PWD}/src/dhcp6config.h \
    $${PWD}/src/vpnconnection.h \
    $${PWD}/src/connection_p.h \
    $${PWD}/src/iptunneldevice_p.h \

SOURCES_fake= \
    $${PWD}/src/fakenetwork/device.cpp \
    $${PWD}/src/fakenetwork/activeconnection.cpp \
    $${PWD}/src/fakenetwork/fakenetwork.cpp \
    $${PWD}/src/fakenetwork/wirelessdevice.cpp \
    $${PWD}/src/fakenetwork/wireddevice.cpp \
    $${PWD}/src/fakenetwork/connection.cpp \
    $${PWD}/src/fakenetwork/settings.cpp \
    $${PWD}/src/fakenetwork/accesspoint.cpp \
       
HEADERS_fake=\
    $${PWD}/src/fakenetwork/connection.h \
    $${PWD}/src/fakenetwork/device.h \
    $${PWD}/src/fakenetwork/settings.h \
    $${PWD}/src/fakenetwork/fakenetwork.h \
    $${PWD}/src/fakenetwork/accesspoint.h \
    $${PWD}/src/fakenetwork/wireddevice.h \
    $${PWD}/src/fakenetwork/activeconnection.h \
    $${PWD}/src/fakenetwork/wirelessdevice.h

SOURCES+= \
    $${SOURCES_src} \
    $${SOURCES_dbus} \
    $${SOURCES_settings} \
    $${SOURCES_example}

HEADERS+= \
    $${HEADERS_src} \
    $${HEADERS_dbus} \
    $${HEADERS_settings} \

for(m, optional_modules) {
    message(including $${m})
    eval(SOURCES+=\$${SRC_$${m}})
    eval(HEADERS+=\$${HDR_$${m}} \$${pHDR_$${m}})
    eval(DEFINES+=\$${DEF_$${m}})
}

PUBLIC_HEADERS=\
  AccessPoint \
  ActiveConnection \
  AdslDevice \
  BluetoothDevice \
  BondDevice \
  BridgeDevice \
  Connection \
  Device \
  DeviceStatistics \
  Dhcp4Config \
  Dhcp6Config \
  GenericDevice \
  GenericTypes \
  GreDevice \
  InfinibandDevice \
  IpAddress \
  IpConfig \
  IpRoute \
  IpTunnelDevice \
  MacVlanDevice \
  Manager \
  ModemDevice \
  OlpcMeshDevice \
  SecretAgent \
  Settings \
  TeamDevice \
  TunDevice \
  Utils \
  VethDevice \
  VlanDevice \
  VpnConnection \
  VpnPlugin \
  WimaxDevice \
  WimaxNsp \
  WiredDevice \
  WirelessDevice \
  WirelessNetwork

PUBLIC_HEADERS_SETTINGS=\
  AdslSetting \
  BluetoothSetting \
  BondSetting \
  BridgeSetting \
  BridgePortSetting \
  CdmaSetting \
  ConnectionSettings \
  GsmSetting \
  GenericSetting \
  InfinibandSetting \
  Ipv4Setting \
  Ipv6Setting \
  OlpcMeshSetting \
  PppoeSetting \
  PppSetting \
  Security8021xSetting \
  SerialSetting \
  Setting \
  TeamSetting \
  TunSetting \
  VlanSetting \
  VpnSetting \
  WimaxSetting \
  WiredSetting \
  WirelessSecuritySetting \
  WirelessSetting

system(mkdir -p $${PWD}/include/NetworkManagerQt/settings) {
    message(mkdir ok)
}

defineReplace(generateHeader) {
    cc=$${1}
    path=$${2}
    f=$$lower($${cc}.h)
    isEmpty(path) {
	dots=../..
    } else {
	path=$${path}/
	dots=../../../
    }
    t=include/NetworkManagerQt/$${cc}
    inc="$${LITERAL_HASH}include \"$${f}\""
    write_file($${PWD}/$${t}, inc)
#    message(ln -sf $${dots}src/$${path}$${f} include/NetworkManagerQt/$${path}$${f})
    return(src/$${path}$${f} $${t})
}

for(h, PUBLIC_HEADERS) {
    public_headers.files += $$generateHeader($${h})
}

for(h, PUBLIC_HEADERS_SETTINGS) {
    public_headers_settings.files += $$generateHeader($${h},settings)
}

message($${public_headers.files})
message($${public_headers_settings.files})

isEmpty(INSTALL_PREFIX):INSTALL_PREFIX=/usr

public_headers.files+= src/networkmanagerqt_export.h

public_headers.path = $${INSTALL_PREFIX}/include/NetworkManagerQt
public_headers_settings.path = $${INSTALL_PREFIX}/include/NetworkManagerQt/settings

INSTALLS+= public_headers public_headers_settings target

target.path=$${INSTALL_PREFIX}/lib

