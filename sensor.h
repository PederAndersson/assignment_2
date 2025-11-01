//
// Created by peder on 2025-10-30.
//

#ifndef ASSIGNMENT_2_SENSOR_H
#define ASSIGNMENT_2_SENSOR_H
#include <string>

#include "SensorData.h"
#include "DataGenerator.h"



class Sensor {
protected:
    SensorData sensorbase_;

public:
    virtual ~Sensor() = default;
    virtual void read() = 0;
};


class TempSensor : public Sensor{
private:
    DataGenerator& data_;
    int id_;
    std::string_view type_ = "Tempsensor";
public:
    TempSensor(DataGenerator& data, int id) : data_(data), id_(id){}
    void read() override;
};
class HumiditySensor : public Sensor {
private:
    DataGenerator& data_;
    int id_;
    std::string_view type_ = "Humiditysensor";
public:
    HumiditySensor(DataGenerator& data, int id) : data_(data), id_(id){}
    void read() override;
};
class AirqualitySensor : public Sensor {
private:
    DataGenerator& data_;
    int id_;
    std::string_view type_ = "Airqualitysensor";
public:
    AirqualitySensor(DataGenerator& data, int id) : data_(data), id_(id){}
    void read() override;
};



#endif //ASSIGNMENT_2_SENSOR_H