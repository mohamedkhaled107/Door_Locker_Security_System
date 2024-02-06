/******************************************************************************
*  Module: DC_MOTOR
*  File name: dcmotor.h
*  Created on: Oct 8, 2023
*  Author: Mohamed Khaled
*******************************************************************************/

#ifndef DCMOTOR_H_
#define DCMOTOR_H_
/*******************************************************************************
 *                                  Includes                                   *
 *******************************************************************************/
#include "gpio.h"
#include "std_types.h"
#include "avr/io.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define DCMOTOR_PORT_ID PORTA_ID
#define DCMOTOR_PINA_ID PIN0_ID
#define DCMOTOR_PINB_ID PIN1_ID
/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
	STOP,CLOCK_WISE,ANTI_CLOCK_WISE
}DCMOTOR_State;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void DCMOTOR_init(void);
void DCMOTOR_rotate(DCMOTOR_State state,uint8 speed);

#endif /* DCMOTOR_H_ */
