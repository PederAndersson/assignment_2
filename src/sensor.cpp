
#include <iostream>
#include <algorithm>

#include "sensor.h"
#include "measurement.h"
#include "Utils.h"
#include "Observer.h"





void TempSensor::print() const {
    std::cout   << "Sensor type: " << Utils::sensorTypeToString(sensorbase_.type_)  << "\n"
                << "Id: " << sensorbase_.id_ << "\n"
                << "Value: " << sensorbase_.value_<< " " << sensorbase_.unit_ << "\n"
                << "Time: " << sensorbase_.timestamp_ << "\n";
}

float TempSensor::read() {
return gen_.generateSensorData(this->sensorbase_.interval_.min_, this->sensorbase_.interval_.max_);
}
void TempSensor::setInterval() {
    float min;
    float max;
    do {
    min = Utils::validFloatInput();
    this->sensorbase_.interval_.min_ = min;
    max = Utils::validFloatInput();
    this->sensorbase_.interval_.max_ = max;
    }while (min > max);
}

void TempSensor::addObserver(std::unique_ptr<IObserver> obs) {
    this->observers_.emplace_back(std::move(obs));
}

const std::vector<std::unique_ptr<IObserver> > &TempSensor::getObservers() const {
    return this->observers_;
}



void TempSensor::setObserver() {
    for (auto& o : observers_) {
        o->setThreshold();
    }
}

void TempSensor::notifyAll(Measurement&m, float value) {
    for (auto& o : observers_) {
        o->checkValue(m,value);
    }
}


void HumiditySensor::print() const {
    std::cout   << "Sensor type: " << Utils::sensorTypeToString(sensorbase_.type_)  << "\n"
                 << "Id: " << sensorbase_.id_ << "\n"
                 << "Value: " << sensorbase_.value_<< " " << sensorbase_.unit_ << "\n"
                 << "Time: " << sensorbase_.timestamp_ << "\n";
}

float HumiditySensor::read() {
    return gen_.generateSensorData(this->sensorbase_.interval_.min_, this->sensorbase_.interval_.max_);
}


void HumiditySensor::setInterval() {
    float min;
    float max;
    do {
        min = Utils::validFloatInput();
        this->sensorbase_.interval_.min_ = min;
        max = Utils::validFloatInput();
        this->sensorbase_.interval_.max_ = max;
    }while (min > max);
}

void HumiditySensor::addObserver(std::unique_ptr<IObserver> obs) {
    this->observers_.emplace_back(std::move(obs));
}

const std::vector<std::unique_ptr<IObserver>>& HumiditySensor::getObservers() const {
    return this->observers_;
}

void HumiditySensor::setObserver() {
    for (auto& o : observers_) {
        o->setThreshold();
    }
}
void HumiditySensor::notifyAll(Measurement&m, float value) {
    for (auto& o : observers_) {
        o->checkValue(m,value);
    }
}



void NoiseSensor::print() const {
    std::cout   << "Sensor type: " << Utils::sensorTypeToString(sensorbase_.type_)  << "\n"
                 << "Id: " << sensorbase_.id_ << "\n"
                 << "Value: " << sensorbase_.value_<< " " << sensorbase_.unit_ << "\n"
                 << "Time: " << sensorbase_.timestamp_ << "\n";
}

float NoiseSensor::read() {
    return gen_.generateSensorData(this->sensorbase_.interval_.min_, this->sensorbase_.interval_.max_);
}


void NoiseSensor::setInterval() {
    float min;
    float max;
    do {
        min = Utils::validFloatInput();
        this->sensorbase_.interval_.min_ = min;
        max = Utils::validFloatInput();
        this->sensorbase_.interval_.max_ = max;
    }while (min > max);
}

void NoiseSensor::addObserver(std::unique_ptr<IObserver> obs) {
    this->observers_.emplace_back(std::move(obs));
}

const std::vector<std::unique_ptr<IObserver>>& NoiseSensor::getObservers() const {
    return this->observers_;
}

void NoiseSensor::setObserver() {
    for (auto& o : observers_) {
        o->setThreshold();
    }
}

void NoiseSensor::notifyAll(Measurement&m, float value) {
    for (auto& o : observers_) {
        o->checkValue(m,value);
    }
}
