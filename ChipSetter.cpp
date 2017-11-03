#include "ChipSetter.hpp"
#include <vector>
#include <pthread.h>
#include "SensorChip.hpp"
#include <ncurses.h>
#include "ChipWindow.hpp"
#include "InputListener.hpp"
#include "ChipWinController.hpp"

ChipSetter::ChipSetter(std::vector <SensorChip> _sensorsChips) {
  sensorsChips = _sensorsChips;
  width = 0;
  widthWithBorder = 0;
  height = 0;
  heightWithBorder = 0;
  startIndex = 0;
  input = 'R';
}

void ChipSetter::setSensor() {
  while(checkInput()) {
    clear();
    ChipWindow chipWin(sensorsChips[startIndex]);
    showArrows();
    showBorder();
    showTitle();
    refresh();
    input = chipWin.showTempFeatures();
  }
}

bool ChipSetter::checkInput() {
  switch(input) {
  case 'Q':
    return false;
  case 'U':
    if(startIndex != 0) startIndex--;
    break;
  case 'D':
    if(startIndex != sensorsChips.size() - 1) startIndex++;
    break;
  case 'R':
    refreshSize();
    break;
  }
  return true;
}

void ChipSetter::showChipWindow(ChipWindow chipWindow) {
  chipWindow.showTempFeatures();
}

void ChipSetter::showHelp() {
  //Create class to generate this window
}

void ChipSetter::showArrows() {
  for(int i = 0; i < width; i++) {
    if(startIndex != 0) mvaddch(1, 1 + i, ACS_UARROW);
    if(startIndex < sensorsChips.size() -1 )
      mvaddch(height, 1 + i, ACS_DARROW);
  }
}

void ChipSetter::refreshSize() {
  heightWithBorder = getmaxy(stdscr);
  widthWithBorder = getmaxx(stdscr);
  height = heightWithBorder - 2;
  width = widthWithBorder - 2;
}

void ChipSetter::showBorder() {
  box(stdscr, 0, 0);
}

void ChipSetter::showTitle() {
  const char * title = "[ AmIHot 1.0.0 ]";
  int titleLength = strlen(title);
  mvprintw(0, width/2 - titleLength/2, "%s", title);
}
