/******************************************************************************
*  Module: PWM
*  File name: pwm.c
*  Created on: Oct 8, 2023
*  Author: Mohamed Khaled
*******************************************************************************/
/*******************************************************************************
*                                                                              *
*                                  INCLUDES                                    *
*                                                                              *
********************************************************************************/
#include "gpio.h"
#include "pwm.h"
#include "common_macros.h"
#include <avr/io.h>
/*******************************************************************************
*                                                                              *
*                              FUNCTIONS Definitions                           *
*                                                                              *
********************************************************************************/
void PWM_Timer0_Start(uint8 duty_cycle){
	/* configure the timer
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01) | (1 << CS01);

	/*set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.*/
	GPIO_setupPinDirection( COMPARE_VALUE_PORT_ID, COMPARE_VALUE_PIN_ID , PIN_OUTPUT);
	TCNT0 = 0; // Set Timer Initial Value to 0
	/* calculations for the compare value
	 * eg: if 50 send then 50% of the duty cycle is set as compare value
	 */
	OCR0 = duty_cycle;

}
