#include <sensors/sensors.h>
#include "SensorSubfeature.hpp"

SensorSubfeature::SensorSubfeature(){}

SensorSubfeature::SensorSubfeature(sensors_chip_name const *chip,
                                   sensors_subfeature const *subfeature){
  this->chip = chip;
  this->subfeature = subfeature;
  this->type = &subfeature->type;
}

double SensorSubfeature::getValue(){
  double value = 0;
  sensors_get_value(chip, subfeature->number, &value);
  return value;
}

sensors_subfeature_type SensorSubfeature::getSensorType() {
  return *type;
}
