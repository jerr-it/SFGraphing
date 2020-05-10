set(SFML_INCLUDE_DIR "/usr/include/")
set(SFML_LIBRARY_DIR "/usr/lib")
link_directories(${SFML_LIBRARY_DIR})
include_directories("${SFML_INCLUDE_DIR}")
set(SFML_DIR "/usr/lib/cmake/SFML/")
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if (SFML_FOUND)

    message(STATUS "SFML_INCLUDE_DIRS: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")

    include_directories(${SFML_INCLUDE_DIRS})
endif ()

set(SOURCES
        PlotDataSet.cpp
        SFPlot.cpp
        PieChartDataSet.cpp
        SFPieChart.cpp)

set(HEADERS
        PlotDataSet.h
        SFPlot.h
        PieChartDataSet.h
        SFPieChart.h)

add_library(SFGraphing ${SOURCES} ${HEADERS})
target_link_libraries(SFGraphing sfml-graphics sfml-window sfml-system)