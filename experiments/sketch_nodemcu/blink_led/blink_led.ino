#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

#include "config.h"


// -- configuration // should be done via api later

uint8_t pin_led = D0;


// -- functions

String httpPost(const char* host, int port, const char* url, String payload) {
  
  WiFiClient client;

  String response = "";
  if(client.connect(host, port)) {

    Serial.println(String("Connected to ") + host + ":" + port + ".");

    // Send request:
    client.print(String("POST ") + url + " HTTP/1.1\r\n");
    client.print(String("Host: ") + host + "\r\n");
    client.print("Connection: close\r\n");
    client.print("\r\n");    
    
    // Wait for reply:
    while (client.connected()) {
      //Serial.print(".");
      if (client.available()) {
        char c = client.read();
        response = response + c;
        Serial.print(c);
        /*response = response + client.readStringUntil('\r\n');
        //Serial.println(response);*/
      
      }
    }
    
    client.stop();
    Serial.println(response);
    return response;

  } else {
    client.stop();
    Serial.println(String("Could not connect to ") + host + ":" + port + ".");    
  }

}

int wifiConnect(const char* ssid, const char* secret, int timeout = 10000) {

  int wifi_connect_retry_delay = 500; // in milliseconds
  
  WiFi.begin(ssid, secret);
  Serial.print("Connecting to WiFi ");
  Serial.print(ssid);
  Serial.print(".");
  
  while (WiFi.status() != WL_CONNECTED) {
    
    if (timeout < 0) {
      Serial.print("Could not connect to WiFi ");
      Serial.print(wifi_ssid);
      Serial.print(". Timeout of ");
      Serial.print(timeout);
      Serial.println(" milliseconds reached.");
      
      return 1;
    }
    
    delay(5000);
    Serial.print(".");
   
    timeout = timeout - wifi_connect_retry_delay;
  }

  Serial.println();
  Serial.print("Connected. Local IP is ");
  Serial.println(WiFi.localIP());
  
  return 0;
}

// timeout in seconds
void deepSleep(int timeout) {
  ESP.deepSleep(timeout * 1000000);
}


// -- main

void setup() {
  pinMode(pin_led, OUTPUT);
  digitalWrite(pin_led, LOW);

  Serial.begin(9600);
  delay(1000);
  
  /*int error = wifiConnect(wifi_ssid, wifi_secret);
  if (error > 0) {
    deepSleep(measurement_interval);
  }*/

  wifiConnect(wifi_ssid, wifi_secret);
  
  String response = httpPost(host, port, "/", "Hello World!");
  Serial.println(response);
}

void loop() {
  digitalWrite(pin_led, HIGH);
  delay(1000);
  digitalWrite(pin_led, LOW);
  delay(1000);
  
  String response = httpPost(host, port, "/", "Hello World!");
  Serial.println(response);
  
}
