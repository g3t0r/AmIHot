#include <ncurses.h>
#include <sensors/sensors.h>
#include <cstring>
#include <time.h>
#include "window.h"
#include "sens.h"

int main(){
	initscr();
	window w1;
	sens s1;
	w1.get_window_parametrs();
	s1.get_sens_patametrs();
	getch();
	endwin();
	
	return 0;
}

