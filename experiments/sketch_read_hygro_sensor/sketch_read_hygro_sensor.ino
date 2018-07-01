
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

#define ANALOG_IN A0
#define DIGITAL_IN 8
#define SENSOR_VCC_OUT 4

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
  Serial.begin(9600);  

  // Take a deep breath:
  delay(1000);
  Serial.println("Arduino ready");
  Serial.println("------------------------");
}

void loop()
{
  // Turn on sensor:
  digitalWrite(SENSOR_VCC_OUT, HIGH);
  delay(100);

  // Read values:
  digital_val = digitalRead(DIGITAL_IN);
  analog_val = analogRead(ANALOG_IN);

  // Turn off sensor:
  digitalWrite(SENSOR_VCC_OUT, LOW);

  // Report values:
  Serial.print("Digital: ");
  Serial.println(digital_val);
  Serial.print("Analog:  ");
  Serial.println(analog_val);
  Serial.println("------------------------");

  // Wait for next cycle:
  delay(1000);
}
