cmake_minimum_required(VERSION 3.4)
project(do_an_cuoi_ky)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp libs/template.h libs/read_csv.h libs/memory.h libs/template.h)
add_executable(do_an_cuoi_ky ${SOURCE_FILES})