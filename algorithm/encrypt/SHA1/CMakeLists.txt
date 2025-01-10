cmake_minimum_required(VERSION 3.19)
project(mySHA1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable(mySHA1 main.cpp sha1.cpp)