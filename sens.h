#include <ncurses.h>
#include <sensors/sensors.h>
//#include <cstring>
#include <time.h>
#include "window.h"

class sens :public window{
	sensors_chip_name const *cn;
	sensors_feature const *ft;
	int c, f;
	double value = 0;
	bool stop_displaying = 0;
	int temp = 0;
	int temp_on_graph = 0;
public:
	void get_sens_patametrs();
	
};