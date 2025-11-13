#include <iomanip>
#include <iostream>
#include <filesystem>
#include <memory>

#include "src/sensor.h"
#include "src/measurement.h"
#include "src/statistics.h"
#include "src/UserInterface.h"
#include "src/Utils.h"

std::unique_ptr<Sensor> makeSensor(SensorType type)
{
    TempConfig tcgf;
    HumidConfig hcfg;
    NoiseConfig ncfg;
    switch (type) {
        case SensorType::TemperatureSensor: return std::make_unique<TempSensor>(1,tcgf);
        case SensorType::HumiditySensor: return  std::make_unique<HumiditySensor>(2,hcfg);
        case SensorType::NoiseSensor: return  std::make_unique<NoiseSensor>(3,ncfg);
        default : return nullptr;
    }
}

namespace fs = std::filesystem;

int main() {

    std::vector<std::unique_ptr<Sensor>> sensors;
    sensors.emplace_back(makeSensor(SensorType::TemperatureSensor));
    sensors.emplace_back(makeSensor(SensorType::HumiditySensor));
    sensors.emplace_back(makeSensor(SensorType::NoiseSensor));

    MeasurementStorage measurement_storage; //vector for sensor data
    std::cout << std::fixed << std::setprecision(2);
    const std::string filename = "Sensor_data.csv";
    bool run = true;
    while (run == true) {
    UserInterface::printMenu();

        switch (Utils::validInput(0,7)) {
            case 1: {
                std::cout << "Read sensor and collect the current value.\n";
                measurement_storage.takeMeasurements(sensors);
                break;
            }
            case 2: {
                std::cout   << "Calculate and shows the current statistics:\n";
                std::cout   << "1. Temperature sensor\n"
                            << "2. Humidity sensor\n"
                            << "3. Noise sensor\n"
                            << ">";
                Statistics stats(measurement_storage);
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
                switch (Utils::validInput(0,3)) {
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
                run = false;
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