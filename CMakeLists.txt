cmake_minimum_required(VERSION 4.0)
project(assignment_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(assignment_2 main.cpp
        sensor.cpp
        sensor.h
        measurement.cpp
        measurement.h
        DataGenerator.cpp
        DataGenerator.h
        SensorData.cpp
        SensorData.h
        Statistics.cpp
        Statistics.h)
