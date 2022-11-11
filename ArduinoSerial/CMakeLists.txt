cmake_minimum_required(VERSION 3.17)
project(ArduinoSerial)

set(CMAKE_CXX_STANDARD 14)


add_executable(ArduinoSerial main.cpp ArduinoInterface.h)
