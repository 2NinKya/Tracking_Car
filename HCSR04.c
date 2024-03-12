/*
 * HCSR04.c
 *
 *  Created on: 2022��7��23��
 *      Author: TANG
 */
#include "driverlib.h"
#include "delay.h"
#include "TA_Capture.h"
#include "sys.h"

/**
 * P6.5��Trig
 * P2.5��������ĸߵ�ƽ
 */
void HCSR04_Init(void)
{
    TA_Capture_Init();
//    GPIO_setAsOutputPin(GPIO_PORT_P6,GPIO_PIN5);
    GPIO_setAsOutputPin(GPIO_PORT_P6,GPIO_PIN5);
}

uint32_t HCSR04_GetDistance(void)
{
    uint32_t Temp=0, Distance=0;
    GPIO_setOutputHighOnPin(GPIO_PORT_P6,GPIO_PIN5);

    delay_us(10);
    GPIO_setOutputLowOnPin(GPIO_PORT_P6,GPIO_PIN5);
    Temp = GetCount();
    Distance = (1*43*Temp)/50000;
    return Distance;
}


