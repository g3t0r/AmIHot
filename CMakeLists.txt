cmake_minimum_required (VERSION 2.6)
project (Amihot)
add_executable(Amihot main.cpp SensorChip.cpp SensorSubfeature.cpp
SensorTemperatureFeature.cpp SensorFanFeature.cpp  SensorAbstractFeature.cpp)
include_directories("${PROJECT_BINARY_DIR}")
find_package( Curses REQUIRED )
find_library(LM_SENSORS libsensors.so /usr/lib)
include_directories( ${CURSES_INCLUDE_DIRS} )
target_link_libraries( Amihot ${CURSES_LIBRARIES} ${LM_SENSORS})

