/*
 * timer.c
 *
 *  Created on: Dec 2, 2024
 *      Author: Mr Duc Anh
 */

#include "timer.h"


uint8_t time_flag = 0;
int counter = 0;
void setTimer(int duration){
	if(duration >0){
		counter = duration /10;
	}
}

void timerRun(){
	counter--;
	if(counter <= 0){
		counter = 50;
		time_flag = 1;
	}
}


