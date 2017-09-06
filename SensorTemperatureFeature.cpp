#include <sensors/sensors.h>
#include "SensorTemperatureFeature.hpp"
#include "SensorSubfeature.hpp"
#include "SensorAbstractFeature.hpp"

SensorTemperatureFeature::SensorTemperatureFeature(sensors_chip_name const *chip,
                                                   sensors_feature const  *feature)
  : SensorAbstractFeature(chip,  feature) {
  this->type = &feature->type;
  setCurrentValueSubfeature();

}

bool SensorTemperatureFeature::isCurrentValueSubfeature(SensorSubfeature subf) {
  return subf.getSensorType() ==  SENSORS_SUBFEATURE_TEMP_INPUT;
}

