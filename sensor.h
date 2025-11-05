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
    DataGenerator gen_;
public:
    virtual ~Sensor() = default;
    virtual void print() const = 0;
    virtual void read() = 0;
};


class TempSensor : public Sensor{
private:
    int id_;
    inline static constexpr std::string_view type_ = "Temperature sensor";
    inline static constexpr std::string_view unit_ = "Celsius";
public:
    TempSensor(int id,SensorData data) :id_(id) {
        sensorbase_ = std::move(data);
        sensorbase_.id_ = id_;
        sensorbase_.unit_ = unit_;
    }

    void print() const override ;
    void read() override;
    [[nodiscard]] SensorData getSensorbase() const {return this->sensorbase_;}
    [[nodiscard]] std::string_view getSensortype() const {return this->type_;}
};
class HumiditySensor : public Sensor {
private:
    int id_;
    inline static constexpr std::string_view  type_ = "Humidity sensor";
    inline static constexpr std::string_view unit_ = "%";
public:
    HumiditySensor(int id, SensorData data) :id_(id) {
        sensorbase_ = std::move(data);
        sensorbase_.id_ = id_;
        sensorbase_.unit_ = unit_;
    }
    void print() const override;
    void read() override;
    [[nodiscard]] SensorData getSensorbase() const {return this->sensorbase_;}
    [[nodiscard]] std::string_view getSensortype() const {return this->type_;}
};
class NoiseSensor : public Sensor {
private:
    int id_;
    inline static constexpr std::string_view type_ = "Noise sensor";
    inline static constexpr std::string_view unit_ = "dB";
public:
    NoiseSensor(int id, SensorData data) :id_(id) {
        sensorbase_ = std::move(data);
        sensorbase_.id_ = id_;
        sensorbase_.unit_ = unit_;
    }
    void print() const override;
    void read() override;
    [[nodiscard]] SensorData getSensorbase() const {return this->sensorbase_;}
    [[nodiscard]] std::string_view getSensortype() const {return this->type_;}
};
constexpr float temp_min = 15.0f;
constexpr float temp_max = 30.0f;
constexpr float humidity_min = 25.0f;
constexpr float humidity_max = 85.0f;
constexpr float noise_min = 15.0f;
constexpr float noise_max = 100.0f;

struct SensorFactory {
    static TempSensor generateTempData(DataGenerator& gen, int id) {

        SensorData d = gen.generateSensorData(temp_min, temp_max);
        return TempSensor{id, std::move(d)};
    }
    static HumiditySensor generateHumidityData(DataGenerator& gen, int id) {

        SensorData d = gen.generateSensorData(humidity_min,humidity_max);
        return HumiditySensor{id, std::move(d)};
    }
    static NoiseSensor generateNoiseData(DataGenerator& gen, int id) {

        SensorData d = gen.generateSensorData(noise_min, noise_max);
        return NoiseSensor{id, std::move(d)};
    }
};


#endif //ASSIGNMENT_2_SENSOR_H