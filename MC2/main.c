/******************************************************************************
 *  Module:    MAIN
 *  File name: main.c
 *  Created on: Oct 26, 2023
 *  Author: Mohamed Khaled
 *******************************************************************************/
/*******************************************************************************
 *                                  Includes                                   *
 *******************************************************************************/
#include "system.h"
#include <avr\io.h>
#include "uart.h"
#include "dcmotor.h"
#include "seven_segment.h"


int main(void){
	uint8 password_match=0;
	SREG |= (1<<7);
	DCMOTOR_init();
	SevenSegment_init();
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
	while( UART_receiveByte()!=MC2_READY);

	while(password_match==0)
	{
	recievePasswordFromUser();
	recieveConfirmPasswordFromUser();
	password_match=checkPasswordMatch();
	}

	while(1)
	{
		second_menu_response();
	}

}
