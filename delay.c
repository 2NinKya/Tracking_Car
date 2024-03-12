/*
 * delay.c
 *
 *  Created on: 2022年7月14日
 *      Author: TANG
 */

#include "msp430.h"
void delay_us(short int us)
{
    for(;us>0;us--) __delay_cycles(25);
}

void delay_ms(short int ms)                         //系统主频被改为了25MHz
{
    for(;ms>0;ms--) __delay_cycles(25000);          //25000000/25000 = 1000Hz
}

void delay_s(unsigned char s)
{
    for(;s>0;s--)   delay_ms(1000);
}

