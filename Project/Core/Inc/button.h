/*
 * button.h
 *
 *  Created on: Oct 5, 2023
 *      Author: KAI
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define NORMAL_STATE 	SET
#define PRESSED_STATE 	RESET
#define NUM_BUTTON		3

int isButtonPressed(int);
void getKeyInput();

#endif /* INC_BUTTON_H_ */

