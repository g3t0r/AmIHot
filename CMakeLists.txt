cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_STANDARD 11)
project(amihot)
add_executable(amihot
  src/main.cpp
  src/SensorChip.cpp
  src/SensorSubfeature.cpp
  src/TempFeature.cpp
  src/SensorFanFeature.cpp
  src/SensorAbstractFeature.cpp
  src/ChipGetter.cpp
  src/Graph.cpp
  src/TempFeatureWin.cpp
  src/ChipWindow.cpp
  src/ChipSetter.cpp
  src/HelpWindow.cpp
)

find_package(Curses REQUIRED)
find_library(LM_SENSORS libsensors.so /usr/lib)
find_library(LIBTINFO libtinfo.so /usr/lib)
include_directories(${CURSES_INCLUDE_DIRS} ${PROJECT_BINARY_DIR})
target_link_libraries(amihot ${CURSES_LIBRARIES} ${LM_SENSORS} ${LIBTINFO})
install(TARGETS amihot DESTINATION /usr/bin/)
