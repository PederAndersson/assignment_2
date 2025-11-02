
#ifndef ASSIGNMENT_2_SENSORDATA_H
#define ASSIGNMENT_2_SENSORDATA_H
#include <string>

struct SensorData {
    float value_ = 0;
    std::string timestamp_;
    std::string unit_;
    int id_ = 0;

};

#endif //ASSIGNMENT_2_SENSORDATA_H