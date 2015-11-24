/*
Janitoo
@author: bibi21000
@copyright: (C) 2011-2015 Sebastien GALLET <bibi21000@gmail.com>
@license: GPL(v3)
*/

void nodeCallback(char* topic, byte* payload, unsigned int length) {
  // In order to republish this payload, a copy must be made
  // as the orignal payload buffer will be overwritten whilst
  // constructing the PUBLISH packet.

  // Allocate the correct amount of memory for the payload copy
  char* p = (char*)malloc(length);
  // Copy the payload to the new buffer
  memcpy(p,payload,length);

  StaticJsonBuffer<JSON_BUFFER> jsonBufferRequest;
  JsonObject& root = jsonBufferRequest.parseObject(p);

  unsigned long cmd_class = root["cmd_class"];
  unsigned long genre = root["genre"];
  const char* uuid = root["uuid"];
  #ifdef DEBUG_MQTT
    Serial.println(F("Receive request message"));
    root.prettyPrintTo(Serial);
    Serial.println(F(""));
  #endif
  if (cmd_class == 0x5000) {
    //Discovery
    if (genre == 0x04) {
      if ( strcmp_P(uuid, pmem_request_info_nodes) == 0 ) {
        strcpy(reply_hadd, root["reply_hadd"]);
        replies_nodes = REPLIES_NODES;
        replies_to_send = true;
      } else if ( strcmp_P(uuid, pmem_request_info_users) == 0 ) {
        strcpy(reply_hadd, root["reply_hadd"]);
        replies_users = REPLIES_USERS;
        replies_to_send = true;
      } else if ( strcmp_P(uuid, pmem_request_info_configs) == 0 ) {
        strcpy(reply_hadd, root["reply_hadd"]);
        replies_configs = REPLIES_CONFIGS;
        replies_to_send = true;
      } else if ( strcmp_P(uuid, pmem_request_info_systems) == 0 ) {
        strcpy(reply_hadd, root["reply_hadd"]);
        replies_systems = REPLIES_SYSTEMS;
        replies_to_send = true;
      }
    }
  } else if (cmd_class == 0x70) {
    //Configuration
    if (genre == 0x03) {
      bool is_writeonly = root["is_writeonly"];
      if (is_writeonly == true) {
          char my_topic[L_TOPIC];
          strcpy_P(my_topic, pmem_topic_configs);
          strcat(my_topic,my_hadd);
          strcat_P(my_topic,pmem_topic_separator);
          strcat(my_topic,uuid);
          if ( strcmp_P(uuid, pmem_name_uuid) == 0 ) {
            char my_data[L_NAME];
            strcpy(my_data, root["data"]);
            ewriteName(my_data);
            root["is_writeonly"]=false;
            root["is_readonly"]=true;
            char msg[JSON_BUFFER+1];
            root.printTo(msg, sizeof(msg));
           #ifdef DEBUG_MQTT
            Serial.print(F("Reply message sent to "));
            Serial.println(my_topic);
            root.prettyPrintTo(Serial);
            Serial.println();
            show_jsonsize(strlen(msg));
          #endif
           mqttClient.publish(my_topic, msg);
          } else if ( strcmp_P(uuid, pmem_location_uuid) == 0 ) {
            char my_data[L_LOCATION];
            strcpy(my_data, root["data"]);
            ewriteLocation(my_data);
            root["is_writeonly"]=false;
            root["is_readonly"]=true;
            char msg[JSON_BUFFER+1];
            root.printTo(msg, sizeof(msg));
           #ifdef DEBUG_MQTT
            Serial.print(F("Reply message sent to "));
            Serial.println(my_topic);
            root.prettyPrintTo(Serial);
            Serial.println();
            show_jsonsize(strlen(msg));
          #endif
            mqttClient.publish(my_topic, msg);
          } else if ( strcmp_P(uuid, pmem_product_uuid) == 0 ) {
            char my_data[L_PRODUCT];
            strcpy(my_data, root["data"]);
            ewriteProduct(my_data);
            root["is_writeonly"]=false;
            root["is_readonly"]=true;
            char msg[JSON_BUFFER+1];
            root.printTo(msg, sizeof(msg));
           #ifdef DEBUG_MQTT
            Serial.print(F("Reply message sent to "));
            Serial.println(my_topic);
            root.prettyPrintTo(Serial);
            Serial.println();
            show_jsonsize(strlen(msg));
          #endif
            mqttClient.publish(my_topic, msg);
          } else if ( strcmp_P(uuid, pmem_type_uuid) == 0 ) {
            char my_data[L_TYPE];
            strcpy(my_data, root["data"]);
            ewriteProduct(my_data);
            root["is_writeonly"]=false;
            root["is_readonly"]=true;
            char msg[JSON_BUFFER+1];
            root.printTo(msg, sizeof(msg));
           #ifdef DEBUG_MQTT
            Serial.print(F("Reply message sent to "));
            Serial.println(my_topic);
            root.prettyPrintTo(Serial);
            Serial.println();
            show_jsonsize(strlen(msg));
          #endif
            mqttClient.publish(my_topic, msg);
        #ifdef BUILD_DHT
          } else if ( strcmp_P(uuid, pmem_in_enabled_uuid) == 0 ) {
            bool my_data;
            my_data = root["data"];
            ewriteDht1Enabled(my_data);
            setup_dht();
            root["is_writeonly"]=false;
            root["is_readonly"]=true;
            char msg[JSON_BUFFER+1];
            root.printTo(msg, sizeof(msg));
           #ifdef DEBUG_MQTT
            Serial.print(F("Reply message sent to "));
            Serial.println(my_topic);
            root.prettyPrintTo(Serial);
            Serial.println();
            show_jsonsize(strlen(msg));
          #endif
            mqttClient.publish(my_topic, msg);
          } else if ( strcmp_P(uuid, pmem_in_poll_uuid) == 0 ) {
            int my_data;
            my_data = root["data"];
            ewriteDht1Poll(my_data);
            setup_dht();
            root["is_writeonly"]=false;
            root["is_readonly"]=true;
            char msg[JSON_BUFFER+1];
            root.printTo(msg, sizeof(msg));
           #ifdef DEBUG_MQTT
            Serial.print(F("Reply message sent to "));
            Serial.println(my_topic);
            root.prettyPrintTo(Serial);
            Serial.println();
            show_jsonsize(strlen(msg));
          #endif
            mqttClient.publish(my_topic, msg);
          } else if ( strcmp_P(uuid, pmem_out_enabled_uuid) == 0 ) {
            bool my_data;
            my_data = root["data"];
            ewriteDht2Enabled(my_data);
            setup_dht();
            root["is_writeonly"]=false;
            root["is_readonly"]=true;
            char msg[JSON_BUFFER+1];
            root.printTo(msg, sizeof(msg));
           #ifdef DEBUG_MQTT
            Serial.print(F("Reply message sent to "));
            Serial.println(my_topic);
            root.prettyPrintTo(Serial);
            Serial.println();
            show_jsonsize(strlen(msg));
          #endif
            mqttClient.publish(my_topic, msg);
          } else if ( strcmp_P(uuid, pmem_out_poll_uuid) == 0 ) {
            int my_data;
            my_data = root["data"];
            ewriteDht2Poll(my_data);
            setup_dht();
            root["is_writeonly"]=false;
            root["is_readonly"]=true;
            char msg[JSON_BUFFER+1];
            root.printTo(msg, sizeof(msg));
           #ifdef DEBUG_MQTT
            Serial.print(F("Reply message sent to "));
            Serial.println(my_topic);
            root.prettyPrintTo(Serial);
            Serial.println();
            show_jsonsize(strlen(msg));
          #endif
            mqttClient.publish(my_topic, msg);
        #endif
        #ifdef BUILD_RGB
          } else if ( strcmp_P(uuid, pmem_rgb_poll_uuid) == 0 ) {
            int my_data;
            my_data = root["data"];
            ewriteRGBPoll(my_data);
            setup_dht();
            root["is_writeonly"]=false;
            root["is_readonly"]=true;
            char msg[JSON_BUFFER+1];
            root.printTo(msg, sizeof(msg));
           #ifdef DEBUG_MQTT
            Serial.print(F("Reply message sent to "));
            Serial.println(my_topic);
            root.prettyPrintTo(Serial);
            Serial.println();
            show_jsonsize(strlen(msg));
          #endif
            mqttClient.publish(my_topic, msg);
        #endif
          }
      }
    } else if (genre == 0x04) {
      bool is_writeonly = root["is_writeonly"];
      if (is_writeonly == true) {
          char my_topic[L_TOPIC];
          strcpy_P(my_topic, pmem_topic_systems);
          strcat(my_topic,my_hadd);
          strcat_P(my_topic,pmem_topic_separator);
          strcat(my_topic,uuid);
          if ( strcmp_P(uuid, pmem_heartbeat_uuid) == 0 ) {
              int my_data;
              my_data = root["data"];
              ewriteHeartbeat(my_data);
              setup_heartbeat();
            #ifdef DEBUG_MQTT
              Serial.print(F("Update heartbeat delay to "));
              Serial.println(my_data);
            #endif
              root["is_writeonly"]=false;
              root["is_readonly"]=true;
              ereadHeartbeat(my_data);
              root["data"]=my_data;
              char msg[JSON_BUFFER+1];
              root.printTo(msg, sizeof(msg));
             #ifdef DEBUG_MQTT
              Serial.print(F("Reply message sent to "));
              Serial.println(my_topic);
              root.prettyPrintTo(Serial);
              Serial.println();
              show_jsonsize(strlen(msg));
            #endif
              mqttClient.publish(my_topic, msg);
        } else if ( strcmp_P(uuid, pmem_hadd_uuid) == 0 ) {
              char my_data[L_HADD];
              strcpy(my_data, root["data"]);
              ewriteHadd(my_data);
              ereadHadd(my_hadd);
              root["data"]=my_hadd;
              root["is_writeonly"]=false;
              root["is_readonly"]=true;
              char msg[JSON_BUFFER+1];
              root.printTo(msg, sizeof(msg));
             #ifdef DEBUG_MQTT
              Serial.print(F("Reply message sent to "));
              Serial.println(my_topic);
              root.prettyPrintTo(Serial);
              Serial.println();
              show_jsonsize(strlen(msg));
            #endif
              mqttClient.publish(my_topic, msg);
              send_heartbeat("offline");
              config_timeout_run_at = millis() + config_timeout*1000;
        } else if ( strcmp_P(uuid, pmem_config_timeout_uuid) == 0 ) {
              int my_data;
              my_data = root["data"];
              ewriteConfigTimeout(my_data);
              ereadConfigTimeout(config_timeout);
              root["data"]=config_timeout;
              root["is_writeonly"]=false;
              root["is_readonly"]=true;
              char msg[JSON_BUFFER+1];
              root.printTo(msg, sizeof(msg));
             #ifdef DEBUG_MQTT
              Serial.print(F("Reply message sent to "));
              Serial.println(my_topic);
              root.prettyPrintTo(Serial);
              Serial.println();
              show_jsonsize(strlen(msg));
            #endif
              mqttClient.publish(my_topic, msg);
        }
      }
    }
  } else if (cmd_class == 0x32) {
  #ifdef DEBUG_MEMORY
    show_memory();
  #endif
    char prefix[L_TOPIC];
    //COMMAND_METER
    #ifdef BUILD_DHT
    if (temp1_enabled == true) {
        if ( strcmp_P(uuid, pmem_dht_in_temp_uuid) == 0 ) {
          temp1_last = millis();
          int chk = 0;
          float h = NULL;
          float t = NULL;
          char serror[L_ERROR];
          bool error = false;
          strcpy(prefix, "dht_in");
          char my_topic[L_TOPIC];
          strcpy_P(my_topic, pmem_topic_users);
          strcat(my_topic,my_hadd);
          strcat_P(my_topic,pmem_topic_separator);
          send_mqttt_dht(DHT1_PIN, my_topic, prefix, chk, h, t, serror, error);
        } else if ( strcmp_P(uuid, pmem_dht_in_hum_uuid) == 0 ) {
          temp1_last = millis();
          int chk = 0;
          float h = NULL;
          float t = NULL;
          char serror[L_ERROR];
          bool error = false;
          char my_topic[L_TOPIC];
          strcpy_P(my_topic, pmem_topic_nodes);
          strcat(my_topic,my_hadd);
          strcat_P(my_topic,pmem_topic_users);
          strcpy(prefix, "dht_in");
          send_mqttt_dht(DHT1_PIN, my_topic, prefix, chk, h, t, serror, error);
        }
    }
    if (temp2_enabled == true) {
          if ( strcmp_P(uuid, pmem_dht_out_temp_uuid) == 0 ) {
            temp2_last = millis();
            int chk = 0;
            float h = NULL;
            float t = NULL;
            char serror[L_ERROR];
            bool error = false;
            char my_topic[L_TOPIC];
            strcpy_P(my_topic, pmem_topic_users);
            strcat(my_topic,my_hadd);
            strcat_P(my_topic,pmem_topic_separator);
            strcpy(prefix, "dht_out");
            send_mqttt_dht(DHT2_PIN, my_topic, prefix, chk, h, t, serror, error);
          } else if ( strcmp_P(uuid, pmem_dht_out_hum_uuid) == 0 ) {
            temp2_last = millis();
            int chk = 0;
            float h = NULL;
            float t = NULL;
            char serror[L_ERROR];
            bool error = false;
            char my_topic[L_TOPIC];
            strcpy_P(my_topic, pmem_topic_users);
            strcat(my_topic,my_hadd);
            strcat_P(my_topic,pmem_topic_separator);
            strcpy(prefix, "dht_out");
            send_mqttt_dht(DHT2_PIN, my_topic, prefix, chk, h, t, serror, error);
          }
    }
    #endif
  }
  #ifdef DEBUG_MEMORY
    show_memory();
  #endif
  // Free the memory
  free(p);
}

void setup_mqtt()
{
  uint32_t random_long;
  random_long = Entropy.random() & 0xFFFFFF;
  char uuid[30];
  ltoa(random_long, uuid, 16);
  random_long = Entropy.random() & 0xFFFFFF;
  ltoa(random_long, &uuid[6], 16);
  #ifdef DEBUG_MQTT
    Serial.print(F("Connect to mqtt using nodes uuid "));
    Serial.println(uuid);
  #endif
  if (mqttClient.connect(uuid)) {
    char topic[L_TOPIC];
    strcpy_P(topic, pmem_topic_nodes);
    strcat(topic,my_hadd);
    strcat_P(topic,pmem_topic_request);
    mqttClient.subscribe(topic);
    strcpy_P(topic,pmem_topic_broadcast_request);
    mqttClient.subscribe(topic);
  }
}

void loop_mqtt()
{
  if (replies_to_send == true) {
    if (replies_nodes>0) {
      reply_node();
      replies_nodes -= 1;
    } else if (replies_users>0) {
      reply_users();
      replies_users -= 1;
    } else if (replies_configs>0) {
      reply_configs();
      replies_configs -= 1;
    } else if (replies_systems>0) {
      reply_systems();
      replies_systems -= 1;
    } else {
      replies_to_send = false;
    }
  }
}


