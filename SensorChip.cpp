#include <sensors/sensors.h>
#include <string.h>
#include "SensorChip.hpp"

SensorChip::SensorChip(sensors_chip_name const *chip) {
  this->chip = chip;
  setTempAndFanFeatures();
}

bool SensorChip::isTempFeature(sensors_feature const  *feature) {
  return feature->type == SENSORS_FEATURE_TEMP;
}

bool SensorChip::isFanFeature(sensors_feature const  *feature) {
  return feature->type == SENSORS_FEATURE_FAN;
}

void SensorChip::setTempAndFanFeatures() {
  sensors_feature const *feature;
  int number = 0;
  while((feature = sensors_get_features(chip, &number)) != 0) {
    if(isTempFeature(feature)) {
      temperatureFeatures.push_back(SensorTemperatureFeature(chip, feature));
    }
    if(isFanFeature(feature)) {
      fanFeatures.push_back(SensorFanFeature(chip, feature));
    }
  }
}

std::string SensorChip::getName(){
  return chip->prefix;
}

std::string SensorChip::getAdapterName() {
  sensors_bus_id const *bus = &chip->bus;

  /* Definied in lm_sensors, sensors.h file:
     https://github.com/Distrotech/lm_sensors/blob/master/lib/sensors.h

     SENSORS_BUS_TYPE_ANY		  (-1)
     SENSORS_BUS_TYPE_I2C		    0
     SENSORS_BUS_TYPE_ISA		    1
     SENSORS_BUS_TYPE_PCI		    2
     SENSORS_BUS_TYPE_SPI		    3
     SENSORS_BUS_TYPE_VIRTUAL	  4
     SENSORS_BUS_TYPE_ACPI		  5
     SENSORS_BUS_TYPE_HID		    6
     SENSORS_BUS_NR_ANY		    (-1)
     SENSORS_BUS_NR_IGNORE		(-2) */

  if(bus->type > 6 || bus->type < 0) {
    return "unknown";
  }
  return sensors_get_adapter_name(bus);
}
