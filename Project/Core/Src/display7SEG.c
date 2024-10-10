/*
 * display7SEG.c
 *
 *  Created on: Oct 9, 2024
 *      Author: Hai
 */

#include "display7SEG.h"

int index_led = 0;
int led_buffer[4] = {1, 2, 3, 4};

void display7SEG(int num) {
	switch (num) {
	case 0:
		HAL_GPIO_WritePin(GPIOB, a_Pin | b_Pin | c_Pin | d_Pin | e_Pin | f_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, g_Pin, 1);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOB, b_Pin | c_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, a_Pin | d_Pin | e_Pin | f_Pin | g_Pin, 1);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOB, a_Pin | b_Pin | d_Pin | e_Pin | g_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, c_Pin | f_Pin, 1);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOB, a_Pin | b_Pin | c_Pin | d_Pin | g_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, e_Pin | f_Pin, 1);
		break;
	case 4:
		HAL_GPIO_WritePin(GPIOB, b_Pin | c_Pin | f_Pin | g_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, a_Pin | d_Pin | e_Pin, 1);
		break;
	case 5:
		HAL_GPIO_WritePin(GPIOB, a_Pin | c_Pin | d_Pin | f_Pin | g_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, b_Pin | e_Pin, 1);
		break;
	case 6:
		HAL_GPIO_WritePin(GPIOB, a_Pin | c_Pin | d_Pin | e_Pin | f_Pin | g_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, b_Pin, 1);
		break;
	case 7:
		HAL_GPIO_WritePin(GPIOB, a_Pin | b_Pin | c_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, d_Pin | e_Pin | f_Pin | g_Pin, 1);
	case 8:
		HAL_GPIO_WritePin(GPIOB, a_Pin | b_Pin | c_Pin | d_Pin | e_Pin | f_Pin | g_Pin, 0);
		break;
	case 9:
		HAL_GPIO_WritePin(GPIOB, a_Pin | b_Pin | c_Pin | d_Pin | f_Pin | g_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, e_Pin, 1);
		break;
	}
}

void display7SEG_2(int num) {
	switch (num) {
	case 0:
		HAL_GPIO_WritePin(GPIOB, a2_Pin | b2_Pin | c2_Pin | d2_Pin | e2_Pin | f2_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, g2_Pin, 1);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOB, b2_Pin | c2_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, a2_Pin | d2_Pin | e2_Pin | f2_Pin | g2_Pin, 1);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOB, a2_Pin | b2_Pin | d2_Pin | e2_Pin | g2_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, c2_Pin | f2_Pin, 1);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOB, a2_Pin | b2_Pin | c2_Pin | d2_Pin | g2_Pin, 0);
		HAL_GPIO_WritePin(GPIOB, e2_Pin | f2_Pin, 1);
		break;
	}
}

void update7SEG(int index){
    switch (index){
        case 0:
            HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 1);
            HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 0);
            display7SEG(led_buffer[0]);
            display7SEG_2(led_buffer[2]);
            break;
        case 1:
        	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, 1);
        	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, 0);
			display7SEG(led_buffer[1]);
			display7SEG_2(led_buffer[3]);
            break;
        default:
            break;
    }
}

void updateClockBuffer() {
    led_buffer[0] = value / 10;
    led_buffer[1] = value % 10;
    led_buffer[2] = value1 / 10;
    led_buffer[3] = value1 % 10;
}

void clearAllClock() {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_All, 1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_All, 1);
}
