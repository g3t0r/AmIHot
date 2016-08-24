#include <ncurses.h>
#include <sensors/sensors.h>
#include <time.h>
#include "window.h"

class sens :public window{
	
	
	sensors_chip_name const *chip_name;
	sensors_feature const *feature_name;
	int chip_number = 0;
	int feature_number = 0;
	
	double value = 0;
	char *name;
	
	
public:
WINDOW *localwin;
	
	bool temperature_sens = false;
	bool fan_sens = false;
	char *label;
	
	void get_sens_patametrs(sensors_chip_name const *, sensors_feature const *, int, int);
	void get_sens_type();
	void refresh_value();
	void refresh_graph();
	void test();
	void create_graph(int);
	void show_graph_border();
	void destroy_graph();
	void show_temp();
	void hide_temp();
	void show_label();
};
