#include <ncurses.h>
#include <sensors/sensors.h>
#include <cstring>
#include <time.h>
#include "sens.h"

void sens::get_sens_patametrs(sensors_chip_name const *cn, sensors_feature const *ft, int c, int f){
	chip_name = cn;
	chip_number = c;
	feature_name = ft;
	feature_number = f;
	name = ft->name;
	label = sensors_get_label(cn, ft);
	space_for_graph = strlen(label) + 5;
}

void sens::refresh_value(){
	sensors_get_value(chip_name, feature_name->first_subfeature, &value);
	temp = (int)value;
	int t = temp;
	
	if(temp%5 == 0)
		temp_on_graph = temp/5;
		
	else{
		switch(t%5){
			case 1:
				t--;
				temp_on_graph = t/5;
				break;
				
			case 2:
				t -= 2;
				temp_on_graph = t/5;
				break;
				
			case 3:
				t += 2;
				temp_on_graph = t/5;
				break;
			case 4:
				t++;
				temp_on_graph = t/5;
				break;
		}
	}
}

void sens::get_sens_type(){
	if(name[0] == 't')
		temperature_sens = true;
		
	if(name[0] == 'f')
		fan_sens = true;
}

void sens::test(){
	mvprintw(1, 1,"%f %d %f %d", temp, temp, temp_on_graph, temp_on_graph);
	refresh();
}

void sens::create_graph(int x){
	window_graph_x = x;
	localwin = newwin(window_graph_max_y, window_graph_max_x,
	window_graph_start_y, x);
}

void sens::show_graph_border(){
	wclear(localwin);
	wattron(localwin ,COLOR_PAIR(1));
	box(localwin, 0, 0);
	//refresh();
	//wrefresh(localwin);
	//refresh();
}

void sens::refresh_graph(){
	for(int i = 0; i < temp_on_graph; i++){
		 
		if(i > 0 ){
			wattron(localwin, COLOR_PAIR(2));
			mvwaddch(localwin, window_graph_max_y -1 - i, 1, ACS_CKBOARD);
			mvwaddch(localwin, window_graph_max_y -1 - i, 2, ACS_CKBOARD);
			wattroff(localwin ,COLOR_PAIR(2));			
		}
		
		if(i >= 10 && i < 18){
			wattron( localwin, COLOR_PAIR(3));
			mvwaddch(localwin, window_graph_max_y -1 - i, 1, ACS_CKBOARD);
			mvwaddch(localwin, window_graph_max_y -1 - i, 2, ACS_CKBOARD);
			wattroff(localwin, COLOR_PAIR(3));
		}
		
		if(i >= 18){
			wattron(localwin, COLOR_PAIR(4));
			mvwaddch(localwin, window_graph_max_y -1 - i, 1, ACS_CKBOARD);
			mvwaddch(localwin, window_graph_max_y -1 - i, 2, ACS_CKBOARD);
			wattroff(localwin, COLOR_PAIR(4));
			
			
		}
	}
	//wrefresh(localwin);
			//refresh();
}

void sens::show_temp(){
	mvprintw(window_graph_start_y + window_graph_max_y, window_graph_x, "%d%cC", temp, 42);
	//wrefresh(localwin);
	//refresh();
}

void sens::hide_temp(){
	mvprintw(window_graph_start_y + window_graph_max_y, window_graph_x, "       ");
	refresh();
}

void sens::show_label(){
	mvprintw(window_graph_start_y -2, window_graph_x - strlen(label)/2 + 2 , "%s", label);
}

void sens::destroy_graph(){
	delwin(localwin);
}
