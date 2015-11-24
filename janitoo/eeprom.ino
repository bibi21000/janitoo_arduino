/*
Janitoo
@author: bibi21000
@copyright: (C) 2011-2015 Sebastien GALLET <bibi21000@gmail.com>
@license: GPL(v3)
*/

#include "janitoo.h";
#include "eeprom.h";

/***********************************************/
int htoi (char c[2]) {  //does not check that input is valid
    return getDecimal(c[0])*16+getDecimal(c[1]);
}

/***********************************************/
void itoh (char c[2], int b) {  //does not check that input is valid
    c[0] = getHexa(b / 16);
    c[1] = getHexa(b % 16);
}

/***********************************************
   getDecimal
   Get decimal value from a hexadecimal char
   Input : hex value (char)
   Output : decimal (int)
***********************************************/
int getDecimal(char value) {
    int decimal = 0;
    if ((value >= 'a') && (value <= 'f')) {
        decimal = value - 'a' + 10;
    }
    if ((value >= 'A') && (value <= 'F')) {
        decimal = value - 'A' + 10;
    }
    if ((value >= '0') && (value <= '9')) {
        decimal = value - '0';
    }
    return decimal;
}

/***********************************************/
char getHexa(byte value) {
    char hexa = '0';
    if (value<=9) {
      hexa = char('0'+value);
    } else if (value==10) {
      hexa = 'A';
    } else if (value==11) {
      hexa = 'B';
    } else if (value==12) {
      hexa = 'C';
    } else if (value==13) {
      hexa = 'D';
    } else if (value==14) {
      hexa = 'E';
    } else if (value==15) {
      hexa = 'F';
    }
    return hexa;
}

/***********************************************/
void ewriteState(byte data) {
    #ifdef DEBUG_EEPROM
      Serial.print(F("ewriteState "));
      Serial.println(data);
    #endif
    int start=L_STATE_I;
    if (data=1) {
        EEPROM.write(start, 14);
        EEPROM.write(start+1, 25);
        EEPROM.write(start+2, 71);
        EEPROM.write(start+3, 83);
    } else {
        EEPROM.write(start, 0);
        EEPROM.write(start+1, 0);
        EEPROM.write(start+2, 0);
        EEPROM.write(start+3, 0);
    }
}

void ereadState(byte &result) {
    int start=L_STATE_I;
    if (EEPROM.read(start)==14 && EEPROM.read(start+1)==25 && EEPROM.read(start+2)==71 && EEPROM.read(start+3)==83) {
        result=1;
    } else {
        result=0;
    }
    #ifdef DEBUG_EEPROM
      Serial.print(F("ereadState "));
      Serial.println(result);
    #endif
}

/***********************************************/
void setWatchdog() {
    //Update the watchdog
    int start=L_WATCHDOG_I;
    byte dog = EEPROM.read(start);
    dog += 1;
    EEPROM.write(start, dog);
    Serial.print(F("Boot watchdog stage "));
    Serial.println(dog);
}

void checkWatchdog() {
    //Check the watchdog
    int start=L_WATCHDOG_I;
    byte dog = EEPROM.read(start);
    if (dog>5) {
        Serial.println(F("Boot watchdog at work ... generate a new UUID for this material"));
        eGenerateUuid();
        resetWatchdog();
        resetFunc();
    } else if (dog>3) {
        Serial.println(F("Boot watchdog at work ... reset to factory settings"));
        eFactorySettings();
        resetWatchdog();
        resetFunc();
    }
}

void resetWatchdog() {
    int start=L_WATCHDOG_I;
    EEPROM.write(start, 0);
    #ifdef DEBUG_EEPROM
      Serial.println(F("resetWatchdog "));
    #endif
}

/***********************************************/
void ewriteUuid(char data[]) {
    #ifdef DEBUG_EEPROM
      Serial.print(F("ewriteUuid "));
      Serial.println(data);
    #endif
    int start=L_UUID_I;
    int i=0;
    for (i=0; i < L_UUID; i++){
        EEPROM.write(start+i, data[i]);
    }
    EEPROM.write(start+i-1, '\0');
}

void ereadUuid(char result[]) {
    int start=L_UUID_I;
    for (int i=0; i < L_UUID; i++){
        result[i]=EEPROM.read(start+i);
    }
    #ifdef DEBUG_EEPROM
      Serial.print(F("ereadUuid "));
      Serial.println(result);
    #endif
}

/***********************************************/
void ewriteName(char data[]) {
    #ifdef DEBUG_EEPROM
      Serial.print(F("ewriteName "));
      Serial.println(data);
    #endif
    int start=L_NAME_I;
    int i=0;
    for (i=0; i < L_NAME; i++){
        EEPROM.write(start+i, data[i]);
    }
    EEPROM.write(start+i-1, '\0');
}

void ereadName(char result[]) {
    int start=L_NAME_I;
    for (int i=0; i < L_NAME; i++){
        result[i]=EEPROM.read(start+i);
    }
    #ifdef DEBUG_EEPROM
      Serial.print(F("ereadName "));
      Serial.println(result);
    #endif
}

/***********************************************/
void ewriteLocation(char data[]) {
    #ifdef DEBUG_EEPROM
      Serial.print(F("ewriteLocation "));
      Serial.println(data);
    #endif
    int start=L_LOCATION_I;
    int i=0;
    for (i=0; i < L_LOCATION; i++){
        EEPROM.write(start+i, data[i]);
    }
    EEPROM.write(start+i-1, '\0');
}

void ereadLocation(char result[]) {
    int start=L_LOCATION_I;
    for (int i=0; i < L_LOCATION; i++){
        result[i]=EEPROM.read(start+i);
    }
    #ifdef DEBUG_EEPROM
      Serial.print(F("ereadLocation "));
      Serial.println(result);
    #endif
}

/***********************************************/
void ewriteProduct(char data[]) {
    #ifdef DEBUG_EEPROM
      Serial.print(F("ewriteProduct "));
      Serial.println(data);
    #endif
    int start=L_PRODUCT_I;
    int i=0;
    for (i=0; i < L_PRODUCT; i++){
        EEPROM.write(start+i, data[i]);
    }
    EEPROM.write(start+i-1, '\0');
}

void ereadProduct(char result[]) {
    int start=L_PRODUCT_I;
    for (int i=0; i < L_PRODUCT; i++){
        result[i]=EEPROM.read(start+i);
    }
    #ifdef DEBUG_EEPROM
      Serial.print(F("ereadProduct "));
      Serial.println(result);
    #endif
}

/***********************************************/
void ewriteType(char data[]) {
    #ifdef DEBUG_EEPROM
      Serial.print(F("ewriteType "));
      Serial.println(data);
    #endif
    int start=L_TYPE_I;
    int i=0;
    for (i=0; i < L_TYPE; i++){
        EEPROM.write(start+i, data[i]);
    }
    EEPROM.write(start+i-1, '\0');
}

void ereadType(char result[]) {
    int start=L_TYPE_I;
    for (int i=0; i < L_TYPE; i++){
        result[i]=EEPROM.read(start+i);
    }
    #ifdef DEBUG_EEPROM
      Serial.print(F("ereadType "));
      Serial.println(result);
    #endif
}

void ereadTypeFull(char result[]) {
    ereadType(result);
    strcat(result, " (v ");
    strcat(result, VERSION);
    strcat(result, ")");   
    #ifdef DEBUG_EEPROM
      Serial.print(F("ereadTypeFull "));
      Serial.println(result);
    #endif
}

/***********************************************/
void ewriteHadd(char data[]) {
    #ifdef DEBUG_EEPROM
      Serial.print(F("ewriteHadd "));
      Serial.println(data);
    #endif
    int start=L_HADD_I;
    int i=0;
    for (i=0; i < L_HADD; i++){
        EEPROM.write(start+i, data[i]);
    }
    EEPROM.write(start+i-1, '\0');
}

void ereadHadd(char result[]) {
    int start=L_HADD_I;
    for (int i=0; i < L_HADD; i++){
        result[i]=EEPROM.read(start+i);
    }
    #ifdef DEBUG_EEPROM
      Serial.print(F("ereadHadd "));
      Serial.println(result);
    #endif
}

/***********************************************/
void ewriteHeartbeat(int data) {
    #ifdef DEBUG_EEPROM
      Serial.print(F("ewriteHeartbeat "));
      Serial.println(data);
    #endif
    int start=L_HEARTBEAT_I;
    EEPROM.write(start, data);
}

void ereadHeartbeat(int &result) {
    int start=L_HEARTBEAT_I;
    result=EEPROM.read(start);
    #ifdef DEBUG_EEPROM
      Serial.print(F("ereadHeartbeat "));
      Serial.println(result);
    #endif
}

/***********************************************/
void ewriteDhcp(byte data) {
    #ifdef DEBUG_EEPROM
      Serial.print(F("ewriteDhcp "));
      Serial.println(data);
    #endif
    int start=L_DHCP_I;
    EEPROM.write(start, data);
}

void ereadDhcp(byte &result) {
    int start=L_DHCP_I;
    result=EEPROM.read(start);
    #ifdef DEBUG_EEPROM
      Serial.print(F("ereadDhcp "));
      Serial.println(result);
    #endif
}

/***********************************************/
void ewriteIp(char data[]) {
    #ifdef DEBUG_EEPROM
      Serial.print(F("ewriteIp "));
      Serial.println(data);
    #endif
    int start=L_IP_I;
    char buffer[5]="\0";
    int j=0;
    int p=0;
    byte add=0;
    for (int i=0;i<strlen(data);i++) {
        if (data[i]=='.') {
            buffer[j]=0;
            #ifdef DEBUG_EEPROM
                Serial.print(F(" buffer : "));
                Serial.print(buffer);
            #endif
            add=atoi(buffer);
            #ifdef DEBUG_EEPROM
                Serial.print(F(" ip"));
                Serial.print(p);
                Serial.print(F("="));
                Serial.println(add);
            #endif
            if (p<L_IP) {
                EEPROM.write(start+p, add);
            }
            p++;
            j=0;
        } else {
            buffer[j]=data[i];
            j++;
        }
    }
    buffer[j]=0;
    #ifdef DEBUG_EEPROM
        Serial.print(F(" buffer : "));
        Serial.print(buffer);
    #endif
    add=atoi(buffer);
    #ifdef DEBUG_EEPROM
        Serial.print(F(" ip"));
        Serial.print(p);
        Serial.print(F("="));
        Serial.println(add);
    #endif
    if (p<L_IP) {
        EEPROM.write(start+p, add);
    }
}

void ereadIp(IPAddress &result) {
    int start=L_IP_I;
    for (int i=0;i<L_IP;i++) {
            byte by=EEPROM.read(start+i);
            result[i]=int(by);
    }
    #ifdef DEBUG_EEPROM
      Serial.print(F("ereadIp "));
      Serial.println(result);
    #endif
}

/***********************************************/
void ewriteBroadCast(char data[]) {
    #ifdef DEBUG_EEPROM
      Serial.print(F("ewriteBroadCast "));
      Serial.println(data);
    #endif
    int start=L_BROADCAST_I;
    char buffer[5]="\0";
    int j=0;
    int p=0;
    byte add=0;
    for (int i=0;i<strlen(data);i++) {
        if (data[i]=='.') {
            buffer[j]=0;
            #ifdef DEBUG_EEPROM
                Serial.print(F(" buffer : "));
                Serial.print(buffer);
            #endif
            add=atoi(buffer);
            #ifdef DEBUG_EEPROM
                Serial.print(F(" ip"));
                Serial.print(p);
                Serial.print(F("="));
                Serial.println(add);
            #endif
            if (p<L_BROADCAST) {
                EEPROM.write(start+p, add);
            }
            p++;
            j=0;
        } else {
            buffer[j]=data[i];
            j++;
        }
    }
    buffer[j]=0;
    #ifdef DEBUG_EEPROM
        Serial.print(F(" buffer : "));
        Serial.print(buffer);
    #endif
    add=atoi(buffer);
    #ifdef DEBUG_EEPROM
        Serial.print(F(" ip"));
        Serial.print(p);
        Serial.print(F("="));
        Serial.println(add);
    #endif
    if (p<L_BROADCAST) {
        EEPROM.write(start+p, add);
    }
}

void ereadBroadCast(IPAddress &result) {
    int start=L_BROADCAST_I;
    for (int i=0;i<L_BROADCAST;i++) {
            byte by=EEPROM.read(start+i);
            result[i]=int(by);
    }
    #ifdef DEBUG_EEPROM
      Serial.print(F("ereadBroadCast "));
      Serial.println(result);
    #endif
}

/***********************************************/
void ewriteGateway(char data[]) {
    #ifdef DEBUG_EEPROM
      Serial.print(F("ewriteGateway "));
      Serial.println(data);
    #endif
    int start=L_GATEWAY_I;
    char buffer[5]="\0";
    int j=0;
    int p=0;
    byte add=0;
    for (int i=0;i<strlen(data);i++) {
        if (data[i]=='.') {
            buffer[j]=0;
            #ifdef DEBUG_EEPROM
                Serial.print(F(" buffer : "));
                Serial.print(buffer);
            #endif
            add=atoi(buffer);
            #ifdef DEBUG_EEPROM
                Serial.print(F(" ip"));
                Serial.print(p);
                Serial.print(F("="));
                Serial.println(add);
            #endif
            if (p<L_GATEWAY) {
                EEPROM.write(start+p, add);
            }
            p++;
            j=0;
        } else {
            buffer[j]=data[i];
            j++;
        }
    }
    buffer[j]=0;
    #ifdef DEBUG_EEPROM
        Serial.print(F(" buffer : "));
        Serial.print(buffer);
    #endif
    add=atoi(buffer);
    #ifdef DEBUG_EEPROM
        Serial.print(F(" ip"));
        Serial.print(p);
        Serial.print(F("="));
        Serial.println(add);
    #endif
    if (p<L_GATEWAY) {
        EEPROM.write(start+p, add);
    }
}

void ereadGateway(IPAddress &result) {
    int start=L_GATEWAY_I;
    for (int i=0;i<L_GATEWAY;i++) {
            byte by=EEPROM.read(start+i);
            result[i]=int(by);
    }
    #ifdef DEBUG_EEPROM
      Serial.print(F("ereadGateway "));
      Serial.println(result);
    #endif
}

/***********************************************/
void ewriteDns(char data[]) {
    #ifdef DEBUG_EEPROM
      Serial.print(F("ewriteDns "));
      Serial.println(data);
    #endif
    int start=L_DNS_I;
    char buffer[5]="\0";
    int j=0;
    int p=0;
    byte add=0;
    for (int i=0;i<strlen(data);i++) {
        if (data[i]=='.') {
            buffer[j]=0;
            #ifdef DEBUG_EEPROM
                Serial.print(F(" buffer : "));
                Serial.print(buffer);
            #endif
            add=atoi(buffer);
            #ifdef DEBUG_EEPROM
                Serial.print(F(" ip"));
                Serial.print(p);
                Serial.print(F("="));
                Serial.println(add);
            #endif
            if (p<L_DNS) {
                EEPROM.write(start+p, add);
            }
            p++;
            j=0;
        } else {
            buffer[j]=data[i];
            j++;
        }
    }
    buffer[j]=0;
    #ifdef DEBUG_EEPROM
        Serial.print(F(" buffer : "));
        Serial.print(buffer);
    #endif
    add=atoi(buffer);
    #ifdef DEBUG_EEPROM
        Serial.print(F(" ip"));
        Serial.print(p);
        Serial.print(F("="));
        Serial.println(add);
    #endif
    if (p<L_DNS) {
        EEPROM.write(start+p, add);
    }
}

void ereadDns(IPAddress &result) {
    int start=L_DNS_I;
    for (int i=0;i<L_DNS;i++) {
            byte by=EEPROM.read(start+i);
            result[i]=int(by);
    }
    #ifdef DEBUG_EEPROM
      Serial.print(F("ereadDns "));
      Serial.println(result);
    #endif
}

/***********************************************/
void ewriteNetwork(char data[]) {
    #ifdef DEBUG_EEPROM
      Serial.print(F("ewriteNetwork "));
      Serial.println(data);
    #endif
    int start=L_NETWORK_I;
    char buffer[5]="\0";
    int j=0;
    int p=0;
    byte add=0;
    for (int i=0;i<strlen(data);i++) {
        if (data[i]=='.') {
            buffer[j]=0;
            #ifdef DEBUG_EEPROM
                Serial.print(F(" buffer : "));
                Serial.print(buffer);
            #endif
            add=atoi(buffer);
            #ifdef DEBUG_EEPROM
                Serial.print(F(" ip"));
                Serial.print(p);
                Serial.print(F("="));
                Serial.println(add);
            #endif
            if (p<L_NETWORK) {
                EEPROM.write(start+p, add);
            }
            p++;
            j=0;
        } else {
            buffer[j]=data[i];
            j++;
        }
    }
    buffer[j]=0;
    #ifdef DEBUG_EEPROM
        Serial.print(F(" buffer : "));
        Serial.print(buffer);
    #endif
    add=atoi(buffer);
    #ifdef DEBUG_EEPROM
        Serial.print(F(" ip"));
        Serial.print(p);
        Serial.print(F("="));
        Serial.println(add);
    #endif
    if (p<L_NETWORK) {
        EEPROM.write(start+p, add);
    }
}

void ereadNetwork(IPAddress &result) {
    int start=L_NETWORK_I;
    for (int i=0;i<L_NETWORK;i++) {
            byte by=EEPROM.read(start+i);
            result[i]=int(by);
    }
    #ifdef DEBUG_EEPROM
      Serial.print(F("ereadNetwork "));
      Serial.println(result);
    #endif
}

/***********************************************/
void ewriteMac(char data[]) {
    #ifdef DEBUG_EEPROM
      Serial.print(F("ewriteMac "));
      Serial.println(data);
    #endif
    int start=L_MAC_I;
    char buffer[5]="\0";
    int j=0;
    int p=0;
    byte add=0;
    for (int i=0;i<strlen(data) && i<L_MAC;i++) {
        if (data[i]==':') {
            buffer[j]=0;
            #ifdef DEBUG_EEPROM
                Serial.print(F(" buffer : "));
                Serial.print(buffer);
            #endif
            add=htoi(buffer);
            #ifdef DEBUG_EEPROM
                Serial.print(F(" mac"));
                Serial.print(p);
                Serial.print(F("="));
                Serial.println(add);
            #endif
            if (p<L_MAC) {
                EEPROM.write(start+p, add);
            }
            p++;
            j=0;
        } else {
            buffer[j]=data[i];
            j++;
        }
    }
    buffer[j]=0;
    #ifdef DEBUG_EEPROM
        Serial.print(F(" buffer : "));
        Serial.print(buffer);
    #endif
    add=htoi(buffer);
    #ifdef DEBUG_EEPROM
        Serial.print(F(" mac"));
        Serial.print(p);
        Serial.print(F("="));
        Serial.println(add);
    #endif
    if (p<L_MAC) {
        EEPROM.write(start+p, add);
    }
}

void ereadMac(byte result[]) {
    int start=L_MAC_I;
    for (int i=0;i<L_MAC;i++) {
            result[i]=EEPROM.read(start+i);
    }
    #ifdef DEBUG_EEPROM
      Serial.print(F("ereadMac "));
      for (int i=0;i<L_MAC;i++) {
          Serial.print(result[i]);
      }
      Serial.println();
    #endif
}

/***********************************************/
void ewriteServer(char data[]) {
    #ifdef DEBUG_EEPROM
      Serial.print(F("ewriteServer "));
      Serial.println(data);
    #endif
    int start=L_SERVER_I;
    char buffer[5]="\0";
    int j=0;
    int p=0;
    byte add=0;
    for (int i=0;i<strlen(data);i++) {
        if (data[i]=='.') {
            buffer[j]=0;
            #ifdef DEBUG_EEPROM
                Serial.print(F(" buffer : "));
                Serial.print(buffer);
            #endif
            add=atoi(buffer);
            #ifdef DEBUG_EEPROM
                Serial.print(F(" ip"));
                Serial.print(p);
                Serial.print(F("="));
                Serial.println(add);
            #endif
            if (p<L_SERVER) {
                EEPROM.write(start+p, add);
            }
            p++;
            j=0;
        } else {
            buffer[j]=data[i];
            j++;
        }
    }
    buffer[j]=0;
    #ifdef DEBUG_EEPROM
        Serial.print(F(" buffer : "));
        Serial.print(buffer);
    #endif
    add=atoi(buffer);
    #ifdef DEBUG_EEPROM
        Serial.print(F(" ip"));
        Serial.print(p);
        Serial.print(F("="));
        Serial.println(add);
    #endif
    if (p<L_SERVER) {
        EEPROM.write(start+p, add);
    }
}

void ereadServer(IPAddress &result) {
    int start=L_SERVER_I;
    for (int i=0;i<L_SERVER;i++) {
            byte by=EEPROM.read(start+i);
            result[i]=int(by);
    }
    #ifdef DEBUG_EEPROM
      Serial.print(F("ereadServer "));
      Serial.println(result);
    #endif
}

#ifdef BUILD_DHT
/***********************************************/
void ewriteDht1Enabled(bool data) {
    #ifdef DEBUG_EEPROM
      Serial.print(F("ewriteDht1Enabled "));
      Serial.println(data);
    #endif
    int start=L_DHT1_ENABLED_I;
    EEPROM.write(start, data);
}

void ereadDht1Enabled(bool &result) {
    int start=L_DHT1_ENABLED_I;
    result=EEPROM.read(start);
    #ifdef DEBUG_EEPROM
      Serial.print(F("ereadDht1Enabled "));
      Serial.println(result);
    #endif
}

/***********************************************/
void ewriteDht2Enabled(bool data) {
    #ifdef DEBUG_EEPROM
      Serial.print(F("ewriteDht2Enabled "));
      Serial.println(data);
    #endif
    int start=L_DHT2_ENABLED_I;
    EEPROM.write(start, data);
}

void ereadDht2Enabled(bool &result) {
    int start=L_DHT2_ENABLED_I;
    result=EEPROM.read(start);
    #ifdef DEBUG_EEPROM
      Serial.print(F("ereadDht2Enabled "));
      Serial.println(result);
    #endif
}

/***********************************************/
void ewriteDht1Poll(int data) {
    #ifdef DEBUG_EEPROM
      Serial.print(F("ewriteDht1Poll "));
      Serial.println(data);
    #endif
    int start=L_DHT1_POLL_I;
    EEPROM.write(start, data);
}

void ereadDht1Poll(int &result) {
    int start=L_DHT1_POLL_I;
    result=EEPROM.read(start);
    #ifdef DEBUG_EEPROM
      Serial.print(F("ereadDht1Poll "));
      Serial.println(result);
    #endif
}

/***********************************************/
void ewriteDht2Poll(int data) {
    #ifdef DEBUG_EEPROM
      Serial.print(F("ewriteDht2Poll "));
      Serial.println(data);
    #endif
    int start=L_DHT2_POLL_I;
    EEPROM.write(start, data);
}

void ereadDht2Poll(int &result) {
    int start=L_DHT2_POLL_I;
    result=EEPROM.read(start);
    #ifdef DEBUG_EEPROM
      Serial.print(F("ereadDht2Poll "));
      Serial.println(result);
    #endif
}
#endif

#ifdef BUILD_RGB
/***********************************************/
void ewriteRGB(char data[]) {
    #ifdef DEBUG_EEPROM
      Serial.print(F("ewriteRGB "));
      Serial.println(data);
    #endif
    int start=L_RGB_I;
    char buffer[3]="\0";
    int j=0;
    int p=0;
    byte add=0;
    for (int i=0;i<strlen(data) && i<L_MAC;i++) {
        if (data[i]=='#') {
            buffer[j]=0;
            #ifdef DEBUG_EEPROM
                Serial.print(F(" buffer : "));
                Serial.print(buffer);
            #endif
            add=htoi(buffer);
            #ifdef DEBUG_EEPROM
                Serial.print(F(" rgb"));
                Serial.print(p);
                Serial.print(F("="));
                Serial.println(add);
            #endif
            if (p<L_RGB) {
                EEPROM.write(start+p, add);
            }
            p++;
            j=0;
        } else {
            buffer[j]=data[i];
            j++;
        }
    }
    buffer[j]=0;
    #ifdef DEBUG_EEPROM
        Serial.print(F(" buffer : "));
        Serial.print(buffer);
    #endif
    add=htoi(buffer);
    #ifdef DEBUG_EEPROM
        Serial.print(F(" rgb"));
        Serial.print(p);
        Serial.print(F("="));
        Serial.println(add);
    #endif
    if (p<L_RGB) {
        EEPROM.write(start+p, add);
    }
}

void ereadRGB(byte result[]) {
    int start=L_RGB_I;
    for (int i=0;i<L_MAC;i++) {
            result[i]=EEPROM.read(start+i);
    }
    #ifdef DEBUG_EEPROM
      Serial.print(F("ereadRGB "));
      for (int i=0;i<L_MAC;i++) {
          Serial.print(result[i]);
      }
      Serial.println();
    #endif
}

/***********************************************/
void ewriteRGBPoll(int data) {
    #ifdef DEBUG_EEPROM
      Serial.print(F("ewriteRGBPoll "));
      Serial.println(data);
    #endif
    int start=L_RGB_POLL_I;
    EEPROM.write(start, data);
}

void ereadRGBPoll(int &result) {
    int start=L_RGB_POLL_I;
    result=EEPROM.read(start);
    #ifdef DEBUG_EEPROM
      Serial.print(F("ereadRGBPoll "));
      Serial.println(result);
    #endif
}

#endif

/***********************************************/
void ewriteConfigTimeout(int data) {
    #ifdef DEBUG_EEPROM
      Serial.print(F("ewriteConfigTimeout "));
      Serial.println(data);
    #endif
    int start=L_CONFIG_TIMEOUT_I;
    EEPROM.write(start, data);
}

void ereadConfigTimeout(int &result) {
    int start=L_CONFIG_TIMEOUT_I;
    result=EEPROM.read(start);
    #ifdef DEBUG_EEPROM
      Serial.print(F("ereadConfigTimeout "));
      Serial.println(result);
    #endif
}

/***********************************************/
void eFactorySettings() {
    //We want to create a pseudo filesystem to EEPROM
    //We need to format it the first time we use it
    #ifdef DEBUG_EEPROM
        Serial.println(F("Format eeprom"));
    #endif
    ewriteState(byte(1));
    resetWatchdog();
    ewriteDhcp(true);
    ewriteServer("192.168.14.54");
    ewriteMac("DE:AD:BE:EF:FE:ED");
    ewriteIp("192.168.14.99");
    ewriteBroadCast("192.168.14.255");
    ewriteGateway("192.168.14.14");
    ewriteDns("192.168.14.5");
    ewriteNetwork("255.255.255.0");
    ewriteHeartbeat(30);
    ewriteName("arduino\0");
    ewriteLocation("location\0");
    ewriteProduct("ArduiLight\0");
    ewriteType("RGB LED and Temperature\0");
    ewriteHadd("1111/0000\0");
  #ifdef BUILD_DHT
    ewriteDht1Enabled(true);
    ewriteDht2Enabled(true);
    ewriteDht1Poll(30);
    ewriteDht2Poll(30);
  #endif
  #ifdef BUILD_RGB
    ewriteRGB("0#0#0\0");
    ewriteRGBPoll(30);
  #endif
    ewriteConfigTimeout(10);
}


/***********************************************/
void eGenerateUuid() {
    uint32_t random_long;
    random_long = Entropy.random() & 0xFFFFFF;
    char uuid[30];
    ltoa(random_long, uuid, 16);
    random_long = Entropy.random() & 0xFFFFFF;
    ltoa(random_long, &uuid[6], 16);
    ewriteUuid(uuid);
}

