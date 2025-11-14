#include <filesystem>
#include <fstream>
#include <iostream>

#include "SystemController.h"
#include "statistics.h"
#include "UserInterface.h"
#include "Utils.h"

void SystemController::addMesurements(const std::vector<std::unique_ptr<Sensor>>& sensors) const {
    if (sensors.empty()) {
        std::cout << "No sensors to read.";
        return;
    }
    for (const auto& s : sensors) {
        Measurement m;
        m.type_ = s->getSensorbase().type_;
        m.id_ = s->getSensorbase().id_;
        m.value_ = s->read();
        m.unit_ = s->getSensorbase().unit_;
        m.timestamp_ = DataGenerator::generateTimeStamp();
        measurements_.addMeasurement(m);
    }
}

void SystemController::addSensor(std::vector<std::unique_ptr<Sensor> > &sensors) {
    int choice = Utils::validInput(1,3);
    switch (static_cast<SensorType>(choice)) {
        case SensorType::TemperatureSensor:
            this->sensors_.emplace_back(makeSensor(SensorType::TemperatureSensor));
            break;
        case SensorType::HumiditySensor:
            this->sensors_.emplace_back(makeSensor(SensorType::HumiditySensor));
            break;
        case SensorType::NoiseSensor:
            this->sensors_.emplace_back(makeSensor(SensorType::NoiseSensor));
            break;
        default:
            nullptr;
            break;
    }
}



void SystemController::run() {
    bool run = true;
    const std::string filename = "Sensor_data.csv";
    while (run == true) {
        UserInterface::mainMenu();
        int menu_choice = Utils::validInput(0,7);
        switch (static_cast<UserMenu>(menu_choice)) {
            case UserMenu::AddSensors: {
                UserInterface::addSensorMenu();
                addSensor(sensors_);
                Utils::awaitResponse();
                Utils::clearTerminal();
                break;
            }
            case UserMenu::SetSensoralarms: {
                std::cout << "Not yet implemented.\n";
                Utils::awaitResponse();
                Utils::clearTerminal();
                break;

            }
            case UserMenu::ReadSensors: {
                UserInterface::readSensorMenu();
                addMesurements(sensors_);
                Utils::awaitResponse();
                Utils::clearTerminal();
                break;
            }
            case UserMenu::SensorStatistics: {
                UserInterface::statisticsMenu();
                Statistics statistics(measurements_);
                statistics.printStatistics();
                Utils::awaitResponse();
                Utils::clearTerminal();
                break;
            }
            case UserMenu::PrintSensorValues: {
                UserInterface::sensorReadingsMenu();
                measurements_.printAllSensors();
                Utils::awaitResponse();
                Utils::clearTerminal();
            break;
            }
            case UserMenu::FileHandling: {
                UserInterface::fileReadingMenu();
                switch (Utils::validInput(1,3)) {
                    case 1: {
                        std::cout << "Writes data to a csv file.\n";
                        writeToFile(filename,measurements_);
                        Utils::awaitResponse();
                        Utils::clearTerminal();
                        break;
                    }
                    case 2: {
                        std::cout << "Reads data fom a csv file.\n";
                        readFromFile(filename,measurements_);
                        Utils::awaitResponse();
                        Utils::clearTerminal();
                        break;
                    }
                    case 3: {
                        std::cout << "Clears the csv file.\n";
                        clearFile(filename);
                        Utils::awaitResponse();
                        Utils::clearTerminal();
                        break;
                    }
                    default: {
                        std::cout << "Wrong choice better luck next time.\n";
                        Utils::awaitResponse();
                        Utils::clearTerminal();
                        break;
                    }
                }
                break;
            }
            case UserMenu::AlarmLog: {
                UserInterface::errorLogMenu();
                std::cout << "Not yet implemented.";
                Utils::awaitResponse();
                Utils::clearTerminal();
                /*int sensor_choice = Utils::validInput(1,3);
                switch (static_cast<SensorType>(sensor_choice)) {
                    case SensorType::TemperatureSensor: {
                        break;
                    }
                    case SensorType::HumiditySensor: {
                        break;
                    }
                    case SensorType::NoiseSensor: {
                        break;
                    }
                }*/
                break;
            }
            case UserMenu::Exit: {
                std::cout << "have a nice day!\n";
                run = false;
                break;
            }
            default: {
                std::cout << "Wrong choice better luck next time.\n";
                break;
            }
        }

    }
}


void SystemController::writeToFile(const std::string& filename, const MeasurementStorage& data)  {
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

void SystemController::readFromFile(const std::string& filename, MeasurementStorage& data) {
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

void SystemController::clearFile(const std::string& filename) {
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

