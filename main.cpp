#include <iomanip>
#include <iostream>
#include <filesystem>

#include "src/sensor.h"
#include "src/DataGenerator.h"
#include "src/measurement.h"
#include "src/statistics.h"
#include "src/UserInterface.h"
#include "src/Utils.h"

namespace fs = std::filesystem;

int main() {
    DataGenerator gen;
    MeasurementStorage measurement_storage;
    Statistics stats;
    auto temp1 = SensorFactory::generateTempData(gen,1);
    auto humid1 = SensorFactory::generateHumidityData(gen,1);
    auto noise1 = SensorFactory::generateNoiseData(gen,1);
    std::cout << std::fixed << std::setprecision(2);
    const std::string filename = "Sensor_data.csv";
    bool check = true;
    while (check == true) {
    UserInterface::printMenu();

        switch (Utils::validInput()) {
            case 1: {
                std::cout << "Read sensor and collect the current value.\n";
                measurement_storage.readAllSensors(temp1,humid1,noise1);
                Measurement measurement(temp1,humid1,noise1);
                measurement_storage.addMeasurement(measurement);
                break;
            }
            case 2: {
                std::cout << "Caluclute and shows the current statistics:\n";
                stats.calculateStatistics(stats,measurement_storage);
                stats.printStatistics();
                break;

            }
            case 3: {
                std::cout << "Print the current sensor data.\n";
                measurement_storage.printAllSensors();
                break;
            }
            case 4: {
                UserInterface::printFileReadingMenu();
                switch (Utils::validInput()) {
                    case 1: {
                        std::cout << "Writes data to a csv file.\n";
                        MeasurementStorage::writeToFile(filename,measurement_storage);
                        break;
                    }
                    case 2: {
                        std::cout << "Reads data fom a csv file.\n";
                        MeasurementStorage::readFromFile(filename,measurement_storage);
                        break;
                    }
                        default: {
                        std::cout << "Wrong choice better luck next time.\n";
                        break;
                    }
                }
            }
            case 5: {
                std::cout << "Clears the csv file.\n";
                MeasurementStorage::clearFile(filename);
                break;
            }
            case 6: {
                std::cout << "Have a nice day.";
            check = false;
            }
                default: {
                std::cout << "Wrong choice better luck next time.\n";
                break;
            }
        }

    }



    return 0;
}