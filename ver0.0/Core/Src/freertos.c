/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
#include "usarthmi.h"
#include "motor.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId usartHmiHandle;
osThreadId motorRunHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void UsartHmiTask(void const * argument);
void MotorRun(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of usartHmi */
  osThreadDef(usartHmi, UsartHmiTask, osPriorityIdle, 0, 128);
  usartHmiHandle = osThreadCreate(osThread(usartHmi), NULL);

  /* definition and creation of motorRun */
  osThreadDef(motorRun, MotorRun, osPriorityIdle, 0, 128);
  motorRunHandle = osThreadCreate(osThread(motorRun), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_UsartHmiTask */
/**
* @brief Function implementing the usartHmi thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_UsartHmiTask */
void UsartHmiTask(void const * argument)
{
  /* USER CODE BEGIN UsartHmiTask */
  /* Infinite loop */
	//__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
	uint8_t buf[4] = {0};
  for(;;)
  {
		HAL_UART_Receive(&huart2, (uint8_t *)&buf, 2, 0xFFFF);
		buf[3] = 0;
		printf("%c%d\r\n",buf[1], buf[0]);
    osDelay(1);
  }
  /* USER CODE END UsartHmiTask */
}

/* USER CODE BEGIN Header_MotorRun */
/**
* @brief Function implementing the motorRun thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_MotorRun */
void MotorRun(void const * argument)
{
  /* USER CODE BEGIN MotorRun */
  /* Infinite loop */
	uint32_t t = 1;
	HAL_GPIO_WritePin(LeftDir_GPIO_Port, LeftDir_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(RightDIr_GPIO_Port, RightDIr_Pin, GPIO_PIN_SET);
	osDelay(2000);
	for(;;)
  {
		if(t)
		{
			t = 0;
//			MotorGoStrate(3100);
//			osDelay(200);
//			MotorTurnRight();
//			osDelay(200);
//			MotorGoStrate(2000);
//			osDelay(200);
//			MotorTurn180();
//			osDelay(200);
//			MotorGoStrate(2000);
//			osDelay(200);
//			MotorTurnLeft();
//			osDelay(200);
//			MotorGoStrate(2600);
			//			MotorGoStrate(3100);
			osDelay(200);
			MotorTurnLeft();
			osDelay(200);
			MotorGoStrate(2000);
			osDelay(200);
			MotorTurn180();
			osDelay(200);
			MotorGoStrate(2000);
			osDelay(200);
			MotorTurnRight();
			osDelay(200);
			MotorGoStrate(2600);
		}
		osDelay(1);
  }
  /* USER CODE END MotorRun */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
