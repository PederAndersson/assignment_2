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
    int id_;
    std::string_view type_ = "Tempsensor";
public:
    TempSensor(int id,SensorData data) :id_(id) {
        sensorbase_ = std::move(data);
        sensorbase_.id_ = id_;
        sensorbase_.unit_ = "C";
    }

    void read() override;
};
class HumiditySensor : public Sensor {
private:
    int id_;
    std::string_view type_ = "Humiditysensor";
public:
    HumiditySensor(int id, SensorData data) :id_(id) {
        sensorbase_ = std::move(data);
        sensorbase_.id_ = id_;
        sensorbase_.unit_ = "%";
    }
    void read() override;
};
class NoiseSensor : public Sensor {
private:
    int id_;
    std::string_view type_ = "Noisesensor";
public:
    NoiseSensor(int id, SensorData data) :id_(id) {
        sensorbase_ = std::move(data);
        sensorbase_.id_ = id_;
        sensorbase_.unit_ = "dB";
    }
    void read() override;
};



struct SensorFactory {
    static inline TempSensor makeTemp(DataGenerator& gen, int id) {
        constexpr float t_min = 15.0f;
        constexpr float t_max = 30.0f;
        SensorData d = gen.generateSensorData(t_min, t_max);
        return TempSensor{id, std::move(d)};
    }
    static inline HumiditySensor makeHumidity(DataGenerator& gen, int id) {
        constexpr float h_min = 25.0f;
        constexpr float h_max = 85.0f;
        SensorData d = gen.generateSensorData(h_min,h_max);
        return HumiditySensor{id, std::move(d)};
    }
    static inline NoiseSensor makeNoise(DataGenerator& gen, int id) {
        constexpr float a_min = 15.0f;
        constexpr float a_max = 100.0f;
        SensorData d = gen.generateSensorData(a_min, a_max);
        return NoiseSensor{id, std::move(d)};
    }
};


#endif //ASSIGNMENT_2_SENSOR_H