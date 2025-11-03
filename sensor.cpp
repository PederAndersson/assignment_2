
#include <iostream>
#include "sensor.h"


void TempSensor::print() const {
    std::cout   << "Sensor type: " << type_
                << " Id: " << sensorbase_.id_
                << " Value: " << sensorbase_.value_<< " " << sensorbase_.unit_
                << " Time: " << sensorbase_.timestamp_ << "\n";
}
void TempSensor::read() {

    this->sensorbase_ = gen_.generateSensorData(temp_min,temp_max);
    this->sensorbase_.id_ = id_;
}


void HumiditySensor::print() const {
    std::cout   << "Sensor type: " << type_
                << " Id: " << sensorbase_.id_
                << " Value: " << sensorbase_.value_<< " " << sensorbase_.unit_
                << " Time: " << sensorbase_.timestamp_ << "\n";
}
void HumiditySensor::read() {
    this->sensorbase_ = gen_.generateSensorData(humidity_min,humidity_max);
    this->sensorbase_.id_ = id_;
}

void NoiseSensor::print() const {
    std::cout   << "Sensor type: " << type_
                << " Id: " << sensorbase_.id_
                << " Value: " << sensorbase_.value_<< " " << sensorbase_.unit_
                << " Time: " << sensorbase_.timestamp_ << "\n";
}
void NoiseSensor::read() {
    this->sensorbase_ = gen_.generateSensorData(noise_min,noise_max);
    this->sensorbase_.id_ = id_;
}

