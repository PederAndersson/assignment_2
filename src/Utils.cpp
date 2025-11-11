#include <iostream>
#include <limits>

#include "Utils.h"
#include "SensorData.h"

int Utils::validInput() {
    int input;
    while (true) {
        if (!(std::cin >> input)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Please input a number instead.\n";
        } else {
            return input;
        }
    }
}
float Utils::validFloatInput() {
    float input;
    while (true) {
        if (!(std::cin >> input)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            std::cout << "Please input a number instead.\n";
        } else {
            return input;
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


