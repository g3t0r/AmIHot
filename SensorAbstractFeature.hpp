#ifndef SENSOR_ABSTRACT_FEATURE
#define SENSOR_ABSTRACT_FEATURE
#include <sensors/sensors.h>
#include "SensorSubfeature.hpp"

class SensorAbstractFeature {
protected:
  sensors_chip_name const *chip;
  sensors_feature const *feature;
  sensors_feature_type const *type;
  SensorSubfeature currentValueSubfeature;
  void setCurrentValueSubfeature();
public:
  SensorAbstractFeature(sensors_chip_name const *, sensors_feature const *);
  virtual bool isCurrentValueSubfeature(SensorSubfeature) = 0;
  double getValue();
  std::string getName();
};

#endif
