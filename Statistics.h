
#ifndef ASSIGNMENT_2_STATISTICS_H
#define ASSIGNMENT_2_STATISTICS_H

#include "measurement.h"

class Statistics {
private:
    int number_measurements_;
    float mean_;
    float min_;
    float max_;
    float variance_;
    float standard_dev_;
public:
    Statistics(int number_measurements, float mean, float min, float max, float variance, float standard_dev) :
    number_measurements_(number_measurements), mean_(mean), min_(min), max_(max), variance_(variance), standard_dev_(standard_dev){}

    float calculateMean(Measurement& data);
    float calculateVariance(Measurement& data);
    float standardDev(Measurement& data);
    float minValue(Measurement& data);
    float maxValue(Measurement& data);
    int numberMeasurements(Measurement& data);

};


#endif //ASSIGNMENT_2_STATISTICS_H