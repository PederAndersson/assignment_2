#ifndef ASSIGNMENT_2_MEASUREMENT_H
#define ASSIGNMENT_2_MEASUREMENT_H

#include <vector>
#include "sensor.h"

struct SensorHub {
    std::vector<TempSensor> temp_sensors;
    std::vector<HumiditySensor> humidity_sensors;
    std::vector<NoiseSensor> airquality_sensors;
};

class Measurement {
private:
    std::vector<SensorHub> datastorage_;
    TempSensor& tempsensor_;
    HumiditySensor& humiditysensor_;
    NoiseSensor& airqualitysensor_;
public:
    Measurement(TempSensor &temp, HumiditySensor &hum, NoiseSensor &air) :
        tempsensor_(temp),humiditysensor_(hum), airqualitysensor_(air){}
    void addMeasurement(const SensorHub& hub, std::vector<SensorHub>& data);
    void printAll(const std::vector<SensorHub>& data);
    void readAll();
};

#endif //ASSIGNMENT_2_MEASUREMENT_H