
#ifndef ASSIGNMENT_2_STATISTICS_H
#define ASSIGNMENT_2_STATISTICS_H


#include "measurement.h"

class Statistics {
private:
    int count_ = 0;
    float mean_ = 0.0f;
    float min_ = 0.0f;
    float max_ = 0.0f;
    float variance_ = 0.0f;
    float standard_dev_ = 0.0f;
    int id_;
    std::string type_;
    std::string unit_;

public:
    explicit Statistics(const MeasurementStorage& data);

    void printStatistics() const;
};


#endif //ASSIGNMENT_2_STATISTICS_H