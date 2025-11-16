
#ifndef ASSIGNMENT_2_SENSORDATA_H
#define ASSIGNMENT_2_SENSORDATA_H
#include <string>

enum class SensorType {
    TemperatureSensor = 1,
    HumiditySensor,
    NoiseSensor,
    All
};

struct Interval {
        float min_;
        float max_;
};


struct SensorData {
    float value_ ; //generator
    std::string timestamp_; // generator
    std::string unit_; //config
    int id_{}; //input
    Interval interval_; //config
    SensorType type_{};// conifg
};

struct TempConfig {
    SensorType type_ = SensorType::TemperatureSensor;
    const std::string unit_ = "Celsius";
    Interval interval_{15.0f,30.0f};
};
struct HumidConfig {
    SensorType type_ = SensorType::HumiditySensor;
    const std::string unit_ = "%";
    Interval interval_ {25.0f,85.0f};
};
struct NoiseConfig {
    SensorType type_ = SensorType::NoiseSensor;
    const std::string unit_ = "dB";
Interval interval_ {15.0f,100.0f};
};
#endif //ASSIGNMENT_2_SENSORDATA_H