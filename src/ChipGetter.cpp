#include <sensors/sensors.h>
#include <vector>
#include "SensorChip.hpp"
#include "ChipGetter.hpp"

std::vector < SensorChip > ChipGetter::getChips() {
  int number = 0;
  sensors_chip_name const * chip;
  std::vector < SensorChip > chips;

  while ((chip = sensors_get_detected_chips(0, &number)) != 0) {
    chips.push_back(SensorChip(chip));
   }
  return chips;
}
