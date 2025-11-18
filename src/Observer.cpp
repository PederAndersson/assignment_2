#include <iostream>
#include "Observer.h"



#include "Logger.h"

#include "Utils.h"




void ThresholdObserver::checkValue(const Measurement& m, const float &value) {
    if (check_upper_ == true && value > value_.upper_) {
        Logger::instance().ifBreachedNotify(m);
    }
    if (check_lower_ == true && value < value_.lower_) {
        Logger::instance().ifBreachedNotify(m);
    }
}

void ThresholdObserver::ifBreachedNotify(const Measurement &m) {

}

MinMax ThresholdObserver::getThreshold() const {
        return value_;
}

void ThresholdObserver::setThreshold() {
    std::cout << "Set new Thresholds.\n" << "Lower: " << value_.lower_ << "\n" << "Higher: " << value_.upper_ << "\n";
    std::cout << "Lower: ";
    value_.lower_ = Utils::validFloatInput();
    std::cout << "Upper: ";
    value_.upper_ = Utils::validFloatInput();

}

