//
// Created by peder on 2025-11-15.
//

#include "Logger.h"

#include <iomanip>

#include "Utils.h"
#include "measurement.h"
#include <iostream>


void Logger::ifBreachedNotify(const Measurement &m) {
    std::string alarm_warning;
        alarm_warning += Utils::sensorTypeToString(m.type_) + " ";
        alarm_warning += std::to_string(m.id_) + ", ";
        alarm_warning += std::to_string(m.value_) + " ";
        alarm_warning += m.unit_ + ", ";
        alarm_warning += m.timestamp_;
    alarmMsg_.emplace_back(alarm_warning);
}

void Logger::printAlarms() const {
    for (const auto& msg : alarmMsg_) {
        std::cout << "[LOG] " << msg << "\n";
    }
}
