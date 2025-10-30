cmake_minimum_required(VERSION 4.0)
project(assignment_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(assignment_2 main.cpp
        sensor.cpp
        sensor.h
        measurement.cpp
        measurement.h
        utility.cpp
        utility.h
        file_handling.cpp
        file_handling.h)
