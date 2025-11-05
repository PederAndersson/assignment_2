#include <iomanip>
#include <iostream>
#include "sensor.h"
#include "DataGenerator.h"
#include "measurement.h"
#include "statistics.h"
#include <filesystem>
namespace fs = std::filesystem;

int main() {
    std::cout << std::fixed << std::setprecision(2);
    const std::string filename = "Sensor_data.csv";
    /*std::cout << "Nuvarande arbetskatalog: "
          << fs::current_path() << std::endl;*/

    DataGenerator gen;
    MeasurementStorage measurement_storage;
    Statistics stats;
    /*auto temp1 = SensorFactory::generateTempData(gen,1);
    auto humid1 = SensorFactory::generateHumidityData(gen,1);
    auto noise1 = SensorFactory::generateNoiseData(gen,1);
    for (int i = 0; i < 2; i++) {
        temp1.read();
        humid1.read();
        noise1.read();
    Measurement measurement(temp1, humid1,noise1);
    measurement_storage.addMeasurement(measurement);
    }*/

    //MeasurementStorage::writeToFile(filename,measurement_storage);
    MeasurementStorage::readFromFile(filename,measurement_storage);
    measurement_storage.printAll();
    stats.calculateStatistics(stats,measurement_storage);
    stats.printStatistics();
    return 0;
}