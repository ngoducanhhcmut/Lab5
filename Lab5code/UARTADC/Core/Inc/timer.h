/*
 * timer.h
 *
 *  Created on: Dec 2, 2024
 *      Author: Mr Duc Anh
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_
#include "main.h"
extern uint8_t time_flag;

void setTimer(int duration);
void timerRun();
#endif /* INC_TIMER_H_ */
