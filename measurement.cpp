

#include <iostream>
#include "measurement.h"


void MeasurementStorage::addMeasurement(const Measurement &measurement) {
    this->measurements_.emplace_back(measurement);
}

void MeasurementStorage::printAll() const {
    for (const auto& sensor : measurements_) {
        sensor.temp_sensor_.print();
        sensor.humidity_sensor_.print();
        sensor.noise_sensor_.print();
    }
}


