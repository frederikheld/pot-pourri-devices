// device:
const int device_id = 0; // has to be unique per datastore!

// wifi:
const char* wifi_ssid = "<wifi-ssid>";
const char* wifi_secret = "<wifi-secret>";
const int wifi_connect_retry_delay = 500; // Time to wait (in milliseconds) before retrying if connect to wifi failed. Defaults to 500.

// mqtt:
const char* mqtt_server = "<mqtt-broker-ip-or-hostname>";
const int mqtt_port = 1883; // defaults to 1883;
const char* mqtt_topic = "<mqtt-topic>";
const int mqtt_connect_retry_delay = 5000; // Time to wait (in milliseconds) before retrying if connect to mqtt broker failed. Defaults to 5000.
