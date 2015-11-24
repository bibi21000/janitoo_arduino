/*
Janitoo
@author: bibi21000
@copyright: (C) 2011-2015 Sebastien GALLET <bibi21000@gmail.com>
@license: GPL(v3)
*/

void setup_network()
{
  byte mac[L_MAC];
  byte byteval;
  ereadDhcp(byteval);
  ereadMac(mac);
  if (byteval == 1) {
    Ethernet.begin(mac);
  } else {
    // Update these with values suitable for your network.
    IPAddress ip;
    ereadIp(ip);
    Ethernet.begin(mac, ip);
  }
  #ifdef DEBUG_NETWORK
    Serial.print(F("Connect to network using IP "));
    for (byte thisByte = 0; thisByte < 3; thisByte++) {
        // print the value of each byte of the IP address:
        Serial.print(Ethernet.localIP()[thisByte], DEC);
        Serial.print("."); 
      }
    Serial.println(Ethernet.localIP()[3], DEC);    
  #endif
  
}

void loop_network()
{
  Ethernet.maintain();
}
