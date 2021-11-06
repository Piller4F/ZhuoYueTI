/**
  ******************************************************************************
  * @file    motor.c
  * @brief   步进电机驱动
  *          
  ******************************************************************************
**/

#include "motor.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

uint8_t turnleft[10000];
uint8_t turnright[10000];

void MotorGoStrate(uint32_t length)
{
	//length = ONELENGTH * length;
	while(length--)
	{
		HAL_GPIO_TogglePin(RightStp_GPIO_Port, RightStp_Pin);
		HAL_GPIO_TogglePin(LeftStp_GPIO_Port, LeftStp_Pin);
		osDelay(1);
	}
}

void MotorTurnLeft(void)
{
	uint32_t times = 920;
	while(times)
	{
		HAL_GPIO_WritePin(LeftDir_GPIO_Port, LeftDir_Pin, GPIO_PIN_RESET);
		HAL_GPIO_TogglePin(RightStp_GPIO_Port, RightStp_Pin);
		HAL_GPIO_TogglePin(LeftStp_GPIO_Port, LeftStp_Pin);
		HAL_GPIO_WritePin(LeftDir_GPIO_Port, LeftDir_Pin, GPIO_PIN_SET);
		times--;
		osDelay(1);
	}
}	

void MotorTurnRight(void) {
	uint32_t times = 900;
	while(times)
	{
		HAL_GPIO_WritePin(RightStp_GPIO_Port, RightDIr_Pin, GPIO_PIN_RESET);
		HAL_GPIO_TogglePin(RightStp_GPIO_Port, RightStp_Pin);
		HAL_GPIO_TogglePin(LeftStp_GPIO_Port, LeftStp_Pin);
		HAL_GPIO_WritePin(RightStp_GPIO_Port, RightDIr_Pin, GPIO_PIN_SET);
		times--;
		osDelay(1);
	}
}

void MotorTurn180(void) {
	uint32_t times = 1800;
	while(times)
	{
		HAL_GPIO_WritePin(LeftDir_GPIO_Port, LeftDir_Pin, GPIO_PIN_RESET);
		HAL_GPIO_TogglePin(RightStp_GPIO_Port, RightStp_Pin);
		HAL_GPIO_TogglePin(LeftStp_GPIO_Port, LeftStp_Pin);
		HAL_GPIO_WritePin(LeftDir_GPIO_Port, LeftDir_Pin, GPIO_PIN_SET);
		times--;
		osDelay(1);
	}
}
