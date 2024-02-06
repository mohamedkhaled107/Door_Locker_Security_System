/******************************************************************************
 *  Module:    I2C
 *  File name: i2c.h
 *  Created on: Oct 23, 2023
 *  Author: Mohamed Khaled
 *******************************************************************************/

#ifndef I2C_H_
#define I2C_H_

#include "std_types.h"

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */
#define FREQ_CPU 8000000

typedef uint8 TWI_Address;
typedef uint16 TWI_BaudRate;


typedef struct{
	TWI_Address address;
	TWI_BaudRate bit_rate;
}TWI_ConfigType;

void TWI_init(const TWI_ConfigType* config_ptr);
void TWI_start(void);
void TWI_stop(void);
void TWI_writeByte(uint8 data);
uint8 TWI_readByteWithACK(void);
uint8 TWI_readByteWithNACK(void);
uint8 TWI_getStatus(void);

#endif /* MC1_I2C_H_ */
