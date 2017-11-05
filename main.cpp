#include <vector>
#include <sensors/sensors.h>
#include <ncurses.h>
#include "ChipGetter.hpp"
#include "ChipSetter.hpp"



int main() {
  sensors_init(NULL);

  setlocale(LC_ALL, "");
  initscr();
  keypad(stdscr, true);
  noecho();
  nodelay(stdscr, true);
  curs_set(0);
  start_color();

  std::vector <SensorChip> sensorChips;
  sensorChips = ChipGetter::getChips();
  ChipSetter chipSetter(sensorChips);
  chipSetter.setSensor();
  endwin();

  return 0;
}
