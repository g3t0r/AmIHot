#include "ChipWindow.hpp"
#include "SensorChip.hpp"
#include "TempFeature.hpp"
#include "TempFeatureWin.hpp"
#include "Graph.hpp"
#include <ncurses.h>
#include <unistd.h>

ChipWindow::ChipWindow(SensorChip sensorChip) {
  sensorChips.push_back(sensorChip);
  refreshWidthAndHeight();
  tempFeatures = sensorChips[0].temperatureFeatures;
  nrOfTempFeatures = tempFeatures.size();
  startIndexToDisplay = 0;

  const char *longestName = "";
  setMaxNrOfTempFeatWin(longestName);
  widthOfTempFeatWin = strlen(longestName) + 4 ;
  padding = (width - (widthOfTempFeatWin * maxNrOfTempFeatWin)) / 2;

}


void ChipWindow::setMaxNrOfTempFeatWin(const char*&longestName) {
  for(int i = 0; i < nrOfTempFeatures; i++) {
    if(strlen(longestName) < strlen(tempFeatures[i].getName()))
      longestName = tempFeatures[i].getName();
  }

  maxNrOfTempFeatWin = width/strlen(longestName);

  if(maxNrOfTempFeatWin > nrOfTempFeatures)
    maxNrOfTempFeatWin = nrOfTempFeatures;
}



void ChipWindow::refreshWidthAndHeight() {
  width = getmaxx(stdscr);
  width = width - 2 - 4; // -2 because of border, -4 because of side arrows
  height = getmaxy(stdscr);
}

char ChipWindow::showTempFeatures() {
  std::vector <TempFeatureWin>  tempFeatWindows;
  int numberOfWindow = 0;

  for(int i = startIndexToDisplay; i < maxNrOfTempFeatWin; i++) {
    tempFeatWindows.push_back(createTempFeatWin(i, numberOfWindow));
    numberOfWindow++;
  }

  while(true) {
    refreshAllWindows(tempFeatWindows);
    sleep(1);
  }
}

TempFeatureWin ChipWindow::createTempFeatWin(int tempFeat, int tempFeatWin) {
  return TempFeatureWin(stdscr, tempFeatures[tempFeat],
                        padding + (tempFeatWin * widthOfTempFeatWin),
                        widthOfTempFeatWin);
}

void ChipWindow::refreshAllWindows(std::vector <TempFeatureWin> tempFeatWin) {
  for(auto a : tempFeatWin) {
    a.refresh();
  }
}
