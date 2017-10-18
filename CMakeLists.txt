cmake_minimum_required (VERSION 2.6)
project (Amihot)
add_executable(Amihot main.cpp SensorChip.cpp SensorSubfeature.cpp
TempFeature.cpp SensorFanFeature.cpp  SensorAbstractFeature.cpp ChipGetter.cpp Graph.cpp TempFeatureWin.cpp ChipWindow.cpp )

find_package( Curses REQUIRED )
find_library(LM_SENSORS libsensors.so /usr/lib)
include_directories( ${CURSES_INCLUDE_DIRS} ${PROJECT_BINARY_DIR})
target_link_libraries( Amihot ${CURSES_LIBRARIES} ${LM_SENSORS})

