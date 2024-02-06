/******************************************************************************
*  Module: SYSTEM
*  File name: system.h
*  Created on: Oct 27, 2023
*  Author: Mohamed Khaled
*******************************************************************************/

#ifndef SYSTEM_H_
#define SYSTEM_H_

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
void recievePasswordFromUser(void);
void recieveConfirmPasswordFromUser(void);
uint8 checkPasswordMatch(void);
void storeInEEPROM(void);
uint8 checkPasswordInEEPROM(void);
void motorOperation(void);
void tickIncreament(void);
void delayInSeconds(uint8 number_seconds);
void BUZZER_active(void);
void first_menu_response(void);
void second_menu_response(void);
void changePassword(void);


#endif /* SYSTEM_H_ */
