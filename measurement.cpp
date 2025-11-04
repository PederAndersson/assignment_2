
#include <iomanip>
#include <iostream>
#include "measurement.h"



void MeasurementStorage::addMeasurement(const Measurement &measurement) {
    this->measurements_.emplace_back(measurement);
}

void MeasurementStorage::printAll() const {
    using namespace std::string_literals;

    for (const auto& sensor : measurements_) {
        const auto& t = sensor.temp_sensor_.getSensorbase() ;
        const auto& h = sensor.humidity_sensor_.getSensorbase();
        const auto& n = sensor.noise_sensor_.getSensorbase();

        // Rubriker
        std::cout << std::left
        << std::setw(35) << ("Sensor type: "s + std::string(sensor.temp_sensor_.getSensortype()))
        << std::setw(35) << ("Sensor type: "s + std::string(sensor.humidity_sensor_.getSensortype()))
        << std::setw(35) << ("Sensor type: "s + std::string(sensor.noise_sensor_.getSensortype()))
                  << "\n";

        // Id
        std::cout << std::left
                  << std::setw(35) << ("Id: " + std::to_string(t.id_))
                  << std::setw(35) << ("Id: " + std::to_string(h.id_))
                  << std::setw(35) << ("Id: " + std::to_string(n.id_))
                  << "\n";

        auto make_value_cell = [](double v, std::string_view unit) {
            std::ostringstream os;
            os << std::fixed << std::setprecision(2)
               << "Value: " << v << ' ' << unit;
            return os.str();           // färdig formatterad cell
        };

        std::cout << std::left
                  << std::setw(35) << make_value_cell(t.value_, t.unit_)
                  << std::setw(35) << make_value_cell(h.value_, h.unit_)
                  << std::setw(35) << make_value_cell(n.value_, n.unit_)
                  << '\n';
        // Time
        std::cout << std::left
                  << std::setw(35) << ("Time: " + t.timestamp_)
                  << std::setw(35) << ("Time: " + h.timestamp_)
                  << std::setw(35) << ("Time: " + n.timestamp_)
                  << "\n";

        // Avgränsare mellan mätningar
        std::cout << std::string(100, '-') << "\n";
    }
}



