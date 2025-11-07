#include <iostream>
#include "UserInterface.h"

void UserInterface::printMenu() {
std::cout   << "1. Read sensor.\n"
            << "2. Sensor statistics.\n"
            << "3. Print sensor values.\n"
            << "4. Write/Read CSV file.\n"
            << "5. Clear CSV file.\n"
            << "6. Exit.\n"
            << ">";
}

void UserInterface::printFileReadingMenu() {
    std::cout   << "1. Write data to a CSV file.\n"
                << "2. Read data from a CSV file.\n";
}
