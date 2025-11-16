//
// Created by peder on 2025-10-30.
//

#ifndef ASSIGNMENT_2_SENSOR_H
#define ASSIGNMENT_2_SENSOR_H
#include <string>
#include <memory>

#include "SensorData.h"
#include "DataGenerator.h"
#include "Observer.h"

class IObserver;

class Sensor { //abstract base class
protected:
    SensorData sensorbase_{};
    DataGenerator gen_;
    std::vector<std::unique_ptr<IObserver>> observers_;
public:
    virtual ~Sensor() = default;
    virtual void print() const = 0;
    virtual float read() = 0;
    virtual void setInterval() = 0;
    [[nodiscard]] virtual SensorData getSensorbase() const = 0;
    virtual void addObserver(std::unique_ptr<IObserver> obs) = 0;
    [[nodiscard]] virtual const std::vector<std::unique_ptr<IObserver>>& getObservers() const = 0;
    virtual void setObserver() = 0;
    virtual void notifyAll(Measurement&m,float value) = 0;

};


class TempSensor : public Sensor{
private:
    int id_{};

public:
    TempSensor(int id, const TempConfig& cfg) : id_(id){
        sensorbase_.id_ = id_;
        sensorbase_.unit_ = std::string(cfg.unit_);
        sensorbase_.interval_ = cfg.interval_;
        sensorbase_.type_ = cfg.type_;

    }
    TempSensor() = default;

    void print() const override ;
    float read() override;
    void setInterval() override;
    [[nodiscard]] SensorData getSensorbase() const override {return this->sensorbase_;}
    void addObserver(std::unique_ptr<IObserver> obs) override;
    [[nodiscard]] const std::vector<std::unique_ptr<IObserver>>& getObservers() const override;
    void setObserver() override;
    void notifyAll(Measurement&m,float value) override;

};
class HumiditySensor : public Sensor {
private:
    int id_{};
public:
    HumiditySensor(int id, const HumidConfig& cfg) :id_(id) {
        sensorbase_.id_ = id_;
        sensorbase_.unit_ = std::string(cfg.unit_);
        sensorbase_.interval_ = cfg.interval_;
        sensorbase_.type_ = cfg.type_;
    }
    HumiditySensor() = default;

     void print() const override;
    float read() override;
    void setInterval() override;
    [[nodiscard]] SensorData getSensorbase() const override {return this->sensorbase_;}
    void addObserver(std::unique_ptr<IObserver> obs) override;
    [[nodiscard]] const std::vector<std::unique_ptr<IObserver>>& getObservers() const override;
    void setObserver() override;
    void notifyAll(Measurement&m,float value) override;
};
class NoiseSensor : public Sensor {
private:
    int id_{};
public:
    NoiseSensor(int id, const NoiseConfig& cfg) :id_(id) {
        sensorbase_.id_ = id_;
        sensorbase_.unit_ = std::string(cfg.unit_);
        sensorbase_.interval_ = cfg.interval_;
        sensorbase_.type_ = cfg.type_;
    }
    NoiseSensor() = default;

    void print() const override;
    float read() override;
    void setInterval() override;
    [[nodiscard]] SensorData getSensorbase() const override {return this->sensorbase_;}
    void addObserver(std::unique_ptr<IObserver> obs) override;
    [[nodiscard]] const std::vector<std::unique_ptr<IObserver>>& getObservers() const override;
    void setObserver() override;
    void notifyAll(Measurement&m,float value) override;
};


#endif //ASSIGNMENT_2_SENSOR_H