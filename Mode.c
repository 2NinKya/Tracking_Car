/*
 * Mode.c
 *
 *  Created on: 2022年7月27日
 *      Author: sbccs
 */
#include <driverlib.h>
#include "sys.h"
#include "delay.h"
#include "Car.h"
#include "IR.h"


//灭的时候是1，亮的时候是0    即踩到黑线是1   没有踩到是0
#define D1      GPIO_getInputPinValue(GPIO_PORT_P1,GPIO_PIN6)
#define D2      GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN2)
#define D3      GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN0)
#define D4      GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN1)

void Mode_Init(void)
{
    GPIO_setAsInputPin(GPIO_PORT_P1,GPIO_PIN6);
    GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN2);
    GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN0);
    GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN1);

}

int M1=2, M2=2,M3=3,M4=4,M5=4;
void Mode(int Number) //走外圈
{
    if(Number == 0)
    {
        stop();
    }
  if(Number==1)//模式一，走外圈（只走一圈）
  {
          if(M1==2|M1==1)
          {
              IR_StraightLine();
          }
          if(M1==0)
          {
              stop();
          }
          if(D1 & D2 & D3 & D4 )   //碰到一次全黑就减一      第一次识别到循迹      第二次识别到停止
          {
              M1--;  //M1==1(继续巡线)    M1==0（停止）
              if(M1==0)
              {
                  stop();
                  GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN4);
                  GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN4);
                  delay_ms(1000);
                  GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN4);
              }
              delay_ms(100);
          }
           if(M1==0)
           {
               stop();
           }
  }



  if(Number==2)//模式二，走内圈
  {
//          if(M2==2|M2==1)
//          {
//              IR_StraightLine_Mode2();
//          }
          if(M2==2)
          {
              IR_StraightLine();
          }
          if(M2==1)
          {
              IR_StraightLine_Mode2();
          }

          if(M2==0)
          {
              stop();
          }
           if(D1 & D2 & D3 & D4 )   //碰到一次全黑就减一      第一次识别到循迹      第二次识别到停止
          {
              M2--;  //M1==1(继续巡线)    M1==0（停止）
              if(M2==0)
              {
                  stop();
                  GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN5);
                  GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN5);
                  delay_ms(1000);
                  GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN5);
              }
              delay_ms(100);
          }

  }

    if(Number==3)//模式三，走外圈（走两圈）
      {
              if(M3==3|M3==2|M3==1)
              {
                     IR_StraightLine();
              }
              if(M3==0)
              {
                  stop();
              }
               if(D1 & D2 & D3 & D4 )   //碰到一次全黑就减一      第一次识别到循迹      第二次识别到停止
              {
                  M3--;  //第一次识别M1==2（继续巡线）         第二次识别M1==1(继续巡线)      第三次识别M1==0（停止）
                  if(M3==0)
                  {
                      stop();
                      GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN4);
                      GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN4);
                      delay_ms(1000);
                      GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN4);
                  }
                  delay_ms(100);
              }
              if(M3==0)
              {
                  stop();
              }
      }



  if(Number==4)//模式四，外圈  内圈 外圈
  {
      if(M4==4|M4==3|M4==1)
      {
          IR_StraightLine();
      }
      if(M4==2)
      {
          IR_StraightLine_Mode2();
      }
      if(M4==0)
      {
          stop();
      }
      if(D1 & D2 & D3 & D4 )   //碰到一次全黑就减一      第一次识别到循迹      第二次识别到停止
      {
          M4--;  //第一次识别M4==3（继续巡线 外圈）         第二次识别M4==2(继续巡线 内圈)   第三次识别M4==1（外圈）   第四次识别M4==0（停止）
          if(M4==0)
          {
              stop();
              GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN4);
              GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN4);
              delay_ms(1000);
              GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN4);
          }
          delay_ms(100);
      }
      if(M4==0)
      {
          stop();
      }

  }


  if(Number==5)//模式五，走外圈（一圈）    第四题
    {
            if(M5==4|M5==3)
            {
                IR_StraightLine();
            }
            if(M5==2)
            {
                run();delay_ms(200);
            }
            if(M5==1)
            {
                IR_StraightLine();
            }
            if(M5==0)
            {
                stop();
            }
             if(D1 & D2 & D3 & D4 )   //碰到一次全黑就减一      第一次识别到循迹      第二次识别到停止
            {
                M5--;  //第一次识别M1==2（继续巡线）         第二次识别M1==1(继续巡线)      第三次识别M1==0（停止）
                if(M5==0)
                {
                    stop();
                    GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN4);
                    GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN4);
                    delay_ms(1000);
                    GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN4);
                }
                delay_ms(100);
            }

    }



}


