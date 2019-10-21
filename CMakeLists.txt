cmake_minimum_required(VERSION 3.15)
project(GameLife)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

add_executable(GameLife main.cpp)