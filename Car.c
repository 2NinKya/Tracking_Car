/*
 * Car.c
 *
 *  Created on: 2022年7月15日
 *      Author: TANG
 */

#include "driverlib.h"
#include "PWM.h"
#include "PID.h"
void Car_Init(void)
{
    PWMA_Init();
    /*P4.1和PP3.5控制一个车轮*/
    GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN1);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4,GPIO_PIN1);
    GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN5);
    GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN5);
    /*P4.2和P3.6控制一个车轮*/
    GPIO_setAsOutputPin(GPIO_PORT_P4,GPIO_PIN2);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4,GPIO_PIN2);
    GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN6);
    GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN6);
    /*P2.7和P7.0控制一个车轮*/
    GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN7);
    GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN7);
    GPIO_setAsOutputPin(GPIO_PORT_P7,GPIO_PIN0);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7,GPIO_PIN0);
    /*P3.2和P6.4控制一个车轮*/
    GPIO_setAsOutputPin(GPIO_PORT_P3,GPIO_PIN2);
    GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN2);
    GPIO_setAsOutputPin(GPIO_PORT_P6,GPIO_PIN4);
    GPIO_setOutputHighOnPin(GPIO_PORT_P6,GPIO_PIN4);
    /*全设高表示一上电停止*/
}

void Car_SetSpeed2(int8_t Speed)
{
        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,40+Speed);//40
        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2,40-Speed);
        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,40-Speed);
        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_4,40+Speed);
}
void Car_SetSpeed_PID(int8_t Speed)
{
    Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,40+Speed);//40
    Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2,40+Speed);
    Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,40+Speed);
    Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_4,40+Speed);
}

void Car_SetSpeed(int8_t Speed)
{

    Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,Speed);
    Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2,Speed);
    Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,Speed);
    Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_4,Speed);
}
void run(void)
{   //Car_SetSpeed(40);
    //Car_SetSpeed(PID());
    Car_SetSpeed_PID(PID());
    GPIO_setOutputHighOnPin(GPIO_PORT_P4,GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN5);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4,GPIO_PIN2);
    GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN6);
    GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P7,GPIO_PIN0);
    GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN2);
    GPIO_setOutputLowOnPin(GPIO_PORT_P6,GPIO_PIN4);
}

void stop(void)
{
    GPIO_setOutputHighOnPin(GPIO_PORT_P4,GPIO_PIN1);
    GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN5);
    GPIO_setOutputHighOnPin(GPIO_PORT_P4,GPIO_PIN2);
    GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN6);
    GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN7);
    GPIO_setOutputHighOnPin(GPIO_PORT_P7,GPIO_PIN0);
    GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN2);
    GPIO_setOutputHighOnPin(GPIO_PORT_P6,GPIO_PIN4);
}
//这里把left和right进行对调
void left(void)
{

        Car_SetSpeed(75);

    GPIO_setOutputHighOnPin(GPIO_PORT_P4,GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN5);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN2);
    GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN6);
    GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN7);
    GPIO_setOutputLowOnPin(GPIO_PORT_P7,GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN2);
    GPIO_setOutputHighOnPin(GPIO_PORT_P6,GPIO_PIN4);
}

void right(void)
{

            Car_SetSpeed(75);//75

       GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN1);
       GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN5);
       GPIO_setOutputHighOnPin(GPIO_PORT_P4,GPIO_PIN2);
       GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN6);
       GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN7);
       GPIO_setOutputHighOnPin(GPIO_PORT_P7,GPIO_PIN0);
       GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN2);
       GPIO_setOutputLowOnPin(GPIO_PORT_P6,GPIO_PIN4);
}

void run_right(void)
{
    if(PID()==0)
    {
        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,5+35);//40
        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2,36-35);//1
        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,36-35);//1
        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_4,5+35);//40
    }
    else
    {
        //Car_SetSpeed2(35);//80
        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,45+30);//40  60
        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2,45-30);
        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,45-30);
        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_4,45+30);
    }
     //   Car_SetSpeed2(35);
       GPIO_setOutputHighOnPin(GPIO_PORT_P4,GPIO_PIN1);
       GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN5);
       GPIO_setOutputHighOnPin(GPIO_PORT_P4,GPIO_PIN2);
       GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN6);
       GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN7);
       GPIO_setOutputLowOnPin(GPIO_PORT_P7,GPIO_PIN0);
       GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN2);
       GPIO_setOutputLowOnPin(GPIO_PORT_P6,GPIO_PIN4);
    }
//void run_right_diyiti(void)
//{
//    if(PID()==0)
//    {
//        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,5+35);//40
//        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2,36-35);//1
//        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,36-35);//1
//        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_4,5+35);//40
//    }
//    else
//    {
//        //Car_SetSpeed2(35);//80
//        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,45+30);//40  60
//        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2,45-30);
//        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,45-30);
//        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_4,45+30);
//    }
//     //   Car_SetSpeed2(35);
//       GPIO_setOutputHighOnPin(GPIO_PORT_P4,GPIO_PIN1);
//       GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN5);
//       GPIO_setOutputHighOnPin(GPIO_PORT_P4,GPIO_PIN2);
//       GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN6);
//       GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN7);
//       GPIO_setOutputLowOnPin(GPIO_PORT_P7,GPIO_PIN0);
//       GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN2);
//       GPIO_setOutputLowOnPin(GPIO_PORT_P6,GPIO_PIN4);
//    }


void run_left(void)

{
     if(PID()==0)
        {
        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,40+(-35));//5
        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2,5-(-35));//40
        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,5-(-35));//40
        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_4,40+(-35));//5
        }
     else
     {
         Car_SetSpeed2(-35);//80
     }
    // Car_SetSpeed2(-35);
       GPIO_setOutputHighOnPin(GPIO_PORT_P4,GPIO_PIN1);
       GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN5);
       GPIO_setOutputHighOnPin(GPIO_PORT_P4,GPIO_PIN2);
       GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN6);
       GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN7);
       GPIO_setOutputLowOnPin(GPIO_PORT_P7,GPIO_PIN0);
       GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN2);
       GPIO_setOutputLowOnPin(GPIO_PORT_P6,GPIO_PIN4);
    }
//void run_left_diyiti(void)
//
//{
//     if(PID()==0)
//        {
//        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_1,40+(-35));//5
//        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_2,5-(-35));//40
//        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_3,5-(-35));//40
//        Timer_A_setCompareValue(TIMER_A0_BASE,TIMER_A_CAPTURECOMPARE_REGISTER_4,40+(-35));//5
//        }
//     else
//     {
//         Car_SetSpeed2(-35);//80
//     }
//    // Car_SetSpeed2(-35);
//       GPIO_setOutputHighOnPin(GPIO_PORT_P4,GPIO_PIN1);
//       GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN5);
//       GPIO_setOutputHighOnPin(GPIO_PORT_P4,GPIO_PIN2);
//       GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN6);
//       GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN7);
//       GPIO_setOutputLowOnPin(GPIO_PORT_P7,GPIO_PIN0);
//       GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN2);
//       GPIO_setOutputLowOnPin(GPIO_PORT_P6,GPIO_PIN4);
//    }
    void houtui(void)
    {
       // Car_SetSpeed(80);
        GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN1);
        GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN5);
        GPIO_setOutputLowOnPin(GPIO_PORT_P4,GPIO_PIN2);
        GPIO_setOutputHighOnPin(GPIO_PORT_P3,GPIO_PIN6);
        GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN7);
        GPIO_setOutputHighOnPin(GPIO_PORT_P7,GPIO_PIN0);
        GPIO_setOutputLowOnPin(GPIO_PORT_P3,GPIO_PIN2);
        GPIO_setOutputHighOnPin(GPIO_PORT_P6,GPIO_PIN4);
    }
