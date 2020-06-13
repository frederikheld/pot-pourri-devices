# Pot Monitoring WiFi device

This is the standard device for your _Pot Pourri_ setup. It's a _NodeMCU_ with sensors that can communicate via WiFi. It publishes sensor readings in defined intervals to a _MQTT_ topic.

## Hardware

![Breadboard schema of the Pot Monitoring WiFi device](./pot-monitoring-wifi_bb.png)

The humidity sensor is connected via an analog/digital converter module that outputs values [0..1024], while 0 is "absolutely wet" and 1024 is "absolutely dry".

Right now this is the only sensor in the setup, but it is possible to add sensors for other kinds of environment data in the same way.

## Prerequisites

In order to be able to compile this sketch, you need to install _PubSubClient by Nick O'Leary_ (tested with 1.7.2) via the Library Manager. Reference: https://github.com/knolleary/pubsubclient
