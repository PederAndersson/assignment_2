#include <iostream>
#include <limits>

#include "Utils.h"
#include "SensorData.h"

int Utils::validInput() {
    int y;
    while (true) {
        if (!(std::cin >> y)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Please input a number instead.\n";
        } else {
            return y;
        }
    }
}

std::string Utils::sensorTypeToString(SensorType type)  {
    switch (type) {
        case SensorType::TemperatureSensor:
            return "Temperature sensor";
        case SensorType::HumiditySensor:
            return "Humidity sensor";
        case SensorType::NoiseSensor:
            return "Noise sensor";
        default:
            return "Unknown";
    }
}


