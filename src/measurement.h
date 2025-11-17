#ifndef ASSIGNMENT_2_MEASUREMENT_H
#define ASSIGNMENT_2_MEASUREMENT_H


#include <vector>
enum class SensorType;
class Sensor;

struct Measurement {
    SensorType type_;
    std::string unit_;
    float value_{};
    std::string timestamp_;
    int id_{};

    Measurement() = default;
    static Measurement fromCsvString(const std::string &);
};

class MeasurementStorage {
private:
    std::vector<Measurement> measurements_;

public:
    void addMeasurement(Measurement &m);
    void printAllSensors() const;
    [[nodiscard]] std::vector<Measurement> getMeasurementStorage() const {return measurements_;}

};

#endif //ASSIGNMENT_2_MEASUREMENT_H