#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#include <ArduinoJson.h> // Has to be 5.* since 6 changes the interface


// -- configuration

#include "config.h"


// -- variables

int analog_val;


// -- main

void setup() {

    // heartbeat led:
    pinMode(HEARTBEAT_PIN, OUTPUT);
    digitalWrite(HEARTBEAT_PIN, LOW);

    // heatbeat led:
    pinMode(HEARTBEAT_PIN, OUTPUT);
    digitalWrite(HEARTBEAT_PIN, LOW);

    // humidity sensor:
    pinMode(SENSOR_HUMIDITY_ANALOG_IN, INPUT);
    pinMode(SENSOR_HUMIDITY_VCC_OUT, OUTPUT);
    digitalWrite(SENSOR_HUMIDITY_VCC_OUT, LOW);

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
  
}

void loop() {

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
    jsonObject["analog_raw"] = analog_raw;


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

/* Works, but it's difficult. No payload yet.
    // connect to client:
    WiFiClient client;
    String response = "";
    if (client.connect(API_HOST, API_PORT)) {
        Serial.println(String("Connected to ") + API_HOST + ":" + API_PORT + ".");


        int content_length = 0;
        
        // send request:
        client.print(String("POST ") + API_ENDPOINT + "samples/ HTTP/1.1\r\n");
        client.print(String("Host: ") + API_HOST + "\r\n");
        client.print("Content-Type: application/json\r\n");
        client.print(String("Content-Length: ") + content_length);
        client.print("Connection: close\r\n");
        client.print("\r\n");

        // wait for reply:
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                response = response + c;
            }
        }
        client.stop();

        Serial.println(String("Response: ") + response);

    }

        */


    // wait for next cycle:
    delay(SAMPLING_INTERVAL * 1000);

}


// -- functions

int getHumidity(uint8_t vcc_out, uint8_t analog_in) {

    // turn sensor on:
    digitalWrite(vcc_out, HIGH);
    delay(100); // the sensors takes some seconds until it is ready

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