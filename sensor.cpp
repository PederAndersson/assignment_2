
#include <iostream>
#include "sensor.h"


void TempSensor::read() {
    sensorbase_ = data_.generateSensorData(15.0,27.0);
    sensorbase_.id_ = id_;

    std::cout << "Sensor type: " << type_ << " Id: " << sensorbase_.id_ << " Value: " << sensorbase_.value_ << " Celsius " << " Time: "  << sensorbase_.timestamp_ << "\n";
}
void HumiditySensor::read() {
    sensorbase_ = data_.generateSensorData(20,80);
    sensorbase_.id_ = id_;
    std::cout << "Sensor type: " << type_ << " Id: " << sensorbase_.id_ << " Value: " << sensorbase_.value_ << " % " << " Time: "  << sensorbase_.timestamp_ << "\n";
}
void AirqualitySensor::read() {
    sensorbase_ = data_.generateSensorData(5,30);
    sensorbase_.id_ = id_;
    std::cout << "Sensor type: " << type_ << " Id: " << sensorbase_.id_ << " Value: " << sensorbase_.value_ << " µg/m3 PM2.5 " << " Time: "  << sensorbase_.timestamp_ << "\n";
}

