#include <ncurses.h>
#include <sensors/sensors.h>
#include <cstring>
#include <time.h>
#include "window.h"

void window::get_window_master_size(){
	getmaxyx(stdscr, window_master_max_y, window_master_max_x);
}

void window::show_window_master_frame(){
	box(stdscr, 0, 0);
	mvwprintw(stdscr, 0, window_master_max_x / 2 - sizeof(" AmIHot v0.01 ")/2 , " AmIHot v0.01 ");
	wrefresh(stdscr);
}
