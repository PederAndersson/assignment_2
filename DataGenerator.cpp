#include <ctime>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include "DataGenerator.h"


SensorData DataGenerator::generateSensorData(float  x,float y) {
    if (x > y) {
        std::swap(x, y);
    }
    SensorData sensor_values;

    std::uniform_real_distribution<float> dist(x,y);
    float sensor_value = dist(gen_);
    sensor_values.value_ = sensor_value;

    time_t time_stamp = time(nullptr);
    tm datetime = *localtime(&time_stamp);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << datetime.tm_hour << ":" //content of the stream
        << std::setfill('0') << std::setw(2) << datetime.tm_min << ":"
        << std::setfill('0') << std::setw(2) << datetime.tm_sec;
    sensor_values.timestamp_ = oss.str();

    return sensor_values;
}
