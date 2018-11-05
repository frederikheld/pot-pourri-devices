// Works with NodeMCU mini
// Using DHTesp library by Mark Rys (https://github.com/beegee-tokyo/DHTesp)
#include <DHTesp.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <OneWire.h>
#include <DallasTemperature.h>


// --- configuration

// DHT humidity and temperature sensor
#define DHT_PIN D4
#define DHT_TYPE DHTesp::DHT11

// raw temperature sensor (via analog input)
#define RAWTEMP_PIN A0

// DS10B20 temperature sensor (via 1-wire bus)
#define DS10B20_DATA D5

// oled display
#define OLED_ADDRESS 0x3c // Hardware says 0x78. Don't trust the print on the board!
#define OLED_RESET D8  // Not used with this display but needed for the constructor


// -- main

DHTesp dht;
Adafruit_SSD1306 display(OLED_RESET);
OneWire oneWire(DS10B20_DATA);

DallasTemperature dallasTemp(&oneWire);

void setup() {
  dht.setup(DHT_PIN, DHT_TYPE);
  
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
  display.clearDisplay();
  display.display();

  dallasTemp.begin();
 
  Serial.begin(115200);
}

void loop() {
  delay(1900);

  // DHT
  float dhtHumidity = dht.getHumidity();
  float dhtTemperature = dht.getTemperature();

  // raw
  int rawTemperature = analogRead(RAWTEMP_PIN);

  // DS10B20
  dallasTemp.requestTemperatures();
  float ds10b20Temperature = dallasTemp.getTempCByIndex(0);

  delay(100);

  Serial.print("humidity: ");
  Serial.print(dhtHumidity);
  Serial.print(" % | ");
  Serial.print("temperature absolute: ");
  Serial.print(dhtTemperature);
  Serial.print(" °C | temperature raw: ");
  Serial.print(rawTemperature);
  Serial.print(" | temperature ds10b20: ");
  Serial.print(ds10b20Temperature);
  Serial.print(" °C");
  Serial.println("");
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  display.setCursor(0, 0);
  display.print("Humidity dht:");
  display.setCursor(80, 0);
  display.print(dhtHumidity);
  display.setCursor(110, 0);
  display.print(" %");
  
  display.setCursor(0, 12);
  display.print("Temp dht:");
  display.setCursor(80, 12);
  display.print(dhtTemperature);
  display.setCursor(110, 12);
  display.print(" ^C");
  
  display.setCursor(0, 24);
  display.print("Temp raw:");
  display.setCursor(80, 24);
  display.print(rawTemperature);
  
  display.setCursor(0, 36);
  display.print("Temp ds10b20:");
  display.setCursor(80, 36);
  display.print(ds10b20Temperature);
  display.setCursor(110, 36);
  display.print(" ^C");
  
  display.display();
  
}
