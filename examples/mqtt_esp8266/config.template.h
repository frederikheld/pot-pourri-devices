// -- DEVICE

// device:
#define DEVICE_ID 0 // has to be unique per datastore!
#define SAMPLING_INTERVAL 10 // in seconds. Note: The time it takes to collect and send the data goes on top!


// -- CONECTIVITY

// wifi:
#define WIFI_SSID "<wifi-ssid>"
#define WIFI_SECRET "<wifi-secret>"
#define WIFI_CONNECT_RETRY_DELAY 500 // time to wait (in milliseconds) before retrying if connect to wifi failed

// mqtt:
#define MQTT_SERVER "<mqtt-broker-ip-or-hostname>"
#define MQTT_PORT = 1883
#define MQTT_CONNECT_RETRY_DELAY 5000 // time to wait (in milliseconds) before retrying if connect to mqtt broker failed
#define MQTT_SEND_REBOUNCE_DELAY 500 // time to wait (in milliseconds) before retrying to receive a rebounced message
#define MQTT_SEND_REBOUNCE_TIMEOUT 10000 // time to wait (in milliseconds) for an sent MQTT message to be rebounced


// -- SENSORS

// humidity sensor:
#define SENSOR_HUMIDITY_ID 0 // has to be unique per device
#define SENSOR_HUMIDITY_VCC_OUT D5
#define SENSOR_HUMIDITY_ANALOG_IN A0
