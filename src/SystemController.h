#ifndef ASSIGNMENT_2_SYSTEMCONTROLLER_H
#define ASSIGNMENT_2_SYSTEMCONTROLLER_H

#include <vector>
#include <memory>
#include <thread>
#include <atomic>

#include "SensorData.h"
#include "measurement.h"
#include "sensor.h"
enum class SensorType;


enum class UserMenu {
    Exit = 0,
    AddSensors,
    SetSensoralarms,
    ReadSensors,
    SensorStatistics,
    PrintSensorValues,
    FileHandling,
    AlarmLog
};



std::unique_ptr<Sensor> makeSensor(SensorType type);

class SystemController {
private:
    std::vector<std::unique_ptr<Sensor>> sensors_;
    MeasurementStorage& measurements_;



public:
    explicit SystemController(MeasurementStorage& measurement_storage) : measurements_(measurement_storage){ }

    void run();
    void addMeasurements(const std::vector<std::unique_ptr<Sensor>>& sensors) const;
    void runCollector(const std::atomic<bool> & is_data_collecting, const std::vector<std::unique_ptr<Sensor>>& sensors) const;
    void addSensor();
    static void makeObservers(const std::vector<std::unique_ptr<Sensor>>& sensors);
    static void checkObservers(const std::vector<std::unique_ptr<Sensor>>& sensors);
    static void setObservers(const std::vector<std::unique_ptr<Sensor>>& sensors);
    static void writeToFile(const std::string& filename, const MeasurementStorage& data);
    static void readFromFile(const std::string& filename, MeasurementStorage& data);
    static void clearFile(const std::string& filename);


};


#endif //ASSIGNMENT_2_SYSTEMCONTROLLER_H