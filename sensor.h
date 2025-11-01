//
// Created by peder on 2025-10-30.
//

#ifndef ASSIGNMENT_2_SENSOR_H
#define ASSIGNMENT_2_SENSOR_H
#include <string>

struct SensorFunc {
    float _value = 0;
    std::string _timestamp;
    int _id = 0;
};

class Sensor {
protected:
    SensorFunc _sensorbase;

public:
    virtual ~Sensor() = default;
    virtual void read() = 0;
};

class TempSensor : public Sensor {
private:
    const std::string _type = "Tempsensor";
public:
    void read();
};
class HumiditySensor : public Sensor {
private:
    const std::string _type = "Humiditysensor";
public:
    void read();
};
class AirqualitySensor : public Sensor {
private:
    const std::string _type = "Airqualitysensor";
public:
    void read();
};



#endif //ASSIGNMENT_2_SENSOR_H