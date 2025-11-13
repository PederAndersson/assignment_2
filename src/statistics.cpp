#include <cmath>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <sstream>
#include <numeric>


#include "statistics.h"

#include "Utils.h"


Statistics::Statistics(const MeasurementStorage& data) {
    if (data.getMeasurementStorage().empty()){ return;}
    int choice = Utils::validInput(1,3);
    auto sensortype = static_cast<SensorType>(choice);

    std::vector<Measurement> temp_data = data.getMeasurementStorage();
    std::vector<Measurement> filterd_data;

    std::copy_if(
        temp_data.begin(), temp_data.end(), std::back_inserter(filterd_data),
        [&](const Measurement &m){ return m.type_ == sensortype; } );

    auto sum = std::accumulate(
        filterd_data.begin(),filterd_data.end(),
        0.0,
        [] (float sum, const Measurement& measurement) {
            return sum + measurement.value_;
    });
    this->count_ = filterd_data.size();
    this->mean_ = sum / this->count_;
    this->min_ = std::min_element(filterd_data.begin(),filterd_data.end(),
        [](const Measurement& a, const Measurement& b) {
            return a.value_ < b.value_;
        })
        ->value_;

    this->max_ = std::max_element(filterd_data.begin(),filterd_data.end(),
        [](const Measurement &a, const Measurement &b) {
            return a.value_ > b.value_;
        })
        ->value_;

    float square_diff = 0.0f;
    for (auto & d : filterd_data) {
        float diff = d.value_ - this->mean_;
        square_diff += diff * diff;
    }

    this->variance_ = square_diff / static_cast<float>(filterd_data.size());

    this->standard_dev_ = std::sqrt(this->variance_);

    this->type_ = Utils::sensorTypeToString(filterd_data.at(0).type_);

    this->unit_ = filterd_data.at(0).unit_;
    this->id_ = filterd_data.at(0).id_;

}

void Statistics::printStatistics() const { // prints the statistics using the same formatting as the sensors

    using namespace std::string_literals;

    const int n = 35;

    std::cout << std::string(n, '-') << "\n";
    // headline
    std::cout << std::left
              << std::setw(n) << this->type_
              << "\n";
    // Id
    std::cout << std::left
             << std::setw(n) <<( "Id: "s + std::to_string(this->id_))
             << "\n";

    // measurement count
    std::cout << std::left
              << std::setw(n) << ("Count: "s + std::to_string(this->count_))
              << "\n";

    auto make_value_cell = [](float v, std::string_view label) {
        std::ostringstream os;
        os << std::fixed << std::setprecision(2)
           << label << v;
        return os.str();
    };

    // mean
    std::cout << std::left
              << std::setw(n) << make_value_cell(this->mean_, "Mean: ")
              << "\n";

    // Min
    std::cout << std::left
              << std::setw(n) << make_value_cell(this->min_, "Min: ")
              << "\n";

    // Max
    std::cout << std::left
              << std::setw(n) << make_value_cell(this->max_, "Max: ")
              << "\n";

    // Variance
    std::cout << std::left
              << std::setw(n) << make_value_cell(this->variance_, "Variance: ")
              << "\n";

    // standard deviation
    std::cout << std::left
              << std::setw(n) << make_value_cell(this->standard_dev_, "Std dev: ")
              << "\n";

    // deliniation
    std::cout << std::string(n, '-') << "\n";
}
