#ifndef SENSOR_CHIP_H
#define SENSOR_CHIP_H
#include <sensors/sensors.h>
#include <string.h>
#include <iostream>
#include <vector>
#include "SensorTemperatureFeature.hpp"
#include "SensorFanFeature.hpp"


class SensorChip {

  sensors_chip_name const *chip;
  void setTempAndFanFeatures();
  bool isTempFeature(sensors_feature const *);
  bool isFanFeature(sensors_feature const *);

public:
  std::vector < SensorTemperatureFeature > temperatureFeatures;
  std::vector < SensorFanFeature > fanFeatures;


  SensorChip(sensors_chip_name const *);
  std::string getName();
  std::string getAdapterName();



};

#endif
