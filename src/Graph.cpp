#include <ncurses.h>
#include "Graph.hpp"

Graph::Graph(WINDOW *masterWindow, int heightWithBorder, int y, int x) {
  this->x = x;
  this->y = y;

  this->heightWithBorder = heightWithBorder;
  height = heightWithBorder - 2; 
  endOfLowLevelScope = height/3;
  endOfMiddleLevelScope = (height/3)*2;
  correctScopesOfLevels();
  width = 2;
  widthWithBorder = 4;
  graphWindow = derwin(masterWindow, heightWithBorder,
                       widthWithBorder, 2, x );

  addBorders();
  wrefresh(graphWindow);
}

void Graph::correctScopesOfLevels() {
  if(height % 3 >= 1)
    endOfLowLevelScope++;
  if(height % 3 == 2)
    endOfMiddleLevelScope++;
  if(height % 3 == 0)
    endOfMiddleLevelScope--;

}

void Graph::addBorders() {
  wborder(graphWindow, 0, 0, 0, 0, 0, 0, 0, 0);
}

void Graph::fillGraph() {
  cleanUpGraph();
  for(int i = 0; i < heightOfGraphFill; i++) {
    if(isInScopeOfLowLevel(i)) {
      fillGraphGreen(height - i);
    }
    if(isInScopeOfMiddleLevel(i)) {
      fillGraphYellow(height - i);
    }
    if(isInScopeOfHighLevel(i)) {
      fillGraphRed(height - i);
    }
  }
  wrefresh(graphWindow);
}

void Graph::setGraphFillFromTemp(int temp) {
  const int PROPORTIONAL_HEIGHT = 21;
  const int PROPORTIONAL_DIVIDER = 5;
  int divider = PROPORTIONAL_HEIGHT * PROPORTIONAL_DIVIDER / height;
  heightOfGraphFill = temp/divider;
  if(heightOfGraphFill > height)
    heightOfGraphFill = height;

}


void Graph::cleanUpGraph() {
  for(int i = 1; i < height; i++) {
    mvwaddch(graphWindow,  i, 1, ' ');
    mvwaddch(graphWindow,  i, 2, ' ');
  }
}






bool Graph::isInScopeOfLowLevel(int currentInteratorValue) {
  return currentInteratorValue <= endOfLowLevelScope;
}

bool Graph::isInScopeOfMiddleLevel(int currentIteratorValue) {
  return currentIteratorValue <= endOfMiddleLevelScope &&
    currentIteratorValue >= endOfLowLevelScope;
}

bool Graph::isInScopeOfHighLevel(int currentIteratorValue) {
  return currentIteratorValue < height &&
    currentIteratorValue > endOfMiddleLevelScope;
}






void Graph::fillGraphGreen(int verticalPosition){
  init_pair(1, COLOR_GREEN, COLOR_GREEN);
  wattron(graphWindow, COLOR_PAIR(1));
  setColorBlocks(verticalPosition);
  wattroff(graphWindow, COLOR_PAIR(1));

}

void Graph::fillGraphYellow(int verticalPosition){
  init_pair(2, COLOR_YELLOW, COLOR_YELLOW);
  wattron(graphWindow, COLOR_PAIR(2));
  setColorBlocks(verticalPosition);
  wattroff(graphWindow, COLOR_PAIR(2));
}

void Graph::fillGraphRed(int verticalPosition){
  init_pair(3, COLOR_RED, COLOR_RED);
  wattron(graphWindow, COLOR_PAIR(3));
  setColorBlocks(verticalPosition);
  wattroff(graphWindow, COLOR_PAIR(3));
}

void Graph::setColorBlocks(int verticalPosition) {
  mvwaddch(graphWindow,  verticalPosition, 1, ACS_CKBOARD);
  mvwaddch(graphWindow,  verticalPosition, 2, ACS_CKBOARD);
}


void Graph::deleteGraph() {
  wborder(graphWindow, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  delwin(graphWindow);
}
