/**
  ******************************************************************************
  * @file    usarthmi.c
  * @brief   串口屏，指令封装 使用usart2 PA2 PA3
  *          
  ******************************************************************************
**/

#include "usarthmi.h"

void Usarthmi_Send_Data(const char *formt, ...)
{
	uint8_t cmd[50] = {0};
	uint8_t cmdlen = 0;
	char *ch;
	__va_list arg;
	__va_start(arg, formt);
	const char *start = formt;
	while(*start)
	{
		char temp[20] = {0};
		if(*start == '%')
		{
			start++;
			switch(*start)
			{
				case 'd':
					sprintf(temp,"%d", __va_arg(arg, int));
					strcat((char *)cmd, temp);
					cmdlen += strlen(temp);
					break;
				case 'c':
					cmd[cmdlen++]=__va_arg(arg, int);
					break;
				case 's':
					ch = __va_arg(arg, char*);
					while(*ch)
					{
						cmd[cmdlen++]=*ch;
						ch++;
					}
					break;
				case 'f':
					sprintf(temp,"%f", (double)__va_arg(arg, double));
					strcat((char *)cmd, temp);
					cmdlen += strlen(temp);
					break;
				default:
					break;
			}
		}
		else
		{
			cmd[cmdlen++]=*start;
		}
		start++;
	}
	strcat((char *)cmd, "\xff\xff\xff");
	HAL_UART_Transmit(&huart2, cmd, strlen((char *)cmd), 0xFFFF);
}

