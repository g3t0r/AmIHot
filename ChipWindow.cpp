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

  wrefresh(chipWindow);


  const char *longestName = getLongestName();
  setMaxNrOfTempFeatWin(longestName);
  widthOfTempFeatWin = strlen(longestName) + 4 ;
  padding = (spaceForTempFeatWins - (widthOfTempFeatWin * maxNrOfTempFeatWin)) / 2;

}


void ChipWindow::refreshWidthAndHeight() {
  width = getmaxx(stdscr) - 2;
  height = getmaxy(stdscr) - 4;
  spaceForTempFeatWins = width - 2;
}

const char * ChipWindow::getLongestName() {
  const char * _longestName = "";
  for(int i = 0; i < nrOfTempFeatures; i++) {
    if(strlen(_longestName) < strlen(tempFeatures[i].getName()))
      _longestName = tempFeatures[i].getName();
  }
  return _longestName;
}

void ChipWindow::setMaxNrOfTempFeatWin(const char* longestName) {
  maxNrOfTempFeatWin = spaceForTempFeatWins/(strlen(longestName) + 4);

  if(maxNrOfTempFeatWin > nrOfTempFeatures)
    maxNrOfTempFeatWin = nrOfTempFeatures;
}

char ChipWindow::showTempFeatures() {
  while(true) {
    wclear(chipWindow);
    showArrows();
    showChipWindowInformations();
    wrefresh(chipWindow);
    char input = startLoop();
    int maxStartIndx = nrOfTempFeatures - maxNrOfTempFeatWin;
    switch(input) {
    case '<':
      if(startIndexToDisplay != 0) {
        startIndexToDisplay--;
      }
      break;

    case '>':
      if(startIndexToDisplay != maxStartIndx) {
        startIndexToDisplay++;
      }
      break;

    default:
      return input;
    }

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

char ChipWindow::startLoop() {
  std::vector <TempFeatureWin>  tempFeatWin;
  int numberOfWindow = 0;

  for(int i = startIndexToDisplay; i < maxNrOfTempFeatWin + startIndexToDisplay; i++) {
    tempFeatWin.push_back(createTempFeatWin(i, numberOfWindow));
    numberOfWindow++;
  }

  char input = 0;
  do {
    refreshAllWindows(tempFeatWin);
    usleep(50000); //0.5s
    input = getInput();
  }while(input == 0);
  return input;
}

char ChipWindow::getInput() {
  int input = wgetch(stdscr);
  switch(input) {
  case 'Q':
  case 'q':
    return 'Q';

  case 'H':
  case 'h':
    return 'H';

  case KEY_RESIZE:
    return 'R';

  case KEY_LEFT:
    return '<';

  case KEY_RIGHT:
    return '>';

  case KEY_UP:
    return 'U';

  case KEY_DOWN:
    return 'D';
  }
  return 0;
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

void ChipWindow::showArrows() {
  if(startIndexToDisplay != 0) {
    for(int i = 0; i < height; i++)
      mvwaddch(chipWindow, i, 0, ACS_LARROW);
  }

  if(startIndexToDisplay != (nrOfTempFeatures - maxNrOfTempFeatWin)) {
    for(int i = 0; i < height; i++)
      mvwaddch(chipWindow, i, width -1, ACS_RARROW);
  }
}
