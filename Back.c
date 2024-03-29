/*
 * Back.c
 *
 *  Created on: 2022年7月15日
 *      Author: sbccs
 */
//+++++++++++++++++++++5 6 转弯条件有改动
#include <driverlib.h>
#include "sys.h"
#include "delay.h"
#include "Car.h"
#include "IR.h"
#define D1      GPIO_getInputPinValue(GPIO_PORT_P1,GPIO_PIN6)
#define D2      GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN2)
#define D3      GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN0)
#define D4      GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN1)

//使用中断给Back函数赋参数backflag，实现返程
void Back_Init(void)//中断初始化
{
        GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

        GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN1);
        //P2.1 interrupt enabled
        GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN1);  //使能中断

        //P2.1 Hi/Lo edge
        GPIO_selectInterruptEdge(GPIO_PORT_P2, GPIO_PIN1, GPIO_HIGH_TO_LOW_TRANSITION); //设置中断类型

        //P2.1 IFG cleared
        GPIO_clearInterrupt(GPIO_PORT_P2, GPIO_PIN1);   //清除中断标志位

        __bis_SR_register(GIE); //启用可屏蔽中断

}



int8_t j1=2,j2=2,j3=3,j4=3,j5=5,j6=5,j7=5,j8=5;
void Back(uint8_t backflag)//backflag是中断返回的房间数（Number）
{

    if(backflag == 1)               //表示是一号房间
    {
        if(j1<0)
        {
        stop();
        }
        if(j1==2)
        {
            //先掉头
            while(!(((!D1) & D2 & D3 & (!D4)))){ left();}
        j1--;//再自减一 j1=1
        }
        //再直走
        else if(((!D1) & (!D2) & D3 & (!D4)) | ((!D1) & D2 & (!D3) & (!D4))|((!D1)&(D2)&(D3)&(!D4))                 |(D1 & (!D2) & (!D3) & (!D4)) |((!D1) & (!D2) & (!D3) & D4))//|     ((!D1)&(!D2)&D3&D4)|((!D1)&D2&(!D3)&D4)|((!D1)&D2&D3&D4)|(D1&(!D2)&D3&(!D4))|(D1&(!D2)&D3&D4)|(D1&D2&(!D3)&(!D4))|(D1&D2&(!D3)&D4)|(D1&D2&D3&(!D4)))//中间两个红外扫到就行
        {
            //run();
            IR_StraightLine();
        }
        else if(D1 & D2 & D3 & D4)
        {
            j1--;//遇见一次黑线就自减一  j1=0
            if(j1==0)
            {
                right();delay_ms(200);//+++++++++++++++++++++
                while(!((!D1) & D2 & D3 & (!D4)) ){right();}
            }
            if(j1==-1)
            {
                stop();
                houtui();
                delay_ms(150);
            }

            if(j1<-126)
            {
                j1=-2;
            }
            stop();
        }

    }


    if(backflag == 2)               //表示是2号房间
    {
        if(j2<0)
        {
        stop();
        }
        if(j2==2)
        {
            //先掉头
        while(!((!D1)&D2&D3&(!D4))){left();}
        j2--;//再自减一 j1=1
        }
        //再直走
        else if(((!D1) & (!D2) & D3 & (!D4)) | ((!D1) & D2 & (!D3) & (!D4))|((!D1)&(D2)&(D3)&(!D4))           |(D1 & (!D2) & (!D3) & (!D4)) |((!D1) & (!D2) & (!D3) & D4))//|     ((!D1)&(!D2)&D3&D4)|((!D1)&D2&(!D3)&D4)|((!D1)&D2&D3&D4)|(D1&(!D2)&D3&(!D4))|(D1&(!D2)&D3&D4)|(D1&D2&(!D3)&(!D4))|(D1&D2&(!D3)&D4)|(D1&D2&D3&(!D4)))//中间两个红外扫到就行
        {
            //run();
            IR_StraightLine();
        }
        else if(D1 & D2 & D3 & D4)
        {
            j2--;//遇见一次黑线就自减一  j1=0
            if(j2==0)
            {
                left();delay_ms(150);//++++++++++++++++++++++++++++++++++++++++++++
                while(!((!D1) & D2 & D3 & (!D4)) ){left();}
            }
            if(j2<-126)
            {
                j2=-1;
            }
            stop();
        }

    }


        if(backflag == 3)               //表示是3号房间
    {
        if(j3<0)     //原j3=3
        {
        stop();
        }
        if(j3==3)
        {
            //先掉头
        while(!((!D1)&D2&D3&(!D4))){left();}
        j3--;//再自减一 j3=2
        }
        //再直走
        else if(((!D1) & (!D2) & D3 & (!D4)) | ((!D1) & D2 & (!D3) & (!D4))|((!D1)&(D2)&(D3)&(!D4))                 |(D1 & (!D2) & (!D3) & (!D4)) |((!D1) & (!D2) & (!D3) & D4))//|     ((!D1)&(!D2)&D3&D4)|((!D1)&D2&(!D3)&D4)|((!D1)&D2&D3&D4)|(D1&(!D2)&D3&(!D4))|(D1&(!D2)&D3&D4)|(D1&D2&(!D3)&(!D4))|(D1&D2&(!D3)&D4)|(D1&D2&D3&(!D4)))//中间两个红外扫到就行
        {
            //run();
            IR_StraightLine();
        }
        else if(D1 & D2 & D3 & D4)
        {
            j3--;//遇见一次黑线就自减一  第一次遇见黑线 j3=1（右转）     第二次遇见黑线 j3=0（直走）    第三次遇见黑线 j3<0 (停止)

            if(j3==1)
            {
                right();delay_ms(150);//+++++++++++++++++++++++++++++++++++++++++++++++++++
                while(!((!D1) & D2 & D3 & (!D4)) ){right();}
            }
            if(j3==0)
            {
                IR_StraightLine();
                delay_ms(100);
            }
            if(j3<-126)
            {
                j3=-1;
            }
            stop();
        }

    }

    if(backflag == 4)               //表示是4号房间
    {
        if(j4<0)     //原j4=3
        {
        stop();
        }
        if(j4==3)
        {
            //先掉头
        while(!((!D1)&D2&D3&(!D4))){left();}
        j4--;//再自减一 j4=2
        }
        //再直走
        else if(((!D1) & (!D2) & D3 & (!D4)) | ((!D1) & D2 & (!D3) & (!D4))|((!D1)&(D2)&(D3)&(!D4))                  |(D1 & (!D2) & (!D3) & (!D4)) |((!D1) & (!D2) & (!D3) & D4)     )//|     ((!D1)&(!D2)&D3&D4)|((!D1)&D2&(!D3)&D4)|((!D1)&D2&D3&D4)|(D1&(!D2)&D3&(!D4))|(D1&(!D2)&D3&D4)|(D1&D2&(!D3)&(!D4))|(D1&D2&(!D3)&D4)|(D1&D2&D3&(!D4)))//中间两个红外扫到就行
        {
            //run();
            IR_StraightLine();
        }
        else if(D1 & D2 & D3 & D4)
        {
            j4--;//遇见一次黑线就自减一  第一次遇见黑线 j4=1（左转）     第二次遇见黑线 j4=0（直走）    第三次遇见黑线 j4<0 (停止)

            if(j4==1)
            {
                left();delay_ms(150);//+++++++++++++++++++++++++++++++++++++++++++++++++++
                while(!((!D1) & D2 & D3 & (!D4)) ){left();}
            }
            if(j4==0)
            {
                IR_StraightLine();
                delay_ms(100);
            }
            if(j4<-126)
            {
                j4=-1;
            }
            stop();
        }

    }

//    if(backflag == 5)               //表示是5号房间
//    {
//        if(j5<0)     //原j5=5
//        {
//        stop();
//        }
//        if(j5==5)
//        {
//            houtui();
//            delay_ms(500);
//            left();delay_ms(200);
//            while(!((!D1)&D2&D3&(!D4))){left();};
//            j5--;//再自减一 j6=4
//        }
//        //再直走
//        else if(((!D1) & (!D2) & D3 & (!D4)) | ((!D1) & D2 & (!D3) & (!D4))|((!D1)&(D2)&(D3)&(!D4))                      |((!D1) & (!D2) & (!D3) & D4) |(D1 & (!D2) & (!D3) & (!D4)))
//        {
//            //run();
//            IR_StraightLine();
//        }
//        else if((D1 & D2 & D3 & D4)|((!D1) & D2 & D3 & D4)               |((!D1) & (!D2) & D3 & D4)    )//+++++++++++++++++++++++++++++++++++++++++++++++
//        {
//            j5--;//遇见一次黑线就自减一  第一次遇见黑线 j5=3（右转）     第二次遇见黑线 j5=2（右转）     第三次遇见黑线j5=1 (直走)     第四次遇见黑线 j5=0 (直走)  第五次遇见黑线 j5<0 (停止)
//            if(j5==3)//|j5==2)
//            {
//                right();delay_ms(200);//++++++++++++++++++++++++++++++++++++++++++++++++
//                while(!((!D1) & D2 & D3 &(!D4)) ){right();}
//            }
//            if(j5==2|j5==1)
//            {
//                IR_StraightLine();
//                delay_ms(200);
//            }
//            if(j5==0)
//            {
//                stop();
//            }
//            if(j5<-126)
//            {
//                j5=-1;
//            }
//            stop();
//        }
//
//    }
    if(backflag == 5)               //表示是6号房间
       {
           if(j5<0)     //原j6=5
           {
           stop();
           }
           if(j5==5)
           {
               houtui();
               delay_ms(500);
               left();delay_ms(200);
           while(!((!D1)&D2&D3&(!D4))){left();}
           j5--;//再自减一 j6=4
           }
           //再直走
           else if(((!D1) & (!D2) & D3 & (!D4)) | ((!D1) & D2 & (!D3) & (!D4))|((!D1)&(D2)&(D3)&(!D4)             |(D1 & (!D2) & (!D3) & (!D4)) |((!D1) & (!D2) & (!D3) & D4))                      |(D1 & (!D2) & (!D3) & (!D4)) |((!D1) & (!D2) & (!D3) & D4))//|     ((!D1)&(!D2)&D3&D4)|((!D1)&D2&(!D3)&D4)|((!D1)&D2&D3&D4)|(D1&(!D2)&D3&(!D4))|(D1&(!D2)&D3&D4)|(D1&D2&(!D3)&(!D4))|(D1&D2&(!D3)&D4)|(D1&D2&D3&(!D4)))//中间两个红外扫到就行
           {
               //run();
               IR_StraightLine();
           }
           else if(D1 & D2 & D3 & D4  |((!D1) & D2 & D3 & (D4))            |((!D1) & (!D2) & (D3) & (D4))    )//++++++++++++++++++++++++++++++++++++++++++++++++++++++++

           {
               j5--;//遇见一次黑线就自减一  第一次遇见黑线 j6=3（左转）     第二次遇见黑线 j6=2  j6==1（直走）   j6=0(停)    第三次遇见黑线j6=1 (直走)     第四次遇见黑线 j6=0 (直走)  第五次遇见黑线 j6<0 (停止)
               if(j5==3)//|j6==2)
               {
                   right();delay_ms(200);//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                   while(!((!D1) & (D2) & (D3) &(!D4)) ){right();}
               }

   //            if(j6==2)
   //            {
   //                left();delay_ms(200);
   //                while(!((D1) & (!D2) & (!D3) &(!D4)) ){left();}
   //            }

               if(j5==2|j5==1)
               {
                   IR_StraightLine();
                   delay_ms(200);
               }
               if(j5==0)
               {
                   stop();
               }
               if(j5<-126)
               {
                   j5=-1;
               }

               stop();
           }

       }
    if(backflag == 6)               //表示是6号房间
    {
        if(j6<0)     //原j6=5
        {
        stop();
        }
        if(j6==5)
        {
            houtui();
            delay_ms(300);
            right();delay_ms(200);
        while(!((!D1)&D2&D3&(!D4))){right();}
        j6--;//再自减一 j6=4
        }
        //再直走
        else if(((!D1) & (!D2) & D3 & (!D4)) | ((!D1) & D2 & (!D3) & (!D4))|((!D1)&(D2)&(D3)&(!D4)             |(D1 & (!D2) & (!D3) & (!D4)) |((!D1) & (!D2) & (!D3) & D4))                      |(D1 & (!D2) & (!D3) & (!D4)) |((!D1) & (!D2) & (!D3) & D4))//|     ((!D1)&(!D2)&D3&D4)|((!D1)&D2&(!D3)&D4)|((!D1)&D2&D3&D4)|(D1&(!D2)&D3&(!D4))|(D1&(!D2)&D3&D4)|(D1&D2&(!D3)&(!D4))|(D1&D2&(!D3)&D4)|(D1&D2&D3&(!D4)))//中间两个红外扫到就行
        {
            //run();
            IR_StraightLine();
        }
        else if(D1 & D2 & D3 & D4  |((D1) & D2 & D3 & (!D4))            |((D1) & (D2) & (!D3) & (!D4))    )//++++++++++++++++++++++++++++++++++++++++++++++++++++++++

        {
            j6--;//遇见一次黑线就自减一  第一次遇见黑线 j6=3（左转）     第二次遇见黑线 j6=2  j6==1（直走）   j6=0(停)    第三次遇见黑线j6=1 (直走)     第四次遇见黑线 j6=0 (直走)  第五次遇见黑线 j6<0 (停止)
            if(j6==3)//|j6==2)
            {
                left();delay_ms(200);//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                while(!((!D1) & (D2) & (D3) &(!D4)) ){left();}
            }

//            if(j6==2)
//            {
//                left();delay_ms(200);
//                while(!((D1) & (!D2) & (!D3) &(!D4)) ){left();}
//            }

            if(j6==2|j6==1)
            {
                IR_StraightLine();
                delay_ms(200);
            }
            if(j6==0)
            {
                stop();
            }
            if(j6<-126)
            {
                j6=-1;
            }

            stop();
        }

    }

    if(backflag == 7)               //表示是7号房间
    {
        if(j7<0)     //原j7=5
        {
        stop();
        }
        if(j7==5)
        {
            //先掉头
        while(!((!D1)&(!D2)&(!D3)&(D4))){right();}
        //left();delay_ms(100);
        j7--;//再自减一 j7=4
        }
        //再直走
        else if(((!D1) & (!D2) & D3 & (!D4)) | ((!D1) & D2 & (!D3) & (!D4))|((!D1)&(D2)&(D3)&(!D4)                 |(D1 & (!D2) & (!D3) & (!D4)) |((!D1) & (!D2) & (!D3) & D4))                     |(D1 & (!D2) & (!D3) & (!D4)) |((!D1) & (!D2) & (!D3) & D4))//|     ((!D1)&(!D2)&D3&D4)|((!D1)&D2&(!D3)&D4)|((!D1)&D2&D3&D4)|(D1&(!D2)&D3&(!D4))|(D1&(!D2)&D3&D4)|(D1&D2&(!D3)&(!D4))|(D1&D2&(!D3)&D4)|(D1&D2&D3&(!D4)))//中间两个红外扫到就行
        {
            //run();
            IR_StraightLine();
        }
        else if(D1 & D2 & D3 & D4          |(D1 & D2 & D3 &(!D4)) |((!D1)& D2 & D3 &  D4 )                      |((D1)&(D2)&(!D3)&(!D4))|((!D1)&(!D2)&(D3)&(D4))              )//+++++++++++++++++++++++++++++++++++++++++++
        {
            j7--;//遇见一次黑线就自减一  第一次遇见黑线 j7=3（左转）     第二次遇见黑线 j7=2（右转）     第三次遇见黑线j7=1 (直走)     第四次遇见黑线 j7=0 (直走)  第五次遇见黑线 j7<0 (停止)
            if(j7==3)
            {
                left();delay_ms(200);//+++++++++++++++++++++++++++++++++++++++++++
                while(!((D1) & (!D2) & (!D3) &(!D4)) ){left();}
            }
            if(j7==2)
            {
                right();delay_ms(150);//+++++++++++++++++++++++++++++++++++++++++++
                while(!((!D1) & (!D2) & (!D3) &(D4)) ){right();}
            }
            if(j7==1|j7==0)
            {
                IR_StraightLine();
                delay_ms(200);
            }
            if(j7<-126)
            {
                j7=-1;
            }
            stop();
        }

    }



    if(backflag == 8)               //表示是8号房间
    {
        if(j8<0)     //原j8=5
        {
        stop();
        }
            if(j8==5)
        {
            //先掉头
        while(!((D1)&(!D2)&(!D3)&(!D4))){left();}
       // right();delay_ms(100);
        j8--;//再自减一 j8=4
        }
        //再直走
        else if(((!D1) & (!D2) & D3 & (!D4)) | ((!D1) & D2 & (!D3) & (!D4))|((!D1)&(D2)&(D3)&(!D4)           |(D1 & (!D2) & (!D3) & (!D4)) |((!D1) & (!D2) & (!D3) & D4))                     |(D1 & (!D2) & (!D3) & (!D4)) |((!D1) & (!D2) & (!D3) & D4))//|     ((!D1)&(!D2)&D3&D4)|((!D1)&D2&(!D3)&D4)|((!D1)&D2&D3&D4)|(D1&(!D2)&D3&(!D4))|(D1&(!D2)&D3&D4)|(D1&D2&(!D3)&(!D4))|(D1&D2&(!D3)&D4)|(D1&D2&D3&(!D4)))//中间两个红外扫到就行
        {
            //run();
            IR_StraightLine();
        }
        else if(D1 & D2 & D3 & D4                   |((!D1)&(D2)&(D3)&(D4)) |((D1)&(D2)&(D3)&(!D4))         |((D1)&(D2)&(!D3)&(!D4)) |((!D1)&(!D2)&(D3)&(D4))   )//+++++++++++++++++++++++++++++++++++++
        {
            j8--;//遇见一次黑线就自减一  第一次遇见黑线 j8=3（右转）     第二次遇见黑线 j8=2（左转）     第三次遇见黑线j8=1 (直走)     第四次遇见黑线 j8=0 (直走)  第五次遇见黑线 j8<0 (停止)
            if(j8==3)
            {
                right();delay_ms(200);//+++++++++++++++++++++++++++++++++++++++++++
                while(!((!D1) & (!D2) & (!D3) &(D4)) ){right();}
            }
            if(j8==2)
            {
                left();delay_ms(200);//+++++++++++++++++++++++++++++++++++++++++++
                while(!((D1) & (!D2) & (!D3) &(!D4)) ){left();}
            }
            if(j8==1|j8==0)
            {
                IR_StraightLine();
               // run();
                delay_ms(200);
            }
            if(j8<-126)
            {
                j8=-1;
            }
            stop();
        }

    }



}



