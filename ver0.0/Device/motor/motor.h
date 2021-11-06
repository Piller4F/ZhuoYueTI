/**
  ******************************************************************************
  * @file    motor.h
  * @brief   
  *          
  ******************************************************************************
**/

#ifndef __MOTOR_H
#define __MOTOR_H

#include "main.h"

#define ONELENGTH (111)

void MotorGoStrate(uint32_t length);
void MotorTurnLeft(void);
void MotorTurnRight(void);
void MotorTurn180(void);

#endif // __USARTHMI_H
