
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
    this->measurements_.emplace_back(m);
}

void MeasurementStorage::printAllSensors() const { // code for formatting the printout looks.
    using namespace std::string_literals;
    if (measurements_.empty()) {
        std::cout << "No measurements available.\n";
        return;
    }
    //iterators sorting by sensortype
    auto itTemp = std::find_if(measurements_.begin(), measurements_.end(),
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

        // check next element
        if (itTemp  != end) itTemp  = std::find_if(std::next(itTemp),  end, [](const Measurement& m){ return m.type_ == SensorType::TemperatureSensor; });
        if (itHum   != end) itHum   = std::find_if(std::next(itHum),   end, [](const Measurement& m){ return m.type_ == SensorType::HumiditySensor; });
        if (itNoise != end) itNoise = std::find_if(std::next(itNoise), end, [](const Measurement& m){ return m.type_ == SensorType::NoiseSensor; });
    }
}


float MeasurementStorage::takeMeasurements(const std::vector<std::unique_ptr<Sensor>>& sensors) {
    if (sensors.empty()) {
        std::cout << "No sensors to read.";
        return 0.0f;
    }
    for (const auto& s : sensors) {
        Measurement m;
        m.type_ = s->getSensorbase().type_;
        m.id_ = s->getSensorbase().id_;
        m.value_ = s->read();
        m.unit_ = s->getSensorbase().unit_;
        m.timestamp_ = DataGenerator::generateTimeStamp();
        this->addMeasurement(m);
    }


    return 0.0f;
}


void MeasurementStorage::writeToFile(const std::string& filename, const MeasurementStorage& data)  {
    std::ofstream myFile;
    myFile.open(filename,std::ios::app | std::ios::out);
    if (!myFile.is_open()) { //checks is you have the right filename
        std::cerr << "Error" << filename << " not found";
        return;
    }
    if (!std::filesystem::exists(filename) || std::filesystem::file_size(filename) == 0) { //writes header if the file is empty
        myFile << "SENSORTYPE" << "," << "ID" << "," << "VALUE" << "," << "UNIT" << "," << "TIMESTAMP" << "\n";
    }
    if (!data.getMeasurementStorage().empty()) { // checks if the vector is empty
        for (const auto& sensor : data.getMeasurementStorage()) {
            myFile  << Utils::sensorTypeToString(sensor.type_) << "," << sensor.id_ << ","
                    << sensor.value_ << "," << sensor.unit_ << "," << sensor.timestamp_ << "\n";
        }
    } else {
        std::cout << "Sensor data is empty" << "\n";
    }

    myFile.close();
    std::cout << "Data saved to file\n";
}

void MeasurementStorage::readFromFile(const std::string& filename, MeasurementStorage& data) {
    std::fstream myFile;
    myFile.open(filename, std::ios::in);

    if (!myFile.is_open()) {
        std::cerr << filename << " not found.\n";
        return;
    }

    if (myFile.peek() == std::ifstream::traits_type::eof()) {
        std::cout << filename << " is empty.\n";
        return;
    }

    std::string line;
    std::getline(myFile, line); // Skip header


    while (std::getline(myFile, line)) {
        if (line.empty()) continue;

        auto measurement = Measurement::fromCsvString(line);
        data.addMeasurement(measurement);
    }

    myFile.close();

    std::cout << "Data retrieved.\n";
}

void MeasurementStorage::clearFile(const std::string& filename) {
    std::cout << "Are you sure you want to delete the data?\n";
    std::cout << "1.Yes \t 2.No :";
    int choice = 0;
    std::cin >> choice;
    if (choice == 1) {
        std::fstream myFile;
        myFile.open(filename, std::ofstream::out | std::ofstream::trunc);
        myFile.flush();
        myFile.close();
        std::cout << "Data cleared.\n";
    } else {
        std::cout << "Data not cleared, have a nice day.\n";
    }
}


