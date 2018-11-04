// Works with Arduino Micro

#include <DHT.h>
#include <DHT_U.h>


// --- configuration

#define DHT_PIN 2
#define DHT_TYPE DHT11


// -- main

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  dht.begin();

  Serial.begin(9600);
  Serial.println("humidity and temperature\n\n");
  
  delay(1000);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  delay(1000);
  Serial.print("humidity: ");
  Serial.print(humidity);
  Serial.print(" % | ");
  Serial.print("temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  delay(1000);

}
