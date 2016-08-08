#include <ncurses.h>
#include <sensors/sensors.h>
#include <cstring>
#include <time.h>

#ifndef WINDOW_H
#define WINDOW_H

class window{
	
	
	
		
	
	
	int number_of_t_sensors = 0;
	
	
protected:
	WINDOW *localwin;
	//int window_slave_start_y;
	//int window_slave_start_x;
	
	int window_graph_start_y = 0;
	int window_graph_start_x = 0;
	
	int temp = 0;
	int temp_on_graph = 0;
	
	
	const static int window_graph_max_y = 23;
	const static int window_graph_max_x = 4;
public:
	int window_master_max_y;
	int window_master_max_x;
	
	int choosed_option = 0;
	
	void get_window_master_size();
	void show_window_master_frame();
	void get_number_of_t_sensors(int);
	void choose_sensor();
	void create_graph();
	void show_graph_border();
	void destroy_graph();
	
	
	//friend void choose_sensor();
};




#endif WINDOW_H