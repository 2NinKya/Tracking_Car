/*
 * PWMA.c
 *
 *  Created on: 2022��7��20��
 *      Author: TANG
 */
#include "driverlib.h"

/*
 * P1.2(TA0.1)     P1.3(TA0.2)     P1.4(TA0.3)     P1.5(TA0.4)
 */
void PWMA_Init(void)
{
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1,GPIO_PIN2 | GPIO_PIN3 | GPIO_PIN4 | GPIO_PIN5);
    /*----------------��ʱ����ʼ��-------------------------*/
    Timer_A_initUpModeParam htim = {0};
    htim.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;                     //25MHz
    htim.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_40;         //40��Ƶ
    htim.timerPeriod = 100 - 1;
    htim.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
    htim.captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE;
    htim.timerClear = TIMER_A_DO_CLEAR;
    htim.startTimer = true;
    Timer_A_initUpMode(TIMER_A0_BASE,&htim);
    /*------------------P1.2(TA0.1)PWM1�ĳ�ʼ��--------------------------*/
    Timer_A_initCompareModeParam htim_PWM1 = {0};
    htim_PWM1.compareInterruptEnable = TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE;
    htim_PWM1.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;

    htim_PWM1.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
    htim_PWM1.compareValue =0;
    Timer_A_initCompareMode(TIMER_A0_BASE, &htim_PWM1);
    /*------------------P1.3(TA0.2)PWM2�ĳ�ʼ��--------------------------*/
    Timer_A_initCompareModeParam htim_PWM2 = {0};                                                  //��ʼ��Ϊ��
    htim_PWM2.compareInterruptEnable = TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE;                   //��������Ӧ�ж�
    htim_PWM2.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;

    htim_PWM2.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2;                                 //���ö�Ӧ�Ŀ�ΪTA0.2
    htim_PWM2.compareValue =0;                                                                 //ARR��ֵ
    Timer_A_initCompareMode(TIMER_A0_BASE, &htim_PWM2);
    /*------------------P1.4(TA0.3)PWM3�ĳ�ʼ��--------------------------*/
    Timer_A_initCompareModeParam htim_PWM3 = {0};
    htim_PWM3.compareInterruptEnable = TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE;
    htim_PWM3.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;

    htim_PWM3.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_3;
    htim_PWM3.compareValue =0;
    Timer_A_initCompareMode(TIMER_A0_BASE, &htim_PWM3);
    /*------------------P1.5(TA0.4)PWM4�ĳ�ʼ��--------------------------*/
    Timer_A_initCompareModeParam htim_PWM4 = {0};
    htim_PWM4.compareInterruptEnable = TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE;
    htim_PWM4.compareOutputMode = TIMER_A_OUTPUTMODE_RESET_SET;

    htim_PWM4.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_4;
    htim_PWM4.compareValue =0;
    Timer_A_initCompareMode(TIMER_A0_BASE, &htim_PWM4);
}
