/*
 * USART.C
 *
 *  Created on: Dec 2, 2024
 *      Author: Mr Duc Anh
 */
#include"USART.h"

uint8_t temp =0; //biến lưu giá trị nhận được.
uint8_t buffer[MAX_BUFFER_SIZE];// bộ đệm nhận dữ liệu
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;//cờ đếm thời gian chờ
uint8_t counter_again = 0;

uint8_t ADC_value = 0;
uint8_t command_flag = 0;// cờ xác định lệnh
char response[30];
uint8_t last_tick = 0;

void command_parser_fsm(){
	static uint8_t state = 0;

	switch(state){
	case 0://kiểm tra kí tự ban đầu
		if(buffer[0] == '!' && buffer_flag){
			state = 1;
		}
		break;
	case 1:// bắt đầu kiểm tra
		if(strncmp((char *)buffer, "!RST#", 5) == 0){//hàm strncmp = 0 khi 2 chuỗi giống nhau
			command_flag = 1;//yêu cầu giá trị từ ADC
			state = 0;
			memset(buffer, 0, MAX_BUFFER_SIZE);
			index_buffer = 0;
		}	else if(strncmp((char *)buffer, "!OK#", 4) == 0){
			command_flag = 2;//đã nhận được giá trị
			state = 0;
			memset(buffer, 0, MAX_BUFFER_SIZE);
			index_buffer = 0;
		}	else{
			state = 0;// thông tin nhận được là rác.
		}
		break;
	}
	buffer_flag = 0;// reset cờ dữ liệu mới
}

void uart_communication_fsm(){

	switch(command_flag){
	case 1:// gửi giá trị ADC
		sprintf(response, "!ADC=%d#\n", ADC_value);
		HAL_UART_Transmit(&huart2, (uint8_t *)response, strlen(response), 1000);
		last_tick = HAL_GetTick();
		command_flag = 0;
		break;
	case 2:
		HAL_UART_Transmit(&huart2, (uint8_t *)"!ACK#", 5, 1000);
		command_flag = 0;
		memset(response, '\0', 30);
		break;
	default:
		if(HAL_GetTick() - last_tick > TIMEOUT_MS && counter_again <4){// gửi lại
			HAL_UART_Transmit(&huart2, (uint8_t *)response, strlen(response), 1000);
			last_tick = HAL_GetTick();
			counter_again++;
		}
		else if(counter_again >= 4){// gửi quá 3 lần, có thể đầu cuối bên kia đã bị lỗi nên không gửi nữa.
			counter_again = 0;
			command_flag = 0;
		}
}
}




























