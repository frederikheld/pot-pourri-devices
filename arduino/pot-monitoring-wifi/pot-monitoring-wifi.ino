#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#include <ArduinoJson.h> // Has to be 5.* since 6 changes the interface


// -- configuration

#include "config.h"


// -- variables

int analog_val;


// -- main

void setup() {

    // -- SETUP

    // heartbeat led:
    pinMode(HEARTBEAT_PIN, OUTPUT);
    digitalWrite(HEARTBEAT_PIN, LOW);

    // humidity sensor:
    pinMode(SENSOR_HUMIDITY_VCC_OUT, OUTPUT);
    digitalWrite(SENSOR_HUMIDITY_VCC_OUT, LOW);
    pinMode(SENSOR_HUMIDITY_ANALOG_IN, INPUT);

    // init serial:
    Serial.begin(9600);

    // debug:
    Serial.print("ArduinoJson version: ");
    Serial.println(ARDUINOJSON_VERSION_MAJOR);

    // init wifi:
    int wifi_connect_retry_delay = 500; // in milliseconds
    WiFi.begin(WIFI_SSID, WIFI_SECRET);
    Serial.print("Attempting to connect to WiFi ");
    Serial.print(WIFI_SSID);
    Serial.print(".");

    while (WiFi.status() != WL_CONNECTED) {
        delay(wifi_connect_retry_delay);
        Serial.print(".");
    }

    Serial.println("");
    Serial.print("Connected. Local IP is ");
    Serial.println(WiFi.localIP());

    // take a deep breath:
    delay(1000);


    // -- LOOP

    // heartbeat:
    digitalWrite(HEARTBEAT_PIN, HIGH);
    delay(1000);
    digitalWrite(HEARTBEAT_PIN, LOW);
    delay(1000);

    // how I would like to do it:
    // int humidity_raw = getHumidity(SENSOR_HUMIDITY_VCC_OUT, SENSOR_HUMIDITY_ANALOG_IN);
    // Serial.println(humidity_raw);

//   JsonObject sample_json = compileSample(humidity_raw, jonsObject);
//   sample_json.printTo(Serial);


    // -- collect data

    int analog_raw = getHumidity(SENSOR_HUMIDITY_VCC_OUT, SENSOR_HUMIDITY_ANALOG_IN);


    // -- compile sample

    // init json object:
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& jsonObject = jsonBuffer.createObject();

    // compile sample:
    jsonObject["device_id"] = DEVICE_ID;
    jsonObject["sensor_id"] = SENSOR_HUMIDITY_ID;
    jsonObject["value_raw"] = analog_raw;


    // -- log to serial:

    jsonObject.printTo(Serial);
    Serial.println();


    // -- send sample to datastore:

    String api_call = "/samples";

    // prepare data:
    String payload;
    jsonObject.printTo(payload);

    // post data via http:
    Serial.println("Attempting to POST " + payload);
    Serial.println(String("  to ") + API_ENDPOINT + api_call + ".");
    
    HTTPClient http;
    http.begin(String("") + API_ENDPOINT + api_call);
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST(payload);
    if (httpCode > 0) {
        Serial.println("POST was successful. HTTP status code " + httpCode);
        if (httpCode == HTTP_CODE_OK) {
            String response = http.getString();
            Serial.println("Response: " + response);
        }
    } else {
        Serial.println("POST failed. HTTP status code " + httpCode);
    }
    http.end();

    sleepSeconds(SAMPLING_INTERVAL);
  
}

void loop() {
    // To enable deep sleep the loop has to be empty.
}


// -- functions

void sleepSeconds(int time_in_seconds) {

    // turn all outputs off:
    digitalWrite(HEARTBEAT_PIN, LOW);
    digitalWrite(SENSOR_HUMIDITY_VCC_OUT, LOW);

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

int getHumidity(uint8_t vcc_out, uint8_t analog_in) {

    // turn sensor on:
    digitalWrite(vcc_out, HIGH);
    delay(100); // the sensors takes some microseconds until it is ready

    // measure:
    int value_raw = analogRead(analog_in);

    // turn sensor off:
    digitalWrite(vcc_out, LOW);

    // return:
    return value_raw;

}

JsonObject compileSample(int value_raw) {
  
    // json object:
    // StaticJsonBuffer<200> jsonBuffer;
    // DynamicJsonBuffer jsonBuffer;
    // JsonObject jsonObject = jsonBuffer.createDocument();

    // add meta data:
    // jsonObject["device_id"] = DEVICE_ID;
    // TBD: add timestamp

    // add sample value:
    // jsonObject["value_analog"] = value_raw;

    // return:
    // return jsonObject;
    // jsonObject.printTo(Serial);

}