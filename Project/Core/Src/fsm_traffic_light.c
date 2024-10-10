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
		clearAllClock();

		status = RED_GREEN;
		setTimer(0, TIME_GREEN);
	case RED_GREEN:
		//TODO
		HAL_GPIO_WritePin(GPIOA, LED_YELLOW_Pin | LED_GREEN_Pin | LED_RED_OP_Pin | LED_YELLOW_OP_Pin, 1);
		HAL_GPIO_WritePin(GPIOA, LED_RED_Pin | LED_GREEN_OP_Pin, 0);

		if (isTimerExpired(0) == 1) {
			status = RED_YELLOW;
			setTimer(0, TIME_YELLOW);
		}

		if (isButtonPressed(0) == 1) {
			value = TIME_RED;
			status = MOD_RED;
			setTimer(0, 500);
		}
		break;
	case RED_YELLOW:
		//TODO
		HAL_GPIO_WritePin(GPIOA, LED_YELLOW_Pin | LED_GREEN_Pin | LED_RED_OP_Pin | LED_GREEN_OP_Pin, 1);
		HAL_GPIO_WritePin(GPIOA, LED_RED_Pin | LED_YELLOW_OP_Pin, 0);

		if (isTimerExpired(0) == 1) {
			status = GREEN_RED;
			setTimer(0, TIME_GREEN);
		}

		if (isButtonPressed(0) == 1) {
			value = TIME_RED;
			status = MOD_RED;
			setTimer(0, 500);
		}
		break;
	case GREEN_RED:
		//TODO
		HAL_GPIO_WritePin(GPIOA, LED_RED_Pin | LED_YELLOW_Pin | LED_YELLOW_OP_Pin | LED_GREEN_OP_Pin, 1);
		HAL_GPIO_WritePin(GPIOA, LED_GREEN_Pin | LED_RED_OP_Pin, 0);

		if (isTimerExpired(0) == 1) {
			status = YELLOW_RED;
			setTimer(0, TIME_YELLOW);
		}

		if (isButtonPressed(0) == 1) {
			value = TIME_RED;
			status = MOD_RED;
			setTimer(0, 500);
		}
		break;
	case YELLOW_RED:
		HAL_GPIO_WritePin(GPIOA, LED_RED_Pin | LED_GREEN_Pin | LED_YELLOW_OP_Pin | LED_GREEN_OP_Pin, 1);
		HAL_GPIO_WritePin(GPIOA, LED_YELLOW_Pin | LED_RED_OP_Pin, 0);

		if (isTimerExpired(0) == 1) {
			status = RED_GREEN;
			setTimer(0, TIME_GREEN);
		}

		if (isButtonPressed(0) == 1) {
			value = TIME_RED;
			status = MOD_RED;
			setTimer(0, 500);
		}
		break;
	case MOD_RED:
		clearAllClock();

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
			value = TIME_YELLOW;
			status = MOD_AMBER;
			setTimer(0, 500);
		}
		break;
	case MOD_AMBER:
		clearAllClock();

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
			value = TIME_GREEN;
			status = MOD_GREEN;
			setTimer(0, 500);
		}
		break;
	case MOD_GREEN:
		clearAllClock();

		if (isTimerExpired(0) == 1) {
			HAL_GPIO_TogglePin(GPIOA, LED_GREEN_Pin | LED_GREEN_OP_Pin);
			setTimer(0, 500);
		}

		if (isButtonPressed(1) == 1) {
			value = (value > 9900) ? 0 : value + 100;
		}
		else if (isButtonPressed(2) == 1) {
			TIME_GREEN_tmp = value;
		}
		else if (isButtonPressed(0) == 1) {
			status = RED_GREEN;
		}
		break;
	default:
		break;
	}
}
