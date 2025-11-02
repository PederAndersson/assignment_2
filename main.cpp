#include <iomanip>
#include <iostream>
#include "sensor.h"
#include "DataGenerator.h"
#include "measurement.h"

int main() {

    std::cout << std::fixed << std::setprecision(2);
    DataGenerator gen;
    Measurement data;
    auto temp1 = SensorFactory::generateTempdata(gen,1);
    auto humid1 = SensorFactory::generateHumiditydata(gen,1);
    auto noise1 = SensorFactory::generateNoisedata(gen,1);

    data.addMeasurement(temp1,humid1,noise1);


    data.printAll();



    return 0;
}
