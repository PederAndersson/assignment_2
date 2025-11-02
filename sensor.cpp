
#include <iostream>
#include "sensor.h"


void TempSensor::read() {
    std::cout   << "Sensor type: " << type_
                << " Id: " << sensorbase_.id_
                << " Value: " << sensorbase_.value_<< " " << sensorbase_.unit_
                << " Time: " << sensorbase_.timestamp_ << "\n";
}

void HumiditySensor::read() {
    std::cout   << "Sensor type: " << type_
                << " Id: " << sensorbase_.id_
                << " Value: " << sensorbase_.value_<< " " << sensorbase_.unit_
                << " Time: " << sensorbase_.timestamp_ << "\n";
}
void NoiseSensor::read() {
    std::cout   << "Sensor type: " << type_
                << " Id: " << sensorbase_.id_
                << " Value: " << sensorbase_.value_<< " " << sensorbase_.unit_
                << " Time: " << sensorbase_.timestamp_ << "\n";
}

