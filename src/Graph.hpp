#ifndef GRAPH_H
#define GRAPH_H

#include <ncurses.h>

class Graph {
  int height;
  int width;
  int heightWithBorder;
  int widthWithBorder;
  int heightOfGraphFill;
  int x;
  int y;
  int endOfLowLevelScope;
  int endOfMiddleLevelScope;
  int startOfHighLevelScope;
  WINDOW * graphWindow;


  bool isInScopeOfLowLevel(int currentIteratorValue);
  bool isInScopeOfMiddleLevel(int currentIteratorValue);
  bool isInScopeOfHighLevel(int currentIteratorValue);
  void correctScopesOfLevels();


  void addBorders();
  void cleanUpGraph();
  void fillGraphGreen(int verticalPosition);
  void fillGraphYellow(int verticalPosition);
  void fillGraphRed(int verticalPosition);
  void setColorBlocks(int verticalPosition);

public:
  Graph(WINDOW *masterWindow, int height, int y, int x);

  void setGraphFillFromTemp(int temp);
  void fillGraph();
  void deleteGraph();

};

#endif
