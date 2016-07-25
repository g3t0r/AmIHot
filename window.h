#include <ncurses.h>
#include <sensors/sensors.h>
#include <cstring>
#include <time.h>

#ifndef WINDOW_H
#define WINDOW_H

class window{
	
	WINDOW *localwin;
	int window_master_max_y;
	int window_master_max_x;
		
	int window_slave_start_y;
	int window_slave_start_x;
	
protected:
	const static int window_graph_max_y = 23;
	const static int window_graph_max_x = 4;
public:
	void get_window_master_size();
	void show_window_master_frame();
	
	
};




#endif WINDOW_H