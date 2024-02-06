/******************************************************************************
*  Module:    Buzzer
*  File name: buzzer.c
*  Created on: Oct 22, 2023
*  Author: Mohamed Khaled
*******************************************************************************/
#include "gpio.h"
#include "buzzer.h"
#include "std_types.h"


void BUZZER_init(void)
{
GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,PIN_OUTPUT);
}

void BUZZER_ON(void)
{
   /*Make the Buzzer Beebs*/
   GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);
}

void BUZZER_OFF(void)
{
	/*Make the Buzzer Stops*/
	 GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}
