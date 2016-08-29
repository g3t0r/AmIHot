#include <ncurses.h>
#include <sensors/sensors.h>
#include <unistd.h>
#include <cstring>
#include <time.h>
#include "window.h"
#include "sens.h"

int get_number_of_pages(window &win_m, sens *t_sens, int n_of_t_sens);
void show_left_arrows(window &win_m, int pages, int actual_page);
void show_right_arrows(window &win_m, int pages, int actual_page);
void show_all_graphs(window &win_m, sens *t_sens, int n_of_t_sens, int *graphs_on_pages, int pages, int &actual_page, char &signal);
void get_number_of_graphs_on_pages(window &win_m, sens *t_sens, int n_of_t_sens, int * graphs_on_pages, int pages);
void all_graphs_screen(window &win_m, sens *t_sens, int n_of_t_sens, bool &exit_program);
void help(window &win_m, bool &exit_program);
void graph_screen(sens *graph, int n_of_graph, window &win_m, bool &exit_program);
void choose_sensor(sens *t_sens, int n_of_t_sens, window &win_m, bool &exit_program);
void main_loop(sens *t_sens, int n_of_t_sens);

void show_left_arrows(window &win_m, int pages, int actual_page){
	if(actual_page > 0){
		for(int i = win_m.window_graph_start_y; i < win_m.window_graph_start_y + win_m.window_graph_max_y; i++)
			mvprintw(i, 1, "<");
	}
}

void show_right_arrows(window &win_m, int pages, int actual_page){
	win_m.get_window_master_size();
	if(actual_page != pages -1){
		for(int i = win_m.window_graph_start_y; i < win_m.window_graph_start_y + win_m.window_graph_max_y; i++)
			mvprintw(i, win_m.window_master_max_x -2, ">");
	}
}

void show_all_graphs(window &win_m, sens *t_sens, int n_of_t_sens, int *graphs_on_pages, int pages, int &actual_page, char &signal){
	clear();
	int graphs_done = 0;
	signal = NULL;
	bool exit = false;
	
	win_m.get_window_master_size();
	for(int i = 0; i < actual_page; i++){
		graphs_done += graphs_on_pages[i];
	}
	
	show_left_arrows(win_m, pages, actual_page);
	show_right_arrows(win_m, pages, actual_page);
	refresh();
	
	int j = 1;
	int k = graphs_on_pages[actual_page];
	for(int i = graphs_done; i < graphs_done + graphs_on_pages[actual_page]; i++){
		
		t_sens[i].get_window_master_size();
		t_sens[i].create_graph(win_m.window_master_max_x/(graphs_on_pages[actual_page]+1)*j - win_m.window_graph_max_x/2);
		t_sens[i].show_label();
		t_sens[i].show_graph_border();
		j++;
	}
	win_m.show_window_master_frame();
	mvprintw(1,1,"Press h for help");
	
	while(exit == false){
		
		for(int i = graphs_done; i < graphs_done + graphs_on_pages[actual_page]; i++){
			t_sens[i].show_graph_border();
		}
		
		for(int i = graphs_done; i < graphs_done + graphs_on_pages[actual_page]; i++){
			t_sens[i].refresh_value();			
		}
		
		for(int i = graphs_done; i < graphs_done + graphs_on_pages[actual_page]; i++){
			t_sens[i].refresh_graph();
		}
			
		for(int i = graphs_done; i < graphs_done + graphs_on_pages[actual_page]; i++){
			t_sens[i].show_temp();
		}
		
		for(int i = graphs_done; i < graphs_done + graphs_on_pages[actual_page]; i++){
			wnoutrefresh(t_sens[i].localwin);
		}
		
		refresh();
		
		
		timeout(500);
		
		switch(wgetch(stdscr)){
			case 'q':
			case 'Q':
				for(int i = graphs_done; i < graphs_done + graphs_on_pages[actual_page]; i++)
					t_sens[i].destroy_graph();
					
				signal = 'q';
				clear();
				return;
				
			case KEY_LEFT:
				if(actual_page > 0){
					for(int i = graphs_done; i < graphs_done + graphs_on_pages[actual_page]; i++)
						t_sens[i].destroy_graph();
						
					actual_page--;
					return;
				}
				
				else
					break;
					
					
			case KEY_RIGHT:				
				if(actual_page < pages -1){
					for(int i = graphs_done; i < graphs_done + graphs_on_pages[actual_page]; i++)
						t_sens[i].destroy_graph();
				
					actual_page++;
					return;
				}					
				else
					break;
					
			case 27:
				for(int i = graphs_done; i < graphs_done + graphs_on_pages[actual_page]; i++)
					t_sens[i].destroy_graph();
				signal = 27;
				return;
				
			case 'H':
			case 'h':
				for(int i = graphs_done; i < graphs_done + graphs_on_pages[actual_page]; i++)
					t_sens[i].destroy_graph();
					
				signal = 'h';
				return;
		}
				
	}
	nodelay(stdscr, 0);
	
	clear();
	
}

void get_number_of_graphs_on_pages(window &win_m, sens *t_sens, int n_of_t_sens, int * graphs_on_pages, int pages){
	int graphs_done = 0;
	int size = 0;
	win_m.get_window_master_size();
	int i = 0;
	int j = 0;
	

	  
	for(int k = 0; k < n_of_t_sens; k++){
		if(t_sens[i].space_for_graph > win_m.window_master_max_x){
			return;
			mvprintw(1,1,"Terminal too small");
			refresh();
			getch();
		}
	}
	
	do{
					
		if(t_sens[i].space_for_graph + size < win_m.window_master_max_x){
			size += t_sens[i].space_for_graph;
			graphs_done++;
			i++;
			
		}
		else{
			size = 0;
			graphs_on_pages[j] = graphs_done;
			j++;
			graphs_done = 0;
		}
	}while(j < pages);
}

int get_number_of_pages(window &win_m, sens *t_sens, int n_of_t_sens){
	
	int graphs_left = n_of_t_sens;
	int size = 0;
	int pages = 1;
	int i = 0;
	win_m.get_window_master_size();
	while(i < n_of_t_sens){
		if(t_sens[i].space_for_graph + size < win_m.window_master_max_x){
			size += t_sens[i].space_for_graph;
			i++;
		}
		else{
			pages++;
			size = 0;
			
			
		}
	}
		
	return pages;
}

void all_graphs_screen(window &win_m, sens *t_sens, int n_of_t_sens, bool &exit_program){
	clear();
	
	bool exit = false;
	int graphs_done = 0;
	int free_space = 0;
	int actual_graph = 0;
	int actual_page = 0;
	int pages = get_number_of_pages(win_m, t_sens, n_of_t_sens);
	int *graphs_on_pages = new int [pages];
	char signal;
	get_number_of_graphs_on_pages(win_m, t_sens, n_of_t_sens, graphs_on_pages, pages);
	
	while(true){
		show_all_graphs(win_m, t_sens, n_of_t_sens, graphs_on_pages, pages, actual_page, signal);
		graphs_done = 0;
		switch(signal){
			case 'q':
			case 'Q':
				exit_program = true;
				return;
			
			case 27:
				clear();
				return;
			
			case 'h':
				help(win_m, exit_program);
				return;
		}
	}
	
			
	
	refresh();
	getch();
	
	
	
	
}

void help(window &win_m, bool &exit_program){
	
	char help_text[18][100] = {
		{"AmIHot v0.02 created by g3t0r (i.never.sleep@op.pl)"},
		{},
		{"Use"},
		{"Arrows to move"},
		{"ESC to choose sensor"},
		{"A or a to show all graphs"},
		{"Q or q to quit"},
		{"H or h to open this window"},
		{},
		{"No sensors detected?"},
		{"Try to run \"sensors-detect\" as root"},
		{},
		{"All bugs and errors please report on my email(i.never.sleep@op.pl)"},
		{},
		{"Updates will be published on my github profile(https://github.com/g3t0r)"},
		{},
		{"Licence"},
		{"GNU/GPL"}		
	};
	
	clear();
	nodelay(stdscr, 0);	
		
	for(int i = 0; i < 18; i++)
		mvprintw(7+i, win_m.window_master_max_x/2 - strlen(help_text[i])/2, "%s", help_text[i]);
		
	refresh();	
	
	switch(wgetch(stdscr)){
		case 'Q':
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
	
	graph[win_m.choosed_option].get_window_master_size();
	win_m.show_window_master_frame();
	graph[win_m.choosed_option].create_graph(win_m.window_master_max_x/2 - win_m.window_graph_max_x/2);
	graph[win_m.choosed_option].show_label();	
	graph[win_m.choosed_option].show_graph_border();
	mvprintw(1,1,"Press h for help");
	mvprintw(2,1,"Press a to show all graphs");

	while(exit == false){
		
		graph[win_m.choosed_option].show_graph_border();
		graph[win_m.choosed_option].refresh_value();
		graph[win_m.choosed_option].refresh_graph();
		graph[win_m.choosed_option].show_temp();
		wnoutrefresh(graph[win_m.choosed_option].localwin);
		
		timeout(100);
		c = wgetch(stdscr);
		nodelay(stdscr, 0);
		switch(c){
			case 'Q':
			case 'q':
				exit_program = true;
				graph[win_m.choosed_option].destroy_graph();
				return;
				break;
				
			case 27:
				exit = true;
				graph[win_m.choosed_option].hide_temp();
				graph[win_m.choosed_option].destroy_graph();
				clear();
				break;
				
			case 'h':
			case 'H':
				exit = true;
				help(win_m, exit_program);
				graph[win_m.choosed_option].destroy_graph();
				break;
				
			case 'A':
			case 'a':
				all_graphs_screen(win_m, graph, n_of_graph, exit_program);
				return;
		}
	}
}

void choose_sensor(sens *t_sens, int n_of_t_sens, window &win_m, bool &exit_program){
	
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
	win_master.get_number_of_t_sensors(n_of_t_sens);
	attron(COLOR_PAIR(1));
	win_master.get_window_master_size();
	
	while(exit_program == false){
		exit_program = false;
		exit = false;
		
		while(exit == false){
			mvprintw(1,1,"Press h for help");
			mvprintw(2,1,"Press a to show all graphs");
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
					
				case 'Q':
				case 'q':
					exit_program = true;
					return;
					break;
				
					
				case 'h':
				case 'H':
					exit = true;					
					clear();
					help(win_master, exit_program);
					break;
					
				case 'a':
				case 'A':
					exit = true;
					all_graphs_screen(win_master, t_sens, n_of_t_sens, exit_program);
				

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
			j++ ;			
		}
	}
			
	main_loop(temp_sens, number_of_t_sens);
	endwin();	
	
	return 0;
}

