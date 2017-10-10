#ifndef TEMP_FEATURE_HPP
#define TEMP_FEATURE_HPP
#include <string.h>
#include <iostream>
#include <sensors/sensors.h>
#include "SensorSubfeature.hpp"
#include "SensorAbstractFeature.hpp"

class TempFeature : public SensorAbstractFeature {

public:
  TempFeature(sensors_chip_name const *, sensors_feature const*);
  bool isCurrentValueSubfeature(SensorSubfeature);
};

#endif
