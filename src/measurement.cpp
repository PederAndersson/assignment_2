
#include <iomanip>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <filesystem>

#include "measurement.h"
#include "Utils.h"

void MeasurementStorage::addMeasurement(const Measurement &measurement) {
    this->measurements_.emplace_back(measurement);
}

void MeasurementStorage::printAllSensors() const { // code for formatting the printout looks.
    using namespace std::string_literals;

    for (const auto& sensor : measurements_) {
        const auto& t = sensor.temp_sensor_.getSensorbase() ;
        const auto& h = sensor.humidity_sensor_.getSensorbase();
        const auto& n = sensor.noise_sensor_.getSensorbase();

        constexpr int n1 = 35;
        // Headlines
        std::cout << std::left
        << std::setw(n1) << ("Sensor type: "s + Utils::sensorTypeToString(SensorType::TemperatureSensor))
        << std::setw(n1) << ("Sensor type: "s + Utils::sensorTypeToString(SensorType::HumiditySensor))
        << std::setw(n1) << ("Sensor type: "s + Utils::sensorTypeToString(SensorType::NoiseSensor))
                  << "\n";

        // Id
        std::cout << std::left
                  << std::setw(n1) << ("Id: " + std::to_string(t.id_))
                  << std::setw(n1) << ("Id: " + std::to_string(h.id_))
                  << std::setw(n1) << ("Id: " + std::to_string(n.id_))
                  << "\n";
        //Value and unit
        auto make_value_cell = [](double v, std::string_view unit) {
            std::ostringstream os;
            os << std::fixed << std::setprecision(2)
               << "Value: " << v << ' ' << unit;
            return os.str();
        };

        std::cout << std::left
                  << std::setw(n1) << make_value_cell(t.value_, t.unit_)
                  << std::setw(n1) << make_value_cell(h.value_, h.unit_)
                  << std::setw(n1) << make_value_cell(n.value_, n.unit_)
                  << '\n';
        // Time
        std::cout << std::left
                  << std::setw(n1) << ("Time: " + t.timestamp_)
                  << std::setw(n1) << ("Time: " + h.timestamp_)
                  << std::setw(n1) << ("Time: " + n.timestamp_)
                  << "\n";

        // Delineation
        std::cout << std::string(100, '-') << "\n";
    }
}
void MeasurementStorage::readAllSensors(TempSensor &T, HumiditySensor &H, NoiseSensor &N) {
    T.read(); // calls the read functions for all sensors.
    H.read();
    N.read();
}


void MeasurementStorage::writeToFile(const std::string& filename, const MeasurementStorage& data)  {
    std::ofstream myFile;
    myFile.open(filename,std::ios::app | std::ios::out);
    if (!myFile.is_open()) { //checks is you have the right filename
        std::cerr << "Error" << filename << " not found";
        return;
    }
    if (!std::filesystem::exists(filename) || std::filesystem::file_size(filename) == 0) { //writes header if the file is empty
        myFile << "SENSORTYPE" << "," << "ID" << "," << "VALUE" << "," << "TIMESTAMP" << "\n";
    }
    if (!data.getMeasurementStorage().empty()) { // checks if the vector is empty
        for (const auto& sensor : data.getMeasurementStorage()) {
            myFile  << Utils::sensorTypeToString(SensorType::TemperatureSensor) << "," << sensor.temp_sensor_.getSensorbase().id_ << ","
                    << sensor.temp_sensor_.getSensorbase().value_ << "," << sensor.temp_sensor_.getSensorbase().timestamp_ << "\n";
            myFile  << Utils::sensorTypeToString(SensorType::HumiditySensor) << "," << sensor.humidity_sensor_.getSensorbase().id_ << ","
                    << sensor.humidity_sensor_.getSensorbase().value_ << "," << sensor.humidity_sensor_.getSensorbase().timestamp_ << "\n";
            myFile  << Utils::sensorTypeToString(SensorType::NoiseSensor) << "," << sensor.noise_sensor_.getSensorbase().id_ << ","
                    << sensor.noise_sensor_.getSensorbase().value_ << "," << sensor.noise_sensor_.getSensorbase().timestamp_ << "\n";
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

    // Temporary storage for each sensor type
    std::vector<SensorData> tempData;
    std::vector<SensorData> humidityData;
    std::vector<SensorData> noiseData;

    while (std::getline(myFile, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string sensorType, idStr, timestampStr, valueStr;

        // assume right format : sensorType,id,value,timestamp
        std::getline(ss, sensorType, ',');
        std::getline(ss, idStr, ',');
        std::getline(ss, valueStr, ',');
        std::getline(ss, timestampStr, ',');

        try {
            int id = std::stoi(idStr); // change string to int
            double value = std::stod(valueStr); // change string to double

            SensorData sensorData;
            sensorData.id_ = id;
            sensorData.timestamp_ = timestampStr;
            sensorData.value_ = static_cast<float>(value); // chang double to float to match the sensor

            // sort with enum to prevent misspelling
            if (sensorType == Utils::sensorTypeToString(SensorType::TemperatureSensor)) {
                TempSensor temp_sensor;
                sensorData.unit_ = temp_sensor.getSensorbase().unit_;
                tempData.push_back(sensorData);
            }
            else if (sensorType == Utils::sensorTypeToString(SensorType::HumiditySensor)) {
                HumiditySensor humidity_sensor;
                sensorData.unit_ = humidity_sensor.getSensorbase().unit_;
                humidityData.push_back(sensorData);
            }
            else if (sensorType == Utils::sensorTypeToString(SensorType::NoiseSensor)) {
                NoiseSensor noise_sensor;
                sensorData.unit_ = noise_sensor.getSensorbase().unit_;
                noiseData.push_back(sensorData);
            }
            else {
                std::cerr << "Unknown sensor type: " << sensorType << " on line: " << line << "\n";
            }

        } catch (const std::invalid_argument&) {
            std::cerr << "Invalid value on line: " << line << "\n";
        } catch (const std::out_of_range&) {
            std::cerr << "Value out of range on line: " << line << "\n";
        }
    }

    myFile.close();

    // Create Measurement objects (you need to adapt this depending on how your sensors are organized)
    // If each row represents a complete measurement:

    for (size_t i = 0; i < std::min({tempData.size(), humidityData.size(), noiseData.size()}); ++i) {
        TempSensor tempSensor(tempData[i].id_, tempData[i]);
        HumiditySensor humiditySensor(humidityData[i].id_, humidityData[i]);
        NoiseSensor noiseSensor(noiseData[i].id_, noiseData[i]);

        Measurement measurement(tempSensor, humiditySensor, noiseSensor);
        data.addMeasurement(measurement);
    }

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


