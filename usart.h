#ifndef      _USART_H//���ļ���һ�£���.����_��ǰ���_��
#define     _USART_H//�����ظ�������ʹ��if no define,define......endif

#include "driverlib.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

bool UART_Init(uint16_t baseAddress, uint32_t Baudrate);
void UART_printf(uint16_t baseAddress, const char *format,...);

#endif

