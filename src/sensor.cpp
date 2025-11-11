
#include <iostream>
#include "sensor.h"
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

