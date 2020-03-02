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


// -- define global variables:

bool mqtt_message_is_received = false;
char* mqtt_received_message;


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

void mqttMessageReceivedCallback(char* topic, byte* payload, unsigned int length) {

    // convert byte* payload to char*:
    char* result;
    result = (char*)payload;

    // truncate to correct length:
    if (length <= strlen(result)) {
      result[length] = '\0';
    }
    
//    // print to serial:
//    Serial.println("");
//    Serial.print("Message received on topic ");
//    Serial.print(topic);
//    Serial.print(": ");
//    Serial.println(result);

    // return value:
    mqtt_message_is_received = true;
    mqtt_received_message = result;
}

void mqttConnect(int device_id, PubSubClient mqttClient, const char* mqtt_server, const int mqtt_port, const int mqtt_connect_retry_delay = 5000) {
  
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
      
      // subscribe to outgoing channel to be able
      // to check if message was delivered:
      mqttClient.subscribe("foo");

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

void deepSleepSeconds(int time_in_seconds) {

//    // turn all outputs off:
//    digitalWrite(HEARTBEAT_PIN, LOW);
//    digitalWrite(SENSOR_HUMIDITY_VCC_OUT, LOW);

    // no deep sleep:
    // delay(time_in_seconds * 1000);

    // with bridge between RST and D0
    ESP.deepSleep(time_in_seconds * 1000 * 1000); // time in microseconds!

    // without bridge between RST and D0
    // esp_sleep_enable_timer_wakeup(BLINK_INTERVAL * 1000 * 1000);
    // esp_deep_sleep_start();
    // Source: http://educ8s.tv/esp32-deep-sleep-tutorial/
    // TODO: I could not get that running yet!

    // Deep sleep will shut off all pins.

}

void setup() {

  // -- SETUP
  
//  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output

  // start serial:
  Serial.begin(115200);

  // connect wifi:
  wifiConnect(WIFI_SSID, WIFI_SECRET, WIFI_CONNECT_RETRY_DELAY);

  // connect mqtt:
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(mqttMessageReceivedCallback);


  // -- LOOP

  // connect to mqtt broker:
  if (!mqttClient.connected()) {
    mqttConnect(DEVICE_ID, mqttClient, MQTT_SERVER, MQTT_PORT, MQTT_CONNECT_RETRY_DELAY);
  }
  mqttClient.loop();

  // read sensors:


  // send data:
  char msg[50];
  int value = 1;
  snprintf (msg, 50, "hello world #%ld", millis());
  Serial.print("Publishing message: ");
  Serial.println(msg);
  mqttClient.publish("foo", msg);

  // wait until data was received
  // (if I received it, the broker has sent it to other clients as well):
  Serial.print("  Waiting for message to be delivered.");
  while (!mqtt_message_is_received) {
    delay(1000);
    Serial.print(".");
    mqttClient.loop();

    // reset mqtt_message_is_received if wrong message was received:
    if (mqtt_message_is_received && !strcmp(mqtt_received_message, msg) == 0) {
      mqtt_message_is_received = false;
    }
  }

  Serial.println(" Done.");


  // -- INITIALIZE DEEP SLEEP

  Serial.println("Entering deep sleep mode.");
  deepSleepSeconds(SAMPLING_INTERVAL);
}

void loop() {
  
}
