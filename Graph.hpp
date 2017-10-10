#ifndef GRAPH_H
#define GRAPH_H

#include <ncurses.h>

class Graph {
  int height;
  int width;
  int height_with_border;
  int width_with_borders;
  int heightOfGraphFill;
  int x;
  int y;
  WINDOW * graphWindow;

  void addBorders();

  void cleanUpGraph();
  void fillGraphGreen(int);
  void fillGraphYellow(int);
  void fillGraphRed(int);

  void setColorBlocks(int);

public:
  Graph(WINDOW*, int, int);

  void setHeightOfGraphFill(int);
  void fillGraph();
  void deleteGraph();

};

#endif
