/*
 * Instructions:
 *  - rename config.template.h to config.h
 *    and fill in the settings according to your setup
 *  - install libraries as explained in README.md
 *  - select the correct board
 *  - upload the sketch
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

  }
  
  Serial.println(" Connected.");
  Serial.print("  Assigned IP is ");
  Serial.print(WiFi.localIP());
  Serial.println(".");
  return true;
  
}

bool mqttConnect(const char* device_id, PubSubClient mqttClient, const char* mqtt_server, const int mqtt_port, const int mqtt_connect_retry_delay = 500, const int mqtt_connect_retry_timeout = 10000) {
  
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
    
  }
    
  Serial.println(" Connected.");
    
  Serial.print("  Client ID is ");
  Serial.print(mqttClientId);
  Serial.println(".");

  return true;
  
}

bool mqttSendMessage(const char* topic, const char* message) {

  // subscibe to outgoing topic to be able
  // to check if message was delivered:
  mqttClient.subscribe((String(MQTT_ROOT_TOPIC) + "/" + topic).c_str());

  // publish message on given topic:
  Serial.print("Publishing message '");
  Serial.print(message);
  Serial.print("' on topic '");
  Serial.print(String(MQTT_ROOT_TOPIC) + "/" + topic);
  Serial.print("'.");
  
  mqttClient.publish((String(MQTT_ROOT_TOPIC) + "/" + topic).c_str(), message, true);

  // wait until message was rebounced:
  // Note: This is not an implement of QoS 1 (which this library is lacking)
  //       as there will be no attempt to send the message again if it failed.
  //       This behavior could be added though.
  //       Right now it just makes sure that the message is fully sent before
  //       the board enters deep sleep mode. By waiting for the message to be
  //       delivered back to this device we can make sure that it was delivered
  //       to the broker.
  
  int receive_retry_delay = MQTT_SEND_REBOUNCE_DELAY;
  int receive_retry_timeout = MQTT_SEND_REBOUNCE_TIMEOUT;
  
  while (!mqtt_message_is_received && receive_retry_timeout > 0) {
    Serial.print(".");
    mqttClient.loop();

    // reset mqtt_message_is_received if wrong message was received:
    if (mqtt_message_is_received && !strcmp(mqtt_received_message, message) == 0) {
      mqtt_message_is_received = false;
    }

    // prepare next loop:
    receive_retry_timeout -= receive_retry_delay;
    delay(receive_retry_delay);
  }

  if (receive_retry_timeout <= 0) {
    Serial.println(" Timed out.");
    return false;
  }

  Serial.println(" Delivered.");
  return true;
  
}

void mqttMessageReceivedCallback(const char* topic, const byte* payload, const unsigned int length) {

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

void deepSleepSeconds(const int time_in_seconds) {

    // deep sleep:
    ESP.deepSleep(time_in_seconds * 1000 * 1000); // time in microseconds!
    // Note: This requires a bridge between RST and D0 in order to work!
  
    // Note: Deep sleep will shut off all pins.

}

int readSensorAnalog(const uint8_t pin_analog_in, const uint8_t pin_vcc_out) {
  
    // init sensor:
    pinMode(pin_vcc_out, OUTPUT);
    digitalWrite(pin_vcc_out, LOW);
    pinMode(pin_analog_in, INPUT);

    // turn sensor on:
    digitalWrite(pin_vcc_out, HIGH);
    delay(100); // the sensors takes some microseconds until it is ready
    
    // measure:
    int value_raw = analogRead(pin_analog_in);

    // turn sensor off:
    digitalWrite(pin_vcc_out, LOW);

    // return:
    return value_raw;

}

/**
 * This function wraps the work, that is being done inside setup().
 * It allows to exit the control flow if an connection attempt
 * times out and then jump directly to deep sleep.
 * This avoids the use of goto statements in setup().
 */
bool doWork() {

  // connect to wifi:
  if (!wifiConnect(WIFI_SSID, WIFI_SECRET, WIFI_CONNECT_RETRY_DELAY, WIFI_CONNECT_RETRY_TIMEOUT)) {
    return false;
  }

  // init mqtt topics:
  String mqtt_topic_humidity = String(MQTT_ROOT_TOPIC) + "/devices/" + String(DEVICE_ID) + "/sensors/" + String(SENSOR_HUMIDITY_ID);

  // connect to mqtt broker:
  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttClient.setCallback(mqttMessageReceivedCallback);

  if(!mqttConnect(DEVICE_ID, mqttClient, MQTT_SERVER, MQTT_PORT, MQTT_CONNECT_RETRY_DELAY, MQTT_CONNECT_RETRY_TIMEOUT)) {
    return false;
  }

  // read sensors:
  int sensor_humidity_value = readSensorAnalog(SENSOR_HUMIDITY_ANALOG_IN, SENSOR_HUMIDITY_VCC_OUT);

  // send data:
  char message_humidity[4]; // a sensor value is between 0 and 1024, so it has a maximum length of 4
  sprintf(message_humidity, "%d", sensor_humidity_value);
  mqttSendMessage(mqtt_topic_humidity.c_str(), message_humidity);
  
  return true;
  
}
  
void setup() {


  // -- SETUP
  
  // start serial:
  Serial.begin(9600);

  
  // -- WORK
  
  if(!doWork()) {
    Serial.println("MESSAGE COULD NOT BE SENT!");
  }

  
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
