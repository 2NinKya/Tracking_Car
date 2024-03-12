/*
 * TA_Capture.c
 *
 *  Created on: 2022��7��16��
 *      Author: TANG
 */

/*
 * TA�������벶��(P2.5��Ϊ���벶������)
 */
#include "driverlib.h"
#include "msp430.h"


uint32_t Sign_Counts;

void TA_Capture_Init(void)
{
    /*  ��ʱ���������� */
    Timer_A_initContinuousModeParam htim = {0};
    htim.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;                                   //SMCLK = 25MHz
    htim.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;                        //����Ƶ,25MHz
    htim.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_ENABLE;                 //TAIE�ж�ʹ��
    htim.timerClear = TIMER_A_DO_CLEAR;                                             //��ʱ������
    htim.startTimer = true;                                                         //������ʱ��
    Timer_A_initContinuousMode(TIMER_A2_BASE, &htim);                               //��ʱ��������������ģʽ
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2,GPIO_PIN5);
    /*  ��ʱ������ģʽ����   */
    Timer_A_initCaptureModeParam capture_htim = {0};
    capture_htim.captureRegister = TIMER_A_CAPTURECOMPARE_REGISTER_2;               //TA2.2(P2.5)
    capture_htim.captureMode = TIMER_A_CAPTUREMODE_RISING_AND_FALLING_EDGE;         //˫���ز���
    capture_htim.captureInputSelect = TIMER_A_CAPTURE_INPUTSELECT_CCIxA;            //
    capture_htim.synchronizeCaptureSource = TIMER_A_CAPTURE_SYNCHRONOUS;            //
    capture_htim.captureInterruptEnable = TIMER_A_CAPTURECOMPARE_INTERRUPT_ENABLE;  //ʹ��
    capture_htim.captureOutputMode = TIMER_A_OUTPUTMODE_OUTBITVALUE;
    Timer_A_initCaptureMode(TIMER_A2_BASE,&capture_htim);
}


//500 /(1/25 000 000 * 1000)
/*
 * ��ȡ�ж��еļ�ʱֵ,�����񵽵ĵ�һ���ߵ�ƽ�ĳ���ʱ�䳤��    ///2pi = 1040����,һ������=���¼���ֵ,
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
//�ٶ����¼���,���ܲ�׼ȷ,�����ԡ�
//r�ǰ뾶,�ȴ�����
//uint32_t GetSpeed(void)
//{
//    2 * 3.14 * r /(GetTime() * 2080 );
//}
/*
 * �ж����ڼ�ʱ,����������½��ض��ᴥ���ж�
 */

#pragma vector=TIMER2_A1_VECTOR
__interrupt
void TIMER2_A1_ISR (void)
{
    static uint16_t Overflow_Times = 0;
    static uint16_t Sign_Begin = 0, Sign_End = 0;
    switch(TA2IV)
    {

        case TA2IV_TACCR2:                                                                                          //�����ж�
            if(GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN5))                                                       //��⵽������
            {
                Sign_Begin = Timer_A_getCaptureCompareCount(TIMER_A2_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2);       //������Ϊ��ʼֵ
            }
            else
            {
                Sign_End = Timer_A_getCaptureCompareCount(TIMER_A2_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2);         //�ڶ����½��ش���
                if(!Overflow_Times)                                                                                 //û�����
                    Sign_Counts = Sign_End - Sign_Begin;                                                            //����ֵ����END - BEGIN
                else                                                                                                //������
                {
                    Sign_Counts = (uint32_t)65536 * Overflow_Times + Sign_End - Sign_Begin;                         //�����������,����ʱ��
                    Overflow_Times = 0;                                                                             //�����꽫�������
                }
            }
            Timer_A_clearCaptureCompareInterrupt(TIMER_A2_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2);                 //����жϱ�־λ
            __bis_SR_register(GIE);
            break;
        case TA2IV_TAIFG:                                                                                          //����������ж�
            if(GPIO_getInputPinValue(GPIO_PORT_P2,GPIO_PIN5))                                                      //��ʱ���̲������
            {
                ++Overflow_Times;                                                                                  //�������ʱ��
            }
            else                                                                                                   //���ڼ�ʱ״̬ʱ�������
                Overflow_Times = 0;                                                                                //�������ʱ
            Timer_A_clearTimerInterrupt(TIMER_A2_BASE);                                                            //����жϱ�־λ
            __bis_SR_register(GIE);
           break;
        default:
            break;
    }
}
//


