#ifndef ASSIGNMENT_2_UTILS_H
#define ASSIGNMENT_2_UTILS_H
#include <string>

#include "SensorData.h"


class Utils {
public:
    static int validInput();
    static std::string sensorTypeToString(SensorType type);
};


#endif //ASSIGNMENT_2_UTILS_H