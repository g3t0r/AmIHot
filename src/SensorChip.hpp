#ifndef SENSOR_CHIP_H
#define SENSOR_CHIP_H
#include <sensors/sensors.h>
#include <string.h>
#include <iostream>
#include <vector>
#include "TempFeature.hpp"
#include "SensorFanFeature.hpp"


class SensorChip {

  sensors_chip_name const *chip;
  void setTempAndFanFeatures();
  bool isTempFeature(sensors_feature const *);
  bool isFanFeature(sensors_feature const *);

public:
  std::vector < TempFeature > temperatureFeatures;
  std::vector < SensorFanFeature > fanFeatures;


  SensorChip(sensors_chip_name const *);
  const char * getName();
  const char * getAdapterName();



};

#endif
