/*
 * IR.c
 *
 *  Created on: 2022年7月15日
 *      Author: sbccs
 */
/*
 * IR.c
 *
 *  Created on: 2022年7月15日
 *      Author: sbccs
 */
#include <driverlib.h>
#include "sys.h"
#include "delay.h"
#include "Car.h"
//灭的时候是1，亮的时候是0 即检测到是1   没有检测到是0
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
//控制小车走直线的程序
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

//左转************************************************************************
       if(D1 & (!D2) & (!D3) & (!D4))//|(D1 & D2  &  (!D3) & (!D4))|(D1 & (!D2)  &  D3 & (!D4)))//*******************************
       {

         //  delay_ms(30);//防止内圈和外圈的误判****************************************(待验证需不需要)
         //  left();delay_ms(150);
           while(!(((!D1) & D2 & D3 & (!D4)))){ left();}
       }
       if((D1 & D2  &  D3 & (!D4)))
       {
//           delay_ms(55);//防止第一次从起点出发误判
//           if((D1 & D2  &  D3 & (!D4)))
//           {
               left();delay_ms(150);
               while(!(((!D1) & D2 & D3 & (!D4)))){ left();}


       }

       if((D1 & D2  &  (!D3) & (!D4))|(D1 & D2  &  D3 & (!D4))|(D1 & (!D2)  &  D3 & (!D4)))//
       {
          // delay_ms(30);//防止内圈和外圈的误判****************************************(待验证需不需要)
          if(deng1==1)
          {
              GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN0);//灯亮
              GPIO_setOutputHighOnPin(GPIO_PORT_P2,GPIO_PIN0);
              deng1--;//deng==0
          }

           left();delay_ms(150);
           while(!(((!D1) & D2 & D3 & (!D4)))){ left();}

       }
       if(((!D1) & D2  &  D3 & D4)|((!D1) & (!D2)  &  D3 & D4)|((!D1) & D2  &  (!D3) & D4)|(D1 & (!D2)  &  (!D3) & D4))
       {
           GPIO_setAsOutputPin(GPIO_PORT_P2,GPIO_PIN0);//灯灭
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
int IR_Room(uint8_t Number)         //Number是串口接收到的蓝牙数据
{

    if(Number == 1)             //表示是一号房间
    {

        if(i1<0)
            {
                stop();
            }
        else if(((!D1) & (!D2) & D3 & (!D4)) | ((!D1) & D2 & (!D3) & (!D4))|((!D1)&(D2)&(D3)&(!D4))           |(D1 & (!D2) & (!D3) & (!D4)) |((!D1) & (!D2) & (!D3) & D4) )       //|     ((!D1)&(!D2)&D3&D4)|((!D1)&D2&(!D3)&D4)|((!D1)&D2&D3&D4)|(D1&(!D2)&D3&(!D4))|(D1&(!D2)&D3&D4)|(D1&D2&(!D3)&(!D4))|(D1&D2&(!D3)&D4)|(D1&D2&D3&(!D4)))//中间两个红外扫到就行
        {
            //run();
            IR_StraightLine();
        }
        else if(D1 & D2 & D3 & D4)                                          // i1原来==1       i1=0   第一次识别到（左转）   i3=-1 第二次识别到（停止）
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

    if(Number == 2)             //表示是二号房间
    {

        if(i2<0)
            {
                stop();
            }
        else if(((!D1) & (!D2) & D3 & (!D4)) | ((!D1) & D2 & (!D3) & (!D4))|((!D1)&(D2)&(D3)&(!D4))       |(D1 & (!D2) & (!D3) & (!D4)) |((!D1) & (!D2) & (!D3) & D4)   )//|     ((!D1)&(!D2)&D3&D4)|((!D1)&D2&(!D3)&D4)|((!D1)&D2&D3&D4)|(D1&(!D2)&D3&(!D4))|(D1&(!D2)&D3&D4)|(D1&D2&(!D3)&(!D4))|(D1&D2&(!D3)&D4)|(D1&D2&D3&(!D4)))//中间两个红外扫到就行
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






        if(Number == 3) //i3=2  房间3总共要识别到3次全黑的情况
    {

        if(i3<0)
            {
                stop();
            }
        else if(((!D1) & (!D2) & D3 & (!D4)) | ((!D1) & D2 & (!D3) & (!D4))|((!D1)&(D2)&(D3)&(!D4))      |(D1 & (!D2) & (!D3) & (!D4)) |((!D1) & (!D2) & (!D3) & D4))//|     ((!D1)&(!D2)&D3&D4)|((!D1)&D2&(!D3)&D4)|((!D1)&D2&D3&D4)|(D1&(!D2)&D3&(!D4))|(D1&(!D2)&D3&D4)|(D1&D2&(!D3)&(!D4))|(D1&D2&(!D3)&D4)|(D1&D2&D3&(!D4)))//中间两个红外扫到就行
        {
            //run();
            IR_StraightLine();
        }
        else if(D1 & D2 & D3 & D4)
        {
            i3--;//i3=1   第一次识别到（直走）   i3=0 第二次识别到（左转）   i3<0第三次识别到（停止）
            if(i3==1)
           {
                IR_StraightLine();
                delay_ms(100);//试一下，感觉这个延时很有必要
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



    if(Number == 4)//i4=2  房间4同3
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
        else if(D1 & D2 & D3 & D4)            //|((!D1)&(!D2)&(!D3)&(!D4)))//碰到一次全黑就减计数一次
        {
            i4--;//i4=1   第一次识别到（直走）   i4=0 第二次识别到（左转）     i4<0第三次识别到（停止）

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
            if(i4<-127)//复位变量i3，防止溢出
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
        else if(D1 & D2 & D3 & D4)//碰到一次全黑就减计数一次
        {
            i5--;//i5=3 第一次识别到（直走）     i5=2 第二次识别到（直走）  i5=1 第三次识别到（左转）   i5=0 第四次识别到（左转） i5<0 第五次识别到（停止）
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
            if(i5<-126)//复位变量i3，防止溢出
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
        else if(D1 & D2 & D3 & D4)//碰到一次全黑就减计数一次
        {
            i6--;//i6=3 第一次识别到（直走）     i6=2 第二次识别到（直走）  i6=1 第三次识别到（右转）   i6=0 第四次识别到（右转） i6<0 第五次识别到（停止）
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
            if(i6<-126)//复位变量i3，防止溢出
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
        else if(D1 & D2 & D3 & D4)//碰到一次全黑就减计数一次
        {
            i7--;//i7=3 第一次识别到（直走）     i7=2 第二次识别到（直走）  i7=1 第三次识别到（左转）   i7=0 第四次识别到（右转） i7<0 第五次识别到（停止）
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
            if(i7<-126)//复位变量i3，防止溢出
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
        else if(D1 & D2 & D3 & D4)//碰到一次全黑就减计数一次
        {
            i8--;//i7=3 第一次识别到（直走）     i8=2 第二次识别到（直走）  i8=1 第三次识别到（右转）   i8=0 第四次识别到（左转） i8<0 第五次识别到（停止）
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
            if(i8<-126)//复位变量i3，防止溢出
            {
                i8=-2;
            }

            //stop();
        }
    }
    return Number;

}
