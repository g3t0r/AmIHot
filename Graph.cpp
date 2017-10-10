#include <ncurses.h>
#include "Graph.hpp"

Graph::Graph(WINDOW *masterWindow, int y, int x) {
  this->x = x;
  this->y = y;

  height = 21;
  width = 2;
  height_with_border = 23;
  width_with_borders = 4;
  graphWindow = derwin(masterWindow, height_with_border,
                       width_with_borders, 2, x );

  addBorders();
  wrefresh(graphWindow);
}

void Graph::addBorders() {
  wborder(graphWindow, 0, 0, 0, 0, 0, 0, 0, 0);
}

void Graph::fillGraph() {
  cleanUpGraph();
  for(int i = 0; i < heightOfGraphFill; i++) {
    if(i <= 7) {
      wprintw(stdscr, "%d ", i);
      fillGraphGreen(height - i);
    }
    if(i <= 14 && i > 7) {
      wprintw(stdscr, "%d ", i);
      fillGraphYellow(height - i);
    }
    if(i < 21 && i > 14) {
      wprintw(stdscr, "%d ", i);
      fillGraphRed(height - i);
    }
  }
  wrefresh(graphWindow);
}

void Graph::setHeightOfGraphFill(int heightOfGraphFill) {
  if(heightOfGraphFill > 21) {
    this->heightOfGraphFill = 21;
  }
  else {
    this->heightOfGraphFill = heightOfGraphFill;
  }
}

void Graph::deleteGraph() {
  wborder(graphWindow, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  delwin(graphWindow);
}

void Graph::fillGraphGreen(int verticalPosition){
  init_pair(1, COLOR_GREEN, COLOR_BLACK);
  wattron(graphWindow, COLOR_PAIR(1));
  setColorBlocks(verticalPosition);
  wattroff(graphWindow, COLOR_PAIR(1));

}

void Graph::fillGraphYellow(int verticalPosition){
  init_pair(2, COLOR_YELLOW, COLOR_BLACK);
  wattron(graphWindow, COLOR_PAIR(2));
  setColorBlocks(verticalPosition);
  wattroff(graphWindow, COLOR_PAIR(2));
}

void Graph::fillGraphRed(int verticalPosition){
  init_pair(3, COLOR_RED, COLOR_BLACK);
  wattron(graphWindow, COLOR_PAIR(3));
  setColorBlocks(verticalPosition);
  wattroff(graphWindow, COLOR_PAIR(3));
}

void Graph::setColorBlocks(int verticalPosition) {
  mvwaddch(graphWindow,  verticalPosition, 1, ACS_BLOCK);
  mvwaddch(graphWindow,  verticalPosition, 2, ACS_BLOCK);
}

void Graph::cleanUpGraph() {
  for(int i = 1; i < height; i++) {
    mvwaddch(graphWindow,  i, 1, ' ');
    mvwaddch(graphWindow,  i, 2, ' ');
  }
}
