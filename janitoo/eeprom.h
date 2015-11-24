/*
Janitoo
@author: bibi21000
@copyright: (C) 2011-2015 Sebastien GALLET <bibi21000@gmail.com>
@license: GPL(v3)
*/

//The start index
// Eeprom is write limited. So it could be a good idea to not start writing a start of it.
//
#define START_I 896
//The device state (confiured or not)
#define L_STATE_I START_I
#define L_STATE 4
//The reboot watchdog
#define L_WATCHDOG_I L_STATE_I+L_STATE
#define L_WATCHDOG 1
//The MAC address
#define L_MAC_I L_WATCHDOG_I+L_WATCHDOG
#define L_MAC 6
//Use of DHCP
#define L_DHCP_I L_MAC_I+L_MAC
#define L_DHCP 1
//The static IP address
#define L_IP_I L_DHCP_I+L_DHCP
#define L_IP 4
//The IP broadcast
#define L_BROADCAST_I L_IP_I+L_IP
#define L_BROADCAST 4
//The IP gateway
#define L_GATEWAY_I L_BROADCAST_I+L_BROADCAST
#define L_GATEWAY 4
//The IP dns
#define L_DNS_I L_GATEWAY_I+L_GATEWAY
#define L_DNS 4
//The IP dns
#define L_NTP_I L_DNS_I+L_DNS
#define L_NTP 4
//The IP network
#define L_NETWORK_I L_NTP_I+L_NTP
#define L_NETWORK 4
//The device uuid
#define L_UUID_I L_NETWORK_I+L_NETWORK
#define L_UUID 20+1
//The device name
#define L_NAME_I L_UUID_I+L_UUID
#define L_NAME 20+1
//The device location
#define L_LOCATION_I L_NAME+L_NAME_I
#define L_LOCATION 30+1
//The device product
#define L_PRODUCT_I L_LOCATION+L_LOCATION_I
#define L_PRODUCT 50+1
//The device type
#define L_TYPE_I L_PRODUCT+L_PRODUCT_I
#define L_TYPE 50+1
//The heartbeat
#define L_HEARTBEAT_I L_TYPE+L_TYPE_I
#define L_HEARTBEAT 2
//The controller hadd
#define L_HADD_I L_HEARTBEAT_I+L_HEARTBEAT
#define L_HADD 9+1
//The MQTT server address
#define L_SERVER_I L_HADD_I+L_HADD
#define L_SERVER 4
//Use of DHT1
#define L_DHT1_ENABLED_I L_SERVER_I+L_SERVER
#define L_DHT1_ENABLED 1
//Use of DHT2_ENABLED
#define L_DHT2_ENABLED_I L_DHT1_ENABLED_I+L_DHT1_ENABLED
#define L_DHT2_ENABLED 1
//Poll of DHT1
#define L_DHT1_POLL_I L_DHT2_ENABLED_I+L_DHT2_ENABLED
#define L_DHT1_POLL 2
//Poll of DHT2
#define L_DHT2_POLL_I L_DHT1_POLL_I+L_DHT1_POLL
#define L_DHT2_POLL 2
//Config timeout
#define L_CONFIG_TIMEOUT_I L_DHT2_POLL_I+L_DHT2_POLL
#define L_CONFIG_TIMEOUT 2
//Current RGB color
#define L_RGB_I L_CONFIG_TIMEOUT_I+L_CONFIG_TIMEOUT
#define L_RGB 3
//Current RGB poll delay
#define L_RGB_POLL_I L_RGB_I+L_RGB
#define L_RGB_POLL 3



