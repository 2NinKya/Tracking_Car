/*
 * PID.c
 *
 *  Created on: 2022��7��29��
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

    if(HCSR04_GetDistance()>30)//����ת�򣬲��ͻȻ���
    {
        Balance=28;//75
        return Balance;
    }



    error = HCSR04_GetDistance() - 20;//25
//    if((error - error_last < -10) | (error - error_last >10))//5  -5
//    {
//        error = error_last;
//    }
    Balance = error * Kp;//35�ľ����Ӧ80   ��ǰBalance���35-25��X 4=40   40+40=80 ////////    30�ľ����Ӧ20 40+20=60//////// 31--64   32--68    33�ľ����Ӧ32  32+40=72  34---76
    //(43-25)*4=72  43�ľ�������Ӧ72   44--76



    if(Balance>=80)//������Balance 40
    {
        Balance=80;//80
    }
    if(Balance<0)
    {
        Balance=0;//Balance=0 ��ʱ����ٶ���40
    }
//    error_last = error;

    return Balance;
}




