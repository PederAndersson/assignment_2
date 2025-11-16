//
// Created by peder on 2025-11-15.
//

#ifndef ASSIGNMENT_2_LOGGER_H
#define ASSIGNMENT_2_LOGGER_H
#include <string>
#include <vector>

#include "Observer.h"


class Logger : public ThresholdObserver {
private:
    std::vector<std::string> alarmMsg_{};
    Logger() : ThresholdObserver(0, 0) {}
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
public:
    void printAlarms() const;
    void ifBreachedNotify(const Measurement& m) override;

    static Logger& instance() {
        static Logger inst;
        return inst;
    }
};


#endif //ASSIGNMENT_2_LOGGER_H
