#ifndef ASSIGNMENT_2_MEASUREMENT_H
#define ASSIGNMENT_2_MEASUREMENT_H

#include <vector>
#include "sensor.h"

struct SensorHub {
    std::vector<TempSensor> temp;
    std::vector<HumiditySensor> humsens;
    std::vector<AirqualitySensor> Airsens;
};

class measurement {
private:
    std::vector<SensorHub> hub;
};


#endif //ASSIGNMENT_2_MEASUREMENT_H