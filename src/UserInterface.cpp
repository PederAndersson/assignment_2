
#include <iostream>
#include "UserInterface.h"


void UserInterface::mainMenu() {
    std::cout   << "1. Add sensor.\n"
                << "2. Set sensor alarms.\n"
                << "3. Take sensor measurements.\n"
                << "4. Print sensor statistics.\n"
                << "5. Print sensor values.\n"
                << "6. Datastorage.\n"
                << "7. Sensor alarms.\n"
                << "0. Exit.\n"
                << ">";
}

void UserInterface::fileReadingMenu() {
    std::cout   << "1. Write data to a CSV file.\n"
                << "2. Read data from a CSV file.\n"
                << "3. Clear data from CSV file.\n"
                << ">";
}

void UserInterface::statisticsMenu() {
    std::cout   << "Calculate and shows the current statistics:\n";
    std::cout   << "1. Temperature sensor\n"
                << "2. Humidity sensor\n"
                << "3. Noise sensor\n"
                << ">";
}

void UserInterface::addSensorMenu() {
    std::cout   << "Add new sensor.\n"
                << "what kind of sensor do you want to add.\n"
                << "1. Temperaturesensor.\n"
                << "2. Humiditysensor.\n"
                << "3. Noisesensor.\n"
                << "4. All sensors.\n"
                << ">";
}

void UserInterface::errorLogMenu() {
    std::cout   << "Logged sensor alarms\n";

}

void UserInterface::setSensorAlarmMenu() {
    std::cout   << "Set the alarm threshold for a given sensor.\n"
                << "which sensor \n"
                << "1. Set alarm thresholds for sensors.\n"
                << "2. Check alarm thresholds.\n"
                << "3. Set new Thresholds.\n"
                << ">";
}

void UserInterface::readSensorMenu() {
    std::cout   << "Read and take measurents from all sensors.\n"
                << "1. Take a single measurement from all sensors.\n"
                << "2. Start data collector.\n"
                << "3. Stop data collector.\n"
                << ">";
}

void UserInterface::sensorReadingsMenu() {
    std::cout << "prints all the sensor readings.\n";
}
