//
// Created by peder on 2025-10-30.
//

#ifndef ASSIGNMENT_2_SENSOR_H
#define ASSIGNMENT_2_SENSOR_H
#include <string>

#include "SensorData.h"
#include "DataGenerator.h"



class Sensor { //abstract base class
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
    inline static constexpr std::string_view temp_type_ = "Temperature sensor";
    inline static constexpr std::string_view temp_unit_ = "Celsius";
public:
    TempSensor(int id,SensorData data) :id_(id) {
        sensorbase_ = std::move(data);
        sensorbase_.id_ = id_;
        sensorbase_.unit_ = temp_unit_;
    }

    void print() const override ;
    void read() override;
    [[nodiscard]] SensorData getSensorbase() const {return this->sensorbase_;}
    static constexpr std::string_view getStaticType() { return temp_type_; }
    static constexpr std::string_view getStaticUnit() { return temp_unit_; }
};
class HumiditySensor : public Sensor {
private:
    int id_;
    inline static constexpr std::string_view humid_type_ = "Humidity sensor";
    inline static constexpr std::string_view humid_unit_ = "%";
public:
    HumiditySensor(int id, SensorData data) :id_(id) {
        sensorbase_ = std::move(data);
        sensorbase_.id_ = id_;
        sensorbase_.unit_ = humid_unit_;
    }
    void print() const override;
    void read() override;
    [[nodiscard]] SensorData getSensorbase() const {return this->sensorbase_;}
    static constexpr std::string_view getStaticType() { return humid_type_; }
    static constexpr std::string_view getStaticUnit() { return humid_unit_; }
};
class NoiseSensor : public Sensor {
private:
    int id_;
    inline static constexpr std::string_view noise_type_ = "Noise sensor";
    inline static constexpr std::string_view noise_unit_ = "dB";
public:
    NoiseSensor(int id, SensorData data) :id_(id) {
        sensorbase_ = std::move(data);
        sensorbase_.id_ = id_;
        sensorbase_.unit_ = noise_unit_;
    }
    void print() const override;
    void read() override;
    [[nodiscard]] SensorData getSensorbase() const {return this->sensorbase_;}
    static constexpr std::string_view getStaticType() { return noise_type_; }
    static constexpr std::string_view getStaticUnit() { return noise_unit_; }
};
// set variables for the different sensors for the intervall in which they generate measurements
constexpr float temp_min = 15.0f;
constexpr float temp_max = 30.0f;
constexpr float humidity_min = 25.0f;
constexpr float humidity_max = 85.0f;
constexpr float noise_min = 15.0f;
constexpr float noise_max = 100.0f;

//"factory" that lets you generate data upon initialization
struct SensorFactory {
    static TempSensor generateTempData(DataGenerator& gen, int id) {
        SensorData temp;
        temp.value_ = gen.generateSensorData(temp_min, temp_max);
        temp.timestamp_ = DataGenerator::generateTimeStamp();
        return TempSensor{id, std::move(temp)};
    }
    static HumiditySensor generateHumidityData(DataGenerator& gen, int id) {
        SensorData humidity;
        humidity.value_ = gen.generateSensorData(humidity_min,humidity_max);
        humidity.timestamp_ = DataGenerator::generateTimeStamp();
        return HumiditySensor{id, std::move(humidity)};
    }
    static NoiseSensor generateNoiseData(DataGenerator& gen, int id) {
        SensorData noise;
        noise.value_ = gen.generateSensorData(noise_min, noise_max);
        noise.timestamp_ = DataGenerator::generateTimeStamp();
        return NoiseSensor{id, std::move(noise)};
    }
};


#endif //ASSIGNMENT_2_SENSOR_H