#ifndef ASSIGNMENT_2_MEASUREMENT_H
#define ASSIGNMENT_2_MEASUREMENT_H

#include <vector>
#include "sensor.h"



class Measurement {
private:
    std::vector<TempSensor> temp_data_ = {};
    std::vector<HumiditySensor> humidity_data_ = {};
    std::vector<NoiseSensor> noise_data_ = {};
public:
    Measurement(std::vector<TempSensor> temp_data, std::vector<HumiditySensor> humidity_data, std::vector<NoiseSensor> noise_data) :
    temp_data_(std::move(temp_data)), humidity_data_(std::move(humidity_data)), noise_data_(std::move(noise_data)) {}
    Measurement() = default;
    void addMeasurement(const TempSensor& temp_sensor, const HumiditySensor& humidity_sensor, const NoiseSensor& noise_sensor);
    void printAll() const;
    void readAll(TempSensor& temp_sensor, HumiditySensor& humidity_sensor, NoiseSensor& noise_sensor);
    int measurementCount();

};

#endif //ASSIGNMENT_2_MEASUREMENT_H