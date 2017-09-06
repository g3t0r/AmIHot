#ifndef  SENSOR_TEMPERATURE_FEATURE_HPP
#define SENSOR_TEMPERATURE_FEATURE_HPP
#include <string.h>
#include <iostream>
#include <sensors/sensors.h>
#include "SensorSubfeature.hpp"
#include "SensorAbstractFeature.hpp"

class SensorTemperatureFeature : public SensorAbstractFeature {

public:
  SensorTemperatureFeature(sensors_chip_name const *, sensors_feature const*);
  bool isCurrentValueSubfeature(SensorSubfeature);
};

#endif
