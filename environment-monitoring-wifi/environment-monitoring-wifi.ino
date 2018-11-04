// Works with NodeMCU mini
// Using DHTesp library by Mark Rys (https://github.com/beegee-tokyo/DHTesp)
#include <DHTesp.h>


// --- configuration

#define DHT_PIN D1
#define DHT_TYPE DHTesp::DHT11


// -- main

DHTesp dht;

void setup() {
  dht.setup(DHT_PIN, DHT_TYPE);

  Serial.begin(9600);
  Serial.println("humidity and temperature\n\n");
  
  delay(1000);
}

void loop() {
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  delay(1000);
  Serial.print("humidity: ");
  Serial.print(humidity);
  Serial.print(" % | ");
  Serial.print("temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  delay(1000);

}
