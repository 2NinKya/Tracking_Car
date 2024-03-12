#ifndef      _USART_H//和文件名一致，将.换成_；前面加_。
#define     _USART_H//避免重复声明，使用if no define,define......endif

#include "driverlib.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

bool UART_Init(uint16_t baseAddress, uint32_t Baudrate);
void UART_printf(uint16_t baseAddress, const char *format,...);

#endif

