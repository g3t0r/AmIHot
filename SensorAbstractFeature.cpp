#include "SensorAbstractFeature.hpp"
#include <sensors/sensors.h>

SensorAbstractFeature::SensorAbstractFeature(sensors_chip_name const *chip,
                                             sensors_feature const  *feature) {
  this->chip = chip;
  this->feature = feature;
  this->type = &feature->type;

}

void SensorAbstractFeature::setCurrentValueSubfeature() {
  sensors_subfeature const *subf;
  int number = 0;
  while((subf = sensors_get_all_subfeatures(chip, feature, &number)) != 0) {
    SensorSubfeature subfeature(chip, subf);
    if(isCurrentValueSubfeature(subfeature)){
      currentValueSubfeature = subfeature;
    }
  }
}

double SensorAbstractFeature::getValue() {
  return currentValueSubfeature.getValue();
}

char * SensorAbstractFeature::getName() {
  return sensors_get_label(chip, feature);
}
