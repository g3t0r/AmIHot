#ifndef  SENSOR_FAN_FEATURE_HPP
#define SENSOR_FAN_FEATURE_HPP
#include <string.h>
#include <iostream>
#include <sensors/sensors.h>
#include "SensorSubfeature.hpp"
#include "SensorAbstractFeature.hpp"

class SensorFanFeature : public SensorAbstractFeature{

public:
  SensorFanFeature(sensors_chip_name const *, sensors_feature const*);
  bool isCurrentValueSubfeature(SensorSubfeature);
};

#endif
