cmake_minimum_required(VERSION 3.8)
project(1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        bigDecimal.cpp
        bigDecimal.h
        main.cpp)

add_executable(1 ${SOURCE_FILES})