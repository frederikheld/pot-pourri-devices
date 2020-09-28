# Environment Monitoring WiFi device

This is the standard device for your _Pot Pourri_ setup. It's a _NodeMCU_ with sensors that can communicate via WiFi. It publishes sensor readings in defined intervals to a _MQTT_ topic.

## Hardware

![Breadboard schema of the Environment Monitoring WiFi device](./environment-monitoring-wifi_bb.png)

The DHT22 air temperature and humidity sensor is connected via OneWire bus. We are using Adafruit's [DHT sensor library](https://github.com/adafruit/DHT-sensor-library) to read temperature in °C and air humidity in % from the bus.

## Prerequisites

In order to be able to compile this sketch, you need to install the following packages via _Arduino IDE_'s _Package Manager_:

* _ESP8266Wifi_ library as described here: https://stackoverflow.com/a/50951309/10043870
* _PubSubClient by Nick O'Leary_ (tested with 1.7.2) via the Library Manager. Reference: https://github.com/knolleary/pubsubclient
* _ArduinoJson_ library via the Library Manager. Reference: https://arduinojson.org/ (note that the sketch will only work if you use version 5!)
* _DHT sensor library  by Adafruit_ (tested with 1.4.0) via the Library Manager. Reference: https://github.com/adafruit/DHT-sensor-library

## Config

You need to configure this Sketch before you upload it to the _NodeMCU_. As the configuration contains sensitive data, it is not part of the sketch, but in a separate `config.h`.

This module comes with a `config.template.h`. Duplicate that file and rename it to `config.h`. Then change the values according to your setting.

You need to provide at least:

`DEVICE_ID`, which needs to be **unique** in your _Pot Pourri_ setup.

`WIFI_SSID` and `WIFI_SECRET` as well as `MQTT_SERVER`.

All other values can stay untouched if you have deployed _Pot Pourri_ with the default settings.

`SAMPLING_INTERVAL` doesn't need to be changed, but the default value of 60 ("send a value once every 60 seconds") is quite low. I encourage you to change it according to your needs. Aspects to keep in mind when choosing the value are _accuracy of data over time_, _rate of change in real environment_, _currentness of data_, _amount of data to be stored_, _energy consumption of the device_, _interference caused by number of devices in WiFi at the same time_, ... Please note as well that the DHT22 sensor can only provide a new value once in 2 seconds!

## Upload the Sketch

Before you upload the sketch, you need to remove the jumper cable that connects the pins "RST" and "D0". It is colored blue in the breadboard diagram above.

If you haven't used NodeMCU boards before, you need to install it via Tools > Board Manager first. The package name is [esp8266 by ESP8266 Community](https://github.com/esp8266/Arduino).

Then select NodeMCU 1.0 (ESP-12E Module) in the Tools menu and upload the sketch to your board.

Don't forget to put the cable between pins "RST" and "D0" back in place. Without it, the NodeMCU can't wake up from Deep Sleep!

## Usage

As you power up the device, it will automatically connect to your wifi, collect the current value and send it over _MQTT_. Then it will go to Deep Sleep mode for the defined `SAMPLING_INTERVAL`.

## Troubleshooting

You can connect the device to your computer via USB and can use the _Serial Monitor_ in the _Arduino IDE_ in order to see the debug output.

Other options for troubleshooting are:

### Wifi Connectivity

To see if the device is connected to your WiFi, you can look into your Router and see if it is in the list. If you have many devices, this will be difficult as they have very similar names. So the best way is to check the list _before_ you power it up for the first time and again a couple of seconds _after_ to see if a new device was added.

### MQTT Connectivity

I have a project called _robotrain_ that uses a similar tech stack. It comes with the tool [_mqtt-sniffer_](https://github.com/frederikheld/robotrain/tree/master/tools/mqtt-sniffer/README.md) that can log messages from MQTT topics to the terminal.

The _Pot Pourri_ device sends values via `potpourri/devices/<device-id>/sensors/#`.