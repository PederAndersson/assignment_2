//
// Created by peder on 2025-11-05.
//

#ifndef ASSIGNMENT_2_USERINTERFACE_H
#define ASSIGNMENT_2_USERINTERFACE_H

enum class UserMenu{ ReadSensor, SensorStatistics, PrintSensorValues, WriteToFile, ReadFromFile, Exit };

class UserInterface {
private:

public:
    void printMenu() const;

};


#endif //ASSIGNMENT_2_USERINTERFACE_H