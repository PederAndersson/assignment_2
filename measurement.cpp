
#include <functional>
#include <iostream>
#include "measurement.h"


void Measurement::addMeasurement(const TempSensor& temp_sensor, const HumiditySensor& humidity_sensor, const NoiseSensor& noise_sensor) {

    temp_data_.emplace_back(temp_sensor);
    humidity_data_.emplace_back(humidity_sensor);
    noise_data_.emplace_back(noise_sensor);

}

void Measurement::printAll() const {

    for (const auto& sensor : temp_data_) {
        sensor.print();
        std::cout << "-----------------------------------------------------------\n";
    }
    for (const auto& sensor : humidity_data_) {
        sensor.print();
        std::cout << "-----------------------------------------------------------\n";
    }
    for (const auto& sensor : noise_data_) {
        sensor.print();
        std::cout << "-----------------------------------------------------------\n";
    }
}

void Measurement::readAll(TempSensor& temp_sensor, HumiditySensor& humidity_sensor, NoiseSensor& noise_sensor) {
    temp_sensor.read();
    humidity_sensor.read();
    noise_sensor.read();
}


