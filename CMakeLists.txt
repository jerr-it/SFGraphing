cmake_minimum_required(VERSION 3.15)
project(graphing)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(SFGraphing)
add_executable(graphing main.cpp)
target_link_libraries(graphing SFGraphing)