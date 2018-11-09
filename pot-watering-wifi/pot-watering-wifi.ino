#include <Servo.h>

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#include <ArduinoJson.h> // Has to be 5.* since 6 changes the interface


// -- configuration

#include "config.h"


// -- variables

#define VALVESERVO_OUT D5


// -- main

Servo valveServo;

void setup() {

    // init serial:
    Serial.begin(115200);

    // init valve:
    valveServo.attach(VALVESERVO_OUT);

    // take a deep breath:
    delay(1000);
  
}

void loop() {
    
    valveServo.write(0);
    Serial.println("Servo at    0°");
    delay(2000);

    valveServo.write(90);
    Serial.println("Servo at   90°");
    delay(2000);

    valveServo.write(0);
    Serial.println("Servo at    0°");
    delay(2000);

    valveServo.write(180);
    Serial.println("Servo at  180°");
    delay(2000);
}


// -- functions