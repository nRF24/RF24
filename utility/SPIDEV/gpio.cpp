/* 
 * https://github.com/mrshu/GPIOlib
 * Copyright (c) 2011, Copyright (c) 2011 mr.Shu
 * All rights reserved. 
 * 
 * Modified on 24 June 2012, 11:06 AM
 * File:   gpio.cpp
 * Author: purinda (purinda@gmail.com)
 * 
 */

#include "gpio.h"
#include <stdlib.h>
#include <unistd.h>

GPIO::GPIO() {
}

GPIO::~GPIO() {
}

void GPIO::open(int port, int DDR)
{
	FILE *f;
	f = fopen("/sys/class/gpio/export", "w");
	fprintf(f, "%d\n", port);
	fclose(f);

    int counter = 0;
	char file[128];    
	sprintf(file, "/sys/class/gpio/gpio%d/direction", port);  
    
    while( ( f = fopen(file,"w")) == NULL ){ //Wait 10 seconds for the file to be accessible if not open on first attempt
        sleep(1);
        counter++;
        if(counter > 10){
          perror("Could not open /sys/class/gpio/gpio%d/direction");
          exit(0);
        }
    }
	if (DDR == 0)
          fprintf(f, "in\n");
	else  fprintf(f, "out\n");
    
    fclose(f);

}

void GPIO::close(int port)
{
	FILE *f;
	f = fopen("/sys/class/gpio/unexport", "w");
	fprintf(f, "%d\n", port);
	fclose(f);
}

int GPIO::read(int port)
{
	FILE *f;
	
	char file[128];
	sprintf(file, "/sys/class/gpio/gpio%d/value", port);
	f = fopen(file, "r");

	int i;
	fscanf(f, "%d", &i);
	fclose(f);
	return i;

}
void GPIO::write(int port, int value){
	FILE *f;

	char file[128];
	sprintf(file, "/sys/class/gpio/gpio%d/value", port);
	f = fopen(file, "w");
	
	if (value == 0)	fprintf(f, "0\n");
	else		fprintf(f, "1\n");
	
	fclose(f);
}
