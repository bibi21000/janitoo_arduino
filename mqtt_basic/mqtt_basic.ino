/*
 Basic MQTT example 
 
  - connects to an MQTT server
  - publishes "hello world" to the topic "outTopic"
  - subscribes to the topic "inTopic"
*/

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <MQTT.h>

const char *ssid =	"xxxxxxxx";		// cannot be longer than 32 characters!
const char *pass =	"yyyyyyyy";		//

// Update these with values suitable for your network.
IPAddress server(192, 168, 14, 54);

// Update these with values suitable for your network.
IPAddress ip(192, 168, 14, 224);

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

void callback(const MQTT::Publish& pub) {
  //Serial.println(pub.payload)
  // handle message arrived
}

//WiFiClient wclient;
EthernetClient wclient;
PubSubClient client(wclient, server);

void setup()
{
  // Setup console
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();

  client.set_callback(callback);

  //WiFi.begin(ssid, pass);
 // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  Serial.println("Network started");

//  int retries = 0;
//  while ((WiFi.status() != WL_CONNECTED) && (retries < 10)) {
//    retries++;
//    delay(500);
//    Serial.print(".");
//  }
//  if (WiFi.status() == WL_CONNECTED) {
//    Serial.println("");
//    Serial.println("WiFi connected");
//  }

  if (client.connect("arduinoClient")) {
    client.publish("/dhcp/heartbeat/0111/0000","online");
    client.subscribe("inTopic");
  }
  Serial.println("Messsage sent.");
}

void loop()
{
  client.loop();
}

