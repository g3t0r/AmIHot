#include <ncurses.h>
#include <sensors/sensors.h>
#include <cstring>
#include <time.h>
#include "window.h"
#include "sens.h"

void main_loop(sens *t_sens, int n_of_t_sens){
	bool exit = false;
	window win_master;
	win_master.get_window_master_size();
	while(exit == false){
		win_master.show_window_master_frame();
		getch();
	}
	
	
}

int main(){
	
	
	
	
	initscr();
	cbreak();
	start_color();
	keypad(stdscr, true);
	curs_set(0);
	sensors_init(NULL);
	
	
	
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
	
	
	getch();
	endwin();
	
	return 0;
}

