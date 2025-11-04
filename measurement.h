#ifndef ASSIGNMENT_2_MEASUREMENT_H
#define ASSIGNMENT_2_MEASUREMENT_H

#include <vector>
#include "sensor.h"
struct Measurement {
    TempSensor temp_sensor_;
    HumiditySensor humidity_sensor_;
    NoiseSensor noise_sensor_;

    Measurement(const TempSensor& temp_sensor, const HumiditySensor& humidity_sensor, const NoiseSensor& noise_sensor) :
    temp_sensor_(temp_sensor), humidity_sensor_(humidity_sensor), noise_sensor_(noise_sensor){}
};


class MeasurementStorage {
private:
    std::vector<Measurement> measurements_;
public:

    void addMeasurement(const Measurement& measurement);
    void printAll() const;

};

#endif //ASSIGNMENT_2_MEASUREMENT_H