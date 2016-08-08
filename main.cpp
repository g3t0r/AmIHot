#include <ncurses.h>
#include <sensors/sensors.h>
#include <unistd.h>
#include <cstring>
#include <time.h>
#include "window.h"
#include "sens.h"

void help(window &win_m, bool &exit_program){
	clear();
	nodelay(stdscr, 0);
	win_m.show_window_master_frame();
	mvprintw(4, win_m.window_master_max_x/2 - sizeof("AmIHot v0.01 created by g3t0r (i.never.sleep@op.pl)")/2, "AmIHot v0.01 created by g3t0r (i.never.sleep@op.pl)" );
	mvprintw(6, win_m.window_master_max_x/2 - sizeof("Use")/2, "Use" );
	mvprintw(7, win_m.window_master_max_x/2 - sizeof("Arrows to move")/2, "Arrows to move" );
	mvprintw(8, win_m.window_master_max_x/2 - sizeof("ESC to choose sensor")/2, "ESC to choose sensor");
	mvprintw(9, win_m.window_master_max_x/2 - sizeof("Q or q to quit")/2, "Q or q to quit");
	mvprintw(10, win_m.window_master_max_x/2 - sizeof("H or h to open this window")/2, "H or h to open this window");
	mvprintw(12, win_m.window_master_max_x/2 - sizeof("No sensors detected?")/2, "No sensors detected?");
	mvprintw(13, win_m.window_master_max_x/2 - sizeof("Try to run \"sensors-detect\" as root")/2, "Try to run \"sensors-detect\" as root");
	mvprintw(15, win_m.window_master_max_x/2 - sizeof("All bugs and errors please report on my email(i.never.sleep@op.pl)")/2, "All bugs and errors please report on my email(i.never.sleep@op.pl)");
	mvprintw(17, win_m.window_master_max_x/2 - sizeof("Updates will be published on my github profile(https://github.com/g3t0r)")/2, "Updates will be published on my github profile(https://github.com/g3t0r)");
	
	
	switch(wgetch(stdscr)){
		case 'Q':
			exit_program = true;
			return;
			break;
				
				case 'q':
					exit_program = true;
					return;
					break;
	}
	clear();
	win_m.show_window_master_frame();
	
}

void graph_screen(sens *graph, int n_of_graph, window &win_m, bool &exit_program){
	clear();
	char c;
	bool exit = false;
	//printw("%s \n", graph[win_m.choosed_option].label);
	//printw("%d", win_m.choosed_option);
	graph[win_m.choosed_option].get_window_master_size();
	win_m.show_window_master_frame();
	graph[win_m.choosed_option].create_graph();
	graph[win_m.choosed_option].show_graph_border();
	
	while(exit == false){
		//graph[win_m.choosed_option].get_window_master_size();
		//win_m.show_window_master_frame();
		
		graph[win_m.choosed_option].show_graph_border();
		graph[win_m.choosed_option].refresh_value();
		graph[win_m.choosed_option].refresh_graph();
		graph[win_m.choosed_option].show_temp();
		
		timeout(100);
		c = wgetch(stdscr);
		nodelay(stdscr, 0);
		switch(c){
			case 'Q':
				exit_program = true;
				return;
				break;
				
			case 'q':
				exit_program = true;
				return;
				break;
				
			case 27:
				exit = true;
				graph[win_m.choosed_option].hide_temp();
				break;
				//return;
				
			case 'h':
				exit = true;
				help(win_m, exit_program);
				break;
				
			case 'H':
				exit = true;
				help(win_m, exit_program);
				break;
			
		}
		
		
		//getch();
		
		
	}
	
		
}

void choose_sensor(sens *t_sens, int n_of_t_sens, window &win_m, bool &exit_program){
	//clear();
	//win_m.show_window_master_frame();
	
	mvprintw(win_m.window_master_max_y/2 - n_of_t_sens/2 -2, win_m.window_master_max_x/2 - sizeof("Choose sensor")/2, "Choose sensor");
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
	bool exit_program = false;
	bool exit = false;
	
	window win_master;
	//win_master.get_window_master_size();
	win_master.get_number_of_t_sensors(n_of_t_sens);
	attron(COLOR_PAIR(1));
	win_master.get_window_master_size();
	mvprintw(1,1,"Press h for help");
	while(exit_program == false){
		exit_program = false;
		exit = false;
		
		while(exit == false){
			
			//clear();
			wrefresh(stdscr);
			

			win_master.show_window_master_frame();
			choose_sensor(t_sens, n_of_t_sens, win_master, exit_program);

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

				case 13:
					exit = true;
					clear();
					graph_screen(t_sens, n_of_t_sens, win_master, exit_program);
					break;
					//continue;
					
				case 'Q':
					exit_program = true;
					return;
					break;
				
				case 'q':
					exit_program = true;
					return;
					break;
					
				case 'h':					
					exit = true;					
					clear();
					help(win_master, exit_program);
					break;
					
				case 'H':					
					exit = true;					
					clear();
					help(win_master, exit_program);
					break;
					
					


		}

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
	nodelay(stdscr, TRUE);
	
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
			//temp_sens[j].test();
			j++ ;
			
			
		}
	}
		
			
	main_loop(temp_sens, number_of_t_sens);
	//printw("%s", temp_sens[0].label);
	
	//getch();
	
	endwin();
	
	return 0;
}

