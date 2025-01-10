cmake_minimum_required(VERSION 3.19)
project(myMD5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_executable(myMD5 main.cpp md5.cpp)