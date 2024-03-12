/*
 * TA_Capture.c
 *
 *  Created on: 2022年7月16日
 *      Author: TANG
 */

/*
 * TA设置输入捕获(P2.5作为输入捕获引脚)
 */
#include "driverlib.h"
#include "msp430.h"


uint32_t Sign_Counts;

void TA_Capture_Init(void)
{
    /*  定时器基础配置 */
    Timer_A_initContinuousModeParam htim = {0};
    htim.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;                                   //SMCLK = 25MHz
    htim.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;                        //不分频,25MHz
    htim.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_ENABLE;                 //TAIE中断使能
    htim.timerClear = TIMER_A_DO_CLEAR;                                             //定时器清零
    htim.startTimer = true;                                                         //开启定时器
    Timer_A_initContinuousMode(TIMER_A2_BASE, &htim);                               //定时器设置连续计数模式
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2,GPIO_PIN5);
    /*  定时器捕获模式配置   */
    Timer_A_initCaptureModeParam capture_htim = {0};
    capture_htim.captureRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2;               //TA2.2(P2.5)
    capture_htim.captureMode = TIMER_A_CAPTUREMODE_RISING_AND_FALLING_EDGE;         //双边沿捕获
    capture_htim.captureInputSelect = TIMER_A_CAPTURE_INPUTSELECT_CCIxA;            //
    capture_htim.synchronizeCaptureSource = TIMER_A_CAPTURE_SYNCHRONOUS;            //
    capture_htim.captureInterruptEnable = TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE;  //使能
    capture_htim.captureOutputMode = TIMER_A_OUTPUTMODE_OUTBITVALUE;
    Timer_A_initCaptureMode(TIMER_A2_BASE,&capture_htim);
}


//500 /(1/25 000 000 * 1000)
/*
 * 获取中断中的计时值,即捕获到的第一个高电平的持续时间长度    ///2pi = 1040方波,一个方波=如下计数值,
 */
uint32_t GetCount(void)
{
    return Sign_Counts;
}


/*us*/
uint32_t GetTime(void)
{
    return (Sign_Counts * 1 / 25);
}
//速度如下计算,可能不准确,待测试。
//r是半径,等待测量
//uint32_t GetSpeed(void)
//{
//    2 * 3.14 * r /(GetTime() * 2080 );
//}
/*
 * 中断用于计时,溢出和上升下降沿都会触发中断
 */

#pragma vector=TIMER2_A1_VECTOR
__interrupt
void TIMER2_A1_ISR (void)
{
    static uint16_t Overflow_Times = 0;
    static uint16_t Sign_Begin = 0, Sign_End = 0;
    switch(TA2IV)
    {

        case TA2IV_TACCR2:                                                                                          //边沿中断
            if(GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN5))                                                       //检测到上升沿
            {
                Sign_Begin = Timer_A_getCaptureCompareCount(TIMER_A2_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2);       //计数作为开始值
            }
            else
            {
                Sign_End = Timer_A_getCaptureCompareCount(TIMER_A2_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2);         //第二次下降沿触发
                if(!Overflow_Times)                                                                                 //没有溢出
                    Sign_Counts = Sign_End - Sign_Begin;                                                            //计数值就是END - BEGIN
                else                                                                                                //如果溢出
                {
                    Sign_Counts = (uint32_t)65536 * Overflow_Times + Sign_End - Sign_Begin;                         //算上溢出次数,求总时间
                    Overflow_Times = 0;                                                                             //计算完将溢出清零
                }
            }
            Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2);                 //清除中断标志位
            __bis_SR_register(GIE);
            break;
        case TA2IV_TAIFG:                                                                                          //若产生溢出中断
            if(GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN5))                                                      //计时过程产生溢出
            {
                ++Overflow_Times;                                                                                  //算入计数时间
            }
            else                                                                                                   //不在计时状态时产生溢出
                Overflow_Times = 0;                                                                                //不算入计时
            Timer_A_clearTimerInterrupt(TIMER_A2_BASE);                                                            //清除中断标志位
            __bis_SR_register(GIE);
           break;
        default:
            break;
    }
}
//


