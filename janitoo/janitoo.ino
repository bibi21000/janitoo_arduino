
/*
 Janitoo example for mega 2560.
Update the max size in pubsubclient.h
// MQTT_MAX_PACKET_SIZE : Maximum packet size
#define MQTT_MAX_PACKET_SIZE 1024

And fix a bug :
boolean PubSubClient::write(uint8_t header, uint8_t* buf, uint16_t length) {
   uint8_t lenBuf[4];
   uint8_t llen = 0;
   uint8_t digit;
   uint8_t pos = 0;
   uint8_t rc;
   uint16_t len = length;
...
}
Change uint8_t to uint16_t len for length


  - connects to an MQTT server
  - publishes "hello world" to the topic "outTopic"
  - subscribes to the topic "inTopic"
*/

#include "janitoo.h";
#include "eeprom.h";
#include "memory.h";
#include "mqtt.h";
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <Entropy.h>
#include <EEPROM.h>

/***************** DEBUG *******************/
#define DEBUG
//#define DEBUG_CONSOLE
//#define DEBUG_EEPROM
#define DEBUG_MEMORY
#ifdef DEBUG_MEMORY
  int last_min_memory = 16000;
#endif

//#define DEBUG_NETWORK
#define DEBUG_MQTT
#ifdef DEBUG_MEMORY
  int last_max_jsonsize;
#endif

//#define DEBUG_DHT
#define BUILD_DHT
#ifdef BUILD_DHT
  #define DHT1_PIN 31
  #define DHT2_PIN 32
  unsigned long temp1_last = 0;
  unsigned long temp2_last = 0;
#endif

#define DEBUG_RGB
#define BUILD_RGB
#ifdef BUILD_RGB
  #define RED_PIN 9
  #define GREEN_PIN 10
  #define BLUE_PIN 9
  unsigned long rgb_last = 0;
#endif

//#define GENERATE_NEW_UUID
char my_hadd[L_HADD];
bool replies_to_send = false;
byte replies_nodes = 0;
byte replies_users = 0;
byte replies_configs = 0;
byte replies_systems = 0;
char reply_hadd[L_HADD];

int config_timeout = 10;

unsigned long config_timeout_run_at = 0;

unsigned int hb_time = 10000;
unsigned long hb_last = 0;

#define REPLIES_NODES 1;
#define REPLIES_USERS 7;
#define REPLIES_CONFIGS 7;
#define REPLIES_SYSTEMS 3;

//Restart the program
void(* resetFunc) (void) = 0; //declare reset function @ address 0

EthernetClient ethClient;

byte server[] = { 192, 168, 14, 54 };
PubSubClient mqttClient(server, 1883, nodeCallback, ethClient);

void setup()
{
  Serial.begin(115200);
  #ifdef DEBUG
    Serial.print(F("Start "));
    char my_node_product[L_PRODUCT];
    char my_node_type[L_TYPE];
    ereadProduct(my_node_product);
    ereadTypeFull(my_node_type);
    Serial.print(my_node_product);
    Serial.print(F(" ["));
    Serial.print(my_node_type);
    Serial.print(F("] ..."));
  #endif
  Entropy.initialize();
  setWatchdog();
  delay(1500);
  checkWatchdog();
  ereadHadd(my_hadd);
  setup_network();
  setup_mqtt();
  setup_heartbeat();
  resetWatchdog();
  #ifdef BUILD_DHT
    setup_dht();
  #endif
  #ifdef BUILD_RGB
    setup_rgb();
  #endif

  ereadConfigTimeout(config_timeout);

  #ifdef DEBUG
      Serial.println(F("... started"));
  #endif
#ifdef DEBUG_MEMORY
  show_memory();
#endif

}

void loop()
{
  //Serial.println(hb_time);
  //Serial.println(millis());
  //Serial.println(hb_last);
  loop_heartbeat();
  #ifdef BUILD_DHT
    loop_dht();
  #endif
  #ifdef BUILD_RGB
    loop_rgb();
  #endif
  loop_network();
  if (!mqttClient.loop()) {
    setup_mqtt();
  }
  loop_mqtt();
  if (config_timeout_run_at !=0 && config_timeout_run_at<millis()) {
    resetFunc();
  }

}

#ifdef DEBUG_MEMORY
void show_memory()
{
  int current = freeMemory();
  if (current < last_min_memory) {
    last_min_memory = current;
  }
  Serial.print(F("Memory free         "));
  Serial.println(current);
  Serial.print(F("Minimal memory free "));
  Serial.println(last_min_memory);
}
#endif

#ifdef DEBUG_MQTT
void show_jsonsize(int len)
{

  if (len > last_max_jsonsize) {
    last_max_jsonsize = len;
  }
  Serial.print(F("JSON length       "));
  Serial.println(len);
  Serial.print(F("Max JSON length "));
  Serial.println(last_max_jsonsize);
}
#endif

const char pmem_seconds[] PROGMEM = "seconds";
const char pmem_degree[] PROGMEM = "°C";
const char pmem_percent[] PROGMEM = "%";
const char pmem_rgb[] PROGMEM = "R#G#B";

const char pmem_name_uuid[] PROGMEM = "name";
const char pmem_name_label[] PROGMEM = "name";
const char pmem_name_help[] PROGMEM = "The node name";
const char pmem_location_uuid[] PROGMEM = "location";
const char pmem_location_label[] PROGMEM = "location";
const char pmem_location_help[] PROGMEM = "The node location";
const char pmem_product_uuid[] PROGMEM = "product";
const char pmem_type_uuid[] PROGMEM = "type";
const char pmem_in_poll_uuid[] PROGMEM = "dht_in_poll";
const char pmem_in_poll_label[] PROGMEM = "DHT In poll";
const char pmem_in_poll_help[] PROGMEM = "The poll delay of the intern temp/humidity sensor";
const char pmem_in_enabled_uuid[] PROGMEM = "dht_in_enabled";
const char pmem_in_enabled_label[] PROGMEM = "DHT In enabled";
const char pmem_in_enabled_help[] PROGMEM = "Is the temp/humidity sensor enabled";
const char pmem_out_poll_uuid[] PROGMEM = "dht_out_poll";
const char pmem_out_poll_label[] PROGMEM = "Out poll";
const char pmem_out_poll_help[] PROGMEM = "The poll delay of the intern temp/humidity sensor";
const char pmem_out_enabled_uuid[] PROGMEM = "dht_out_enabled";
const char pmem_out_enabled_label[] PROGMEM = "Out enabled";
const char pmem_out_enabled_help[] PROGMEM = "Is the temp/humidity sensor enabled";
const char pmem_rgb_poll_uuid[] PROGMEM = "rgb_poll";
const char pmem_rgb_poll_label[] PROGMEM = "RGB poll";
const char pmem_rgb_poll_help[] PROGMEM = "The poll delay of the rgb led driver";

const char pmem_request_info_users[] PROGMEM = "request_info_users";
const char pmem_request_info_systems[] PROGMEM = "request_info_systems";
const char pmem_request_info_nodes[] PROGMEM = "request_info_nodes";
const char pmem_request_info_configs[] PROGMEM = "request_info_configs";

const char pmem_heartbeat_uuid[] PROGMEM = "heartbeat";
const char pmem_heartbeat_label[] PROGMEM = "heartbeat poll";
const char pmem_heartbeat_help[] PROGMEM = "The heartbeat delay in seconds";
const char pmem_hadd_uuid[] PROGMEM = "hadd";
const char pmem_hadd_label[] PROGMEM = "hadd";
const char pmem_hadd_help[] PROGMEM = "The Janitoo Home address";
const char pmem_config_timeout_uuid[] PROGMEM = "config_timeout";
const char pmem_config_timeout_label[] PROGMEM = "config timeout";
const char pmem_config_timeout_help[] PROGMEM = "The delay to wait to reboot to apply new config";

const char pmem_dht_in_temp_uuid[] PROGMEM = "dht_in_temp";
const char pmem_dht_in_temp_label[] PROGMEM = "in temperature";
const char pmem_dht_in_temp_help[] PROGMEM = "The inside temperature";
const char pmem_dht_in_hum_uuid[] PROGMEM = "dht_in_hum";
const char pmem_dht_in_hum_label[] PROGMEM = "in humidity";
const char pmem_dht_in_hum_help[] PROGMEM = "The inside relative humidity";
const char pmem_dht_out_temp_uuid[] PROGMEM = "dht_out_temp";
const char pmem_dht_out_temp_label[] PROGMEM = "out temperature";
const char pmem_dht_out_temp_help[] PROGMEM = "The outside temperature";
const char pmem_dht_out_hum_uuid[] PROGMEM = "dht_out_hum";
const char pmem_dht_out_hum_label[] PROGMEM = "out humidity";
const char pmem_dht_out_hum_help[] PROGMEM = "The outside relative humidity";
const char pmem_rgb_color_uuid[] PROGMEM = "rgb_color";
const char pmem_rgb_color_label[] PROGMEM = "rgb color";
const char pmem_rgb_color_help[] PROGMEM = "Get the color to the RGB value";
const char pmem_set_rgb_color_uuid[] PROGMEM = "set_rgb_color";
const char pmem_set_rgb_color_label[] PROGMEM = "set rgb color";
const char pmem_set_rgb_color_help[] PROGMEM = "Set the color to the RGB value";
const char pmem_dim_rgb_color_uuid[] PROGMEM = "dim_rgb_color";
const char pmem_dim_rgb_color_label[] PROGMEM = "dim rgb color";
const char pmem_dim_rgb_color_help[] PROGMEM = "Dim the color to the RGB value";

const char pmem_topic_separator[] PROGMEM = "/";
const char pmem_topic_heartbeat[] PROGMEM = "/dhcp/heartbeat/";
const char pmem_topic_nodes[] PROGMEM = "/nodes/";
const char pmem_topic_users[] PROGMEM = "/values/user/";
const char pmem_topic_basics[] PROGMEM = "/values/basic/";
const char pmem_topic_systems[] PROGMEM = "/values/system/";
const char pmem_topic_configs[] PROGMEM = "/values/config/";
const char pmem_topic_request[] PROGMEM = "/request";
const char pmem_topic_reply[] PROGMEM = "/reply";
const char pmem_topic_broadcast_request[] PROGMEM = "/broadcast/request";
