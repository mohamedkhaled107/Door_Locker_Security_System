/******************************************************************************
 *  Module:    USER
 *  File name: user.c
 *  Created on: Oct 26, 2023
 *  Author: Mohamed Khaled
 *******************************************************************************/
/*******************************************************************************
 *                                  Includes                                   *
 *******************************************************************************/
#include "user.h"
#include "std_types.h"
#include "keypad.h"
#include "lcd.h"
#include "uart.h"
#include "timer1.h"
#include <util\delay.h>
/*******************************************************************************
*                                                                              *
*                                  Global Variables                            *
*                                                                              *
********************************************************************************/
static volatile uint16  g_tick=0;
static uint8 message_counter=0;

/*******************************************************************************
*                                                                              *
*                              FUNCTIONS Definitions                           *
*                                                                              *
********************************************************************************/
void insertPassword(void)
{
	/*Clear screen from previous operation*/
	LCD_clearScreen();


	if(message_counter==0)
	{
	/* Actual operation */
	LCD_displayStringRowColumn(0,0,"Plz enter pass: ");
	LCD_moveCursor(1,0);
	}
	else if(message_counter==1)
	{
		LCD_displayStringRowColumn(0,0,"Plz enter new ");
			LCD_moveCursor(1,0);
			LCD_displayStringRowColumn(1,0,"Password: ");
			LCD_moveCursor(1,10);
	}
	/* password must be 5 digits*/
	uint8 password_digit_counter=0;

	/*Variable to hold keypad press*/
	uint8 key1;



	/* Agreement between the two MCS to start send password */
	UART_sendByte(MC1_WILL_SEND_PASSWORD);


	/* take 5-Digits from USER */
	while(password_digit_counter<PASSWORD_DIGITS_NUMBER){

		/* get key pressed by USER   */
		key1=KEYPAD_getPressedKey();

		/* take only numbers and ignore (+,-,%,*)  */
		if(key1>=0 && key1<=9){

			/* send the number to MC2 */
			UART_sendByte(key1);

			LCD_intgerToString(key1);

			/* debounce time */
			_delay_ms(800);

			LCD_sendCommand(0x10);

			/* display * on the LCD represent entering number */
			LCD_displayCharacter('*');

			/* increment counter */
			password_digit_counter++;
		}
	}
	while(KEYPAD_getPressedKey()!='=');


UART_sendByte('=');

}


void reInsertPassword(void)
{
	/*Clear screen from previous operation*/
	LCD_clearScreen();

	/* Actual operation */
	LCD_displayStringRowColumn(0,0,"Plz re-enter the");
	LCD_displayStringRowColumn(1,0,"same pass:");
	LCD_moveCursor(1,11);

	/* counter for password Digits */
	uint8 password_digit_counter=0;

	/* Agreement between the two MCS to start send confirm password */
	UART_sendByte(MC1_WILL_SEND_CONFIRM_PASSWORD);

	/*Variable to hold keypad press*/
	uint8 key;

	/* take 5-Digits from USER */
	while(password_digit_counter<PASSWORD_DIGITS_NUMBER)
	{
		/* get key pressed by USER   */
		key=KEYPAD_getPressedKey();

		/* take only numbers and ignore (+,-,%,*)  */
		if(key>=0 && key<=9){

			/* send the number to MC2 */
			UART_sendByte(key);

			LCD_intgerToString(key);

			/* debounce time */
			_delay_ms(800);

			LCD_sendCommand(0x10);

			/* display * on the LCD represent entering number */
			LCD_displayCharacter('*');

			/* increament counter */
			password_digit_counter++;
		}
	}

	while(KEYPAD_getPressedKey()!='=');

	UART_sendByte('=');
}

/*Function     :recievePasswordChecked
 * Description :1-receive passwords matching state form CONTROL_ECU(MC2)
 *              2-if the two passwords don't matches the user will insert password and confirm password again
 *              3-if the two passwords matches the second menu will display to user
*/
uint8 recievePasswordChecked(void)
{
	/* variable to hold state of the two passwords */
	/* we initialized it with any value except 0,1  */
	uint8 password_equal_flag=2;




	while(UART_receiveByte() != MC2_WILL_SEND_CHECK);

	/*receive state of the two passwords from MC2  */
	password_equal_flag=UART_receiveByte();

	/* value 0 : the two passwords are not identical and the user will enter the password and confirm password again */
	/* value 1 : the two passwords are identical and the user will continue to the next operation */
	switch(password_equal_flag)
	{
	case 0:
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"NOT SAME");
		LCD_displayStringRowColumn(1,0,"PASSWORD");

		delayInSeconds(1);

		break;

	case 1:
		LCD_clearScreen();
		LCD_displayStringRowColumn(0,0,"NEW PASSWORD");
		LCD_displayStringRowColumn(1,0,"IS SET");

		delayInSeconds(1);

		break;

	}
	return password_equal_flag;

}


/*function    : second_menu
 *Description : 1-take the current password from user which is in EEPROM
 *              2-match password with EEPROM password
 *              3-take user choice(+ for open the door, - for change the password )
 *              4-if password doesn't match with EEPROM password  try again while mismatch counter<3
 *              5-if password doesn't match with EEPROM password for 3 times
 *              BUZZER will be active for 1 minute
 *              6-if password match with EEPROM password then open the door or change password as user chose
*/
void second_menu(void){

	/* variable to hold key pressed from USER */
	uint8 key;

	/*Clear screen from previous operation*/
	LCD_clearScreen();

	/*Variable to check Driving Motor*/
	uint8 match_password_in_eeprom = 2;

	/*Variable to hold number of miss matches*/
	static uint8 missmatch_counter = 0;


	/* Actual operation */
	LCD_displayStringRowColumn(0,0,"+ : Open Door");
	LCD_displayStringRowColumn(1,0,"- : Change Pass");

	/* get key pressed by USER   */
	key=KEYPAD_getPressedKey();

	/* debounce time */
//	_delay_ms(500);
	insertPassword();
	match_password_in_eeprom=UART_receiveByte();

	UART_sendByte(MC1_WILL_SEND_USER_CHOICE);

	/* send choice to MC2 */
	UART_sendByte(key);

while(match_password_in_eeprom==0)
{
	missmatch_counter++;

	 if(missmatch_counter == PASSWORD_MISMATCH_MAXIMUM)
			 {
				 LCD_clearScreen();
				 LCD_displayString("Error");
				 LCD_moveCursor(1,0);
				 LCD_displayString("BUZZER ACTIVE");
				 delayInSeconds(60);
				 missmatch_counter = 0;
				 break;
			 }
	 insertPassword();
	 match_password_in_eeprom= UART_receiveByte();
}

if(match_password_in_eeprom==1)
{
	missmatch_counter=0;
	switch(key)
	{
	case '+' :openDoor();
	break;
	case '-' :changePassword();
		break;
	default: break;
	}
}
}




void openDoor(void){

	/* clear screen from previous operation */
	LCD_clearScreen();
	/* display (Door is Unlocking) for 15 seconds */
	LCD_displayStringRowColumn(0,4,"Door is");
	LCD_displayStringRowColumn(1,4,"Unlocking  ");
	delayInSeconds(15);

	/* clear screen from previous operation */
	LCD_clearScreen();

	/* display (Waiting) for 3 seconds */
	LCD_displayStringRowColumn(0,4,"Waiting ");
	delayInSeconds(3);

	/* clear screen from previous operation */
	LCD_clearScreen();

	/* display (Door is Locking) for 15 seconds */
	LCD_displayString("Door is Locking");
	delayInSeconds(15);
}


void changePassword()
{
	/* to display (enter new password) message */
	message_counter=1;
	insertPassword();
	reInsertPassword();
	recievePasswordChecked();
	message_counter=0;

}


void tickIncreament(void)
{
	g_tick++;
}


void delayInSeconds(uint8 number_seconds)
{
	g_tick=0;

	Timer1_ConfigType timer1={0,1563,CPU_1024,CTC};
	Timer1_init(&timer1);

	Timer1_setCallBack(tickIncreament);
	while(g_tick<5*number_seconds);
	Timer1_deInit();
}


