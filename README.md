# pot-pourri-devices

This repository contains devices that can used together with pot-purri. You can find pot-pourri at https://github.com/frederikheld/pot-pourri.

## How does it work?

In configured intervals the sensors will create a sample and send it to the configured API endpoint of _Datastore service_ of _pot-pourri_.

### pot-monitoring-wifi

WiFi-enabled NodeMCU devices are able to communicate directly with the configured API endpoint. They will do it in configured intervals and go to deep-sleep mode in-between to save battery life.

To be able to compile the sketch, first you have to add the _ESP8266Wifi_ library as described here: https://stackoverflow.com/a/50951309/10043870

You also need to install the _ArduinoJson_ library via the Library Manager. Reference: https://arduinojson.org/ (note that the sketch will only work if you use version 5!)

> Attention: Don't forget to select the correct board and remove the jumper cable that connects RST with D0 before you flash the board!

> DEPRECATION WARNING! Communication via the _Pot Pourri's_ own API is going to be deprecated and will be replaced by communication via MQTT!

### pot-monitoring-wifi-mqtt

For commuication via MQTT instead of _Pot Pourri's_ own API, won't need to install _ArduinoJson_.

Instead you need to install _PubSubClient by Nick O'Leary_ (tested with 1.7.2) via the Library Manager. Reference: https://github.com/knolleary/pubsubclient


### pot-monitoring-serial

`pot-monitoring-serial` is made for Arduino Uno devices without network connectivity. Therefore it comes with a service that provides connectivity to the _Datastore_ of _pot-pourri_. You have to run the service on a machine with network access and a serial connection to the device.

To start the service run `npm start` in _./pot-monitoring-serial_.

> DEPRECATION WARNING! Communication via the _Pot Pourri's_ own API is going to be deprecated and will be replaced by communication via MQTT! This is not implemented for _pot-monitoring-serial_ yet.

## Useful links

### NodeMCU

- NodeMCU power supply: http://henrysbench.capnfatz.com/henrys-bench/arduino-projects-tips-and-more/powering-the-esp-12e-nodemcu-development-board/
- ESP32 deep sleep: http://educ8s.tv/esp32-deep-sleep-tutorial/

### Sensors

- Humidity sensors compared: https://www.youtube.com/watch?v=udmJyncDvw0
