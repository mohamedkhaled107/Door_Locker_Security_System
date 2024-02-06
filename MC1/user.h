/******************************************************************************
 *  Module:    USER
 *  File name: user.c
 *  Created on: Oct 26, 2023
 *  Author: Mohamed Khaled
 *******************************************************************************/

#ifndef USER_H_
#define USER_H_
/*******************************************************************************
 *                                  Includes                                   *
 *******************************************************************************/
#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define PASSWORD_DIGITS_NUMBER                 5
#define PASSWORD_MISMATCH_MAXIMUM              3
#define MC2_READY                              0xFF
#define MC1_WILL_SEND_PASSWORD                 0xAA
#define MC1_WILL_SEND_CONFIRM_PASSWORD         0xBB
#define MC2_WILL_SEND_CHECK                    0xCC
#define MC1_WILL_SEND_USER_CHOICE              0xDD
#define MC2_WILL_SEND_MATCH_PASSWORD_IN_EEPROM 0xEE
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void insertPassword(void);
void reInsertPassword(void);
uint8 recievePasswordChecked(void);
void tickIncreament(void);
void delayInSeconds(uint8 number_seconds);
void openDoor(void);
void changePassword();
void first_menu(void);
void second_menu(void);
void delayInSeconds(uint8 number_seconds);

#endif /* USER_H_ */
