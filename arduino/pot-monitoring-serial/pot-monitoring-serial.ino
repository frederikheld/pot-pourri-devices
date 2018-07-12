
/*
 * This experiments shows how values are read from the hygro sensor.
 *
 * The sensor is only supplied with current for the time of measurement
 * to avoid early corrosion of the electrodes.
 * It takes about 100 ms until it is ready to provide correct values.
 * The out pin does not supply full 5V, so the max value is about 1006
 * compared to the real max of 1023 which is only achieved by supplying
 * it via the 5V pin.
*/

#include <ArduinoJson.h>

// Board Information
#define DEVICE_ID 0001

// Hygro Sensor
#define ANALOG_IN A0
#define DIGITAL_IN 8
#define SENSOR_VCC_OUT 4

// Variables
int analog_val;
int digital_val;

void setup()
{
  // Initialize hygro sensor:
  pinMode(ANALOG_IN, INPUT);
  pinMode(DIGITAL_IN, INPUT);
  pinMode(SENSOR_VCC_OUT, OUTPUT);
  digitalWrite(SENSOR_VCC_OUT, LOW);

  // Initialize serial port:
  Serial.begin(115200);
  
  // Take a deep breath:
  delay(1000);
}

void loop()
{
  
  // Turn on sensor:
  digitalWrite(SENSOR_VCC_OUT, HIGH);
  delay(100);

  // Store meta data:
  jsonObject["device_id"] = DEVICE_ID;

  // Read values:
  jsonObject["digital"] = digitalRead(DIGITAL_IN);
  jsonObject["analog"] = analogRead(ANALOG_IN);

  // Turn off sensor:
  digitalWrite(SENSOR_VCC_OUT, LOW);
  
  // Initialize JSON object:
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& jsonObject = jsonBuffer.createObject();

  // Report values:
  jsonObject.printTo(Serial);
  Serial.println();

  // Wait for next cycle:
  delay(1000);
  
}
