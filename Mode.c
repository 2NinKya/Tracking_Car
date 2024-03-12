/*
 * Mode.c
 *
 *  Created on: 2022��7��27��
 *      Author: sbccs
 */
#include <driverlib.h>
#include "sys.h"
#include "delay.h"
#include "Car.h"
#include "IR.h"


//���ʱ����1������ʱ����0    ���ȵ�������1   û�вȵ���0
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
void Mode(int Number) //����Ȧ
{
    if(Number == 0)
    {
        stop();
    }
  if(Number==1)//ģʽһ������Ȧ��ֻ��һȦ��
  {
          if(M1==2|M1==1)
          {
              IR_StraightLine();
          }
          if(M1==0)
          {
              stop();
          }
          if(D1 & D2 & D3 & D4 )   //����һ��ȫ�ھͼ�һ      ��һ��ʶ��ѭ��      �ڶ���ʶ��ֹͣ
          {
              M1--;  //M1==1(����Ѳ��)    M1==0��ֹͣ��
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



  if(Number==2)//ģʽ��������Ȧ
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
           if(D1 & D2 & D3 & D4 )   //����һ��ȫ�ھͼ�һ      ��һ��ʶ��ѭ��      �ڶ���ʶ��ֹͣ
          {
              M2--;  //M1==1(����Ѳ��)    M1==0��ֹͣ��
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

    if(Number==3)//ģʽ��������Ȧ������Ȧ��
      {
              if(M3==3|M3==2|M3==1)
              {
                     IR_StraightLine();
              }
              if(M3==0)
              {
                  stop();
              }
               if(D1 & D2 & D3 & D4 )   //����һ��ȫ�ھͼ�һ      ��һ��ʶ��ѭ��      �ڶ���ʶ��ֹͣ
              {
                  M3--;  //��һ��ʶ��M1==2������Ѳ�ߣ�         �ڶ���ʶ��M1==1(����Ѳ��)      ������ʶ��M1==0��ֹͣ��
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



  if(Number==4)//ģʽ�ģ���Ȧ  ��Ȧ ��Ȧ
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
      if(D1 & D2 & D3 & D4 )   //����һ��ȫ�ھͼ�һ      ��һ��ʶ��ѭ��      �ڶ���ʶ��ֹͣ
      {
          M4--;  //��һ��ʶ��M4==3������Ѳ�� ��Ȧ��         �ڶ���ʶ��M4==2(����Ѳ�� ��Ȧ)   ������ʶ��M4==1����Ȧ��   ���Ĵ�ʶ��M4==0��ֹͣ��
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


  if(Number==5)//ģʽ�壬����Ȧ��һȦ��    ������
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
             if(D1 & D2 & D3 & D4 )   //����һ��ȫ�ھͼ�һ      ��һ��ʶ��ѭ��      �ڶ���ʶ��ֹͣ
            {
                M5--;  //��һ��ʶ��M1==2������Ѳ�ߣ�         �ڶ���ʶ��M1==1(����Ѳ��)      ������ʶ��M1==0��ֹͣ��
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


