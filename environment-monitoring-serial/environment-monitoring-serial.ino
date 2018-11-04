// Works with Arduino Micro

#include <DHT.h>
#include <DHT_U.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


// --- configuration

// DHT humidity and temperature sensor
#define DHT_PIN 2
#define DHT_TYPE DHT11

// oled display
#define OLED_ADDRESS 0x78
#define OLED_RESET 4


// -- main

DHT dht(DHT_PIN, DHT_TYPE);
Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  dht.begin();

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
  display.clearDisplay();
  display.display();
  
  Serial.begin(9600);
  Serial.println("humidity and temperature\n\n");
  
  delay(1000);
}

void loop() {
  delay(1000);
  
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  Serial.print("humidity: ");
  Serial.print(humidity);
  Serial.print(" % | ");
  Serial.print("temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  
  /*display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Hello World!");
  display.display();*/

}
