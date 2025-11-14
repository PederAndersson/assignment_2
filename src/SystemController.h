#ifndef ASSIGNMENT_2_SYSTEMCONTROLLER_H
#define ASSIGNMENT_2_SYSTEMCONTROLLER_H

#include <vector>
#include <memory>
#include "SensorData.h"
#include "measurement.h"
class Sensor;


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

inline std::unique_ptr<Sensor> makeSensor(SensorType type)
{
    TempConfig tcgf;
    HumidConfig hcfg;
    NoiseConfig ncfg;
    switch (type) {
        case SensorType::TemperatureSensor: return std::make_unique<TempSensor>(1,tcgf);
        case SensorType::HumiditySensor: return  std::make_unique<HumiditySensor>(2,hcfg);
        case SensorType::NoiseSensor: return  std::make_unique<NoiseSensor>(3,ncfg);
        default : return nullptr;
    }
}


class SystemController {
private:
    std::vector<std::unique_ptr<Sensor>> sensors_;
    MeasurementStorage& measurements_;
    //threshold

public:
    SystemController(MeasurementStorage& measurement_storage) : measurements_(measurement_storage){ }

    void run();
    void addMesurements(const std::vector<std::unique_ptr<Sensor>>& sensors) const;
    void addSensor(std::vector<std::unique_ptr<Sensor>>& sensors);
    static void writeToFile(const std::string& filename, const MeasurementStorage& data);
    static void readFromFile(const std::string& filename, MeasurementStorage& data);
    static void clearFile(const std::string& filename);


};


#endif //ASSIGNMENT_2_SYSTEMCONTROLLER_H