/*
 * display7SEG.h
 *
 *  Created on: Oct 9, 2024
 *      Author: Hai
 */

#ifndef INC_DISPLAY7SEG_H_
#define INC_DISPLAY7SEG_H_

#include "global.h"

void display7SEG(int num);
void display7SEG_2(int num);
void update7SEG(int index);
void updateClockBuffer();
void clearAllClock();

#endif /* INC_DISPLAY7SEG_H_ */
