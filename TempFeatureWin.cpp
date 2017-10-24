#include "TempFeatureWin.hpp"
#include "TempFeature.hpp"
#include "Graph.hpp"
#include <ncurses.h>
#include <string.h>


TempFeatureWin::TempFeatureWin(WINDOW * masterWin, TempFeature feat,
                               int x, int heightWithBorder,  int widthWithBorder) {

  this->widthWithBorder = widthWithBorder;
  width = widthWithBorder - 2;
  height = heightWithBorder - 2;
  this->x = x;
  y = 3;
  x += 1; //Not 0 because of border
  tempFeature.push_back(feat);

  featureWindow = derwin(masterWin, heightWithBorder,
                          widthWithBorder, y, x);
  box(featureWindow, 0, 0);

  createGraphWindow();
  showFeatureName();

}

void TempFeatureWin::createGraphWindow() {
  int graphY = 4;
  int graphX = width/2 -1;
  int graphHeight = height -2;

  graphWindow.push_back(Graph(featureWindow, graphHeight, graphY, graphX));
}


void TempFeatureWin::refresh() {
  refreshTemp();
  wrefresh(featureWindow);
  refreshGraphWindow(); 
}


void TempFeatureWin::showFeatureName() {
  const char * name = tempFeature[0].getName();
  int nameLength = strlen(name);
  int textX = width/2 - nameLength/2 + 1;
  int textY = 1;
  mvwprintw(featureWindow, textY, textX, name);
}

void TempFeatureWin::refreshGraphWindow() {
  int temp = tempFeature[0].getValue();
  graphWindow[0].setGraphFillFromTemp(temp);
  graphWindow[0].fillGraph();
}

void TempFeatureWin::refreshTemp() {
  int tempStartX = width/2 -1;
  int tempLength = 1;
  int temp = (int)tempFeature[0].getValue();
  if(temp > 9 && temp < 100) tempLength = 2;
  if(temp >= 100) tempLength = 3;


  mvwprintw(featureWindow, height , tempStartX, "%d", temp);
  mvwaddch(featureWindow, height, tempStartX + tempLength, ACS_DEGREE);
  mvwprintw(featureWindow, height,tempStartX + tempLength + 1, "C");
}
