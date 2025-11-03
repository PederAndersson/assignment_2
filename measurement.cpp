
#include <functional>
#include <iostream>
#include "measurement.h"


Measurement& Measurement::addMeasurement(const TempSensor& temp_sensor, const HumiditySensor& humidity_sensor, const NoiseSensor& noise_sensor) {

    SensorHub hub;

    hub.temp_sensors.emplace_back(temp_sensor);
    hub.humidity_sensors.emplace_back(humidity_sensor);
    hub.noise_sensors.emplace_back(noise_sensor);
    datastorage_.emplace_back(hub);
    return *this;

}

void Measurement::printAll() const {
    for (const auto& sensorhub : datastorage_) {
        for (const auto& sensor : sensorhub.temp_sensors) {
        sensor.print();
        }
        for (const auto& sensor : sensorhub.humidity_sensors) {
            sensor.print();
        }
        for (const auto& sensor : sensorhub.noise_sensors) {
            sensor.print();
        }
    }
}

void Measurement::readAll(TempSensor& temp_sensor, HumiditySensor& humidity_sensor, NoiseSensor& noise_sensor) {
    temp_sensor.read();
    humidity_sensor.read();
    noise_sensor.read();
}

