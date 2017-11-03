cmake_minimum_required (VERSION 2.6)
project (Amihot)
add_executable(Amihot
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

  )

find_package( Curses REQUIRED )
find_package(Threads)
find_library(LM_SENSORS libsensors.so /usr/lib)
find_library(LIBTINFO libtinfo.so.6 /usr/lib )
include_directories( ${CURSES_INCLUDE_DIRS} ${PROJECT_BINARY_DIR})
target_link_libraries( Amihot ${CURSES_LIBRARIES} ${LM_SENSORS} ${LIBTINFO} ${CMAKE_THREAD_LIBS_INIT})

