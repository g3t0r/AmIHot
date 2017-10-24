#ifndef TEMP_FEATURE_WIN
#define TEMP_FEATURE_WIN

#include <ncurses.h>
#include <string.h>
#include "Graph.hpp"
#include "SensorChip.hpp"
#include "TempFeature.hpp"
#include "vector"
#include "Graph2.hpp"

class TempFeatureWin {

  std::vector <TempFeature> tempFeature;
  std::vector <Graph> graphWindow;

  WINDOW *featureWindow;

  int height;
  int heightWithBorder;
  int width;
  int widthWithBorder;
  int x;
  int y;

  void createGraphWindow();
  void showFeatureName();

  void refreshGraphWindow();
  void refreshTemp();


public:
  TempFeatureWin(WINDOW *masterWin, TempFeature feat, int x,
                 int heightWithBorder, int widthWithBorder);
  void refresh();
};

#endif
