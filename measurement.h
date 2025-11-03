#ifndef ASSIGNMENT_2_MEASUREMENT_H
#define ASSIGNMENT_2_MEASUREMENT_H

#include <vector>
#include "sensor.h"
struct Statistics {

};


struct SensorHub {
    std::vector<TempSensor> temp_sensors = {};
    std::vector<HumiditySensor> humidity_sensors = {};
    std::vector<NoiseSensor> noise_sensors = {};
};

class Measurement {
private:
    std::vector<SensorHub> datastorage_;

public:
    explicit Measurement(std::vector<SensorHub> datastorage) : datastorage_(std::move(datastorage)) {}
    Measurement() = default;
    Measurement& addMeasurement(const TempSensor& temp_sensor, const HumiditySensor& humidity_sensor, const NoiseSensor& noise_sensor);
    void printAll() const;
    void readAll(TempSensor& temp_sensor, HumiditySensor& humidity_sensor, NoiseSensor& noise_sensor);
};

#endif //ASSIGNMENT_2_MEASUREMENT_H