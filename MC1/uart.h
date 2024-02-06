/******************************************************************************
 *  Module:    Uart
 *  File name: uart.c
 *  Created on: Oct 23, 2023
 *  Author: Mohamed Khaled
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

/*******************************************************************************
*                                                                              *
*                                  INCLUDES                                    *
*                                                                              *
********************************************************************************/
#include "std_types.h"
/*******************************************************************************
*                                                                              *
*                                  Definitions                                 *
*                                                                              *
********************************************************************************/


/*******************************************************************************
*                                                                              *
*                       External   Global Variables                            *
*                                                                              *
********************************************************************************/
 extern uint16 g_UBRR_value;
 extern uint8  g_speed_mode_division_factor;

/*******************************************************************************
*                                                                              *
*                             User-Defined Data Types                          *
*                                                                              *
********************************************************************************/

typedef enum
{
	Receiver,
	Transmitter,
	Transmitter_Receiver
}Operation_Mode;

typedef enum
{
	Normal_Speed,
	Double_Speed
}Transmission_Speed;

typedef enum
{
	Asynchronous,
	Synchronous
}Synchronization;

typedef enum
{
	Parity_Disabled,
	Parity_Odd,
	Parity_Even
}Parity_Bit;

typedef enum
{
	StopBit_1,
	StopBit_2
}Stop_Bit;

typedef enum
{
	DataFrame_5Bits,
	DataFrame_6Bits,
	DataFrame_7Bits,
	DataFrame_8Bits,
	DataFrame_9Bits=7
}DataFrame_Bits;

typedef enum
{
    BaudRate_9600,
	BaudRate_14400,
	BaudRate_19200,
	BaudRate_115200,
}Baud_Rate;

typedef enum
{
	RX_InterruptDisable,
	RX_InterruptEnable,
}RX_Interrupt;

typedef enum
{
	TX_InterruptDisable,
	TX_InterruptEnable,
}TX_Interrupt;

typedef struct
{
	Operation_Mode operation_mode;
	Transmission_Speed speed;
	Synchronization  synchronization;
	Parity_Bit parity;
	Stop_Bit stop_bit;
	DataFrame_Bits dataframe_bits;
	Baud_Rate baud_rate;
	RX_Interrupt rx_interrupt;
	TX_Interrupt tx_interrupt;
}UART_ConfigType;
/*******************************************************************************
*                                                                              *
*                                  FUNCTIONS PROTOTYPE                         *
*                                                                              *
********************************************************************************/
void UART_Init(const UART_ConfigType * Config_Ptr);
void UART_sendByte(const uint8 data );
uint8 UART_receiveByte (void);
void UART_sendString( const uint8 * Str);
void UART_receiveString (uint8 *Str);

#endif /* UART_H_ */
