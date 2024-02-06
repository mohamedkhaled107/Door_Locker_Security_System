/******************************************************************************
*  Module: DC_MOTOR
*  File name: dcmotor.c
*  Created on: Oct 8, 2023
*  Author: Mohamed Khaled
*******************************************************************************/
/*******************************************************************************
*                                                                              *
*                                  INCLUDES                                    *
*                                                                              *
********************************************************************************/
#include "gpio.h"
#include "dcmotor.h"
#include "pwm.h"
/*******************************************************************************
*                                                                              *
*                              FUNCTIONS Definitions                           *
*                                                                              *
********************************************************************************/
void DCMOTOR_init(void){
	GPIO_setupPinDirection(DCMOTOR_PORT_ID,DCMOTOR_PINA_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(DCMOTOR_PORT_ID,DCMOTOR_PINB_ID,PIN_OUTPUT);

	GPIO_writePin(DCMOTOR_PORT_ID,DCMOTOR_PINA_ID,LOGIC_LOW);
	GPIO_writePin(DCMOTOR_PORT_ID,DCMOTOR_PINB_ID,LOGIC_LOW);
}

void DCMOTOR_rotate(DCMOTOR_State state,uint8 speed){
	uint8 temp_duty_cycle;
	switch (state){
	case STOP :
		GPIO_writePin(DCMOTOR_PORT_ID,DCMOTOR_PINA_ID,LOGIC_LOW);
		GPIO_writePin(DCMOTOR_PORT_ID,DCMOTOR_PINB_ID,LOGIC_LOW);
		break;
	case CLOCK_WISE :
		GPIO_writePin(DCMOTOR_PORT_ID,DCMOTOR_PINA_ID,LOGIC_HIGH);
		GPIO_writePin(DCMOTOR_PORT_ID,DCMOTOR_PINB_ID,LOGIC_LOW);
		break;
	case ANTI_CLOCK_WISE :
		GPIO_writePin(DCMOTOR_PORT_ID,DCMOTOR_PINA_ID,LOGIC_LOW);
		GPIO_writePin(DCMOTOR_PORT_ID,DCMOTOR_PINB_ID,LOGIC_HIGH);
		break;
	}
	temp_duty_cycle = (speed * 255) / 100 ;
	PWM_Timer0_Start(temp_duty_cycle);
}

