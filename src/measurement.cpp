
#include <iomanip>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <filesystem>

#include "measurement.h"
#include "Utils.h"

Measurement Measurement::fromCsvString(const std::string & line) {
    Measurement m;
    std::istringstream ss(line);
    std::string string;

    // Sensor type
    std::getline(ss, string, ',');
    m.type_ = Utils::stringToType(string);

    // Sensor id
    std::getline(ss, string, ',');
    m.id_ = std::stoi(string);

    // Value
    std::getline(ss, string, ',');
    m.value_ = std::stof(string);

    // Sensor unit
    std::getline(ss, string, ',');
    m.unit_ = string;

    // Timestamp
    std::getline(ss, string, ',');
    m.timestamp_ = string;

    return m;
}



void MeasurementStorage::addMeasurement(Measurement &m) {
    measurements_.emplace_back(m);
}

void MeasurementStorage::printAllSensors() const { // code for formatting the printout looks.
    using namespace std::string_literals;
    if (measurements_.empty()) {
        std::cout << "No measurements available.\n";
        return;
    }
    //iterators sorting by sensor types
    auto itTemp = std::ranges::find_if(measurements_,
                                       [](const Measurement& m){ return m.type_ == SensorType::TemperatureSensor; });
    auto itHum  = std::find_if(measurements_.begin(), measurements_.end(),
                               [](const Measurement& m){ return m.type_ == SensorType::HumiditySensor; });
    auto itNoise= std::find_if(measurements_.begin(), measurements_.end(),
                               [](const Measurement& m){ return m.type_ == SensorType::NoiseSensor; });

    auto end = measurements_.end();

    auto make_value_cell = [](double v, std::string_view unit) {
        std::ostringstream os;
        os << std::fixed << std::setprecision(2)
           << "Value: " << v << ' ' << unit;
        return os.str();
    };

    while (itTemp != end || itHum != end || itNoise != end) {
        constexpr int n1 = 35;
        // headline
        std::cout << std::left
                  << std::setw(n1) << (itTemp  != end ? "Sensor type: "s + Utils::sensorTypeToString(itTemp->type_)  : ""s)
                  << std::setw(n1) << (itHum   != end ? "Sensor type: "s + Utils::sensorTypeToString(itHum->type_)   : ""s)
                  << std::setw(n1) << (itNoise != end ? "Sensor type: "s + Utils::sensorTypeToString(itNoise->type_) : ""s)
                  << "\n";

        // ID
        std::cout << std::left
                  << std::setw(n1) << (itTemp  != end ? "Id: "s + std::to_string(itTemp->id_)  : ""s)
                  << std::setw(n1) << (itHum   != end ? "Id: "s + std::to_string(itHum->id_)   : ""s)
                  << std::setw(n1) << (itNoise != end ? "Id: "s + std::to_string(itNoise->id_) : ""s)
                  << "\n";

        // values, units
        std::cout << std::left
                  << std::setw(n1) << (itTemp  != end ? make_value_cell(itTemp->value_,  itTemp->unit_)  : ""s)
                  << std::setw(n1) << (itHum   != end ? make_value_cell(itHum->value_,   itHum->unit_)   : ""s)
                  << std::setw(n1) << (itNoise != end ? make_value_cell(itNoise->value_, itNoise->unit_) : ""s)
                  << "\n";

        // timestamp
        std::cout << std::left
                  << std::setw(n1) << (itTemp  != end ? "Time: "s + itTemp->timestamp_  : ""s)
                  << std::setw(n1) << (itHum   != end ? "Time: "s + itHum->timestamp_   : ""s)
                  << std::setw(n1) << (itNoise != end ? "Time: "s + itNoise->timestamp_ : ""s)
                  << "\n";

        std::cout << std::string(100, '-') << "\n";

        // check the next element
        if (itTemp  != end) itTemp  = std::find_if(std::next(itTemp),  end, [](const Measurement& m){ return m.type_ == SensorType::TemperatureSensor; });
        if (itHum   != end) itHum   = std::find_if(std::next(itHum),   end, [](const Measurement& m){ return m.type_ == SensorType::HumiditySensor; });
        if (itNoise != end) itNoise = std::find_if(std::next(itNoise), end, [](const Measurement& m){ return m.type_ == SensorType::NoiseSensor; });
    }
}



