/*
 * IR.c
 *
 *  Created on: 2022��7��15��
 *      Author: sbccs
 */
/*
 * IR.c
 *
 *  Created on: 2022��7��15��
 *      Author: sbccs
 */
#include <driverlib.h>
#include "sys.h"
#include "delay.h"
#include "Car.h"
//���ʱ����1������ʱ����0 ����⵽��1   û�м�⵽��0
#define D1      GPIO_getInputPinValue(GPIO_PORT_P1,GPIO_PIN6)
#define D2      GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN2)
#define D3      GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN0)
#define D4      GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN1)

void IR_Init(void)
{
    GPIO_setAsInputPin(GPIO_PORT_P1,GPIO_PIN6);
    GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN2);
    GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN0);
    GPIO_setAsInputPin(GPIO_PORT_P6,GPIO_PIN1);
}
//����С����ֱ�ߵĳ���
void IR_StraightLine(void)
{//***********************************************************************************************************************
    while((!D1)  &  D2  & (!D3) & (!D4))// //      |(   D1  &  D2  & D3 & (!D4))|((!D1)  &  D2  & (!D3) & D4))
   {run_left();}

    while((!D1)  &  (!D2)  & D3 & (!D4))//
    {run_right();}
    if(D1 & (!D2) & (!D3) & (!D4))
    {
        while(!(((!D1) & D2 & D3 & (!D4)))){ left();}
    }
    if((!D1) & (!D2) & (!D3) & D4)
    {
        while(!(((!D1) & D2 & D3 & (!D4)))){ right();}
    }
    if((!D1)&(D2)&(D3)&(!D4))
    {
        run();
    }

}
int deng1=1;
void IR_StraightLine_Mode2(void)
{
       while((!D1)  &  D2  & (!D3) & (!D4))// //      |(   D1  &  D2  & D3 & (!D4))|((!D1)  &  D2  & (!D3) & D4))
       {run_left();}

       while((!D1)  &  (!D2)  & D3 & (!D4))//
       {run_right();}

//��ת************************************************************************
       if(D1 & (!D2) & (!D3) & (!D4))//|(D1 & D2  &  (!D3) & (!D4))|(D1 & (!D2)  &  D3 & (!D4)))//*******************************
       {

         //  delay_ms(30);//��ֹ��Ȧ����Ȧ������****************************************(����֤�費��Ҫ)
         //  left();delay_ms(150);
           while(!(((!D1) & D2 & D3 & (!D4)))){ left();}
       }
       if((D1 & D2  &  D3 & (!D4)))
       {
//           delay_ms(55);//��ֹ��һ�δ�����������
//           if((D1 & D2  &  D3 & (!D4)))
//           {
               left();delay_ms(150);
               while(!(((!D1) & D2 & D3 & (!D4)))){ left();}


       }

       if((D1 & D2  &  (!D3) & (!D4))|(D1 & D2  &  D3 & (!D4))|(D1 & (!D2)  &  D3 & (!D4)))//
       {
          // delay_ms(30);//��ֹ��Ȧ����Ȧ������****************************************(����֤�費��Ҫ)
          if(deng1==1)
          {
              GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN0);//����
              GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN0);
              deng1--;//deng==0
          }

           left();delay_ms(150);
           while(!(((!D1) & D2 & D3 & (!D4)))){ left();}

       }
       if(((!D1) & D2  &  D3 & D4)|((!D1) & (!D2)  &  D3 & D4)|((!D1) & D2  &  (!D3) & D4)|(D1 & (!D2)  &  (!D3) & D4))
       {
           GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN0);//����
           GPIO_setOutputLowOnPin(GPIO_PORT_P2,GPIO_PIN0);
       }

       if((!D1) & (!D2) & (!D3) & D4)
       {
           delay_ms(50);
           if((!D1) & (!D2) & (!D3) & D4)
           {
               while(!(((!D1) & D2 & D3 & (!D4)))){ right();}
           }

       }
       if((!D1)&(D2)&(D3)&(!D4))
       {
           run();
       }
}


int8_t  i1=1,i2=1,i3=2,i4=2,i5=4,i6=4,i7=4,i8=4;
int IR_Room(uint8_t Number)         //Number�Ǵ��ڽ��յ�����������
{

    if(Number == 1)             //��ʾ��һ�ŷ���
    {

        if(i1<0)
            {
                stop();
            }
        else if(((!D1) & (!D2) & D3 & (!D4)) | ((!D1) & D2 & (!D3) & (!D4))|((!D1)&(D2)&(D3)&(!D4))           |(D1 & (!D2) & (!D3) & (!D4)) |((!D1) & (!D2) & (!D3) & D4) )       //|     ((!D1)&(!D2)&D3&D4)|((!D1)&D2&(!D3)&D4)|((!D1)&D2&D3&D4)|(D1&(!D2)&D3&(!D4))|(D1&(!D2)&D3&D4)|(D1&D2&(!D3)&(!D4))|(D1&D2&(!D3)&D4)|(D1&D2&D3&(!D4)))//�м���������ɨ������
        {
            //run();
            IR_StraightLine();
        }
        else if(D1 & D2 & D3 & D4)                                          // i1ԭ��==1       i1=0   ��һ��ʶ�𵽣���ת��   i3=-1 �ڶ���ʶ�𵽣�ֹͣ��
        {
            i1--;  //i1=0
            if(i1==0)
            {
                left();delay_ms(150);//+++++++++++++++++++++++++++++++++++++++++
                while(!(((!D1) & D2 & D3 & (!D4))    )){ left();}
            }
            if(i1==-1)
            {
                stop();
                houtui();
                delay_ms(200);
            }
            if(i1==-2)
            {
                stop();
            }
            if(i1<-126)
            {
                i1=-2;
            }

            stop();
        }

    }

    if(Number == 2)             //��ʾ�Ƕ��ŷ���
    {

        if(i2<0)
            {
                stop();
            }
        else if(((!D1) & (!D2) & D3 & (!D4)) | ((!D1) & D2 & (!D3) & (!D4))|((!D1)&(D2)&(D3)&(!D4))       |(D1 & (!D2) & (!D3) & (!D4)) |((!D1) & (!D2) & (!D3) & D4)   )//|     ((!D1)&(!D2)&D3&D4)|((!D1)&D2&(!D3)&D4)|((!D1)&D2&D3&D4)|(D1&(!D2)&D3&(!D4))|(D1&(!D2)&D3&D4)|(D1&D2&(!D3)&(!D4))|(D1&D2&(!D3)&D4)|(D1&D2&D3&(!D4)))//�м���������ɨ������
        {
            //run();
            IR_StraightLine();
        }
        else if(D1 & D2 & D3 & D4)
        {
            i2--;
            if(i2==0)
            {
                right();delay_ms(150);//+++++++++++++++++++++++++++
                while(!((!D1) & D2 & D3 & (!D4)) ){right();}
            }
            if(i2==-1)
            {
                stop();
                houtui();
                delay_ms(200);
            }
            if(i2==-2)
            {
                stop();
            }
            if(i2<-126)
            {
                i2=-2;
            }
            stop();
        }
    }






        if(Number == 3) //i3=2  ����3�ܹ�Ҫʶ��3��ȫ�ڵ����
    {

        if(i3<0)
            {
                stop();
            }
        else if(((!D1) & (!D2) & D3 & (!D4)) | ((!D1) & D2 & (!D3) & (!D4))|((!D1)&(D2)&(D3)&(!D4))      |(D1 & (!D2) & (!D3) & (!D4)) |((!D1) & (!D2) & (!D3) & D4))//|     ((!D1)&(!D2)&D3&D4)|((!D1)&D2&(!D3)&D4)|((!D1)&D2&D3&D4)|(D1&(!D2)&D3&(!D4))|(D1&(!D2)&D3&D4)|(D1&D2&(!D3)&(!D4))|(D1&D2&(!D3)&D4)|(D1&D2&D3&(!D4)))//�м���������ɨ������
        {
            //run();
            IR_StraightLine();
        }
        else if(D1 & D2 & D3 & D4)
        {
            i3--;//i3=1   ��һ��ʶ�𵽣�ֱ�ߣ�   i3=0 �ڶ���ʶ�𵽣���ת��   i3<0������ʶ�𵽣�ֹͣ��
            if(i3==1)
           {
                IR_StraightLine();
                delay_ms(100);//��һ�£��о������ʱ���б�Ҫ
           }
            if(i3==0)
            {
                left();delay_ms(150);//+++++++++++++++++++++++++++
                while(!((!D1) & D2 & D3 &(!D4)) ){left();}
            }
            if(i3==-1)
            {
                stop();
                houtui();
                delay_ms(200);
            }
            if(i3==-2)
            {
                stop();
            }
            if(i3<-126)
            {
                i3=-2;
            }
         //   stop();
        }

    }



    if(Number == 4)//i4=2  ����4ͬ3
    {
        if(i4<-1)
            {
                stop();
            }
//        if(i4<0)
//              {
//                 stop();
//              }
        if(((!D1) & (!D2) & D3 & (!D4)) | ((!D1) & D2 & (!D3) & (!D4))|((!D1)&(D2)&(D3)&(!D4))                    |(D1 & (!D2) & (!D3) & (!D4)) |((!D1) & (!D2) & (!D3) & D4)   )

        //if(((!D1) & (!D2) & D3 & (!D4)) | ((!D1) & D2 & (!D3) & (!D4))|((!D1)&(D2)&(D3)&(!D4))|     ((!D1)&(!D2)&D3&D4)|((!D1)&D2&(!D3)&D4)|((!D1)&D2&D3&D4)|(D1&(!D2)&D3&(!D4))|(D1&(!D2)&D3&D4)|(D1&D2&(!D3)&(!D4))|(D1&D2&(!D3)&D4)|(D1&D2&D3&(!D4)))
        {
            //run();
        IR_StraightLine();
        }
        else if(D1 & D2 & D3 & D4)            //|((!D1)&(!D2)&(!D3)&(!D4)))//����һ��ȫ�ھͼ�����һ��
        {
            i4--;//i4=1   ��һ��ʶ�𵽣�ֱ�ߣ�   i4=0 �ڶ���ʶ�𵽣���ת��     i4<0������ʶ�𵽣�ֹͣ��

            if(i4==1)
            {
                //run();
                IR_StraightLine();
                delay_ms(100);
            }
            if(i4==0)
            {
                right();delay_ms(100);//+++++++++++++++++++++++++++
                while(!((!D1) & D2 & D3 & (!D4)) ){right();}
            }
//            if(i4<0)//i4=-1
//            {
//                stop();
//            }
            if(i4==-1)
            {
                stop();
                houtui();
                delay_ms(200);
            }
            if(i4==-2)
            {
                stop();
            }
            if(i4<-127)//��λ����i3����ֹ���
            {
                i4=-2;
            }

        //  stop();
        }

    }




    if(Number == 5) //i5=4
    {
        if(i5<0)
            {
                stop();
            }
        if(((!D1) & (!D2) & D3 & (!D4)) | ((!D1) & D2 & (!D3) & (!D4))|((!D1)&(D2)&(D3)&(!D4))|((!D1) & (!D2) & (!D3) & D4)          |(D1 & (!D2) & (!D3) & (!D4)) )
        {

            IR_StraightLine();
        }
        else if(D1 & D2 & D3 & D4)//����һ��ȫ�ھͼ�����һ��
        {
            i5--;//i5=3 ��һ��ʶ�𵽣�ֱ�ߣ�     i5=2 �ڶ���ʶ�𵽣�ֱ�ߣ�  i5=1 ������ʶ�𵽣���ת��   i5=0 ���Ĵ�ʶ�𵽣���ת�� i5<0 �����ʶ�𵽣�ֹͣ��
            if(i5==3|i5==2)
            {

                IR_StraightLine();
                delay_ms(100);
            }

            if(i5==1|i5==0)
            {
                left();delay_ms(150);//+++++++++++++++++++++++++++
                while(!((!D1) & D2 & D3 & (!D4)) ){left();}
            }
            if(i5==-1)
            {
                stop();
                houtui();
                delay_ms(200);
            }
            if(i5==-2)
            {
                stop();
            }
            if(i5<-126)//��λ����i3����ֹ���
            {
                i5=-2;
            }

            //stop();
        }
    }

    if(Number == 6) //i6=4
    {
        if(i6<0)
            {
                stop();
            }
        if(((!D1) & (!D2) & D3 & (!D4)) | ((!D1) & D2 & (!D3) & (!D4))|((!D1)&(D2)&(D3)&(!D4))                           |(D1 & (!D2) & (!D3) & (!D4)) |((!D1) & (!D2) & (!D3) & D4))
        {
            IR_StraightLine();
        }
        else if(D1 & D2 & D3 & D4)//����һ��ȫ�ھͼ�����һ��
        {
            i6--;//i6=3 ��һ��ʶ�𵽣�ֱ�ߣ�     i6=2 �ڶ���ʶ�𵽣�ֱ�ߣ�  i6=1 ������ʶ�𵽣���ת��   i6=0 ���Ĵ�ʶ�𵽣���ת�� i6<0 �����ʶ�𵽣�ֹͣ��
            if(i6==3|i6==2)
            {
                IR_StraightLine();
                delay_ms(100);
            }

            if(i6==1|i6==0)
            {
                right();delay_ms(100);//+++++++++++++++++++++++++++
                while(!((!D1) & D2 & D3 & (!D4)) ){right();}
            }
            if(i6==-1)
            {
                stop();
                houtui();
                delay_ms(200);
            }
            if(i6==-2)
            {
                stop();
            }
            if(i6<-126)//��λ����i3����ֹ���
            {
                i6=-2;
            }

            //stop();
        }
    }


    if(Number == 7) //i7=4
    {
        if(i7<0)
            {
                stop();
            }
        if(((!D1) & (!D2) & D3 & (!D4)) | ((!D1) & D2 & (!D3) & (!D4))|((!D1)&(D2)&(D3)&(!D4))                     |(D1 & (!D2) & (!D3) & (!D4)) |((!D1) & (!D2) & (!D3) & D4))
        {
            IR_StraightLine();
        }
        else if(D1 & D2 & D3 & D4)//����һ��ȫ�ھͼ�����һ��
        {
            i7--;//i7=3 ��һ��ʶ�𵽣�ֱ�ߣ�     i7=2 �ڶ���ʶ�𵽣�ֱ�ߣ�  i7=1 ������ʶ�𵽣���ת��   i7=0 ���Ĵ�ʶ�𵽣���ת�� i7<0 �����ʶ�𵽣�ֹͣ��
            if(i7==3|i7==2)
            {
                IR_StraightLine();
                delay_ms(100);
            }
            if(i7==1)
            {
                left();delay_ms(150);//+++++++++++++++++++++++++++
                while(!((!D1) & D2 & D3 & (!D4)) ){left();}
            }
            if(i7==0)
            {
                right();delay_ms(150);//+++++++++++++++++++++++++++
                while(!((!D1) & D2 & D3 & (!D4)) ){right();}
            }

            if(i7==-1)
            {
                stop();
                houtui();
                delay_ms(200);
            }
            if(i7==-2)
            {
                stop();
            }
            if(i7<-126)//��λ����i3����ֹ���
            {
                i7=-2;
            }

            //stop();
        }
    }

    if(Number == 8) //i8=4
    {
        if(i8<0)
            {
                stop();
            }
        if(((!D1) & (!D2) & D3 & (!D4)) | ((!D1) & D2 & (!D3) & (!D4))|((!D1)&(D2)&(D3)&(!D4))       |(D1 & (!D2) & (!D3) & (!D4)) |((!D1) & (!D2) & (!D3) & D4))
        {
            IR_StraightLine();
        }
        else if(D1 & D2 & D3 & D4)//����һ��ȫ�ھͼ�����һ��
        {
            i8--;//i7=3 ��һ��ʶ�𵽣�ֱ�ߣ�     i8=2 �ڶ���ʶ�𵽣�ֱ�ߣ�  i8=1 ������ʶ�𵽣���ת��   i8=0 ���Ĵ�ʶ�𵽣���ת�� i8<0 �����ʶ�𵽣�ֹͣ��
            if(i8==3|i8==2)
            {
                IR_StraightLine();
                delay_ms(200);
            }
            if(i8==1)
            {
                right();delay_ms(200);//++++++++++++++++++++
                while(!((!D1) & D2 & D3 & (!D4)) ){right();}
            }
            if(i8==0)
            {
                left();delay_ms(200);//+++++++++++++++++++++
                while(!((!D1) & D2 & D3 & (!D4)) ){left();}
            }

            if(i8==-1)
            {
                stop();
                houtui();
                delay_ms(200);
            }
            if(i8==-2)
            {
                stop();
            }
            if(i8<-126)//��λ����i3����ֹ���
            {
                i8=-2;
            }

            //stop();
        }
    }
    return Number;

}
