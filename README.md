# assignment_2 – Multi-Sensor Monitoring System

Console-based OOP project that simulates a small multi-sensor environment system.  
It reads values from three virtual sensors, stores measurements, calculates basic statistics, and supports CSV import/export via a simple text menu.

---

## Features

- **Object-oriented design**
  - Abstract `Sensor` base class with concrete sensors:
    - `TempSensor`
    - `HumiditySensor`
    - `NoiseSensor`
  - Separation of concerns into dedicated classes for:
    - Data generation
    - Measurements & storage
    - Statistics
    - User interface & input validation

- **Virtual sensors**
  - Randomized sensor readings generated with `std::mt19937`
  - Configurable value ranges:
    - Temperature: `15.0–30.0 °C`
    - Humidity: `25–85 %`
    - Noise: `15–100 dB`

- **Measurement handling**
  - `Measurement` groups one reading from each sensor.
  - `MeasurementStorage` keeps a collection of measurements.
  - Functions to:
    - Add new measurements
    - Print all stored measurements

- **Statistics**
  - `Statistics` calculates and prints:
    - Number of measurements
    - Mean
    - Min / Max
    - Variance
    - Standard deviation
  - Calculated separately for temperature, humidity, and noise.

- **CSV file support**
  - `MeasurementStorage::writeToFile(...)` – export stored data to `Sensor_data.csv`
  - `MeasurementStorage::readFromFile(...)` – import data from `Sensor_data.csv`
  - `MeasurementStorage::clearFile(...)` – clear CSV contents

- **Console user interface**
  - `UserInterface` prints menus
  - `Utils::validInput()` validates numeric input
  - Loop-based menu to control:
    1. Read sensors & store measurement
    2. Calculate & show statistics
    3. Print current sensor data
    4. Write/read CSV file
    5. Clear CSV file
    6. Exit program

---

## Requirements

- C++20 compatible compiler (e.g. `g++`, `clang++`, MSVC)
- CMake (version as specified in `CMakeLists.txt`)
- Standard C++ library with:
  - `<random>`
  - `<filesystem>`
  - `<iomanip>`
  - and other standard headers used in the project

---

## Build

```bash
git clone https://github.com/PederAndersson/assignment_2.git
cd assignment_2

mkdir build
cd build

cmake ..
cmake --build .
```

This produces an executable named `assignment_2`.

---

## Run

From the `build` directory (or wherever your executable is):

```bash
./assignment_2
```

You’ll be presented with a text-based menu similar to:

1. Read sensor and store current values  
2. Calculate and show statistics  
3. Print all stored sensor values  
4. File options (write/read CSV)  
5. Clear CSV file  
6. Exit  

Follow the prompts to generate measurements, inspect statistics, and manage CSV data.

---

## Project Structure

```text
assignment_2/
├─ CMakeLists.txt
├─ main.cpp
└─ src/
   ├─ sensor.h / sensor.cpp
   ├─ SensorData.h / SensorData.cpp
   ├─ DataGenerator.h / DataGenerator.cpp
   ├─ measurement.h / measurement.cpp
   ├─ statistics.h / statistics.cpp
   ├─ UserInterface.h / UserInterface.cpp
   └─ Utils.h / Utils.cpp
```

Each module is focused on a single responsibility to demonstrate clean, object-oriented design for the assignment.

---

## Notes

- Intended as an Object-Oriented Programming course assignment.
- The CSV filename is currently hard-coded as `Sensor_data.csv` in `main.cpp`.
- Behavior and ranges can be adjusted in the corresponding header/source files as needed.
