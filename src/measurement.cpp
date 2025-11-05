
#include <iomanip>
#include <iostream>
#include "measurement.h"
#include <algorithm>
#include <filesystem>
#include <fstream>


void MeasurementStorage::addMeasurement(const Measurement &measurement) {
    this->measurements_.emplace_back(measurement);
}

void MeasurementStorage::printAll() const {
    using namespace std::string_literals;

    for (const auto& sensor : measurements_) {
        const auto& t = sensor.temp_sensor_.getSensorbase() ;
        const auto& h = sensor.humidity_sensor_.getSensorbase();
        const auto& n = sensor.noise_sensor_.getSensorbase();

        constexpr int n1 = 35;
        // Rubriker
        std::cout << std::left
        << std::setw(n1) << ("Sensor type: "s + std::string(TempSensor::getStaticType()))
        << std::setw(n1) << ("Sensor type: "s + std::string(HumiditySensor::getStaticType()))
        << std::setw(n1) << ("Sensor type: "s + std::string(NoiseSensor::getStaticType()))
                  << "\n";

        // Id
        std::cout << std::left
                  << std::setw(n1) << ("Id: " + std::to_string(t.id_))
                  << std::setw(n1) << ("Id: " + std::to_string(h.id_))
                  << std::setw(n1) << ("Id: " + std::to_string(n.id_))
                  << "\n";

        auto make_value_cell = [](double v, std::string_view unit) {
            std::ostringstream os;
            os << std::fixed << std::setprecision(2)
               << "Value: " << v << ' ' << unit;
            return os.str();           // färdig formatterad cell
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

        // Avgränsare mellan mätningar
        std::cout << std::string(100, '-') << "\n";
    }
}

void MeasurementStorage::writeToFile(const std::string& filename, const MeasurementStorage& data)  {
    std::ofstream myFile;
    myFile.open(filename,std::ios::app | std::ios::out);
    if (!myFile.is_open()) {
        std::cerr << "Error" << filename << " not found";
        return;
    }
    if (!std::filesystem::exists(filename) || std::filesystem::file_size(filename) == 0) {
        myFile << "SENSORTYPE" << "," << "ID" << "," << "VALUE" << "," << "TIMESTAMP" << "\n";
    }
    if (!data.getMeasurementStorage().empty()) {
        for (const auto& sensor : data.getMeasurementStorage()) {
            myFile  << TempSensor::getStaticType() << "," << sensor.temp_sensor_.getSensorbase().id_ << ","
                    << sensor.temp_sensor_.getSensorbase().value_ << "," << sensor.temp_sensor_.getSensorbase().timestamp_ << "\n";
            myFile  << HumiditySensor::getStaticType() << "," << sensor.humidity_sensor_.getSensorbase().id_ << ","
                    << sensor.humidity_sensor_.getSensorbase().value_ << "," << sensor.humidity_sensor_.getSensorbase().timestamp_ << "\n";
            myFile  << NoiseSensor::getStaticType() << "," << sensor.noise_sensor_.getSensorbase().id_ << ","
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
            int id = std::stoi(idStr);
            double value = std::stod(valueStr);

            SensorData sensorData;
            sensorData.id_ = id;
            sensorData.timestamp_ = timestampStr;
            sensorData.value_ = static_cast<float>(value);

            // sort with a constexpr variable to prevent misspelling
            if (sensorType == TempSensor::getStaticType()) {
                sensorData.unit_ = TempSensor::getStaticUnit();
                tempData.push_back(sensorData);
            }
            else if (sensorType == HumiditySensor::getStaticType()) {
                sensorData.unit_ = HumiditySensor::getStaticUnit();
                humidityData.push_back(sensorData);
            }
            else if (sensorType == NoiseSensor::getStaticType()) {
                sensorData.unit_ = NoiseSensor::getStaticType();
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

    // Skapa Measurement objekt (du behöver anpassa detta beroende på hur dina sensorer är organiserade)
    // Om varje rad representerar en komplett measurement:
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


