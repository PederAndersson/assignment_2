#include <iostream>
#include <limits>

#include "Utils.h"

#include "measurement.h"
#include "sensor.h"
#include "SensorData.h"

int Utils::validInput(int min, int max) {
    int number;
    std::cout << "> ";
    while (!(std::cin >> number) || number < min || number > max) {

        std::cin.clear(); // Clear error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                        '\n'); // Flush bad input
    }
    return number;
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

SensorType Utils::stringToType(std::string &line) {
    if (line == "Temperature sensor") {
        return SensorType::TemperatureSensor;
    }
    if (line == "Humidity sensor") {
        return SensorType::HumiditySensor;
    }
    if (line == "Noise sensor") {
        return SensorType::NoiseSensor;
    }
}

