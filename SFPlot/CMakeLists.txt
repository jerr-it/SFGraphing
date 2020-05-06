set(SFML_INCLUDE_DIR "/usr/include/")
set(SFML_LIBRARY_DIR "/usr/lib")
link_directories("/usr/lib")
include_directories("/usr/include/")
set(SFML_DIR "/usr/lib/cmake/SFML/")
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)

    message(STATUS "SFML_INCLUDE_DIRS: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")

    include_directories(${SFML_INCLUDE_DIRS})

endif()

set(SOURCES 
    DataSet.cpp
    SFPlot.cpp)
    
set(HEADERS
    DataSet.h
    SFPlot.h)
    
add_library(SFPlot ${SOURCES} ${HEADERS})
target_link_libraries (SFPlot sfml-graphics sfml-window sfml-system)
