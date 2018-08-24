#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#define BLINK_OUT D2

void setup() {
    pinMode(BLINK_OUT, OUTPUT);
    digitalWrite(BLINK_OUT, LOW);
}

void loop() {
    digitalWrite(BLINK_OUT, HIGH);
    delay(1000);
    digitalWrite(BLINK_OUT, LOW);
    delay(1000);
}