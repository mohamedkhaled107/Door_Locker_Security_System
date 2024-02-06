/******************************************************************************
*  Module:    Buzzer
*  File name: buzzer.c
*  Created on: Oct 22, 2023
*  Author: Mohamed Khaled
*******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_

#include "gpio.h"

#define BUZZER_PORT_ID PORTD_ID
#define BUZZER_PIN_ID  PIN3_ID


void BUZZER_init(void);
void BUZZER_ON(void);
void BUZZER_OFF(void);

#endif /* BUZZER_H_ */
