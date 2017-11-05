cmake_minimum_required (VERSION 2.6)
project (amihot)
add_executable(amihot
  main.cpp
  SensorChip.cpp
  SensorSubfeature.cpp
  TempFeature.cpp
  SensorFanFeature.cpp
  SensorAbstractFeature.cpp
  ChipGetter.cpp
  Graph.cpp
  TempFeatureWin.cpp
  ChipWindow.cpp
  ChipSetter.cpp
  HelpWindow.cpp

  )

find_package( Curses REQUIRED )
find_library(LM_SENSORS libsensors.so /usr/lib)
find_library(LIBTINFO libtinfo.so /usr/lib )
include_directories( ${CURSES_INCLUDE_DIRS} ${PROJECT_BINARY_DIR})
target_link_libraries( amihot ${CURSES_LIBRARIES} ${LM_SENSORS} ${LIBTINFO} )
install(TARGETS amihot DESTINATION /usr/bin/)


