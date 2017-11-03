#include "ChipWinController.hpp"
#include "ChipWindow.hpp"
#include <unistd.h>



ChipWinController::ChipWinController(void * chipWindow, char * input) {
  this->chipWindow = chipWindow;
  this->input = input;
  exit = false;
}

void ChipWinController::startController() {
  while(!exit) {
    sleep(1);
    if(*input == '0') continue;
    interpretSignal();
  }
}

void ChipWinController::interpretSignal() {
  switch(*input) {
  case 'Q':
  case 'H':
  case 'R':
    breakChipWindwowLoop(); //About this will care ChipSelector
    break;

  case '<':
    scrollTFWinsLeft();
    break;

  case '>':
    scrollTFWinsRight();
    break;

  default:
    resetInput();
    break;
  }
}

void ChipWinController::scrollTFWinsLeft() {
  int index =   ((ChipWindow *) chipWindow)->startIndexToDisplay;
  if(index != 0) {
    ((ChipWindow *) chipWindow)->startIndexToDisplay--;
    breakRefreshLoop();
    resetInput();
  }
}

void ChipWinController::scrollTFWinsRight() {
  int startIndex =  ((ChipWindow *) chipWindow)->startIndexToDisplay;
  int maxNrOfTempFeatWin = ((ChipWindow *) chipWindow)->maxNrOfTempFeatWin;
  int nrOfTempFeat = ((ChipWindow *) chipWindow)->nrOfTempFeatures;
  if(startIndex + maxNrOfTempFeatWin == nrOfTempFeat)
    return;
  ((ChipWindow *) chipWindow)->startIndexToDisplay++;
  breakRefreshLoop();
  resetInput();
}

void ChipWinController::setSignal(int signal) {
  ((ChipWindow *) chipWindow)->signal = signal;
}

void ChipWinController::breakRefreshLoop() {
  setSignal(1);
}

void ChipWinController::breakChipWindwowLoop() {
  setSignal(2);
}

void ChipWinController::resetInput() {
  *input = '0';
}
