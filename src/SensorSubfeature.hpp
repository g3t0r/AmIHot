#ifndef SENSOR_SUBFEATURE_HPP
#define SENSOR_SUBFEATURE_HPP
#include <string.h>
#include <iostream>
#include <sensors/sensors.h>

class SensorSubfeature {
  sensors_subfeature const *subfeature;
  sensors_chip_name const *chip;
  sensors_subfeature_type const *type;

public:
  SensorSubfeature();
  SensorSubfeature(sensors_chip_name const *, sensors_subfeature const  *);
  double getValue();
  sensors_subfeature_type getSensorType();

};

#endif
