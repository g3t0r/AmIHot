#ifndef CHIP_WINDOW_H
#define CHIP_WINDOW_H
#include <vector>
#include "SensorChip.hpp"
#include "TempFeature.hpp"
#include "TempFeatureWin.hpp"


class ChipWindow {
  std::vector <SensorChip> sensorChips;
  std::vector <TempFeature> tempFeatures;
  int widthOfTempFeatWin;
  int startIndexToDisplay;
  int nrOfTempFeatures;
  int maxNrOfTempFeatWin;
  int width;
  int height;
  int padding;

  void setMaxNrOfTempFeatWin(const char*&name);
  void refreshAllWindows(std::vector <TempFeatureWin> tempFeatWin);
  TempFeatureWin createTempFeatWin(int tempFeat, int tempFeatWin);

public:
  ChipWindow(SensorChip);
  void refreshWidthAndHeight();
  char showTempFeatures();
};

#endif
