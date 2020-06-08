# PotMonitoring WiFi device

This is the standard device for your setup. It is powered by a _NodeMCU_, which can connect to your local WiFi. It pulishes current sensor readings in defined intervals to a _MQTT_ topic.

## Sensors

Currently, the only sensor is an analog humidity sensor, which generates values betwen 0 (zero humidity) to 1024 (100 % humidity).