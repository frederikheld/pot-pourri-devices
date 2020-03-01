/*
 * Rename config.template.h to config.h
 * and fill in the settings according to your setup!
 */

// -- import config

#include "config.h"


// -- import libraries

#include <ESP8266WiFi.h>
#include <PubSubClient.h>


// -- define global objects

// wifi client:
WiFiClient wifiClient;

// mqtt client:
PubSubClient mqttClient(wifiClient);


// -- define global vars

long lastMsg = 0;
char msg[50];
int value = 0;


// -- functions

void wifiConnect(const char* ssid, const char* password, int retry_delay = 500) {

  delay(10);
  
  Serial.println();
  Serial.print("Attempting to connect to WiFi ");
  Serial.print(ssid);
  Serial.print(".");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(retry_delay);
    Serial.print(".");
  }

  randomSeed(micros());
    
  Serial.println();
  Serial.print("  WiFi connected. Local IP is ");
  Serial.println(WiFi.localIP());
}

//void mqttMessageReceivedCallback(char* topic, byte* payload, unsigned int length) {
//  Serial.print("Message arrived [");
//  Serial.print(topic);
//  Serial.print("] ");
//  for (int i = 0; i < length; i++) {
//    Serial.print((char)payload[i]);
//  }
//  Serial.println();
//
//  // Switch on the LED if an 1 was received as first character
//  if ((char)payload[0] == '1') {
//    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
//    // but actually the LED is on; this is because
//    // it is active low on the ESP-01)
//  } else {
//    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
//  }
//
//}

void mqttConnect(int device_id, PubSubClient mqttClient, const char* mqtt_server, const int mqtt_port = 1883, const int mqtt_connect_retry_delay = 5000) {
  
  Serial.print("Attempting to connect to MQTT broker at ");
  Serial.print(mqtt_server);
  Serial.print(":");
  Serial.print(mqtt_port);
  Serial.println(".");
  
  while (!mqttClient.connected()) {
    
    // create a mqtt client id out of the device_id:
    String mqttClientId = "PotPourriDevice-";
    mqttClientId += String(device_id);
    
    // attempt to connect:
    if (mqttClient.connect(mqttClientId.c_str())) {
      
      Serial.print("  MQTT connected. Client ID is ");
      Serial.println(mqttClientId);
      
//      // once connected, publish an announcement...
//      mqttClient.publish(mqtt_topic, "hello world");
      
//      // ... and subscribe
//      mqttClient.subscribe(mqtt_topic);

    } else {
      
      Serial.print("  Failed with error code = ");
      Serial.print(mqttClient.state());
      Serial.print("! Trying again in ");
      Serial.print(mqtt_connect_retry_delay);
      Serial.println(" ms.");
      
      // wait 5 seconds before retrying:
      delay(mqtt_connect_retry_delay);
    }
  }
}

void setup() {
//  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output

  // start serial:
  Serial.begin(115200);

  // connect wifi:
  wifiConnect(wifi_ssid, wifi_secret, wifi_connect_retry_delay);

  // connect mqtt:
  mqttClient.setServer(mqtt_server, 1883);
//  mqttClient.setCallback(mqttMessageReceivedCallback);
}

void loop() {

  if (!mqttClient.connected()) {
    mqttConnect(device_id, mqttClient, mqtt_server, mqtt_port, mqtt_connect_retry_delay);
  }
  mqttClient.loop();

  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 50, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    mqttClient.publish(mqtt_topic, msg);
  }
}
