///*
// * WIFI_Slave.c
// *
// *  Created on: 2022��7��27��
// *      Author: TANG
// */
//#include "driverlib.h"
//#include "delay.h"
//#include "usart.h"
//#include "oled.h"
//#define WIFI_UART USCI_A0_BASE
//extern uint8_t buf[];
//extern uint8_t Status;
//
//void WIFI_Slave(void)
//{
//    UART_printf(WIFI_UART,"%s\r\n","AT+CWMODE=2");
//    delay_ms(1);
//    UART_printf(WIFI_UART,"AT+CIPMUX=1\r\n");                                         //����Ϊ������ģʽ
//    delay_ms(1);
//    UART_printf(WIFI_UART,"AT+CIPSERVER=1,1001\r\n");
//    delay_ms(1);
//    Status = 1;
//}
//
