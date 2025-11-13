#ifndef ASSIGNMENT_2_UTILS_H
#define ASSIGNMENT_2_UTILS_H

#include <memory>
#include <string>
#include <vector>

#include "SensorData.h"


class Sensor;

class Utils {
public:
    static int validInput(int min, int max);
    static float validFloatInput();
    static std::string sensorTypeToString(SensorType type);
    static SensorType stringToType(std::string& line);

};


#endif //ASSIGNMENT_2_UTILS_H