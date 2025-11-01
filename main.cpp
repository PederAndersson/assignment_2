#include <iomanip>
#include <iostream>
#include <windows.h>
#include "sensor.h"
#include "DataGenerator.h"

int main() {
SetConsoleOutputCP(CP_UTF8);
    std::cout << std::fixed << std::setprecision(2);
    DataGenerator data;
    TempSensor tempsens1(data,1);
    HumiditySensor humsens1(data,1);
    AirqualitySensor airsens1(data,1);

    tempsens1.read();
    humsens1.read();
    airsens1.read();


    return 0;
}
