cmake_minimum_required(VERSION 3.15)
project(sfplot)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

add_subdirectory(SFPlot)

add_executable(sfplot main.cpp)
target_link_libraries(sfplot SFPlot)
