#include <ncurses.h>
#include <sensors/sensors.h>
#include <cstring>
#include <time.h>
#include "window.h"

void window::get_window_master_size(){
	getmaxyx(stdscr, window_master_max_y, window_master_max_x);
	window_graph_start_x = window_master_max_x/2 - window_graph_max_x/2;
	window_graph_start_y = window_master_max_y/2 - window_graph_max_y/2;
}

void window::show_window_master_frame(){
	box(stdscr, 0, 0);
	mvwprintw(stdscr, 0, window_master_max_x / 2 - sizeof(" AmIHot v0.02 ")/2 , " AmIHot v0.02 ");
	wrefresh(stdscr);
}

void window::get_number_of_t_sensors(int n){
	number_of_t_sensors = n;
}

/*void window::create_graph(int x){
	
	window_graph_x = x;
	localwin = newwin(window_graph_max_y, window_graph_max_x,
	window_graph_start_y, x);
}*/

/*void window::show_graph_border(){
	wclear(localwin);
	wattron(localwin ,COLOR_PAIR(1));
	box(localwin, 0, 0);
	refresh();
	wrefresh(localwin);
	refresh();
}

void window::destroy_graph(){
	delwin(localwin);
}*/