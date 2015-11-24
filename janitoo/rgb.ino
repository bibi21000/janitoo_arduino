/*
Janitoo
@author: bibi21000
@copyright: (C) 2011-2015 Sebastien GALLET <bibi21000@gmail.com>
@license: GPL(v3)
*/
#ifdef BUILD_RGB

boolean rgb_polled = true;
unsigned int rgb_time = 10*1000;

void setup_rgb()
{
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void loop_rgb()
{

  if ( (rgb_time != 0) && (((millis() - rgb_last) > rgb_time) || (millis() < rgb_last)))  {
    byte vrgb[L_RGB];
    char topic[L_TOPIC];
    strcpy_P(topic, pmem_topic_users);
    strcat(topic,my_hadd);
    strcat_P(topic,pmem_topic_separator);
    rgb_last = millis();
    ereadRGB(vrgb);
    send_mqttt_rgb(topic, vrgb[0], vrgb[1], vrgb[2]);
  }
}

void send_mqttt_rgb(char ptopic[], byte vred, byte vgreen, byte vblue) {
    char sm_uuid[L_MIDDLE];
    char sm_label[L_LONG];
    char sm_help[L_XLONG];
    char sm_units[L_SHORT];
    char msg[JSON_BUFFER+1];
    StaticJsonBuffer<JSON_BUFFER> jsonBufferReply;
    JsonObject& root = jsonBufferReply.createObject();
    char mytopic[L_TOPIC];
    char mycolor[L_MIDDLE];
    char mychar[L_SHORT];
    root["cmd_class"] = 0x33;
    root["genre"] = 0x04;
    root["index"] = 0;
    root["hadd"] = my_hadd;
    root["is_readonly"] = true;
    root["is_writeonly"] = false;
    root["genre"] = 0x02;
    strcpy_P(sm_units, pmem_rgb);
    root["units"] = sm_units;
    strcpy_P(sm_uuid, pmem_rgb_color_uuid);
    root["uuid"] = sm_uuid;
    strcpy(mytopic, ptopic);
    strcat(mytopic, sm_uuid);
    strcpy_P(sm_label, pmem_rgb_color_label);
    root["label"] = sm_label;
    itoa(vred,mychar,10);
    int intval;
    ereadRGBPoll(intval);
    root["is_polled"] = intval > 0;
    root["poll_delay"] = intval;
    strcpy(mycolor, mychar);
    strcat(mycolor, "#");
    itoa(vgreen,mychar,10);
    strcat(mycolor, mychar);
    strcat(mycolor, "#");
    itoa(vblue,mychar,10);
    strcat(mycolor,mychar);
    root["data"] = mycolor;
    root.printTo(msg, sizeof(msg));
    mqttClient.publish(mytopic, msg);
    #ifdef DEBUG_MQTT
      Serial.print(F("Reply message sent to "));
      Serial.println(mytopic);
      root.prettyPrintTo(Serial);
      Serial.println();
      show_jsonsize(strlen(msg));
    #endif
    #ifdef DEBUG_MEMORY
      show_memory();
    #endif
}

#endif

