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