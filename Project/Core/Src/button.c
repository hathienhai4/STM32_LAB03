#include "button.h"

int KeyReg0 = NORMAL_STATE;
int KeyReg1 = NORMAL_STATE;
int KeyReg2 = NORMAL_STATE;
int KeyReg3 = NORMAL_STATE;

int TimeOutForKeyPress = 200;
int button1_pressed = 0;
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

void getKeyInput(int id){
	KeyReg0 = KeyReg1;
	KeyReg1 = KeyReg2;
	switch (id) {
	case 0:
		KeyReg2 = HAL_GPIO_ReadPin(MODULE_GPIO_Port, MODULE_Pin);
	case 1:
		KeyReg2 = HAL_GPIO_ReadPin(TIME_GPIO_Port, TIME_Pin);
	case 2:
		KeyReg2 = HAL_GPIO_ReadPin(VALUE_GPIO_Port, VALUE_Pin);
	}

	if ((KeyReg0 == KeyReg1) && (KeyReg1 == KeyReg2)) {
		if (KeyReg3 != KeyReg2) {
			KeyReg3 = KeyReg2;
			if (KeyReg2 == PRESSED_STATE) {
				TimeOutForKeyPress = 200;
				button_flag[id] = 1;
			}
    } else {
    	TimeOutForKeyPress--;
        if (TimeOutForKeyPress == 0) {
        	KeyReg3 = NORMAL_STATE;
        }
    }
	}
}

