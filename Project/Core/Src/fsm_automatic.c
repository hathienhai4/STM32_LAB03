/*
 * fsm_automatic.c
 *
 *  Created on: Oct 9, 2024
 *      Author: Hai
 */

#include "fsm_automatic.h"

void fsm_automatic_run() {
	switch (status) {
	case INIT:
		//TODO
		HAL_GPIO_WritePin(GPIOA, LED_RED_Pin | LED_YELLOW_Pin | LED_GREEN_Pin, 1);

		status = AUTO_RED;
		setTimer(0, 5000);
		isButton1Pressed();
		break;
	case AUTO_RED:
		//TODO
		HAL_GPIO_WritePin(GPIOA, LED_YELLOW_Pin | LED_GREEN_Pin, 1);
		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, 0);

		if (isTimerExpired(0) == 1) {
			status = AUTO_GREEN;
			setTimer(0, 3000);
		}

		if (isButton1Pressed() == 1) {
			status = MAN_RED;
			setTimer(0, 10000);
		}
		break;
	case AUTO_GREEN:
		//TODO
		HAL_GPIO_WritePin(GPIOA, LED_RED_Pin | LED_YELLOW_Pin, 1);
		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, 0);

		if (isTimerExpired(0) == 1) {
			status = AUTO_YELLOW;
			setTimer(0, 2000);
		}
		break;
	case AUTO_YELLOW:
		//TODO
		HAL_GPIO_WritePin(GPIOA, LED_RED_Pin | LED_GREEN_Pin, 1);
		HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, 0);

		if (isTimerExpired(0) == 1) {
			status = AUTO_RED;
			isButton1Pressed();
			setTimer(0, 5000);
		}
		break;
	default:
		break;
	}
}
