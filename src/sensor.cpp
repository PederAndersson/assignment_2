
#include <iostream>
#include "sensor.h"

#include <algorithm>

#include "Utils.h"


void TempSensor::print() const {
    std::cout   << "Sensor type: " << Utils::sensorTypeToString(sensorbase_.type_)  << "\n"
                << "Id: " << sensorbase_.id_ << "\n"
                << "Value: " << sensorbase_.value_<< " " << sensorbase_.unit_ << "\n"
                << "Time: " << sensorbase_.timestamp_ << "\n";
}
void TempSensor::read() {

    this->sensorbase_.value_ = gen_.generateSensorData(this->sensorbase_.interval_.min_,this->sensorbase_.interval_.max_);
    this->sensorbase_.timestamp_ = DataGenerator::generateTimeStamp();
    this->sensorbase_.id_ = id_;
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

void TempSensor::setThreshold() {
    float lower = Utils::validFloatInput();
    float upper = Utils::validFloatInput();
    do {
        this->sensorbase_.threshold_.lower_ = lower;
        this->sensorbase_.threshold_.upper_ = upper;

    } while (lower < this->sensorbase_.interval_.min_ && upper > this->sensorbase_.interval_.max_);
}



void HumiditySensor::print() const {
    std::cout   << "Sensor type: " << Utils::sensorTypeToString(sensorbase_.type_)  << "\n"
                 << "Id: " << sensorbase_.id_ << "\n"
                 << "Value: " << sensorbase_.value_<< " " << sensorbase_.unit_ << "\n"
                 << "Time: " << sensorbase_.timestamp_ << "\n";
}

void HumiditySensor::read() {
    this->sensorbase_.value_ = gen_.generateSensorData(this->sensorbase_.interval_.min_,this->sensorbase_.interval_.max_);
    this->sensorbase_.timestamp_ = DataGenerator::generateTimeStamp();
    this->sensorbase_.id_ = id_;
}

void HumiditySensor::setThreshold() {
    float lower = Utils::validFloatInput();
    float upper = Utils::validFloatInput();
    do {
        this->sensorbase_.threshold_.lower_ = lower;
        this->sensorbase_.threshold_.upper_ = upper;

    } while (lower < this->sensorbase_.interval_.min_ && upper > this->sensorbase_.interval_.max_);
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

void NoiseSensor::print() const {
    std::cout   << "Sensor type: " << Utils::sensorTypeToString(sensorbase_.type_)  << "\n"
                 << "Id: " << sensorbase_.id_ << "\n"
                 << "Value: " << sensorbase_.value_<< " " << sensorbase_.unit_ << "\n"
                 << "Time: " << sensorbase_.timestamp_ << "\n";
}

void NoiseSensor::read() {
    this->sensorbase_.value_ = gen_.generateSensorData(this->sensorbase_.interval_.min_,this->sensorbase_.interval_.max_);
    this->sensorbase_.timestamp_ = DataGenerator::generateTimeStamp();
    this->sensorbase_.id_ = id_;
}

void NoiseSensor::setThreshold() {
    float lower = Utils::validFloatInput();
    float upper = Utils::validFloatInput();
    do {
        this->sensorbase_.threshold_.lower_ = lower;
        this->sensorbase_.threshold_.upper_ = upper;

    } while (lower < this->sensorbase_.interval_.min_ && upper > this->sensorbase_.interval_.max_);
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
