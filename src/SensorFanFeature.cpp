 #include <sensors/sensors.h>
#include "SensorFanFeature.hpp"
#include "SensorSubfeature.hpp"
#include "SensorAbstractFeature.hpp"

SensorFanFeature::SensorFanFeature(sensors_chip_name const *chip,
                                                   sensors_feature const  *feature)
  : SensorAbstractFeature(chip, feature) {
  this->type = &feature->type;
  setCurrentValueSubfeature();
}

bool SensorFanFeature::isCurrentValueSubfeature(SensorSubfeature subf) {
  return subf.getSensorType() == SENSORS_SUBFEATURE_FAN_INPUT;
}
