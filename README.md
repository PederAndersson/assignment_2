# assignment_2 – Multi-Sensor Monitoring System

Console-based OOP project that simulates a multi-sensor environment system with real-time monitoring capabilities.
It reads values from virtual sensors, stores measurements, calculates statistics, and includes an Observer-based alarm system with CSV import/export via an interactive menu.

---

## Features

- **Object-oriented design**
  - Abstract `Sensor` base class with concrete sensors:
    - `TempSensor`
    - `HumiditySensor`
    - `NoiseSensor`
  - Design patterns implemented:
    - **Factory Pattern**: Dynamic sensor creation
    - **Observer Pattern**: Threshold-based alarm system
    - **Singleton Pattern**: Global alarm logger
  - Separation of concerns into dedicated classes for:
    - Data generation
    - Measurements & storage
    - Statistics
    - System control & orchestration
    - User interface & input validation

- **Virtual sensors**
  - Randomized sensor readings generated with `std::mt19937`
  - Configurable value ranges per sensor type:
    - Temperature: `15.0–30.0 °C`
    - Humidity: `25–85 %`
    - Noise: `15–100 dB`
  - Each sensor can have multiple threshold observers attached

- **Observer Pattern & Alarm System**
  - `IObserver` interface with `ThresholdObserver` implementation
  - Set custom upper and lower threshold limits per sensor
  - Real-time threshold breach detection
  - `Logger` singleton captures all alarm events
  - View alarm history through dedicated menu

- **Measurement handling**
  - `Measurement` stores individual sensor readings with timestamp
  - `MeasurementStorage` manages collection of all measurements
  - Functions to:
    - Add new measurements
    - Print all stored measurements
    - Thread-safe access with mutex protection

- **Real-time Data Collection**
  - Manual single-reading mode
  - Continuous background data collection using threads
  - Thread-safe operations with `std::mutex`
  - Configurable collection interval (5 seconds)
  - Start/stop collector on demand

- **Statistics**
  - `Statistics` calculates and prints:
    - Count of measurements
    - Mean
    - Min / Max
    - Variance
    - Standard deviation
  - Calculated per sensor type (temperature, humidity, noise)

- **CSV file support**
  - `SystemController::writeToFile(...)` – export stored data to `Sensor_data.csv`
  - `SystemController::readFromFile(...)` – import data from `Sensor_data.csv`
  - `SystemController::clearFile(...)` – clear CSV contents with confirmation
  - Automatic header generation

- **Interactive console interface**
  - `UserInterface` provides clear menu navigation
  - `Utils` handles input validation and terminal control
  - Comprehensive menu system:
    1. Add sensors (individual or all types)
    2. Set sensor alarms (create/check/modify thresholds)
    3. Read sensors (manual/start collector/stop collector)
    4. Calculate & show statistics
    5. Print all sensor readings
    6. File handling (write/read/clear CSV)
    7. View alarm log
    8. Exit program

---

## Requirements

- C++20 compatible compiler (e.g. `g++`, `clang++`, MSVC)
- CMake 4.0 or later
- Standard C++ library with:
  - `<random>` – random number generation
  - `<filesystem>` – file operations
  - `<iomanip>` – formatting
  - `<thread>` – multi-threading support
  - `<mutex>` – thread synchronization
  - `<atomic>` – atomic operations
  - Other standard headers

---

## Build

```bash
mkdir build
cd build

cmake ..
cmake --build .
```

This produces an executable named `assignment_2` (or `assignment_2.exe` on Windows).

---

## Run

From the `build` directory (or wherever your executable is):

```bash
./assignment_2          # Linux/Mac
assignment_2.exe        # Windows
```

### Main Menu

You'll be presented with an interactive menu:

```
=== Multi-Sensor Monitoring System ===
0. Exit
1. Add Sensors
2. Set Sensor Alarms
3. Read Sensors
4. Sensor Statistics
5. Print Sensor Values
6. File Handling
7. Alarm Log
```

### Typical Workflow

1. **Add Sensors** – Create one or more sensors (Temperature, Humidity, Noise)
2. **Set Sensor Alarms** – Define threshold limits for each sensor
3. **Read Sensors** – Either:
   - Take a single manual reading
   - Start continuous background collection (runs every 5 seconds)
4. **View Statistics** – Analyze collected data (mean, variance, etc.)
5. **Save to File** – Export measurements to CSV
6. **Check Alarm Log** – Review any threshold breaches

The system will automatically notify when sensor values exceed configured thresholds.

---

## Project Structure

```text
assignment_2/
├─ CMakeLists.txt
├─ main.cpp
└─ src/
   ├─ sensor.h / sensor.cpp              # Abstract Sensor + concrete implementations
   ├─ SensorData.h / SensorData.cpp      # Sensor configuration structs
   ├─ DataGenerator.h / DataGenerator.cpp # Random data generation
   ├─ measurement.h / measurement.cpp     # Measurement & storage classes
   ├─ statistics.h / statistics.cpp       # Statistical analysis
   ├─ Observer.h / Observer.cpp           # Observer pattern implementation
   ├─ Logger.h / Logger.cpp               # Singleton alarm logger
   ├─ SystemController.h / SystemController.cpp # Main system orchestrator
   ├─ UserInterface.h / UserInterface.cpp # Menu display
   └─ Utils.h / Utils.cpp                 # Input validation & utilities
```

Each module is focused on a single responsibility demonstrating:
- Clean object-oriented design
- SOLID principles
- Common design patterns (Factory, Observer, Singleton)
- Thread-safe concurrent operations

---

## CSV Format

Data is stored in `Sensor_data.csv` with the following format:

```csv
SENSORTYPE,ID,VALUE,UNIT,TIMESTAMP
TemperatureSensor,1,22.5,Celsius,2025-11-17 14:30:00
HumiditySensor,2,65.3,%,2025-11-17 14:30:00
NoiseSensor,3,45.8,dB,2025-11-17 14:30:00
```

---

## Architecture Highlights

### Observer Pattern
- Sensors notify attached observers when readings are taken
- `ThresholdObserver` checks if values breach configured limits
- `Logger` singleton records all alarm events for later review

### Thread Safety
- Background data collection runs in separate thread
- `std::mutex` protects shared `MeasurementStorage`
- `std::atomic<bool>` controls collector lifecycle

### Factory Pattern
- `makeSensor()` creates appropriate sensor type based on enum
- Encapsulates sensor instantiation logic

---

## Notes

- Intended as an Object-Oriented Programming course assignment
- The CSV filename is `Sensor_data.csv` and stored in the working directory
- Data collection interval: 5 seconds (configurable in `SystemController.cpp:52`)
- Sensor ranges can be adjusted in `SensorData.h` configuration structs
