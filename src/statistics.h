
#ifndef ASSIGNMENT_2_STATISTICS_H
#define ASSIGNMENT_2_STATISTICS_H


#include "measurement.h"
struct Sensorstats {
    float number_measurements_ = 0;
    float mean_ = 0.0f;
    float min_ = 0.0f;
    float max_ = 0.0f;
    float variance_ = 0.0f;
    float standard_dev_ = 0.0f;
};
struct Stats {
    Sensorstats temp_;
    Sensorstats humid_;
    Sensorstats noise_;
};

class Statistics {
private:
    Stats stats_;

public:
    explicit Statistics(Stats stats) : stats_(stats){}
    Statistics() = default;
    Statistics calculateStatistics(Statistics& stats, const MeasurementStorage& data);
    void printStatistics() const;
};


#endif //ASSIGNMENT_2_STATISTICS_H