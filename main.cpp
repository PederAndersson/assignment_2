#include <iostream>

#include "sensor.h"
#include <windows.h>
int main() {
SetConsoleOutputCP(CP_UTF8);

    TempSensor sensor1;
    HumiditySensor sensor2;
    AirqualitySensor sensor3;
    sensor1.read();
    sensor2.read();
    sensor3.read();

    return 0;
}
