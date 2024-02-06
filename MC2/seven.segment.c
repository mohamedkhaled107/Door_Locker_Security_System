/******************************************************************************
 *  Module:    SEVEN_SEGMENT
 *  File name: seven_segment.c
 *  Created on: Oct 26, 2023
 *  Author: Mohamed Khaled
 *******************************************************************************/
/*******************************************************************************
*                                                                              *
*                                  INCLUDES                                    *
*                                                                              *
********************************************************************************/
#include "seven_segment.h"
#include "gpio.h"
#include "std_types.h"
/*******************************************************************************
*                                                                              *
*                              FUNCTIONS Definitions                           *
*                                                                              *
********************************************************************************/
void SevenSegment_init(void)
{
	GPIO_setupPinDirection(SEVEN_SEGMENT_PORT_ID,FIRST_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+1,PIN_OUTPUT);
	GPIO_setupPinDirection(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+2,PIN_OUTPUT);
	GPIO_setupPinDirection(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+3,PIN_OUTPUT);
}

void SevenSegment_number(uint8 number)
{
	switch(number)
	{
	case 0 :
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN,LOGIC_LOW);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+1,LOGIC_LOW);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+2,LOGIC_LOW);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+3,LOGIC_LOW);
		break;
	case 1 :
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN,LOGIC_HIGH);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+1,LOGIC_LOW);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+2,LOGIC_LOW);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+3,LOGIC_LOW);
		break;

	case 2 :
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN,LOGIC_LOW);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+1,LOGIC_HIGH);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+2,LOGIC_LOW);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+3,LOGIC_LOW);
		break;

	case 3 :
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN,LOGIC_HIGH);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+1,LOGIC_HIGH);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+2,LOGIC_LOW);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+3,LOGIC_LOW);
		break;

	case 4 :
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN,LOGIC_LOW);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+1,LOGIC_LOW);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+2,LOGIC_HIGH);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+3,LOGIC_LOW);
		break;

	case 5 :
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN,LOGIC_HIGH);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+1,LOGIC_LOW);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+2,LOGIC_HIGH);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+3,LOGIC_LOW);
		break;

	case 6 :
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN,LOGIC_LOW);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+1,LOGIC_HIGH);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+2,LOGIC_HIGH);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+3,LOGIC_LOW);
		break;
	case 7 :
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN,LOGIC_HIGH);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+1,LOGIC_HIGH);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+2,LOGIC_HIGH);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+3,LOGIC_LOW);
		break;

	case 8 :
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN,LOGIC_LOW);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+1,LOGIC_LOW);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+2,LOGIC_LOW);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+3,LOGIC_HIGH);
		break;
	case 9 :
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN,LOGIC_HIGH);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+1,LOGIC_LOW);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+2,LOGIC_LOW);
		GPIO_writePin(SEVEN_SEGMENT_PORT_ID,FIRST_PIN+3,LOGIC_HIGH);
		break;

	}
}
