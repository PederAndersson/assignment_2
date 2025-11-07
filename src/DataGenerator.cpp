#include <ctime>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include "DataGenerator.h"


SensorData DataGenerator::generateSensorData(float  min,float max) {
    if (min > max) { // simple failsafe incase you input the numbers in the wrong order
        std::swap(min, max);
    }
    SensorData sensor_values;

    std::uniform_real_distribution<float> dist(min,max);
    float sensor_value = dist(gen_);
    sensor_values.value_ = sensor_value;

    time_t time_stamp = time(nullptr); // gets you the local time.
    tm datetime = *localtime(&time_stamp);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << datetime.tm_hour << ":" //content of the stream
        << std::setfill('0') << std::setw(2) << datetime.tm_min << ":"
        << std::setfill('0') << std::setw(2) << datetime.tm_sec;
    sensor_values.timestamp_ = oss.str();

    return sensor_values;
}
