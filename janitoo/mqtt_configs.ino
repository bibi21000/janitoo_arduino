/*
Janitoo
@author: bibi21000
@copyright: (C) 2011-2015 Sebastien GALLET <bibi21000@gmail.com>
@license: GPL(v3)
*/

void reply_configs() {
  // Send the node reply
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
  strcpy_P(sm_root_uuid, pmem_request_info_configs);
  root["uuid"] = sm_root_uuid;
  if (replies_configs == 1) {
    JsonObject& data = root.createNestedObject("data");
    data["hadd"] = my_hadd;
    data["node_uuid"] = my_node_uuid;
    data["index"] = 0;
    data["is_readonly"] = false;
    data["is_writeonly"] = true;
    data["genre"] = 0x03;
    data["type"] = 0x08;
    data["units"] = NULL;
    JsonArray& cmd_classes = data.createNestedArray("cmd_classes");
    cmd_classes.add(0x70);
    strcpy_P(sm_uuid, pmem_name_uuid);
    data["uuid"] = sm_uuid;
    strcpy_P(sm_label, pmem_name_label);
    data["label"] = sm_label;
    strcpy_P(sm_help, pmem_name_help);
    data["help"] = sm_help;
    char my_data[L_NAME];
    ereadName(my_data);
    data["data"] = my_data;
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
  } else if (replies_configs == 2) {
    JsonObject& data = root.createNestedObject("data");
    data["hadd"] = my_hadd;
    data["node_uuid"] = my_node_uuid;
    data["is_readonly"] = false;
    data["is_writeonly"] = true;
    data["index"] = 0;
    data["genre"] = 0x03;
    data["type"] = 0x08;
    data["units"] = NULL;
    JsonArray& cmd_classes = data.createNestedArray("cmd_classes");
    cmd_classes.add(0x70);
    strcpy_P(sm_uuid, pmem_location_uuid);
    data["uuid"] = sm_uuid;
    strcpy_P(sm_label, pmem_location_label);
    data["label"] = sm_label;
    strcpy_P(sm_help, pmem_location_help);
    data["help"] = sm_help;
    char my_data[L_LOCATION];
    ereadLocation(my_data);
    data["data"] = my_data;
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
  } else if (replies_configs == 3) {
#ifdef BUILD_DHT
    JsonObject& data = root.createNestedObject("data");
    data["hadd"] = my_hadd;
    data["node_uuid"] = my_node_uuid;
    data["is_readonly"] = false;
    data["is_writeonly"] = true;
    data["index"] = 0;
    data["genre"] = 0x01;
    data["type"] = 0x03;
    data["units"] = NULL;
    JsonArray& cmd_classes = data.createNestedArray("cmd_classes");
    cmd_classes.add(0x70);
    strcpy_P(sm_uuid, pmem_in_poll_uuid);
    data["uuid"] = sm_uuid;
    strcpy_P(sm_label, pmem_in_poll_label);
    data["label"] = sm_label;
    strcpy_P(sm_help, pmem_in_poll_help);
    data["help"] = sm_help;
    strcpy_P(sm_units, pmem_seconds);
    data["units"] = sm_units;
    int intval;
    ereadDht1Poll(intval);
    data["data"] = intval;
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
  } else if (replies_configs == 4) {
#ifdef BUILD_DHT
    JsonObject& data = root.createNestedObject("data");
    data["hadd"] = my_hadd;
    data["node_uuid"] = my_node_uuid;
    data["is_readonly"] = false;
    data["is_writeonly"] = true;
    data["index"] = 0;
    data["genre"] = 0x01;
    data["type"] = 0x01;
    data["units"] = NULL;
    JsonArray& cmd_classes = data.createNestedArray("cmd_classes");
    cmd_classes.add(0x70);
    strcpy_P(sm_uuid, pmem_in_enabled_uuid);
    data["uuid"] = sm_uuid;
    strcpy_P(sm_label, pmem_in_enabled_label);
    data["label"] = sm_label;
    strcpy_P(sm_help, pmem_in_enabled_help);
    data["help"] = sm_help;
    bool boolval;
    ereadDht1Enabled(boolval);
    data["data"] = boolval;
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
  } else if (replies_configs == 5) {
#ifdef BUILD_DHT
    JsonObject& data = root.createNestedObject("data");
    data["hadd"] = my_hadd;
    data["node_uuid"] = my_node_uuid;
    data["is_readonly"] = false;
    data["is_writeonly"] = true;
    data["index"] = 0;
    data["genre"] = 0x01;
    data["type"] = 0x03;
    data["units"] = NULL;
    JsonArray& cmd_classes = data.createNestedArray("cmd_classes");
    cmd_classes.add(0x70);
    strcpy_P(sm_uuid, pmem_out_poll_uuid);
    data["uuid"] = sm_uuid;
    strcpy_P(sm_label, pmem_out_poll_label);
    data["label"] = sm_label;
    strcpy_P(sm_help, pmem_out_poll_help);
    data["help"] = sm_help;
    strcpy_P(sm_units, pmem_seconds);
    data["units"] = sm_units;
    int intval;
    ereadDht2Poll(intval);
    data["data"] = intval;
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
  } else if (replies_configs == 6) {
#ifdef BUILD_DHT
    JsonObject& data = root.createNestedObject("data");
    data["hadd"] = my_hadd;
    data["node_uuid"] = my_node_uuid;
    data["is_readonly"] = false;
    data["is_writeonly"] = true;
    data["index"] = 0;
    data["genre"] = 0x01;
    data["type"] = 0x01;
    data["units"] = NULL;
    JsonArray& cmd_classes = data.createNestedArray("cmd_classes");
    cmd_classes.add(0x70);
    strcpy_P(sm_uuid, pmem_out_enabled_uuid);
    data["uuid"] = sm_uuid;
    strcpy_P(sm_label, pmem_out_enabled_label);
    data["label"] = sm_label;
    strcpy_P(sm_help, pmem_out_enabled_help);
    data["help"] = sm_help;
    bool boolval;
    ereadDht2Enabled(boolval);
    data["data"] = boolval;
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
  } else if (replies_configs == 7) {
#ifdef BUILD_RGB
    JsonObject& data = root.createNestedObject("data");
    data["hadd"] = my_hadd;
    data["node_uuid"] = my_node_uuid;
    data["is_readonly"] = false;
    data["is_writeonly"] = true;
    data["index"] = 0;
    data["genre"] = 0x01;
    data["type"] = 0x03;
    data["units"] = NULL;
    JsonArray& cmd_classes = data.createNestedArray("cmd_classes");
    cmd_classes.add(0x70);
    strcpy_P(sm_uuid, pmem_rgb_poll_uuid);
    data["uuid"] = sm_uuid;
    strcpy_P(sm_label, pmem_rgb_poll_label);
    data["label"] = sm_label;
    strcpy_P(sm_help, pmem_rgb_poll_help);
    data["help"] = sm_help;
    strcpy_P(sm_units, pmem_seconds);
    data["units"] = sm_units;
    int intval;
    ereadRGBPoll(intval);
    data["data"] = intval;
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
