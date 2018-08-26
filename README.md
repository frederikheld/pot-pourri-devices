# pot-pourri

// todo: What does it do?

## Run it

To run the app, navigate in the terminal to the root directory of the app (where this README.md is located) and run `docker-compose up`. To stop the application, you can run `docker-compose down` in a separate terminal at the same location.

`docker-compose up` will first build and then run all containers. If the containers already exist, it will not re-build them but use the existing ones. If you explicitly want to re-build all containers, use `docker-compose build` before you call `docker-compose up`.

## Architecture

The pot-pourri application consists of several microservices that communicate via rest apis. See the api description of each service for more details.

### datastore

The `datasore` service accepts data items and stores them in an internal database.

It also answers to requests for specified chunks of data.

### ui

The `ui` provides a graphical user interface that allows interaction with the app.

### pot-monitoring-serial

The `pot-monitoring-serial` microservice provides connectivity to the datastore for devices, that do not have their own network interface, e. g. the classic Arduino Uno. You can connect such devices via serial interface to a device with network access and run this service there.

> This service will _not_ be automatically run when the app is started with `docker-compose up`!

## Useful links

### NodeMCU

- NodeMCU power supply: http://henrysbench.capnfatz.com/henrys-bench/arduino-projects-tips-and-more/powering-the-esp-12e-nodemcu-development-board/
- ESP32 deep sleep: http://educ8s.tv/esp32-deep-sleep-tutorial/

### Sensors

- Humidity sensors compared: https://www.youtube.com/watch?v=udmJyncDvw0
