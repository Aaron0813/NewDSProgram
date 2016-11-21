cmake_minimum_required(VERSION 3.6)
project(NewDSProgram)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp preDefine.h function.cpp park.h park.cpp)
add_executable(NewDSProgram ${SOURCE_FILES})