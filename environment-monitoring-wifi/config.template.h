// -- DEVICE

// device:
#define DEVICE_ID "0" // has to be unique within the Pot Pourri network!
#define SAMPLING_INTERVAL 60 // in seconds. Note: The time it takes to collect and send the data goes on top!


// -- CONECTIVITY

// wifi:
#define WIFI_SSID "<wifi-ssid>"
#define WIFI_SECRET "<wifi-secret>"
#define WIFI_CONNECT_RETRY_DELAY 500 // time to wait (in milliseconds) before retrying if connect to wifi failed
#define WIFI_CONNECT_RETRY_TIMEOUT 10000 // time (in milliseconds) until a failed attempt to connect to wifi will be aborted

// mqtt:
#define MQTT_SERVER "<mqtt-broker-ip-or-hostname>"
#define MQTT_PORT 1883
#define MQTT_CONNECT_RETRY_DELAY 500 // time to wait (in milliseconds) before retrying if connect to mqtt broker failed. The connection attempt itself will timeout after 1000 ms.
#define MQTT_CONNECT_RETRY_TIMEOUT 10000 // time (in milliseconds) until a failed attempt to connect to mqtt broker will be aborted. This includes 1000 ms per connection attempt as well as MQTT_CONNECT_RETRY_DELAY.
#define MQTT_SEND_REBOUNCE_DELAY 500 // time to wait (in milliseconds) before retrying to receive a rebounced message
#define MQTT_SEND_REBOUNCE_TIMEOUT 10000 // time to wait (in milliseconds) for an sent MQTT message to be rebounced
#define MQTT_ROOT_TOPIC "potpourri" // basic topic of the potpourri setup

// -- SENSORS

// humidity sensor:
#define SENSOR_HUMIDITY_ID "humidity" // has to be unique per device. Can be a string or an integer.
#define SENSOR_HUMIDITY_VCC_OUT D5
#define SENSOR_HUMIDITY_ONEWIRE_IN D6
