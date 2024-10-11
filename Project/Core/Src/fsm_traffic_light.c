/*
 * fsm_traffic_light.c
 *
 *  Created on: Oct 9, 2024
 *      Author: Hai
 */

#include "fsm_traffic_light.h"

int TIME_RED_tmp = 0;
int TIME_AMBER_tmp = 0;
int TIME_GREEN_tmp = 0;

void fsm_traffic_light_run() {
	switch (status) {
	case INIT:
		status = RED_GREEN;
		setTimer(0, TIME_GREEN);
		break;
	case RED_GREEN:
		value = timer_counter[0] + TIME_YELLOW / 10;
		value1 = timer_counter[0];
		HAL_GPIO_WritePin(GPIOA, LED_YELLOW_Pin | LED_GREEN_Pin | LED_RED_OP_Pin | LED_YELLOW_OP_Pin, 1);
		HAL_GPIO_WritePin(GPIOA, LED_RED_Pin | LED_GREEN_OP_Pin, 0);
		if (isTimerExpired(0) == 1) {
			status = RED_YELLOW;
			setTimer(0, TIME_YELLOW);
		}
		if (isButtonPressed(0) == 1) {
			status = MOD_RED;
			clearAllClock();
			value = TIME_RED / 10;
			value1 = 200;
			setTimer(0, 500);
		}
		break;
	case RED_YELLOW:
		value = timer_counter[0];
		value1 = timer_counter[0];
		HAL_GPIO_WritePin(GPIOA, LED_YELLOW_Pin | LED_GREEN_Pin | LED_RED_OP_Pin | LED_GREEN_OP_Pin, 1);
		HAL_GPIO_WritePin(GPIOA, LED_RED_Pin | LED_YELLOW_OP_Pin, 0);
		if (isTimerExpired(0) == 1) {
			status = GREEN_RED;
			setTimer(0, TIME_GREEN);
		}
		if (isButtonPressed(0) == 1) {
			status = MOD_RED;
			clearAllClock();
			value = TIME_RED / 10;
			value1 = 200;
			setTimer(0, 500);
		}
		break;
	case GREEN_RED:
		value = timer_counter[0];
		value1 = timer_counter[0] + TIME_YELLOW / 10;
		HAL_GPIO_WritePin(GPIOA, LED_RED_Pin | LED_YELLOW_Pin | LED_YELLOW_OP_Pin | LED_GREEN_OP_Pin, 1);
		HAL_GPIO_WritePin(GPIOA, LED_GREEN_Pin | LED_RED_OP_Pin, 0);
		if (isTimerExpired(0) == 1) {
			status = YELLOW_RED;
			setTimer(0, TIME_YELLOW);
		}
		if (isButtonPressed(0) == 1) {
			value = TIME_RED / 10;
			value1 = 200;
			status = MOD_RED;
			clearAllClock();
			setTimer(0, 500);
		}
		break;
	case YELLOW_RED:
		value = timer_counter[0];
		value1 = timer_counter[0];
		HAL_GPIO_WritePin(GPIOA, LED_RED_Pin | LED_GREEN_Pin | LED_YELLOW_OP_Pin | LED_GREEN_OP_Pin, 1);
		HAL_GPIO_WritePin(GPIOA, LED_YELLOW_Pin | LED_RED_OP_Pin, 0);
		if (isTimerExpired(0) == 1) {
			status = RED_GREEN;
			setTimer(0, TIME_GREEN);
		}
		if (isButtonPressed(0) == 1) {
			value = TIME_RED / 10;
			value1 = 200;
			status = MOD_RED;
			clearAllClock();
			setTimer(0, 500);
		}
		break;
	case MOD_RED:
		if (isTimerExpired(0) == 1) {
			HAL_GPIO_TogglePin(GPIOA, LED_RED_Pin | LED_RED_OP_Pin);
			setTimer(0, 500);
		}
		if (isButtonPressed(1) == 1) {
			value = (value > 9900) ? 0 : value + 100;
		}
		else if (isButtonPressed(2) == 1) {
			TIME_RED_tmp = value;
		}
		else if (isButtonPressed(0) == 1) {
			status = MOD_AMBER;
			clearAllClock();
			value = TIME_YELLOW / 10;
			value1 = 300;
			setTimer(0, 500);
		}
		break;
	case MOD_AMBER:
		if (isTimerExpired(0) == 1) {
			HAL_GPIO_TogglePin(GPIOA, LED_YELLOW_Pin | LED_YELLOW_OP_Pin);
			setTimer(0, 500);
		}

		if (isButtonPressed(1) == 1) {
			value = (value > 9900) ? 0 : value + 100;
		}
		else if (isButtonPressed(2) == 1) {
			TIME_AMBER_tmp = value;
		}
		else if (isButtonPressed(0) == 1) {
			status = MOD_GREEN;
			clearAllClock();
			value = TIME_GREEN / 10;
			value1 = 400;
			setTimer(0, 500);
		}
		break;
	case MOD_GREEN:
		if (isTimerExpired(0) == 1) {
			HAL_GPIO_TogglePin(GPIOA, LED_GREEN_Pin | LED_GREEN_OP_Pin);
			setTimer(0, 500);
		}

		if (isButtonPressed(1) == 1) {
			value = (value > 9900) ? 0 : value + 100;
		}
		else if (isButtonPressed(2) == 1) {
			TIME_GREEN_tmp = value;
			if (TIME_GREEN_tmp + TIME_AMBER_tmp == TIME_RED_tmp) {
				TIME_GREEN = TIME_GREEN_tmp * 10;
				TIME_YELLOW = TIME_AMBER_tmp * 10;
				TIME_RED = TIME_RED_tmp * 10;
			}
		}
		else if (isButtonPressed(0) == 1) {
			status = RED_GREEN;
			setTimer(0, TIME_GREEN);
		}
		break;
	default:
		break;
	}
}
