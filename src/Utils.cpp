#include "Utils.h"

#include <iostream>
#include <limits>


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

