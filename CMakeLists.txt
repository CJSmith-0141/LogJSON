cmake_minimum_required (VERSION 3.10)
project(LogJSON VERSION 0.0.1
        DESCRIPTION "cpp library for logging using Java Script Object Notation"
        LANGUAGES CXX)
    
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
include_directories(.)
include_directories(./include)
include_directories(./examples)
include_directories(./lib)

add_executable(streamouttest examples/StreamOut.cpp examples/StreamOut.h)

