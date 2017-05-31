cmake_minimum_required(VERSION 3.7)
project(mybank)

set(CMAKE_C_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES main.c defs.h)
add_executable(mybank ${SOURCE_FILES} defs.h)