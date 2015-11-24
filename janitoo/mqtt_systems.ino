/*
Janitoo
@author: bibi21000
@copyright: (C) 2011-2015 Sebastien GALLET <bibi21000@gmail.com>
@license: GPL(v3)
*/

void reply_systems() {
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
  strcpy_P(sm_root_uuid, pmem_request_info_systems);
  root["uuid"] = sm_root_uuid;
  JsonObject& data = root.createNestedObject("data");
  data["hadd"] = my_hadd;
  data["node_uuid"] = my_node_uuid;
  data["is_readonly"] = false;
  data["is_writeonly"] = true;
  data["genre"] = 0x04;
  if (replies_systems == 1) {
    JsonArray& cmd_classes = data.createNestedArray("cmd_classes");
    cmd_classes.add(0x70);
    strcpy_P(sm_uuid, pmem_heartbeat_uuid);
    data["uuid"] = sm_uuid;
    strcpy_P(sm_label, pmem_heartbeat_label);
    data["label"] = sm_label;
    strcpy_P(sm_help, pmem_heartbeat_help);
    data["help"] = sm_help;
    strcpy_P(sm_units, pmem_seconds);
    data["units"] = sm_units;
    data["type"] = 0x04;
    int intval;
    ereadHeartbeat(intval);
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
  } else if (replies_systems == 2) {
    JsonArray& cmd_classes = data.createNestedArray("cmd_classes");
    cmd_classes.add(0x70);
    strcpy_P(sm_uuid, pmem_hadd_uuid);
    data["uuid"] = sm_uuid;
    strcpy_P(sm_label, pmem_hadd_label);
    data["label"] = sm_label;
    strcpy_P(sm_help, pmem_hadd_help);
    data["help"] = sm_help;
    data["type"] = 0x20;
    char my_data[L_HADD];
    ereadHadd(my_data);
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
  } else if (replies_systems == 3) {
    JsonArray& cmd_classes = data.createNestedArray("cmd_classes");
    cmd_classes.add(0x70);
    strcpy_P(sm_uuid, pmem_config_timeout_uuid);
    data["uuid"] = sm_uuid;
    strcpy_P(sm_label, pmem_config_timeout_label);
    data["label"] = sm_label;
    strcpy_P(sm_help, pmem_config_timeout_help);
    data["help"] = sm_help;
    strcpy_P(sm_units, pmem_seconds);
    data["units"] = sm_units;
    data["type"] = 0x04;
    int intval;
    ereadConfigTimeout(intval);
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
  }
}
