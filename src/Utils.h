#ifndef ASSIGNMENT_2_UTILS_H
#define ASSIGNMENT_2_UTILS_H

#include <memory>
#include <string>


#include "SensorData.h"


class Sensor;

class Utils {
public:
    static int validInput(int min, int max);
    static float validFloatInput();
    static std::string sensorTypeToString(SensorType type);
    static SensorType stringToType(const std::string& line);
    static void clearTerminal();
    static void awaitResponse();
};


#endif //ASSIGNMENT_2_UTILS_H