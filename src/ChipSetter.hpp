#ifndef CHIP_SETTER_HPP
#define CHIP_SETTER_HPP
#include <vector>
#include "SensorChip.hpp"
#include <pthread.h>
#include "ChipWindow.hpp"

class ChipSetter {
  int heightWithBorder, height;
  int widthWithBorder, width;
  int startIndex;
  bool exit;
  char input;
  std::vector <SensorChip> sensorsChips;


  bool checkInput();
  void showChipWindow(ChipWindow chipWindow);
  void showHelp();
  void showArrows();
  void refreshSize();
  bool isInputCorrect(int _input);
  void translateInput(int _input);

public:
  ChipSetter(std::vector <SensorChip> sensorsChips);
  void setSensor();
  static void showBorder();
  static void showTitle();
};

#endif
