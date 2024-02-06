/******************************************************************************
 *  Module:    MAIN
 *  File name: main.c
 *  Created on: Oct 26, 2023
 *  Author: Mohamed Khaled
 *******************************************************************************/

#include "user.h"
#include "lcd.h"
#include "uart.h"
#include <avr\io.h>

int main(void){
	uint8 password_match=0;
	SREG |= (1<<7);
	LCD_init();

	UART_ConfigType UART_Config_Struct =
	{
			Transmitter_Receiver,
			Double_Speed,
			Asynchronous,
			Parity_Disabled,
			StopBit_1,
			DataFrame_8Bits,
			BaudRate_9600,
			RX_InterruptDisable,
			TX_InterruptDisable
	};
	UART_Init(&UART_Config_Struct);

	UART_sendByte(MC2_READY);
	while(password_match==0)
	{
	insertPassword();
	reInsertPassword();
	password_match=recievePasswordChecked();
	}

	while(1)
	{
		second_menu();
	}





}
