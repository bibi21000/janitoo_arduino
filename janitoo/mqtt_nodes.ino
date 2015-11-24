/*
Janitoo
@author: bibi21000
@copyright: (C) 2011-2015 Sebastien GALLET <bibi21000@gmail.com>
@license: GPL(v3)
*/

void reply_node() {
  // Send the node reply
  StaticJsonBuffer<JSON_BUFFER> jsonBufferReply;
  char sm_root_uuid[L_MIDDLE];
  char my_node_uuid[L_UUID];
  char my_node_name[L_NAME];
  char my_node_location[L_LOCATION];
  char my_node_product[L_PRODUCT];
  char my_node_type[L_TYPE];
  ereadUuid(my_node_uuid);
  ereadName(my_node_name);
  ereadLocation(my_node_location);
  ereadProduct(my_node_product);
  ereadTypeFull(my_node_type);
  JsonObject& root = jsonBufferReply.createObject();
  root["cmd_class"] = 0x5000;
  root["genre"] = 0x04;
  strcpy_P(sm_root_uuid, pmem_request_info_nodes);
  root["uuid"] = sm_root_uuid;
  JsonObject& data = root.createNestedObject("data");
  data["hadd"] = my_hadd;
  data["uuid"] = my_node_uuid;
  data["name"] = my_node_name;
  data["location"] = my_node_location;
  data["product_name"] = my_node_product;
  data["product_type"] = my_node_type;
  JsonArray& cmd_classes = data.createNestedArray("cmd_classes");
  cmd_classes.add(0x32);
  cmd_classes.add(0x33);
  cmd_classes.add(0x05);
  cmd_classes.add(0x25);
  cmd_classes.add(0x26);
  char topic[L_TOPIC];
  strcpy_P(topic, pmem_topic_nodes);
  strcat(topic,reply_hadd);
  strcat_P(topic,pmem_topic_reply);
  char msg[JSON_BUFFER+1];
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
