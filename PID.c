/*
 * PID.c
 *
 *  Created on: 2022年7月29日
 *      Author: sbccs
 */
#include "driverlib.h"
#include "HCSR04.h"
#include "oled.h"

extern uint8_t Distance;


int error;
//int error_last;
int Balance;
int Balance_Last;
int8_t PID(void)               //10
{
    int Kp=4;

    if(HCSR04_GetDistance()>30)//主车转向，测距突然变大
    {
        Balance=28;//75
        return Balance;
    }



    error = HCSR04_GetDistance() - 20;//25
//    if((error - error_last < -10) | (error - error_last >10))//5  -5
//    {
//        error = error_last;
//    }
    Balance = error * Kp;//35的距离对应80   当前Balance最大（35-25）X 4=40   40+40=80 ////////    30的距离对应20 40+20=60//////// 31--64   32--68    33的距离对应32  32+40=72  34---76
    //(43-25)*4=72  43的距离最大对应72   44--76



    if(Balance>=80)//最大输出Balance 40
    {
        Balance=80;//80
    }
    if(Balance<0)
    {
        Balance=0;//Balance=0 此时电机速度是40
    }
//    error_last = error;

    return Balance;
}




