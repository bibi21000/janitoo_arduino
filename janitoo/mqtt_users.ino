/*
Janitoo
@author: bibi21000
@copyright: (C) 2011-2015 Sebastien GALLET <bibi21000@gmail.com>
@license: GPL(v3)
*/

void reply_users() {
  // Send the node reply
  char sm_tmp[L_MIDDLE];
  char sm_uuid[L_MIDDLE];
  char sm_label[L_LONG];
  char sm_help[L_XLONG];
  char sm_units[L_SHORT];
  char sm_root_uuid[L_LONG];
  char topic[L_TOPIC];
  strcpy_P(topic, pmem_topic_nodes);
  strcat(topic,reply_hadd);
  strcat_P(topic,pmem_topic_reply);
  char msg[JSON_BUFFER+1];
  char my_node_uuid[L_UUID];
  ereadUuid(my_node_uuid);
  StaticJsonBuffer<JSON_BUFFER> jsonBufferReply;
  JsonObject& root = jsonBufferReply.createObject();
  root["cmd_class"] = 0x5000;
  root["genre"] = 0x04;
  strcpy_P(sm_root_uuid, pmem_request_info_users);
  root["uuid"] = sm_root_uuid;
  if (replies_users == 1) {
#ifdef BUILD_DHT
    JsonObject& data = root.createNestedObject("data");
    data["hadd"] = my_hadd;
    data["node_uuid"] = my_node_uuid;
    data["is_readonly"] = true;
    data["is_writeonly"] = false;
    data["genre"] = 0x02;
    data["type"] = 0x03;
    JsonArray& cmd_classes = data.createNestedArray("cmd_classes");
    cmd_classes.add(0x32);
    strcpy_P(sm_uuid, pmem_dht_in_temp_uuid);
    data["uuid"] = sm_uuid;
    strcpy_P(sm_label, pmem_dht_in_temp_label);
    data["label"] = sm_label;
    strcpy_P(sm_help, pmem_dht_in_temp_help);
    data["index"] = 0;
    data["help"] = sm_help;
    strcpy_P(sm_units, pmem_degree);
    data["units"] = sm_units;
    int intval;
    ereadDht1Poll(intval);
    bool boolval;
    ereadDht1Enabled(boolval);
    data["is_polled"] = boolval;
    data["poll_delay"] = intval;
    if ( temp1_enabled == true) {
      temp1_last = millis();
      int chk = 0;
      float h = NULL;
      float t = NULL;
      char serror[L_ERROR];
      bool error = false;
      read_dht(DHT1_PIN, chk, h, t, serror, error);
      data["data"] = t;
    } else {
      data["data"] = "NULL";
    }
    root.printTo(msg, sizeof(msg));
    mqttClient.publish(topic, msg);
  #ifdef DEBUG_MQTT
    Serial.print(F("Reply message sent to "));
    Serial.println(topic);
    root.prettyPrintTo(Serial);
    Serial.println();
    show_jsonsize(strlen(msg));
  #endif
  #ifdef DEBUG_MEMORY
    show_memory();
  #endif
#endif  
  } else if (replies_users == 2) {
#ifdef BUILD_DHT
    JsonObject& data = root.createNestedObject("data");
    data["hadd"] = my_hadd;
    data["node_uuid"] = my_node_uuid;
    data["is_readonly"] = true;
    data["is_writeonly"] = false;
    data["genre"] = 0x02;
    data["type"] = 0x02;
    data["index"] = 0;
    JsonArray& cmd_classes = data.createNestedArray("cmd_classes");
    cmd_classes.add(0x32);

    strcpy_P(sm_uuid, pmem_dht_in_hum_uuid);
    data["uuid"] = sm_uuid;
    strcpy_P(sm_label, pmem_dht_in_hum_label);
    data["label"] = sm_label;
    strcpy_P(sm_help, pmem_dht_in_hum_help);
    data["help"] = sm_help;
    strcpy_P(sm_units, pmem_percent);
    data["units"] = sm_units;
    int intval;
    ereadDht1Poll(intval);
    bool boolval;
    ereadDht1Enabled(boolval);
    data["is_polled"] = boolval;
    data["poll_delay"] = intval;
    if ( temp1_enabled == true) {
      temp1_last = millis();
      int chk = 0;
      float h = NULL;
      float t = NULL;
      char serror[L_ERROR];
      bool error = false;
      read_dht(DHT1_PIN, chk, h, t, serror, error);
      data["data"] = h;
    } else {
      data["data"] = "NULL";
    }
    data["min"] = 0;
    data["max"] = 100;
    root.printTo(msg, sizeof(msg));
    mqttClient.publish(topic, msg);
  #ifdef DEBUG_MQTT
    Serial.print(F("Reply message sent to "));
    Serial.println(topic);
    root.prettyPrintTo(Serial);
    Serial.println();
    show_jsonsize(strlen(msg));
  #endif
  #ifdef DEBUG_MEMORY
    show_memory();
  #endif
#endif  
  } else if (replies_users == 3) {
#ifdef BUILD_DHT
    JsonObject& data = root.createNestedObject("data");
    data["hadd"] = my_hadd;
    data["node_uuid"] = my_node_uuid;
    data["is_readonly"] = true;
    data["is_writeonly"] = false;
    data["genre"] = 0x02;
    data["type"] = 0x03;
    data["index"] = 0;
    JsonArray& cmd_classes = data.createNestedArray("cmd_classes");
    cmd_classes.add(0x32);

    strcpy_P(sm_uuid, pmem_dht_out_temp_uuid);
    data["uuid"] = sm_uuid;
    strcpy_P(sm_label, pmem_dht_out_temp_label);
    data["label"] = sm_label;
    strcpy_P(sm_help, pmem_dht_out_temp_help);
    data["help"] = sm_help;
    strcpy_P(sm_units, pmem_degree);
    data["units"] = sm_units;
    int intval;
    ereadDht2Poll(intval);
    bool boolval;
    ereadDht2Enabled(boolval);
    data["is_polled"] = boolval;
    data["poll_delay"] = intval;
    if ( temp2_enabled == true) {
      temp2_last = millis();
      int chk = 0;
      float h = NULL;
      float t = NULL;
      char serror[L_ERROR];
      bool error = false;
      read_dht(DHT2_PIN, chk, h, t, serror, error);
      data["data"] = t;
    } else {
      data["data"] = "NULL";
    }
    root.printTo(msg, sizeof(msg));
    mqttClient.publish(topic, msg);
  #ifdef DEBUG_MQTT
    Serial.print(F("Reply message sent to "));
    Serial.println(topic);
    root.prettyPrintTo(Serial);
    Serial.println();
    show_jsonsize(strlen(msg));
  #endif
  #ifdef DEBUG_MEMORY
    show_memory();
  #endif
#endif
  } else if (replies_users == 4) {
#ifdef BUILD_DHT
    JsonObject& data = root.createNestedObject("data");
    data["hadd"] = my_hadd;
    data["node_uuid"] = my_node_uuid;
    data["is_readonly"] = true;
    data["is_writeonly"] = false;
    data["genre"] = 0x02;
    data["type"] = 0x02;
    data["index"] = 0;
    JsonArray& cmd_classes = data.createNestedArray("cmd_classes");
    cmd_classes.add(0x32);

    strcpy_P(sm_uuid, pmem_dht_out_hum_uuid);
    data["uuid"] = sm_uuid;
    strcpy_P(sm_label, pmem_dht_out_hum_label);
    data["label"] = sm_label;
    strcpy_P(sm_help, pmem_dht_out_hum_help);
    data["help"] = sm_help;
    strcpy_P(sm_units, pmem_percent);
    data["units"] = sm_units;
    int intval;
    ereadDht2Poll(intval);
    bool boolval;
    ereadDht2Enabled(boolval);
    data["is_polled"] = boolval;
    data["poll_delay"] = intval;
    if ( temp2_enabled == true) {
      temp2_last = millis();
      int chk = 0;
      float h = NULL;
      float t = NULL;
      char serror[L_ERROR];
      bool error = false;
      read_dht(DHT2_PIN, chk, h, t, serror, error);
      data["data"] = h;
    } else {
      data["data"] = "NULL";
    }
    data["min"] = 0;
    data["max"] = 100;
    root.printTo(msg, sizeof(msg));
    mqttClient.publish(topic, msg);
  #ifdef DEBUG_MQTT
    Serial.print(F("Reply message sent to "));
    Serial.println(topic);
    root.prettyPrintTo(Serial);
    Serial.println();
    show_jsonsize(strlen(msg));
  #endif
  #ifdef DEBUG_MEMORY
    show_memory();
  #endif
#endif  
  } else if (replies_users == 5) {
#ifdef BUILD_RGB
    JsonObject& data = root.createNestedObject("data");
    data["hadd"] = my_hadd;
    data["node_uuid"] = my_node_uuid;
    data["is_readonly"] = true;
    data["is_writeonly"] = false;
    data["genre"] = 0x02;
    data["type"] = 0x30;
    data["index"] = 0;
    JsonArray& cmd_classes = data.createNestedArray("cmd_classes");
    cmd_classes.add(0x33);
    strcpy_P(sm_uuid, pmem_rgb_color_uuid);
    data["uuid"] = sm_uuid;
    strcpy_P(sm_label, pmem_rgb_color_label);
    data["label"] = sm_label;
    strcpy_P(sm_help, pmem_rgb_color_help);
    data["help"] = sm_help;
    byte rgb[L_RGB];
    ereadRGB(rgb);
    int intval;
    ereadRGBPoll(intval);
    data["is_polled"] = intval > 0;
    data["poll_delay"] = intval;
    data["data"] = rgb;
    data["min"] = 0;
    data["max"] = 255;
    strcpy_P(sm_units, pmem_rgb);
    data["units"] = sm_units;
    root.printTo(msg, sizeof(msg));
    mqttClient.publish(topic, msg);
  #ifdef DEBUG_MQTT
    Serial.print(F("Reply message sent to "));
    Serial.println(topic);
    root.prettyPrintTo(Serial);
    Serial.println();
    show_jsonsize(strlen(msg));
  #endif
  #ifdef DEBUG_MEMORY
    show_memory();
  #endif
#endif  
  } else if (replies_users == 6) {
#ifdef BUILD_RGB
    JsonObject& data = root.createNestedObject("data");
    data["hadd"] = my_hadd;
    data["node_uuid"] = my_node_uuid;
    data["is_readonly"] = false;
    data["is_writeonly"] = false;
    data["genre"] = 0x02;
    data["type"] = 0x30;
    data["index"] = 0;
    JsonArray& cmd_classes = data.createNestedArray("cmd_classes");
    cmd_classes.add(0x25);

    strcpy_P(sm_uuid, pmem_set_rgb_color_uuid);
    data["uuid"] = sm_uuid;
    strcpy_P(sm_label, pmem_set_rgb_color_label);
    data["label"] = sm_label;
    strcpy_P(sm_help, pmem_set_rgb_color_help);
    data["help"] = sm_help;
    byte rgb[L_RGB];
    ereadRGB(rgb);
    int intval;
    ereadRGBPoll(intval);
    data["is_polled"] = intval > 0;
    data["poll_delay"] = intval;
    data["data"] = rgb;
    data["min"] = 0;
    data["max"] = 255;
    strcpy_P(sm_units, pmem_rgb);
    data["units"] = sm_units;
    root.printTo(msg, sizeof(msg));
    mqttClient.publish(topic, msg);
  #ifdef DEBUG_MQTT
    Serial.print(F("Reply message sent to "));
    Serial.println(topic);
    root.prettyPrintTo(Serial);
    Serial.println();
    show_jsonsize(strlen(msg));
  #endif
  #ifdef DEBUG_MEMORY
    show_memory();
  #endif
#endif  
  } else if (replies_users == 7) {
#ifdef BUILD_RGB
    JsonObject& data = root.createNestedObject("data");
    data["hadd"] = my_hadd;
    data["node_uuid"] = my_node_uuid;
    data["is_readonly"] = false;
    data["is_writeonly"] = false;
    data["genre"] = 0x02;
    data["type"] = 0x30;
    data["index"] = 0;
    JsonArray& cmd_classes = data.createNestedArray("cmd_classes");
    cmd_classes.add(0x26);

    strcpy_P(sm_uuid, pmem_dim_rgb_color_uuid);
    data["uuid"] = sm_uuid;
    strcpy_P(sm_label, pmem_dim_rgb_color_label);
    data["label"] = sm_label;
    strcpy_P(sm_help, pmem_dim_rgb_color_help);
    data["help"] = sm_help;
    byte rgb[L_RGB];
    ereadRGB(rgb);
    int intval;
    ereadRGBPoll(intval);
    data["is_polled"] = intval > 0;
    data["poll_delay"] = intval;
    data["data"] = rgb;
    data["min"] = 0;
    data["max"] = 255;
    strcpy_P(sm_units, pmem_rgb);
    data["units"] = sm_units;
    root.printTo(msg, sizeof(msg));
    mqttClient.publish(topic, msg);
  #ifdef DEBUG_MQTT
    Serial.print(F("Reply message sent to "));
    Serial.println(topic);
    root.prettyPrintTo(Serial);
    Serial.println();
    show_jsonsize(strlen(msg));
  #endif
  #ifdef DEBUG_MEMORY
    show_memory();
  #endif
#endif  
  }
}

