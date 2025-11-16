#include <ctime>
#include <iomanip>
#include <sstream>
#include "DataGenerator.h"


float DataGenerator::generateSensorData(float  min,float max) {
    if (min > max) { // simple failsafe incase you input the numbers in the wrong order
        std::swap(min, max);
    }

    std::uniform_real_distribution<float> dist(min,max);
    float sensor_value = dist(gen_);
    return sensor_value;
}

std::string DataGenerator::generateTimeStamp() {
    time_t time_stamp = time(nullptr); // gets you the local time.
    tm datetime = *localtime(&time_stamp);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << datetime.tm_hour << ":" //content of the stream
        << std::setfill('0') << std::setw(2) << datetime.tm_min << ":"
        << std::setfill('0') << std::setw(2) << datetime.tm_sec;

    return oss.str();
}

