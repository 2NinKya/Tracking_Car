/*
 * KeyMode.c
 *
 *  Created on: 2022年7月27日
 *      Author: TANG
 */
#include "driverlib.h"
#include "OLED.h"
#include "Mode.h"



//extern int M1,M2,M3,M4,M5;
//extern uint8_t buf[];
//
//
//
//int KeyNum(void)
//{
//         if(buf[5] == 48)                                          //副车收到测试信号
//         {
//
//             OLED_ShowString(0,0,"Link OK",15);
//             return 0;                                             //KeyNum = 0
//                 HCSR04_Init();
//         }
//         if(buf[9] == 49)                                          //副车收到起跑信号
//         {
//             OLED_ShowString(0,4,"Run",15);
//             return 1;                                             //KeyNum = 1
//         }
//         if(buf[9] == 50)
//         {
//             OLED_ShowString(0,4,"   ",15);
//             OLED_ShowString(0,6,"Stop",15);
//             return 0;
//         }
//         if(buf[9]  == 51)                                         //跑两圈
//         {
//             OLED_ShowString(0,6,"    ",15);
//             OLED_ShowString(0,4,"Round Two",15);
//             return 3;
//         }
//         if(buf[9] == 52)                                          //跑三圈
//         {
//             OLED_ShowString(0,4,"         ",15);
//             OLED_ShowString(0,6,"Round Three",15);
//             return 4;
//         }
//         if(buf[9] == 53)                                         //最后一问
//         {
//             OLED_ShowString(0,6,"           ",15);
//             OLED_ShowString(0,4,"Last Round!",15);
//             return 5;
////         }
//         return 0;
//}


//void Mode_Select(void)
//{
//            if(buf[9] == 49)
//             {
//                 M1 = KeyNum();
//                 Mode(1);
//             }
//             if(buf[9] == 51)
//             {
//                 M3 = KeyNum();
//                 Mode(3);
//             }
//             if(buf[9] == 52)
//             {
//                 M4 = KeyNum();
//                 Mode(4);
//             }
//             if(buf[9] == 53)
//             {
//                 M5 = KeyNum();
//                 Mode(5);
//             }
//
//}
