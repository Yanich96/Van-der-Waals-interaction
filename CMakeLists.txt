cmake_minimum_required(VERSION 3.10)

project(oscillator_quant)
set(CMAKE_BUILD_TYPE Release)
#set(CMAKE_BUILD_TYPE Debug)
add_subdirectory(eigen)
include_directories(eigen)
set(CMAKE_CXX_STANDARD 14)

add_executable(oscillator_quant SystemOscillators.cpp main.cpp)

target_link_libraries(oscillator_quant)