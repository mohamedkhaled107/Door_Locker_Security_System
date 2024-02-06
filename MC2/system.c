/******************************************************************************
 *  Module: SYSTEM
 *  File name: system.c
 *  Created on: Oct 27, 2023
 *  Author: Mohamed Khaled
 *******************************************************************************/
/*******************************************************************************
 *                                  Includes                                   *
 *******************************************************************************/
#include "system.h"
#include "std_types.h"
#include "dcmotor.h"
#include "external_eeprom.h"
#include "uart.h"
#include "timer1.h"
#include "buzzer.h"
#include "seven_segment.h"
#include <util\delay.h>
/*******************************************************************************
 *                                                                              *
 *                                  Global Arrays                               *
 *                                                                              *
 ********************************************************************************/
uint8 password[5],confirm_password[5];
/*******************************************************************************
 *                                                                              *
 *                                  Global Variables                            *
 *                                                                              *
 ********************************************************************************/
static volatile uint16 g_tick=0;
/*******************************************************************************
 *                                                                              *
 *                              FUNCTIONS Definitions                           *
 *                                                                              *
 ********************************************************************************/
void first_menu_response(void)
{
	recievePasswordFromUser();
	recieveConfirmPasswordFromUser();
	checkPasswordMatch();
}



void recievePasswordFromUser(void){
	/* counter for password Digits */
	uint8 i=0;

	/* MC2 won't start receiving password until MC1 sends this starting bit  */
	while(UART_receiveByte()!=MC1_WILL_SEND_PASSWORD);

	/* for loop to receive the password bit by bit and store it in a global array */
	for(i=0;i<PASSWORD_DIGITS_NUMBER;i++){
		password[i]=UART_receiveByte();
	}

	while(UART_receiveByte()!='=');

}

void recieveConfirmPasswordFromUser(void){
	/* counter for confirm password Digits */
	uint8 i=0;
	/* MC2 won't start receiving confirm password until MC1 sends this starting bit  */
	while(UART_receiveByte()!=MC1_WILL_SEND_CONFIRM_PASSWORD);

	for(i=0;i<PASSWORD_DIGITS_NUMBER;i++){
		confirm_password[i]=UART_receiveByte();
	}

	while(UART_receiveByte()!='=');

}


uint8 checkPasswordMatch(void){
	uint8 i=0;
	uint8 flag=1;

	for(i=0;i<PASSWORD_DIGITS_NUMBER;i++)
	{
		//g_password[i]=arr1[i]; /* store password while the first password entry is the same of the second password entry */
		if(password[i]!=confirm_password[i])
		{

			flag=0;
			/* break the loop if a digit is not identical in password and confirm password  */
			break;

		}

	}
	UART_sendByte(MC2_WILL_SEND_CHECK);

	UART_sendByte(flag);

	if(flag==1)
	{

		storeInEEPROM();

	}
	return flag;
}


void storeInEEPROM(void)
{
	uint8 i;
	/* Write pass in EEPROM*/
	for(i=0 ;i<PASSWORD_DIGITS_NUMBER ;i++)
	{
		EEPROM_writeByte(((0x0311)+i) ,password[i]);
		_delay_ms(50);
	}

}

uint8 checkPasswordInEEPROM(void)
{
	uint8 i,read_data;
	uint8 flag = 1 ;
	/* read password stored in EEPROM*/
	for(i=0 ;i<PASSWORD_DIGITS_NUMBER ;i++)
	{
		EEPROM_readByte(((0x0311)+i) ,&read_data);
		if(read_data!=password[i]){
			flag=0;
			break;
		}

	}

	return flag;
}


void motorOperation(void)
{
	DCMOTOR_rotate(CLOCK_WISE,100);
	delayInSeconds(15);
	DCMOTOR_rotate(STOP,0);
	delayInSeconds(3);
	DCMOTOR_rotate(ANTI_CLOCK_WISE,100);
	delayInSeconds(15);
	DCMOTOR_rotate(STOP,0);


}

/*Function    : second_menu_response
 *Description : 1-take the current password from user which is in EEPROM
 *              2-match password with EEPROM password
 *              3-take user choice(+ for open the door, - for change the password )
 *              4-if password doesn't match with EEPROM password  try again while mismatch counter<3
 *              5-if password doesn't match with EEPROM password for 3 times
 *              BUZZER will be active for 1 minute
 *              6-if password match with EEPROM password then open the door or change password as user chose
 *
 */
void second_menu_response(void){
	/* variable to hold user choice */
	uint8 user_choice=0;
	uint8 match_password_in_eeprom=2;
	static uint8 missmatch_counter=0;

	recievePasswordFromUser();
	match_password_in_eeprom=checkPasswordInEEPROM();
	UART_sendByte(match_password_in_eeprom);

	while(UART_receiveByte()!=MC1_WILL_SEND_USER_CHOICE);
	/* receive the choice from MC1 */
	user_choice=UART_receiveByte();


	while(match_password_in_eeprom==0)
	{
		missmatch_counter++;

		if(missmatch_counter == PASSWORD_MISMATCH_MAXIMUM)
		{
			SevenSegment_number(missmatch_counter);
			BUZZER_active();
			missmatch_counter = 0;
			SevenSegment_number(missmatch_counter);
			break;
		}
		SevenSegment_number(missmatch_counter);
		recievePasswordFromUser();
		match_password_in_eeprom=checkPasswordInEEPROM();
		UART_sendByte(match_password_in_eeprom);
	}

	if(match_password_in_eeprom==1)
	{
		missmatch_counter=0;
		SevenSegment_number(missmatch_counter);

		switch(user_choice)
		{
		case '+' :motorOperation();
		break;
		case '-' :first_menu_response();;
		break;
		default: break;
		}
	}
}



void tickIncrement(void)
{
	g_tick++;
}

void delayInSeconds(uint8 number_seconds)
{
	/* essential to start count from zero for every use */
	g_tick=0;

	/* initialize Timer 1 configuration structure */
	Timer1_ConfigType timer1={0,1563,F_CPU_1024,CTC};
	Timer1_init(&timer1);

	/* call back (tickIncrement) to increase tick counter */
	Timer1_setCallBack(tickIncrement);

	/* polling method */
	while(g_tick<5*number_seconds);

	/* close Timer 1 */
	Timer1_deInit();

}

/* function to active BUZZER for a period of time */
void BUZZER_active(void)
{
	/* initialize buzzer driver */
	BUZZER_init();
	/* buzzer on for 1 minute */
	BUZZER_ON();
	delayInSeconds(60);
	BUZZER_OFF();
}



