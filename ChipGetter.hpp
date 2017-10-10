#ifndef CHIP_GETTER_H
#define CHIP_GETTER_H

#include <sensors/sensors.h>
#include <vector>
#include "SensorChip.hpp"

class ChipGetter {
public:
  static std::vector < SensorChip > getChips();
};

#endif
