// Works with NodeMCU mini
// Using DHTesp library by Mark Rys (https://github.com/beegee-tokyo/DHTesp)
#include <DHTesp.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


// --- configuration

// DHT humidity and temperature sensor
#define DHT_PIN D4
#define DHT_TYPE DHTesp::DHT11

// raw temperature sensor
#define RAWTEMP_PIN A0

// oled display
#define OLED_ADDRESS 0x3c // Hardware says 0x78. Don't trust the print on the board!
#define OLED_RESET D8  // Not used with this display but needed for the constructor


// -- main

DHTesp dht;
Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  dht.setup(DHT_PIN, DHT_TYPE);
  
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
  display.clearDisplay();
  display.display();
 
  Serial.begin(115200);
}

void loop() {
  delay(1900);

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  int temperatureRaw = analogRead(RAWTEMP_PIN);

  delay(100);

  Serial.print("humidity: ");
  Serial.print(humidity);
  Serial.print(" % | ");
  Serial.print("temperature absolute: ");
  Serial.print(temperature);
  Serial.print(" °C | temperature raw: ");
  Serial.print(temperatureRaw);
  Serial.println("");
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  display.setCursor(0, 0);
  display.print("Humidity:");
  display.setCursor(20, 10);
  display.print(humidity);
  display.setCursor(48, 10);
  display.print(" %");
  
  display.setCursor(0, 22);
  display.print("Temperature:");
  display.setCursor(20, 32);
  display.print(temperature);
  display.setCursor(48, 32);
  display.print(" C");
  
  display.setCursor(0, 44);
  display.print("TempRaw:");
  display.setCursor(20, 54);
  display.print(temperatureRaw);
  
  display.display();
  
}
