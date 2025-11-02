
#include "measurement.h"

#include <functional>
#include <iostream>

void Measurement::readAll() {

}

void addMeasurement(const TempSensor& temp_sensor, const HumiditySensor& humidity_sensor, const NoiseSensor& noise_sensor) {
    SensorHub hub;
    Measurement data;
    hub.temp_sensors.emplace_back(temp_sensor);
    hub.humidity_sensors.emplace_back(humidity_sensor);
    hub.noise_sensors.emplace_back(noise_sensor);



}

void Measurement::printAll(const std::vector<SensorHub> &data) {

}
