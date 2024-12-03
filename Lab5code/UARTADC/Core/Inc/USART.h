/*
 * USART.h
 *
 *  Created on: Dec 2, 2024
 *      Author: Mr Duc Anh
 */
#ifndef INC_USART_H_
#define INC_USART_H_

#include"main.h"
#include"string.h"
#include "stm32f1xx_hal.h"
#include <stdio.h>

#define MAX_BUFFER_SIZE 30
#define TIMEOUT_MS 3000

extern uint8_t temp; //biến lưu giá trị nhận được.
extern uint8_t buffer[MAX_BUFFER_SIZE];// bộ đệm nhận dữ liệu
extern uint8_t index_buffer;
extern uint8_t buffer_flag;//cờ đếm thời gian chờ
extern uint8_t counter_again;

extern uint8_t ADC_value;
extern uint8_t command_flag;// cờ xác định lệnh
extern char response[30];
extern uint8_t last_tick ;

void command_parser_fsm();
void uart_communication_fsm();

#endif /* INC_USART_H_ */
