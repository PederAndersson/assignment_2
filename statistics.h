
#ifndef ASSIGNMENT_2_STATISTICS_H
#define ASSIGNMENT_2_STATISTICS_H

#include "sensor.h"

class statistics {
private:
    int number_measurements_ = 0;
    float mean_ = 0.0f;
    float min_ = 0.0f;
    float max_ = 0.0f;
    float variance_ = 0.0f;
    float standard_dev_ = 0.0f;
public:
    statistics() = default;

};


#endif //ASSIGNMENT_2_STATISTICS_H