#include <ncurses.h>
#include <sensors/sensors.h>
//#include <cstring>
#include <time.h>
#include "window.h"

class sens :public window{
	sensors_chip_name const *chip_name;
	sensors_feature const *feature_name;
	int chip_number = 0;
	int feature_number = 0;
	int temp = 0;
	int temp_on_graph = 0;
	double value = 0;
	char *name;
	char *label;
	
public:
	bool temperature_sens = false;
	bool fan_sens = false;
	
	void get_sens_patametrs(sensors_chip_name const *, sensors_feature const *, int, int);
	void get_sens_type();
	void refresh_value();
	void test();
	
};