
#ifndef ASSIGNMENT_2_UTILITY_H
#define ASSIGNMENT_2_UTILITY_H
#include <random>
#include "SensorData.h"


class DataGenerator {
private:
    std::mt19937 gen_;
public:
    DataGenerator() : gen_(std::random_device{}()) {}

    SensorData generateSensorData(float x,float y);
};


#endif //ASSIGNMENT_2_UTILITY_H