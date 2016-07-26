#include <ncurses.h>
#include <sensors/sensors.h>
#include <cstring>
#include <time.h>
#include "window.h"
#include "sens.h"

void graph_screen(sens *graph, int n_of_graph, window &win_m){
	//printw("%s \n", graph[win_m.choosed_option].label);
	//printw("%d", win_m.choosed_option);
	graph[0].get_window_master_size();
	graph[0].create_graph();
	graph[0].show_graph_border();
		
}

void choose_sensor(sens *t_sens, int n_of_t_sens, window &win_m){
	for(int i = 0; i < n_of_t_sens; i++){
		if(win_m.choosed_option == i){
			attron(A_REVERSE);
			mvprintw(win_m.window_master_max_y/2 - n_of_t_sens/2 + i, win_m.window_master_max_x/2 - sizeof(t_sens[i].label), "%s", t_sens[i].label);
			attroff(A_REVERSE);
		}
		else{
			mvprintw(win_m.window_master_max_y/2 - n_of_t_sens/2 + i, win_m.window_master_max_x/2 - sizeof(t_sens[i].label), "%s", t_sens[i].label);
		}
	}
	
}

void main_loop(sens *t_sens, int n_of_t_sens){
	bool exit = false;
	
	window win_master;
	//win_master.get_window_master_size();
	win_master.get_number_of_t_sensors(n_of_t_sens);
	attron(COLOR_PAIR(1));
	win_master.get_window_master_size();
	while(exit == false){
		
		win_master.show_window_master_frame();
		choose_sensor(t_sens, n_of_t_sens, win_master);
		
		switch(wgetch(stdscr)){
			case KEY_UP:
				if(win_master.choosed_option > 0){
					win_master.choosed_option-- ;
				}
				
				break;
				continue;
				
			case KEY_DOWN:
				if(win_master.choosed_option < n_of_t_sens -1){
					win_master.choosed_option++ ;
				}
				
				break;
				continue;
				
			case 27:
				exit = true;
				clear();
				graph_screen(t_sens, n_of_t_sens, win_master);
				break;
					
				
		}
		
	}
	
	
}

int main(){
	
	
	
	
	initscr();
	cbreak();
	start_color();
	keypad(stdscr, true);
	raw();
	nonl();
	curs_set(0);
	sensors_init(NULL);
	noecho();
	
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	
	
	
	sensors_chip_name const *chip;
	sensors_feature const *feature;
	int c = 0;
	int number_of_features = 0;
	int number_of_t_sens = 0;
	int i = 0;
	int j = 0;
	
	while((chip = sensors_get_detected_chips(0, &c)) != 0){
		int f = 0;
		while((feature = sensors_get_features(chip, &f)) != 0){
			number_of_features++ ;
		}		
	}
	
	sens *all_sens = new sens [number_of_features];
	
	c = 0;
	while((chip = sensors_get_detected_chips(0, &c)) != 0){
		int f = 0;
		while((feature = sensors_get_features(chip, &f)) != 0){
			all_sens[i].get_sens_patametrs(chip, feature, c, f);
			i++ ;
		}		
	}
	
	for(i = 0; i < number_of_features; i++){
		all_sens[i].get_sens_type();
		if(all_sens[i].temperature_sens == true){
			number_of_t_sens++ ;
		}
			
	}
	
	sens *temp_sens = new sens [number_of_t_sens];
	
	for(i = 0; i < number_of_features; i++){
		if(all_sens[i].temperature_sens == true){
			temp_sens[j] = all_sens[i];
			temp_sens[j].test();
			j++ ;
			
			
		}
	}
		
			
	main_loop(temp_sens, number_of_t_sens);
	//printw("%s", temp_sens[0].label);
	
	getch();
	
	endwin();
	
	return 0;
}

