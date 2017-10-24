#ifndef CHIP_WINDOW_H
#define CHIP_WINDOW_H
#include <vector>
#include "SensorChip.hpp"
#include "TempFeature.hpp"
#include "TempFeatureWin.hpp"
#include "ChipWinController.hpp"

class ChipWindow {
  friend class ChipWinController;
  std::vector <SensorChip> sensorChips;
  std::vector <TempFeature> tempFeatures;
  int widthOfTempFeatWin;
  int startIndexToDisplay;
  int nrOfTempFeatures;
  int maxNrOfTempFeatWin;
  int width;
  int height;
  int padding;
  int spaceForTempFeatWins;
  int signal;
  WINDOW * chipWindow;

  void setMaxNrOfTempFeatWin(const char*&name);
  void refreshAllWindows(std::vector <TempFeatureWin> tempFeatWin);
  void showChipWindowInformations();
  TempFeatureWin createTempFeatWin(int tempFeat, int tempFeatWin);

public:
  ChipWindow(SensorChip sensorChip);
  void refreshWidthAndHeight();
  char showTempFeatures();
};

#endif
