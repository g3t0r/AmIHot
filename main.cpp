#include <iostream>
#include <vector>
#include <sensors/sensors.h>
#include <unistd.h>
#include "SensorChip.hpp"
#include "ChipGetter.hpp"
#include <ncurses.h>
#include "Graph.hpp"
#include "TempFeatureWin.hpp"
#include "ChipSetter.hpp"
#include "ChipWindow.hpp"





SensorChip * sensorChip;

void test() {

  std::vector < SensorChip >  chips;
  chips = ChipGetter::getChips();

  
  sensorChip = &chips[1];
  SensorChip a = *sensorChip;
  

  /*  for(auto a : chips) {
    std::cout << "Name: " << a.getName() << std::endl;
    std::cout << "Adapter Name: " << a.getAdapterName() << std::endl;
    for(auto b : a.temperatureFeatures) {
      std::cout <<  "    Name: " << b.getName() << std::endl;
      std::cout <<  "    Value: " << b.getValue() << std::endl;
    }

  }*/
}


int main() {
  sensors_init(NULL);
  //test();
  // std::cout << sensorChip->getName() << "     " << &sensorChip  << std::endl;
  initscr();

  keypad(stdscr, true);
  //''cbreak();
  noecho();
  nodelay(stdscr, true);
  curs_set(0);
  //wborder(stdscr, 0,0,0,0,0,0,0,0);
  /*mvprintw(getmaxy(stdscr) -2,0, "!");
  refresh();
  getch();*/

  start_color();
  std::vector <SensorChip> sensorChips;
  sensorChips = ChipGetter::getChips();
  //  ChipSetter chipSetter(sensorChips);
  // chipSetter.setSensor();
  //ChipWindow cw(sensorChips[0]);
  //cw.showTempFeatures();

  ChipSetter cS(sensorChips);
  cS.setSensor();

  endwin();

  return 0;
}
