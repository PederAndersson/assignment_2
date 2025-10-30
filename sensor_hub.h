//
// Created by peder on 2025-10-30.
//

#ifndef ASSIGNMENT_2_SENSOR_H
#define ASSIGNMENT_2_SENSOR_H
#include <string>
struct heatSensor {
    std::string type = "Heatsensor";
    std::string timestamp;
    float value;
    int id;
};
struct humiditySensor {
    std::string type = "Humiditysensor";
    std::string timestamp;
    float value;
    int id;
};
struct windSensor {
    std::string type = "Windsensor";
    std::string timestamp;
    float value;
    int id;
};


class sensor_hub {
private:
    heatSensor _heatsensor;
    humiditySensor _humiditysensor;
    windSensor _windsensor;
public:
    sensor_hub() = default;
    void sensorRead();
    std::string generateTimestamp();
    float generateWindValue();
    float generateHeatValue();
    float generateHumidityValue();
};


#endif //ASSIGNMENT_2_SENSOR_H