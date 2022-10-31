cmake_minimum_required(VERSION 3.0)
project(graphing)

###################################################################
# Option Setting
option(ENABLE_SAMPLE "build sample program.(Default:ON)" ON)

###################################################################
# import SFML library
find_package(SFML 2.5.1 COMPONENTS system window graphics)
if (SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIRS: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif ()

###################################################################
# Configure general build settings
set(CMAKE_CXX_STANDARD 17)

###################################################################
# Configure build for SFGraphing library
file(GLOB SFGRAPHING_SRC src/*.cpp)
add_library(SFGraphing ${SFGRAPHING_SRC} )
target_link_libraries(SFGraphing PUBLIC sfml-graphics sfml-window sfml-system)
target_include_directories(SFGraphing PUBLIC include/)

###################################################################
# Configure build for Sample program
if(ENABLE_SAMPLE)
file(GLOB SAMPLE_SRC sample/*.cpp)
add_executable(graphing ${SAMPLE_SRC})
target_link_libraries(graphing SFGraphing)
endif()
