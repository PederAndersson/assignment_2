#ifndef ASSIGNMENT_2_MEASUREMENT_H
#define ASSIGNMENT_2_MEASUREMENT_H

#include <utility>
#include <vector>

#include "sensor.h"
struct Measurement {
    TempSensor temp_sensor_;
    HumiditySensor humidity_sensor_;
    NoiseSensor noise_sensor_;

    Measurement(TempSensor  temp_sensor,HumiditySensor humidity_sensor,NoiseSensor noise_sensor) :
    temp_sensor_(std::move(temp_sensor)), humidity_sensor_(std::move(humidity_sensor)), noise_sensor_(std::move(noise_sensor)){}
};


class MeasurementStorage {
private:
    std::vector<Measurement> measurements_;
public:

    void addMeasurement(const Measurement& measurement);
    void printAllSensors() const;
    static void readAllSensors(TempSensor& T,HumiditySensor& H,NoiseSensor& N);
    [[nodiscard]] std::vector<Measurement> getMeasurementStorage() const {return measurements_;}
    static void writeToFile(const std::string& filename, const MeasurementStorage& data);
    static void readFromFile(const std::string& filename, MeasurementStorage& data);
    static void clearFile(const std::string& filename);

};

#endif //ASSIGNMENT_2_MEASUREMENT_H