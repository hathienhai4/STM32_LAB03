#include "button.h"

int KeyReg0[NUM_BUTTON] = {NORMAL_STATE};
int KeyReg1[NUM_BUTTON] = {NORMAL_STATE};
int KeyReg2[NUM_BUTTON] = {NORMAL_STATE};
int KeyReg3[NUM_BUTTON] = {NORMAL_STATE};

int TimeOutForKeyPress[NUM_BUTTON] = {100, 100, 100};
int button_long_pressed[10];
int button_flag[10];

int isButtonPressed(int index){
	if(button_flag[index] == 1){
		button_flag[index] = 0;
		return 1;
	}
	return 0;
}

int isButtonLongPressed(int index){
	if(button_long_pressed[index] == 1){
		button_long_pressed[index] = 0;
		return 1;
	}
	return 0;
}

void subKeyProcess(){
	//TODO
//	button1_flag = 1;
}

void getKeyInput(){
	for (int i = 0; i < NUM_BUTTON; ++i) {
		KeyReg0[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg2[i];
		switch (i) {
		case 0:
			KeyReg2[0] = HAL_GPIO_ReadPin(MODULE_GPIO_Port, MODULE_Pin);
		case 1:
			KeyReg2[1] = HAL_GPIO_ReadPin(TIME_GPIO_Port, TIME_Pin);
		case 2:
			KeyReg2[2] = HAL_GPIO_ReadPin(VALUE_GPIO_Port, VALUE_Pin);
		}

		if ((KeyReg0[i] == KeyReg1[i]) && (KeyReg1[i] == KeyReg2[i])) {
			if (KeyReg3[i] != KeyReg2[i]) {
				KeyReg3[i] = KeyReg2[i];
				if (KeyReg2[i] == PRESSED_STATE) {
					TimeOutForKeyPress[i] = 100;
					button_flag[i] = 1;
				}
			}
			else {
				--TimeOutForKeyPress[i];
				if (TimeOutForKeyPress[i] == 0) {
					if (KeyReg2[i] == PRESSED_STATE) {
						button_flag[i] = 1;
					}
					TimeOutForKeyPress[i] = 25;
				}
			}
		}
	}
}

