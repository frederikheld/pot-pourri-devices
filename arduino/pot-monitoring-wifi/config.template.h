// -- MANDATORY:

// device:
#define DEVICE_ID 1 // unique per datastore
#define SAMPLING_INTERVAL 60 // in seconds // the time it takes to collect and send the data goes on top!

// wifi:
#define WIFI_SSID "<wifi ssid>"
#define WIFI_SECRET "<wifi secret>"

// api:
#define API_ENDPOINT "<url>"

// heartbeat led:
#define HEARTBEAT_PIN D3

// humidity sensor:
#define SENSOR_HUMIDITY_VCC_OUT D5
#define SENSOR_HUMIDITY_ANALOG_IN A0
#define SENSOR_HUMIDITY_ID 1 // unique per device


// -- OPTIONAL:

// #define WIFI_TIMEOUT 30000; // in milliseconds. Default: 10000 // not used yet
