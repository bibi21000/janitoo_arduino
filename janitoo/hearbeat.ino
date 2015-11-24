/*
Janitoo
@author: bibi21000
@copyright: (C) 2011-2015 Sebastien GALLET <bibi21000@gmail.com>
@license: GPL(v3)
*/

void setup_heartbeat()
{
  int intval;
  ereadHeartbeat(intval);
  hb_time=1000*intval;
  hb_last = millis();
  #ifdef DEBUG_HEARTBEAT
      Serial.print(F("Set heartbeat to "));
      Serial.print(byteval);
      Serial.println(F(" seconds"));
  #endif
}

void loop_heartbeat()
{
  if ( ((millis() - hb_last) > hb_time) || (millis() < hb_last) || (hb_last == 0))  {
    hb_last = millis();
    send_heartbeat("ONLINE");
  }
}

void send_heartbeat(char* status)
{
    char topic[L_TOPIC];
    strcpy_P(topic, pmem_topic_heartbeat);
    strcat(topic,my_hadd);
  #ifdef DEBUG_HEARTBEAT
    Serial.print(F("send headrbeat "));
    Serial.print(status);
    Serial.print(F(" to "));
    Serial.println(topic);
  #endif
  #ifdef DEBUG_MEMORY
    show_memory();
  #endif
    hb_last = millis();
    mqttClient.publish(topic,status);
}
