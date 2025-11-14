cmake_minimum_required(VERSION 4.0)
project(assignment_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(assignment_2 main.cpp
        src/sensor.cpp
        src/sensor.h
        src/measurement.cpp
        src/measurement.h
        src/DataGenerator.cpp
        src/DataGenerator.h
        src/SensorData.cpp
        src/SensorData.h
        src/statistics.cpp
        src/statistics.h
        src/SystemController.cpp
        src/SystemController.h
        src/Utils.cpp
        src/Utils.h
        src/UserInterface.cpp
        src/UserInterface.h
)