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

bool wifiConnect(const char* ssid, const char* password, const int wifi_connect_retry_delay = 500, const int wifi_connect_retry_timeout = 10000) {

  int retry_delay = wifi_connect_retry_delay;
  int retry_timeout = wifi_connect_retry_timeout;
  
  Serial.println();
  Serial.print("Attempting to connect to WiFi ");
  Serial.print(ssid);
  Serial.print(".");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED && retry_timeout > 0) {
    Serial.print(".");

    // prepare next loop:
    retry_timeout -= retry_delay;
    delay(retry_delay);
  }

  if (retry_timeout <= 0) {
    Serial.println(" Timed out.");
    return false;
  } else {
    Serial.println(" Connected.");
    Serial.print("  Assigned IP is ");
    Serial.print(WiFi.localIP());
    Serial.println(".");
    return true;
  }
}

bool mqttConnect(int device_id, PubSubClient mqttClient, const char* mqtt_server, const int mqtt_port, const int mqtt_connect_retry_delay = 500, const int mqtt_connect_retry_timeout = 10000) {
  
  int retry_delay = mqtt_connect_retry_delay;
  int retry_timeout = mqtt_connect_retry_timeout;
  
  Serial.print("Attempting to connect to MQTT broker at ");
  Serial.print(mqtt_server);
  Serial.print(":");
  Serial.print(mqtt_port);
  Serial.print(".");
      
  // create a mqtt client id out of the device_id:
  String mqttClientId = "PotPourriDevice-";
  mqttClientId += String(device_id);
    
  while (!mqttClient.connected() && retry_timeout > 0) {
    
    // attempt to connect:
    if (mqttClient.connect(mqttClientId.c_str())) {
      break;
    } else {
      Serial.print(".");
            
      // prepare next loop:
      retry_timeout -= (retry_delay + 1000); // * see note below
      delay(retry_delay);
    }
  }

  // * note: PubSubClient::connect() uses Arduinos client.connect() function
  //         which has a default timeout of 1000 ms. This adds to the timeout
  //         which is defined in config.h!

  if (retry_timeout <= 0) {
    
    Serial.print(" Timed out. Error code ");
    Serial.println(mqttClient.state());
    
    return false;
    
  } else {
    
    Serial.println(" Connected.");
      
    Serial.print("  Client ID is ");
    Serial.print(mqttClientId);
    Serial.println(".");

    return true;
    
  }
  
}

void mqttMessageReceivedCallback(char* topic, byte* payload, unsigned int length) {

    // convert byte* payload to char*:
    char* result = (char*) payload;

    // truncate to correct length:
    if (length <= strlen(result)) {
      result[length] = '\0';
    }

    // return value:
    mqtt_message_is_received = true;
    mqtt_received_message = result;
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

/**
 * This function wraps the work, that is being done inside setup().
 * It allows to exit the control flow if an connection attempt
 * times out and then jump directly to deep sleep.
 * This avoids the use of goto statements.
 */
bool doWork() {

  // connect to wifi:
  if (!wifiConnect(WIFI_SSID, WIFI_SECRET, WIFI_CONNECT_RETRY_DELAY, WIFI_CONNECT_RETRY_TIMEOUT)) {
    return false;
  }

  // connect to mqtt broker:
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(mqttMessageReceivedCallback);

  if(!mqttConnect(DEVICE_ID, mqttClient, MQTT_SERVER, MQTT_PORT, MQTT_CONNECT_RETRY_DELAY, MQTT_CONNECT_RETRY_TIMEOUT)) {
    return false;
  }

  // subscibe to outgoing topic to be able
  // to check if message was delivered:
  mqttClient.subscribe("foo");

  // receive messages:
//  mqttClient.loop();

  // read sensors:


  // send data:
  char msg[50];
  int value = 1;
  snprintf (msg, 50, "hello world #%ld", millis());
  Serial.print("Publishing message: ");
  Serial.println(msg);
  mqttClient.publish("foo", msg);

  // wait until message was rebounced:
  // (if I received it, the broker has sent it to other clients as well
  // but we can't make sure that it was acutally delivered to the datastore):
  Serial.print("  Waiting for message to be rebounced.");
  
  int receive_retry_delay = MQTT_SEND_REBOUNCE_DELAY;
  int receive_retry_timeout = MQTT_SEND_REBOUNCE_TIMEOUT;
  
  while (!mqtt_message_is_received && receive_retry_timeout > 0) {
    Serial.print(".");
    mqttClient.loop();

    // reset mqtt_message_is_received if wrong message was received:
    if (mqtt_message_is_received && !strcmp(mqtt_received_message, msg) == 0) {
      mqtt_message_is_received = false;
    }

    // prepare next loop:
    receive_retry_timeout -= receive_retry_delay;
    delay(receive_retry_delay);
  }

  if (receive_retry_timeout <= 0) {
    Serial.println(" Timed out.");
    return false;
  } else {
    Serial.println(" Done.");
  }
  
  return true;
  
}
  
void setup() {

  // -- SETUP
  
//  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output

  // start serial:
  Serial.begin(9600);

  
  // -- WORK
  
  doWork();

  
  // -- SLEEP

  // init deep sleep:
  Serial.print("Going to deep sleep for ");
  Serial.print(SAMPLING_INTERVAL);
  Serial.println(" seconds.");
  deepSleepSeconds(SAMPLING_INTERVAL);


}

void loop() {
  // to be able to use deep sleep, loop has to stay empty!
}
