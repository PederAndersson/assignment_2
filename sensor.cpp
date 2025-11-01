
#include <iomanip>
#include <iostream>
#include "sensor.h"


/*
std::string sensortest::generateTimestamp() {
    time_t timestamp = time(nullptr);
    tm datetime = *localtime(&timestamp);

    std::ostringstream oss;

    oss << std::setfill('0') << std::setw(2) << datetime.tm_hour << ":" //content of the stream
        << std::setfill('0') << std::setw(2) << datetime.tm_min << ":"
        << std::setfill('0') << std::setw(2) << datetime.tm_sec << "\n";
    std::string arrivaltime = oss.str();

    return arrivaltime;
}
*/

void TempSensor::read() {
    std::cout << "Sensor type: " << _type << " Id: " << _sensorbase._id << " Value: " << _sensorbase._value << " Celsius " << " Time: "  << _sensorbase._timestamp << "\n";
}
void HumiditySensor::read() {
    std::cout << "Sensor type: " << _type << " Id: " << _sensorbase._id << " Value: " << _sensorbase._value << " % " << " Time: "  << _sensorbase._timestamp << "\n";
}
void AirqualitySensor::read() {
    std::cout << "Sensor type: " << _type << " Id: " << _sensorbase._id << " Value: " << _sensorbase._value << " µg/m3 PM2.5 " << " Time: "  << _sensorbase._timestamp << "\n";
}

