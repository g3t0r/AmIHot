#include "ChipWindow.hpp"
#include "SensorChip.hpp"
#include "TempFeature.hpp"
#include "TempFeatureWin.hpp"
#include "Graph.hpp"
#include <ncurses.h>
#include <unistd.h>
#include <string.h>

ChipWindow::ChipWindow(SensorChip sensorChip) {
  sensorChips.push_back(sensorChip);
  refreshWidthAndHeight();
  tempFeatures = sensorChips[0].temperatureFeatures;
  nrOfTempFeatures = tempFeatures.size();
  startIndexToDisplay = 0;
  chipWindow = derwin(stdscr, height, width , 2, 1);
  showChipWindowInformations();

  box(chipWindow, 0, 0);
  wrefresh(chipWindow);


  const char *longestName = "";
  setMaxNrOfTempFeatWin(longestName);
  widthOfTempFeatWin = strlen(longestName) + 4 ;
  padding = (spaceForTempFeatWins - (widthOfTempFeatWin * maxNrOfTempFeatWin)) / 2;

}


void ChipWindow::refreshWidthAndHeight() {
  width = getmaxx(stdscr) - 2;
  height = getmaxy(stdscr) - 4;
  spaceForTempFeatWins = width - 2;
}


void ChipWindow::setMaxNrOfTempFeatWin(const char*&longestName) {
  for(int i = 0; i < nrOfTempFeatures; i++) {
    if(strlen(longestName) < strlen(tempFeatures[i].getName()))
      longestName = tempFeatures[i].getName();
  }

   maxNrOfTempFeatWin = spaceForTempFeatWins/strlen(longestName);

  if(maxNrOfTempFeatWin > nrOfTempFeatures)
    maxNrOfTempFeatWin = nrOfTempFeatures;
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
  int heightOfTempFeatWin = height - 4;
  return TempFeatureWin(chipWindow, tempFeatures[tempFeat],
                       padding + (tempFeatWin * widthOfTempFeatWin),
                        heightOfTempFeatWin,
                        widthOfTempFeatWin);
}

void ChipWindow::refreshAllWindows(std::vector <TempFeatureWin> tempFeatWin) {
  for(auto a : tempFeatWin) {
    a.refresh();
  }

}

void ChipWindow::showChipWindowInformations() {
  const char * chipName = sensorChips[0].getName();
  const char * adapterName = sensorChips[0].getAdapterName();
  std::string tmpText = "Chip: ";
  tmpText += chipName;
  tmpText += "\t Adapter: ";
  tmpText += adapterName;
  const char * text = tmpText.c_str();
  int textLength = strlen(text);
  mvwprintw(chipWindow, 2, spaceForTempFeatWins/2 - textLength / 2, "%s", text);
  wrefresh(chipWindow);
}
