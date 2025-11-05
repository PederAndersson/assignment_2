#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <sstream>


#include "statistics.h"


Statistics Statistics::calculateStatistics(Statistics& stats, const MeasurementStorage& data) {
    float temp_sum = 0;
    float humid_sum = 0;
    float noise_sum = 0;
    stats_.temp_.number_measurements_ = data.getMeasurementStorage().size();
    stats_.humid_.number_measurements_ = data.getMeasurementStorage().size();
    stats_.noise_.number_measurements_ = data.getMeasurementStorage().size();
    for (auto& sensor :  data.getMeasurementStorage()) {
        temp_sum += sensor.temp_sensor_.getSensorbase().value_;
        humid_sum += sensor.humidity_sensor_.getSensorbase().value_;
        noise_sum += sensor.noise_sensor_.getSensorbase().value_;
    }
    stats_.temp_.mean_ = temp_sum/stats_.temp_.number_measurements_;
    stats_.humid_.mean_ = humid_sum/stats_.temp_.number_measurements_;
    stats_.noise_.mean_ = noise_sum/stats_.temp_.number_measurements_;

    float temp_squarediff = 0.0;
    float humid_squarediff = 0.0;
    float noise_squarediff = 0.0;
    for (auto& value : data.getMeasurementStorage()) {
        const float temp_diff = value.temp_sensor_.getSensorbase().value_ - stats_.temp_.mean_;
        temp_squarediff += temp_diff*temp_diff;
        const float humid_diff = value.temp_sensor_.getSensorbase().value_ - stats_.temp_.mean_;
        humid_squarediff += humid_diff*humid_diff;
        const float noise_diff = value.temp_sensor_.getSensorbase().value_ - stats_.temp_.mean_;
        noise_squarediff += noise_diff*noise_diff;
    }
    stats_.temp_.variance_ = temp_squarediff/data.getMeasurementStorage().size();
    stats_.humid_.variance_ = humid_squarediff/data.getMeasurementStorage().size();
    stats_.noise_.variance_ = noise_squarediff/data.getMeasurementStorage().size();
    stats_.temp_.standard_dev_ = sqrt(stats_.temp_.variance_);
    stats_.humid_.standard_dev_ = sqrt(stats_.humid_.variance_);
    stats_.noise_.standard_dev_ = sqrt(stats_.noise_.variance_);

    const auto &storage = data.getMeasurementStorage();

    auto findMinMax = [&](auto getValue, auto &outMin, auto &outMax) {
        if (storage.empty()) return;

        auto [min_it, max_it] = std::minmax_element(
            storage.begin(), storage.end(),
            [&](const Measurement &a, const Measurement &b) {
                return getValue(a) < getValue(b);
            });

        outMin = getValue(*min_it);
        outMax = getValue(*max_it);
    };
    findMinMax(
    [](const Measurement &m) { return m.temp_sensor_.getSensorbase().value_; },
    stats_.temp_.min_, stats_.temp_.max_);

    findMinMax(
        [](const Measurement &m) { return m.humidity_sensor_.getSensorbase().value_; },
        stats_.humid_.min_, stats_.humid_.max_);

    findMinMax(
        [](const Measurement &m) { return m.noise_sensor_.getSensorbase().value_; },
        stats_.noise_.min_, stats_.noise_.max_);


    return stats;
}

void Statistics::printStatistics() const {

    using namespace std::string_literals;

    const int n = 35;
    // Rubriker
    std::cout << std::left
              << std::setw(n) << "Temperature stats"
              << std::setw(n) << "Humidity stats"
              << std::setw(n) << "Noise stats"
              << "\n";

    // Antal mätningar
    std::cout << std::left
              << std::setw(n) << ("Count: "s + std::to_string(static_cast<int>(stats_.temp_.number_measurements_)))
              << std::setw(n) << ("Count: "s + std::to_string(static_cast<int>(stats_.humid_.number_measurements_)))
              << std::setw(n) << ("Count: "s + std::to_string(static_cast<int>(stats_.noise_.number_measurements_)))
              << "\n";

    auto make_value_cell = [](float v, std::string_view label) {
        std::ostringstream os;
        os << std::fixed << std::setprecision(2)
           << label << v;
        return os.str();
    };

    // Medelvärde
    std::cout << std::left
              << std::setw(n) << make_value_cell(stats_.temp_.mean_, "Mean: ")
              << std::setw(n) << make_value_cell(stats_.humid_.mean_, "Mean: ")
              << std::setw(n) << make_value_cell(stats_.noise_.mean_, "Mean: ")
              << "\n";

    // Min
    std::cout << std::left
              << std::setw(n) << make_value_cell(stats_.temp_.min_, "Min: ")
              << std::setw(n) << make_value_cell(stats_.humid_.min_, "Min: ")
              << std::setw(n) << make_value_cell(stats_.noise_.min_, "Min: ")
              << "\n";

    // Max
    std::cout << std::left
              << std::setw(n) << make_value_cell(stats_.temp_.max_, "Max: ")
              << std::setw(n) << make_value_cell(stats_.humid_.max_, "Max: ")
              << std::setw(n) << make_value_cell(stats_.noise_.max_, "Max: ")
              << "\n";

    // Varians
    std::cout << std::left
              << std::setw(n) << make_value_cell(stats_.temp_.variance_, "Variance: ")
              << std::setw(n) << make_value_cell(stats_.humid_.variance_, "Variance: ")
              << std::setw(n) << make_value_cell(stats_.noise_.variance_, "Variance: ")
              << "\n";

    // Standardavvikelse
    std::cout << std::left
              << std::setw(n) << make_value_cell(stats_.temp_.standard_dev_, "Std dev: ")
              << std::setw(n) << make_value_cell(stats_.humid_.standard_dev_, "Std dev: ")
              << std::setw(n) << make_value_cell(stats_.noise_.standard_dev_, "Std dev: ")
              << "\n";

    // Avgränsare
    std::cout << std::string(100, '-') << "\n";
}
