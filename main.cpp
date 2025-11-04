#include <iomanip>
#include <iostream>
#include "sensor.h"
#include "DataGenerator.h"
#include "measurement.h"
#include "statistics.h"

int main() {

    std::cout << std::fixed << std::setprecision(2);
    DataGenerator gen;
    MeasurementStorage measurement_storage;
        auto temp1 = SensorFactory::generateTempData(gen,1);
        auto humid1 = SensorFactory::generateHumidityData(gen,1);
        auto noise1 = SensorFactory::generateNoiseData(gen,1);

    for (int i = 0; i < 5; i++) {
        temp1.read();
        humid1.read();
        noise1.read();
        Measurement measurement(temp1, humid1,noise1);
        measurement_storage.addMeasurement(measurement);
    }

    measurement_storage.printAll();
    return 0;
}