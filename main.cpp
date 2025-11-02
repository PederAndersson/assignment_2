#include <iomanip>
#include <iostream>
#include <windows.h>
#include "sensor.h"
#include "DataGenerator.h"
#include "measurement.h"

int main() {
SetConsoleOutputCP(CP_UTF8);
    std::cout << std::fixed << std::setprecision(2);
    DataGenerator gen;
    auto temp1 = SensorFactory::makeTemp(gen,1);
    auto humid1 = SensorFactory::makeHumidity(gen,1);
    auto noise1 = SensorFactory::makeNoise(gen,1);

    temp1.read();
    humid1.read();
    noise1.read();



    return 0;
}
