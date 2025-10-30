
#include <iomanip>
#include "sensor_hub.h"

std::string sensor_hub::generateTimestamp() {
    time_t timestamp = time(nullptr);
    tm datetime = *localtime(&timestamp);

    std::ostringstream oss;

    oss << std::setfill('0') << std::setw(2) << datetime.tm_hour << ":" //content of the stream
        << std::setfill('0') << std::setw(2) << datetime.tm_min << ":"
        << std::setfill('0') << std::setw(2) << datetime.tm_sec << "\n";
    std::string arrivaltime = oss.str();

    return arrivaltime;
}

float sensor_hub::generateHeatValue() {

}
float sensor_hub::generateHumidityValue() {

}
float sensor_hub::generateWindValue() {

}

