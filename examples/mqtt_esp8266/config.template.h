// -- DEVICE

// device:
#define DEVICE_ID 0 // has to be unique per datastore!


// -- CONECTIVITY

// wifi:
#define WIFI_SSID "<wifi-ssid>"
#define WIFI_SECRET "<wifi-secret>"
#define WIFI_CONNECT_RETRY_DELAY 500 // Optional. Time to wait (in milliseconds) before retrying if connect to wifi failed. Defaults to 500.

// mqtt:
#define MQTT_SERVER "<mqtt-broker-ip-or-hostname>"
#define MQTT_PORT = 1883
#define MQTT_CONNECT_RETRY_DELAY 5000 // Optional. Time to wait (in milliseconds) before retrying if connect to mqtt broker failed. Defaults to 5000.


// -- SENSORS

// humidity sensor:
#define SENSOR_HUMIDITY_ID 0 // has to be unique per device
#define SENSOR_HUMIDITY_VCC_OUT D5
#define SENSOR_HUMIDITY_ANALOG_IN A0
