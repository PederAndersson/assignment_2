#include <filesystem>
#include <fstream>
#include <iostream>
#include <mutex>

#include "SystemController.h"

#include "DataGenerator.h"
#include "Logger.h"
#include "statistics.h"
#include "UserInterface.h"
#include "Utils.h"
#include "Observer.h"
#include "sensor.h"


std::unique_ptr<Sensor> makeSensor(SensorType type)
{
    TempConfig tcgf;
    HumidConfig hcfg;
    NoiseConfig ncfg;
    switch (type) {
        case SensorType::TemperatureSensor: return std::make_unique<TempSensor>(Utils::validInput(1,10),tcgf);
        case SensorType::HumiditySensor: return  std::make_unique<HumiditySensor>(Utils::validInput(1,10),hcfg);
        case SensorType::NoiseSensor: return  std::make_unique<NoiseSensor>(Utils::validInput(1,10),ncfg);
        default : return nullptr;
    }
}
std::mutex datamutex;
void SystemController::addMeasurements(const std::vector<std::unique_ptr<Sensor>>& sensors) const {
    std::unique_lock datalock(datamutex);
    if (sensors.empty()) {
        std::cout << "No sensors to read.";
        return;
    }
    for (const auto& s : sensors) {
        Measurement m;
        m.type_ = s->getSensorbase().type_;
        m.id_ = s->getSensorbase().id_;
        m.value_ = s->read();
        m.unit_ = s->getSensorbase().unit_;
        m.timestamp_ = DataGenerator::generateTimeStamp();
        s->notifyAll(m,m.value_);
        measurements_.addMeasurement(m);
    }
    datalock.unlock();
}

void SystemController::runCollector(const std::atomic<bool> &is_data_collecting, const std::vector<std::unique_ptr<Sensor> >& sensors) const {
    while (is_data_collecting) {
        addMeasurements(sensors);
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}


void SystemController::addSensor() {
    int choice = Utils::validInput(1,4);
    switch (static_cast<SensorType>(choice)) {
        case SensorType::TemperatureSensor:
            std::cout << "Please enter the sensor Id: ";
            this->sensors_.emplace_back(makeSensor(SensorType::TemperatureSensor));
            break;
        case SensorType::HumiditySensor:
            std::cout << "Please enter the sensor Id: ";
            this->sensors_.emplace_back(makeSensor(SensorType::HumiditySensor));
            break;
        case SensorType::NoiseSensor:
            std::cout << "Please enter the sensor Id: ";
            this->sensors_.emplace_back(makeSensor(SensorType::NoiseSensor));
            break;
        case SensorType::All:
            std::cout << "Please enter the temperature sensor Id: ";
            this->sensors_.emplace_back(makeSensor(SensorType::TemperatureSensor));
            std::cout << "Please enter the humidity sensor Id: ";
            this->sensors_.emplace_back(makeSensor(SensorType::HumiditySensor));
            std::cout << "Please enter the noise sensor Id: ";
            this->sensors_.emplace_back(makeSensor(SensorType::NoiseSensor));
            break;
        }
}


void SystemController::makeObservers(const std::vector<std::unique_ptr<Sensor>>& sensors) {

    for (const auto& s : sensors) {
        std::cout   << "Set new thresholds observers.\n";
        std::cout   << "1. Set upper and lower threshold.\n"
                    << "2. Set upper Threshold.\n"
                    << "3. Set lower Threshold.\n"
                    << ">";
        switch (Utils::validInput(1,3)) {
            case 1: {
                std::cout   << "Set the " << Utils::sensorTypeToString(s->getSensorbase().type_) << " alarm interval between "
                << s->getSensorbase().interval_.min_ << " and " << s->getSensorbase().interval_.max_ << "\n";
                std::cout << "Please input the lower value then upper.\n" << ">";

                auto obs = std::make_unique<ThresholdObserver>(
                Utils::validFloatInput(),
                Utils::validFloatInput()
                );
                s->addObserver(std::move(obs));
                break;
            }
            case 2: {
                std::cout   << "Set the upper threshold for " << Utils::sensorTypeToString(s->getSensorbase().type_) << " alarm "
                << s->getSensorbase().interval_.max_ << "\n";
                std::cout << "Please input the upper value.\n" << ">";

                auto obs = std::make_unique<ThresholdObserver>(Utils::validFloatInput(),Bound::upper);
                s->addObserver(std::move(obs));
                break;
            }
            case 3: {
                std::cout   << "Set the lower threshold for " << Utils::sensorTypeToString(s->getSensorbase().type_) << " alarm "
                << s->getSensorbase().interval_.min_ << "\n";
                std::cout << "Please input the upper value.\n" << ">";

                auto obs = std::make_unique<ThresholdObserver>(Utils::validFloatInput(),Bound::lower);
                s->addObserver(std::move(obs));
                break;
            }
            default: std::cout << "donkey!\n";
        }
    }

}

void SystemController::checkObservers(const std::vector<std::unique_ptr<Sensor> > &sensors) {
    std::cout << "Checks the current observer settings.\n";

    for (const auto& s : sensors) {
        std::cout << Utils::sensorTypeToString(s->getSensorbase().type_) << "\n";

        const auto& observers = s->getObservers();

        if (observers.empty()) {
            std::cout << "  No observers set.\n";
            continue;
        }

        for (const auto& obs : observers) {
            MinMax t = obs->getThreshold();
            std::cout << "  Lower threshold: " << t.lower_
                      << "  Upper threshold: " << t.upper_ << "\n";
        }
    }
}

void SystemController::setObservers(const std::vector<std::unique_ptr<Sensor> > &sensors) {
    std::cout << "Changes the current observer settings.\n";
    for (const auto& s : sensors) {
        std::cout   << Utils::sensorTypeToString(s->getSensorbase().type_) << "\n";
        s->setObserver();
    }
}


void SystemController::writeToFile(const std::string& filename, const MeasurementStorage& data)  {
    std::ofstream myFile;
    myFile.open(filename,std::ios::app | std::ios::out);
    if (!myFile.is_open()) { //checks if you have the right filename
        std::cerr << "Error" << filename << " not found";
        return;
    }
    if (!std::filesystem::exists(filename) || std::filesystem::file_size(filename) == 0) { //writes header if the file is empty
        myFile << "SENSORTYPE" << "," << "ID" << "," << "VALUE" << "," << "UNIT" << "," << "TIMESTAMP" << "\n";
    }
    if (!data.getMeasurementStorage().empty()) { // checks if the vector is empty
        for (const auto& sensor : data.getMeasurementStorage()) {
            myFile  << Utils::sensorTypeToString(sensor.type_) << "," << sensor.id_ << ","
                    << sensor.value_ << "," << sensor.unit_ << "," << sensor.timestamp_ << "\n";
        }
    } else {
        std::cout << "Sensor data is empty" << "\n";
    }

    myFile.close();
    std::cout << "Data saved to file\n";
}

void SystemController::readFromFile(const std::string& filename, MeasurementStorage& data) {
    std::fstream myFile;
    myFile.open(filename, std::ios::in);

    if (!myFile.is_open()) {
        std::cerr << filename << " not found.\n";
        return;
    }

    if (myFile.peek() == std::ifstream::traits_type::eof()) {
        std::cout << filename << " is empty.\n";
        return;
    }

    std::string line;
    std::getline(myFile, line); // Skip header


    while (std::getline(myFile, line)) {
        if (line.empty()) continue;

        auto measurement = Measurement::fromCsvString(line);
        data.addMeasurement(measurement);
    }

    myFile.close();

    std::cout << "Data retrieved.\n";
}

void SystemController::clearFile(const std::string& filename) {
    std::cout << "Are you sure you want to delete the data?\n";
    std::cout << "1.Yes \t 2.No :";
    int choice = 0;
    std::cin >> choice;
    if (choice == 1) {
        std::fstream myFile;
        myFile.open(filename, std::ofstream::out | std::ofstream::trunc);
        myFile.flush();
        myFile.close();
        std::cout << "Data cleared.\n";
    } else {
        std::cout << "Data not cleared, have a nice day.\n";
    }
}




void SystemController::run() {
    std::atomic<bool> is_running = true;
    std::atomic<bool> is_datacollecting = false;
    std::thread collector;
    const std::string filename = "Sensor_data.csv";
    while (is_running == true) {
        if (is_datacollecting == true) {
            std::cout << "\033[31mDatacollector is running.\033[0m\n";
        }
        UserInterface::mainMenu();
        int menu_choice = Utils::validInput(0,7);
        switch (static_cast<UserMenu>(menu_choice)) {
            case UserMenu::AddSensors: {
                UserInterface::addSensorMenu();
                addSensor();
                Utils::awaitResponse();
                Utils::clearTerminal();
                break;
            }
            case UserMenu::SetSensoralarms: {
                UserInterface::setSensorAlarmMenu();
                switch (Utils::validInput(1,3)) {
                    case 1: {

                        makeObservers(sensors_);
                        Utils::awaitResponse();
                        Utils::clearTerminal();
                        break;
                    }
                    case 2: {
                        checkObservers(sensors_);
                        Utils::awaitResponse();
                        Utils::clearTerminal();
                        break;
                    }
                    case 3: {
                        setObservers(sensors_);
                        Utils::awaitResponse();
                        Utils::clearTerminal();
                        break;
                    }
                    default: {
                        std::cout << "DONKEY!!";
                    }
                }
                break;
            }
            case UserMenu::ReadSensors: {
                UserInterface::readSensorMenu();
                switch (Utils::validInput(1,3)) {
                    case 1: {
                        std::cout << "Measurement collected.\n";
                        addMeasurements(sensors_);
                        Utils::awaitResponse();
                        Utils::clearTerminal();
                        break;
                    }
                    case 2: {
                        std::cout << "Data collector started.\n";
                        if (sensors_.empty()) {
                            std::cout << "No sensors active.\n";
                        }
                        else if (!is_datacollecting && !collector.joinable()) {
                        is_datacollecting = true;
                        collector = std::thread(&SystemController::runCollector,
                            this,
                            std::ref(is_datacollecting),
                            std::ref(sensors_));
                        } else {
                            std::cout << "Collector is running.\n";
                        }
                        Utils::awaitResponse();
                        Utils::clearTerminal();
                        break;
                    }
                    case 3: {
                        std::cout << "Data collector stopping \n";
                        is_datacollecting = false;
                        if (collector.joinable()){collector.join();}
                        Utils::awaitResponse();
                        Utils::clearTerminal();
                        break;
                    }
                    default: std::cout << "wrooooong\n";
                }
                break;
            }
            case UserMenu::SensorStatistics: {
                UserInterface::statisticsMenu();
                Statistics statistics(measurements_);
                statistics.printStatistics();
                Utils::awaitResponse();
                Utils::clearTerminal();
                break;
            }
            case UserMenu::PrintSensorValues: {
                UserInterface::sensorReadingsMenu();
                measurements_.printAllSensors();
                Utils::awaitResponse();
                Utils::clearTerminal();
            break;
            }
            case UserMenu::FileHandling: {
                UserInterface::fileReadingMenu();
                switch (Utils::validInput(1,3)) {
                    case 1: {
                        std::cout << "Writes data to a csv file.\n";
                        writeToFile(filename,measurements_);
                        Utils::awaitResponse();
                        Utils::clearTerminal();
                        break;
                    }
                    case 2: {
                        std::cout << "Reads data fom a csv file.\n";
                        readFromFile(filename,measurements_);
                        Utils::awaitResponse();
                        Utils::clearTerminal();
                        break;
                    }
                    case 3: {
                        std::cout << "Clears the csv file.\n";
                        clearFile(filename);
                        Utils::awaitResponse();
                        Utils::clearTerminal();
                        break;
                    }
                    default: {
                        std::cout << "Wrong choice better luck next time.\n";
                        Utils::awaitResponse();
                        Utils::clearTerminal();
                        break;
                    }
                }
                break;
            }
            case UserMenu::AlarmLog: {
                UserInterface::errorLogMenu();
                Logger::instance().printAlarms();
                Utils::awaitResponse();
                Utils::clearTerminal();

                break;
            }
            case UserMenu::Exit: {
                std::cout << "have a nice day!\n";
                Utils::awaitResponse();
                is_running = false;
                break;
            }
            default: {
                std::cout << "Wrong choice better luck next time.\n";
                Utils::awaitResponse();
                Utils::clearTerminal();
                break;
            }
        }

    }
}

