#include <sensors/sensors.h>
#include "TempFeature.hpp"
#include "SensorSubfeature.hpp"
#include "SensorAbstractFeature.hpp"

TempFeature::TempFeature(sensors_chip_name const *chip,
                                                   sensors_feature const  *feature)
  : SensorAbstractFeature(chip,  feature) {
  this->type = &feature->type;
  setCurrentValueSubfeature();

}

bool TempFeature::isCurrentValueSubfeature(SensorSubfeature subf) {
  return subf.getSensorType() ==  SENSORS_SUBFEATURE_TEMP_INPUT;
}

