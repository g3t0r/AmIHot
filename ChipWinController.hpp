#ifndef CHIP_WINDOW_CONTROLLER
#define CHIP_WINDOW_CONTROLLER
#include "ChipWindow.hpp"

class ChipWinController {
  void * chipWindow;
  char * input;
  bool exit;
  void interpretSignal();
  void scrollTFWinsLeft();
  void scrollTFWinsRight();
  void setSignal(int signal);
  void breakRefreshLoop();
  void breakChipWindwowLoop();
  void resetInput();

public:
  ChipWinController(void * ChipWindow, char * input);
  void startListening();
};


#endif
