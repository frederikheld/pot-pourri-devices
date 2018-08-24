#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#define BLINK_OUT D2
#define BLINK_INTERVAL 2 // in seconds

void setup() {

    // -- SETUP

    pinMode(BLINK_OUT, OUTPUT);
    digitalWrite(BLINK_OUT, LOW);


    // -- LOOP

    digitalWrite(BLINK_OUT, HIGH);
    delay(BLINK_INTERVAL * 1000); // time in milliseconds
    digitalWrite(BLINK_OUT, LOW);
    
    // with bridge between RST and D0
    ESP.deepSleep(BLINK_INTERVAL * 1000 * 1000); // time in microseconds!

    // without bridge between RST and D0
    // esp_sleep_enable_timer_wakeup(BLINK_INTERVAL * 1000 * 1000);
    // esp_deep_sleep_start();

    // Deep sleep will shut off all pins.
    // So we can't use it while the LED is turned on.
}

void loop() {
    // Loop has to be empty to enable deep sleep!
}

