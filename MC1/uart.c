/******************************************************************************
 *  Module:    Uart
 *  File name: uart.c
 *  Created on: Oct 23, 2023
 *  Author: Mohamed Khaled
 *******************************************************************************/
/*******************************************************************************
*                                                                              *
*                                  INCLUDES                                    *
*                                                                              *
********************************************************************************/
#include "uart.h"
#include "std_types.h"
#include "avr/io.h"
#include "avr/interrupt.h"
#include "common_macros.h"
/*******************************************************************************
*                                                                              *
*                                  Global Variables                            *
*                                                                              *
********************************************************************************/
 uint16 g_UBRR_value = 0;
 uint8  g_speed_mode_division_factor = 0;
 /*******************************************************************************
 *                                                                              *
 *                          Interrupt Service Routine                           *
 *                                                                              *
 ********************************************************************************/
ISR(USART_RXC_vect)
 {

 }

ISR(USART_TXC_vect)
 {

 }
/*******************************************************************************
*                                                                              *
*                              FUNCTIONS Definitions                           *
*                                                                              *
********************************************************************************/
void UART_Init(const UART_ConfigType * Config_Ptr)
{
	/*Configuration Operation Mode*/
    switch( Config_Ptr ->operation_mode)
    {
      case Receiver:                SET_BIT(UCSRB,RXEN);
    	                            break;
      case Transmitter:             SET_BIT(UCSRB,TXEN);
    	                            break;
      case Transmitter_Receiver:    SET_BIT(UCSRB,RXEN);
                                    SET_BIT(UCSRB,TXEN);
    	                            break;
    }
	/*Configuration Transmission Speed*/
	switch( Config_Ptr ->speed)
	{
	  case Normal_Speed:   CLEAR_BIT(UCSRA,U2X);
	                       g_speed_mode_division_factor = 16;
	 	                   break;
	  case Double_Speed:   SET_BIT(UCSRA,U2X);
                           g_speed_mode_division_factor = 8;
	  		               break;
	}

	/*Configuration Synchronization of UART*/
	switch ( Config_Ptr->synchronization)
	{
	 case Asynchronous: SET_BIT(UCSRC,URSEL);
	                    CLEAR_BIT(UCSRC,UMSEL);
		                break;
	 case Synchronous:  SET_BIT(UCSRC,URSEL);
	                    SET_BIT(UCSRC,UMSEL);
	 		            break;
	}

	/*Configuration Parity Bit of UART*/
	switch ( Config_Ptr ->parity)
	{
	  case Parity_Disabled: SET_BIT(UCSRC,URSEL);
		                    CLEAR_BIT(UCSRC,UPM0);
	                        CLEAR_BIT(UCSRC,UPM1);
	                        break;
	  case Parity_Odd:      SET_BIT(UCSRC,URSEL);
		                    SET_BIT(UCSRC,UPM0);
                            SET_BIT(UCSRC,UPM1);
                            break;
	  case Parity_Even:     SET_BIT(UCSRC,URSEL);
		                    CLEAR_BIT(UCSRC,UPM0);
                            SET_BIT(UCSRC,UPM1);
                            break;
	}

	/*Configuration Number of Stop Bits of UART*/
    switch( Config_Ptr ->stop_bit)
    {
    case StopBit_1:  CLEAR_BIT(UCSRC,USBS);
    	             break;
    case StopBit_2:  SET_BIT(UCSRC,USBS);
    	             break;
    }

    /*Configuration Number of Data Frame Bits*/
    switch ( Config_Ptr ->dataframe_bits )
    {
    case DataFrame_5Bits:  CLEAR_BIT(UCSRC,UCSZ0);
                           CLEAR_BIT(UCSRC,UCSZ1);
                           CLEAR_BIT(UCSRB,UCSZ2);
    	                   break;
    case DataFrame_6Bits:  SET_BIT(UCSRC,UCSZ0);
                           CLEAR_BIT(UCSRC,UCSZ1);
                           CLEAR_BIT(UCSRB,UCSZ2);
    	                   break;
    case DataFrame_7Bits:  CLEAR_BIT(UCSRC,UCSZ0);
                           SET_BIT(UCSRC,UCSZ1);
                           CLEAR_BIT(UCSRB,UCSZ2);
    	                   break;
    case DataFrame_8Bits:  SET_BIT(UCSRC,UCSZ0);
                           SET_BIT(UCSRC,UCSZ1);
                           CLEAR_BIT(UCSRB,UCSZ2);
    	                   break;
    case DataFrame_9Bits:  SET_BIT(UCSRC,UCSZ0);
                           SET_BIT(UCSRC,UCSZ1);
                           SET_BIT(UCSRB,UCSZ2);
    	                   break;
    }


    switch( Config_Ptr ->baud_rate)
    {
    case BaudRate_9600:   /*For 1 MHz  value = 12 , For 8MHz value = 103*/
    	                  UBRRH = 103>>8;
                           UBRRL = 103;
    	                  break;
    	                  /*There is a bug in the equation shown blow */
    case BaudRate_14400:  g_UBRR_value= (uint16)(((F_CPU / (g_speed_mode_division_factor * 14400 )))-1);
    	                  break;
    case BaudRate_19200:  g_UBRR_value= (uint16)(((F_CPU / (g_speed_mode_division_factor * 19200 )))-1);
    	                  break;
    case BaudRate_115200: g_UBRR_value= (uint16)(((F_CPU / (g_speed_mode_division_factor * 115200)))-1);
    	                  break;
    }


    /*Configuration RX Interrupt*/
    switch(Config_Ptr ->rx_interrupt)
    {
    case RX_InterruptDisable: CLEAR_BIT(UCSRB,RXCIE);
                              break;
    case RX_InterruptEnable:  SET_BIT(UCSRB,RXCIE);
                              break;

    }

    /*Configuration TX Interrupt*/
    switch(Config_Ptr ->tx_interrupt)
    {
    case TX_InterruptDisable: CLEAR_BIT(UCSRB,TXCIE);
                              break;
    case TX_InterruptEnable:  SET_BIT(UCSRB,TXCIE);
                              break;

    }

}



void UART_sendByte(const uint8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR = data;
}


uint8 UART_receiveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
	return UDR;
}


void UART_sendString( const uint8 * Str)
{
	uint8 i = 0;

		/* Send the whole string */
		while(Str[i] != '\0')
		{
			UART_sendByte(Str[i]);
			i++;
		}
}


void UART_receiveString (uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_receiveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_receiveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}
