cmake_minimum_required(VERSION 3.19)
project(myAStar)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable(myAStar main.cpp)