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
    TempConfig tcgf;
    HumidConfig hcfg;
    NoiseConfig ncfg;
    DataGenerator gen; //generator for data
    MeasurementStorage measurement_storage; //vector for sensor data
    Statistics stats;
    TempSensor temp (1,tcgf);
    HumiditySensor humid (1,hcfg);
    NoiseSensor noise(1,ncfg);
    std::cout << std::fixed << std::setprecision(2);
    const std::string filename = "Sensor_data.csv";
    bool check = true;
    while (check == true) {
    UserInterface::printMenu();

        switch (Utils::validInput()) {
            case 1: {
                std::cout << "Read sensor and collect the current value.\n";
                MeasurementStorage::readAllSensors(temp,humid,noise);
                Measurement measurement(temp,humid,noise);
                measurement_storage.addMeasurement(measurement);
                break;
            }
            case 2: {
                std::cout << "Calculate and shows the current statistics:\n";
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
                break;
            }
            case 5: {
                std::cout << "Clears the csv file.\n";
                MeasurementStorage::clearFile(filename);
                break;
            }
            case 6: {
                std::cout << "Have a nice day.";
                check = false;
                break;
            }
                default: {
                std::cout << "Wrong choice better luck next time.\n";
                break;
            }
        }

    }



    return 0;
}