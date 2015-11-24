/*
Ardilight
@author: Thomas A. Anderson <neo@ardilight.com>
@copyright: (C) 2011-2012 Ardilight company
@license: GPL(v3)
@organization: Ardilight company
Manage the core.
Also manage the button use to change state of the arduino.
State i represented by a state led.
*/
#ifdef BUILD_DHT

#include <dht.h>

const char error_dht_chk[] PROGMEM = "Checksum error";
const char error_dht_timeout[] PROGMEM = "Time out error";
const char error_dht_connect[] PROGMEM = "Connect error";
const char error_dht_acklow[] PROGMEM = "Ack Low error";
const char error_dht_ackhigh[] PROGMEM = "Ack High error";
const char error_dht_unknown[] PROGMEM = "Checksum error";

dht DHT;

boolean temp1_enabled = true;
boolean temp1_polled = true;
unsigned int temp1_time = 10*1000;

bool temp2_enabled = true;
bool temp2_polled = true;
unsigned int temp2_time = 10*1000;

/***********************************************/
void setup_dht()
{
    ereadDht1Enabled(temp1_enabled);
    int intval;
    ereadDht1Poll(intval);
    temp1_time=1000*intval;
    #ifdef DEBUG_DHT
        Serial.print(F("Set dht1 poll to "));
        Serial.print(intval);
        Serial.println(F(" seconds"));
        Serial.print(F("Set dht1 enabled to "));
        Serial.println(temp1_enabled);
    #endif
    ereadDht2Enabled(temp2_enabled);
    ereadDht2Poll(intval);
    temp2_time=1000*intval;
    #ifdef DEBUG_DHT
        Serial.print(F("Set dht2 poll to "));
        Serial.print(intval);
        Serial.println(F(" seconds"));
        Serial.print(F("Set dht2 enabled to "));
        Serial.println(temp2_enabled);
    #endif
}

void read_dht(byte ppin, int &pchk, float &ph, float &pt, char pserror[], bool &perror) {
    pchk = DHT.read11(ppin);
    switch (pchk)
        {
          case DHTLIB_OK:
            #ifdef DEBUG_DHT
              Serial.print("OK,\t");
            #endif
              ph = DHT.humidity;
              pt = DHT.temperature;
              break;
          case DHTLIB_ERROR_CHECKSUM:
              strcpy_P(pserror, error_dht_chk);
            #ifdef DEBUG_DHT
              Serial.print(pserror);
            #endif
              perror = true;
              break;
          case DHTLIB_ERROR_TIMEOUT:
              strcpy_P(pserror, error_dht_timeout);
            #ifdef DEBUG_DHT
              Serial.print(pserror);
            #endif
              perror = true;
              break;
          case DHTLIB_ERROR_CONNECT:
              strcpy_P(pserror, error_dht_connect);
            #ifdef DEBUG_DHT
              Serial.print(pserror);
            #endif
              perror = true;
              break;
          case DHTLIB_ERROR_ACK_L:
              strcpy_P(pserror, error_dht_acklow);
            #ifdef DEBUG_DHT
              Serial.print(pserror);
            #endif
              perror = true;
              break;
          case DHTLIB_ERROR_ACK_H:
              strcpy_P(pserror, error_dht_ackhigh);
            #ifdef DEBUG_DHT
              Serial.print(pserror);
            #endif
              perror = true;
              break;
          default:
              strcpy_P(pserror, error_dht_unknown);
            #ifdef DEBUG_DHT
              Serial.print(pserror);
            #endif
              perror = true;
              break;
        }

    if (perror == true) {
      #ifdef DEBUG_DHT
          Serial.println();
          Serial.println(F("Failed to read from DHT"));
      #endif
    } else {
      #ifdef DEBUG_DHT
          Serial.print(F("Humidity: "));
          Serial.print(ph);
          Serial.print(F(" % - Temperature: "));
          Serial.print(pt);
          Serial.println(F(" *C"));
      #endif
    }
}

void send_mqttt_dht(byte ppin, char ptopic[], char pprefix[], int &pchk, float &ph, float &pt, char pserror[], bool &perror) {

    char msg[JSON_BUFFER+1];
    StaticJsonBuffer<JSON_BUFFER> jsonBufferReply;
    JsonObject& root = jsonBufferReply.createObject();
    char mytopic[L_TOPIC];
    char myuuid[L_TOPIC];
    char sm_label[L_LONG];
    char sm_help[L_XLONG];
    root["cmd_class"] = 0x32;
    root["genre"] = 0x04;
    root["hadd"] = my_hadd;
    root["is_readonly"] = true;
    root["is_writeonly"] = true;
    root["genre"] = 0x02;
    strcpy(myuuid, pprefix);
    strcat(myuuid, "_temp");
    strcpy(mytopic, ptopic);
    strcat(mytopic, myuuid);
    root["units"] = "°C";
    root["uuid"] = myuuid;
    root["index"] = 0;
    if (perror==true) {
      root["data"] = "NULL";
      root["error"] = pserror;
    } else {
      root["data"] = pt;
    }
    if (ppin == DHT1_PIN){
      strcpy_P(sm_label, pmem_dht_in_temp_label);
    } else {
      strcpy_P(sm_label, pmem_dht_out_temp_label);
    }
    root["label"] = sm_label;
    root.printTo(msg, sizeof(msg));
    mqttClient.publish(mytopic, msg);
    #ifdef DEBUG_MQTT
      Serial.print(F("Reply message sent to "));
      Serial.println(mytopic);
      root.prettyPrintTo(Serial);
      Serial.println();
      show_jsonsize(strlen(msg));
    #endif
    strcpy(myuuid, pprefix);
    strcat(myuuid, "_hum");
    strcpy(mytopic, ptopic);
    strcat(mytopic, myuuid);
    if (ppin == DHT1_PIN){
      strcpy_P(sm_label, pmem_dht_in_hum_label);
    } else {
      strcpy_P(sm_label, pmem_dht_out_hum_label);
    }
    root["label"] = sm_label;
    root["units"] = "%";
    root["uuid"] = myuuid;
    if (perror==true) {
      root["data"] = "NULL";
      root["error"] = pserror;
    } else {
      root["data"] = ph;
    }
    root.printTo(msg, sizeof(msg));
    mqttClient.publish(mytopic, msg);
  #ifdef DEBUG_MQTT
    Serial.print(F("Reply message sent to "));
    Serial.println(mytopic);
    root.prettyPrintTo(Serial);
    Serial.println();
    show_jsonsize(strlen(msg));
  #endif

}

void loop_dht()
{

  //if ( (temp1_polled == true) && ((millis() - temp1_last) > temp1_time || millis() < temp1_last))  {
  if ( (temp1_enabled == true) && (temp1_time != 0) && (((millis() - temp1_last) > temp1_time) || (millis() < temp1_last)))  {
    char prefix[L_TOPIC];
    char topic[L_TOPIC];
    strcpy_P(topic, pmem_topic_users);
    strcat(topic,my_hadd);
    strcat_P(topic,pmem_topic_separator);
    temp1_last = millis();
    int chk = 0;
    float h = NULL;
    float t = NULL;
    char serror[L_ERROR];
    bool error = false;
    strcpy(prefix, "dht_in");
    read_dht(DHT1_PIN, chk, h, t, serror, error);
    send_mqttt_dht(DHT1_PIN, topic, prefix, chk, h, t, serror, error);
  } else if ( (temp2_enabled == true) && (temp2_time != 0) && (((millis() - temp2_last) > temp2_time) || (millis() < temp2_last)))  {
    char prefix[L_TOPIC];
    char topic[L_TOPIC];
    strcpy_P(topic, pmem_topic_users);
    strcat(topic,my_hadd);
    strcat_P(topic,pmem_topic_separator);
    temp2_last = millis();
    int chk = 0;
    float h = NULL;
    float t = NULL;
    char serror[L_ERROR];
    bool error = false;
    strcpy(prefix, "dht_out");
    send_mqttt_dht(DHT2_PIN, topic, prefix, chk, h, t, serror, error);
  }
}
#endif

