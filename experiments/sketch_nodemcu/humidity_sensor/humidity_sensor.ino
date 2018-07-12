#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>


// -- configuration

// humidity sensor
#define HUMIDITY_ANALOG_IN A0
#define HUMIDITY_VCC_OUT D5

// heartbeat led
#define HEARTBEAT_PIN D3


// -- variables

int analog_val;
int digital_val;


// -- functions

int getHumidity() {

    // turn sensor on:
    digitalWrite(HUMIDITY_VCC_OUT, HIGH);
    delay(100); // the sensors takes some seconds until it is ready

    // measure:
    int value_raw = analogRead(HUMIDITY_ANALOG_IN);

    // turn sensor off:
    digitalWrite(HUMIDITY_VCC_OUT, LOW);

    // return:
    return value_raw;

}


// -- main

void setup() {

    // heatbeat led:
    pinMode(HEARTBEAT_PIN, OUTPUT);
    digitalWrite(HEARTBEAT_PIN, LOW);

    // humidity sensor:
    pinMode(HUMIDITY_ANALOG_IN, INPUT);
    pinMode(HUMIDITY_VCC_OUT, OUTPUT);
    digitalWrite(HUMIDITY_VCC_OUT, LOW);

    // serial:
    Serial.begin(9600);

    // Take a deep breath:
    delay(1000);
  
}

void loop() {
  digitalWrite(HEARTBEAT_PIN, HIGH);
  delay(1000);
  digitalWrite(HEARTBEAT_PIN, LOW);
  delay(1000);

  int humidity_raw = getHumidity();
  Serial.println(humidity_raw);
}
