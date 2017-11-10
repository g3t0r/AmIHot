#include "HelpWindow.hpp"
#include "ChipSetter.hpp"
#include <iostream>
#include <string.h>
#include <ncurses.h>

void HelpWindow::showHelpWindow() {
  nodelay(stdscr, false);
  std::string text[8] = {"AmIHot 1.1.0 created by g3t0r (g3t0r.github@gmail.com)",
                         "Use arrows to move or VIM keybindigs (h,j,k,l)",
                         "Press Q to quit",
                         "No sensors detected?",
                         "Try to run sensors-detect",
                         "Please, report bugs and issues on github",
                         "License",
                         "GNU/GPL"};
  do {
    clear();
    ChipSetter::showBorder();
    ChipSetter::showTitle();
    for(int i = 0; i < 8; i++) {
      mvprintw(2 + i, getmaxx(stdscr)/2 - text[i].length()/2, text[i].c_str());
    }
  refresh();
  }while(getch() == KEY_RESIZE);
  nodelay(stdscr, true);
}
