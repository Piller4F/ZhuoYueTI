/**
  ******************************************************************************
  * @file    usarthmi.h
  * @brief   
  *          
  ******************************************************************************
**/

#ifndef __USARTHMI_H
#define __USARTHMI_H

#include "usart.h"
#include "string.h"
#include "stdio.h"
#include "stdarg.h"

void Usarthmi_Send_Data(const char *formt, ...);

#endif // __USARTHMI_H
