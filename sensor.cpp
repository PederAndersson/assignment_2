
#include <iostream>
#include "sensor.h"


void TempSensor::print() const {
    std::cout   << "Sensor type: " << type_
                << " Id: " << sensorbase_.id_
                << " Value: " << sensorbase_.value_<< " " << sensorbase_.unit_
                << " Time: " << sensorbase_.timestamp_ << "\n";
}
void TempSensor::read() {
    DataGenerator gen;
    this->sensorbase_ = gen.generateSensorData(t_min,t_max);
    this->sensorbase_.id_ = id_;
}


void HumiditySensor::print() const {
    std::cout   << "Sensor type: " << type_
                << " Id: " << sensorbase_.id_
                << " Value: " << sensorbase_.value_<< " " << sensorbase_.unit_
                << " Time: " << sensorbase_.timestamp_ << "\n";
}
void HumiditySensor::read() {

}

void NoiseSensor::print() const {
    std::cout   << "Sensor type: " << type_
                << " Id: " << sensorbase_.id_
                << " Value: " << sensorbase_.value_<< " " << sensorbase_.unit_
                << " Time: " << sensorbase_.timestamp_ << "\n";
}
void NoiseSensor::read() {

}

