# pot-pourri-devices

This repository contains devices that can used together with pot-purri. You can find pot-pourri at https://github.com/frederikheld/pot-pourri.

## How does it work?

In configured intervals the sensors will create a sample and send it to the configured API endpoint of _Datastore service_ of _pot-pourri_.

### pot-monitoring-wifi

WiFi-enabled NodeMCU devices are able to communicate directly with the configured API endpoint. They will do it in configured intervals and go to deep-sleep mode in-between to save battery life.

### pot-monitoring-serial

`pot-monitoring-serial` is made for Arduino Uno devices without network connectivity. Therefore it comes with a service that provides connectivity to the _Datastore_ of _pot-pourri_. You have to run the service on a machine with network access and a serial connection to the device.

To start the service run `npm start` in _./pot-monitoring-serial_.

## Useful links

### NodeMCU

- NodeMCU power supply: http://henrysbench.capnfatz.com/henrys-bench/arduino-projects-tips-and-more/powering-the-esp-12e-nodemcu-development-board/
- ESP32 deep sleep: http://educ8s.tv/esp32-deep-sleep-tutorial/

### Sensors

- Humidity sensors compared: https://www.youtube.com/watch?v=udmJyncDvw0
