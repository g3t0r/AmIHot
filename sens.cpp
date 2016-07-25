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
	
	
}

void sens::refresh_value(){
	sensors_get_value(chip_name, feature_name->first_subfeature, &value);
}

void sens::get_sens_type(){
	if(name[0] == 't')
		temperature_sens = true;
		
	if(name[0] == 'f')
		fan_sens = true;
}

void sens::test(){
	printf("%s \n", label);
}