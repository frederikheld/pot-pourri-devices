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

### pot-monitoring-wifi

_pot-monitoring-wifi_ is the main device in the _Pot Pourri_ ecosystem. It's a _NodeMCU_, that communicates with the _MQTT broker_ via WiFi. It will send sensor values in defined intervals and go into Deep Sleep mode in between.

See [_pot-monitoring-wifi_](./pot-monitoring-wifi/README.md) for more details.

### pot-watering-wifi

_pot-watering-wifi_ is a first prototype that puts actors on the NodeMCU device. It is planned to have valves as actors to be able to water the plants automatically. This is still in a very early stage!

See [_pot-watering-wifi_](./pot-watering-wifi/README.md) for more details.

### pot-monitoring-serial

_pot-monitoring-serial_ is made for _Arduino Uno_ devices without network connectivity. Instead you connect the Arduino via USB serial to a computer that is connected to the WiFi. The package comes with a service that translates serial messages to MQTT messages and sends them to the broker.

> Note: this is being refactored at the moment. The docs describe how it is going to be. Right now, the service sends the data to _datastore_.

To start the service run `npm start` in _./pot-monitoring-serial_.

> DEPRECATION WARNING! Communication via the _Pot Pourri's_ own API is going to be deprecated and will be replaced by communication via MQTT! This is not implemented for _pot-monitoring-serial_ yet.

See [_pot-monitoring-serial_](./pot-monitoring-serial/README.md) for more details.

## Useful links

### NodeMCU

- NodeMCU power supply: http://henrysbench.capnfatz.com/henrys-bench/arduino-projects-tips-and-more/powering-the-esp-12e-nodemcu-development-board/
- ESP32 deep sleep: http://educ8s.tv/esp32-deep-sleep-tutorial/

### Sensors

- Humidity sensors compared: https://www.youtube.com/watch?v=udmJyncDvw0
