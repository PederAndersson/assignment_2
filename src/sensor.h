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
    virtual float read() = 0;
    virtual void setThreshold() = 0;
    virtual void setInterval() = 0;
    virtual SensorData getSensorbase() const = 0;
};


class TempSensor : public Sensor{
private:
    int id_;

public:
    TempSensor(int id, const TempConfig& cfg) : id_(id)
    {
        sensorbase_.id_ = id;
        sensorbase_.unit_ = std::string(cfg.unit_);
        sensorbase_.interval_ = cfg.interval_;
        sensorbase_.type_ = cfg.type_;

    }
    TempSensor() = default;

    TempSensor(int id, std::vector<SensorData>::const_reference value) : id_(id){sensorbase_ = value;}

    void print() const override ;
    float read() override;
    void setThreshold() override;
    void setInterval() override;
    [[nodiscard]] SensorData getSensorbase() const override {return this->sensorbase_;}
};
class HumiditySensor : public Sensor {
private:
    int id_;
public:
    HumiditySensor(int id, const HumidConfig& cfg) :id_(id) {
        sensorbase_.id_ = id_;
        sensorbase_.unit_ = std::string(cfg.unit_);
        sensorbase_.interval_ = cfg.interval_;
        sensorbase_.type_ = cfg.type_;
    }
    HumiditySensor() = default;

    HumiditySensor(int id, std::vector<SensorData>::const_reference value) : id_(id){sensorbase_ = value;}

    void print() const override;
    float read() override;
    void setThreshold() override;
    void setInterval() override;

    [[nodiscard]] SensorData getSensorbase() const override {return this->sensorbase_;}
};
class NoiseSensor : public Sensor {
private:
    int id_;
public:
    NoiseSensor(int id, const NoiseConfig& cfg) :id_(id) {
        sensorbase_.id_ = id_;
        sensorbase_.unit_ = std::string(cfg.unit_);
        sensorbase_.interval_ = cfg.interval_;
        sensorbase_.type_ = cfg.type_;
    }
    NoiseSensor() = default;

    NoiseSensor(int id, std::vector<SensorData>::const_reference value) : id_(id){sensorbase_ = value;}

    void print() const override;
    float read() override;
    void setThreshold() override;
    void setInterval() override;
    [[nodiscard]] SensorData getSensorbase() const override {return this->sensorbase_;}
};


#endif //ASSIGNMENT_2_SENSOR_H