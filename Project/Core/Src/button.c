#include "button.h"

int KeyReg0[3] = {NORMAL_STATE};
int KeyReg1[3] = {NORMAL_STATE};
int KeyReg2[3] = {NORMAL_STATE};
int KeyReg3[3] = {NORMAL_STATE};

int TimeOutForKeyPress[3] = {200, 200, 200};
int button1_long_pressed = 0;
int button_flag[10];

int isButtonPressed(int id){
	if(button_flag[id] == 1){
		button_flag[id] = 0;
		return 1;
	}
	return 0;
}

int isButton1LongPressed(){
	if(button1_long_pressed == 1){
		button1_long_pressed = 0;
		return 1;
	}
	return 0;
}

void subKeyProcess(){
	//TODO
//	button1_flag = 1;
}

void getKeyInput(){
	for (int i = 0; i < 3; ++i) {
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
						TimeOutForKeyPress[i] = 200;
						button_flag[i] = 1;
					}
		    } else {
		    	TimeOutForKeyPress[i]--;
		        if (TimeOutForKeyPress[i] == 0) {
		        	KeyReg3[i] = NORMAL_STATE;
		        }
		    }
		}
	}
}

