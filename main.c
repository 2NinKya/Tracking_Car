#include "driverlib.h"
#include "sys.h"
#include "car.h"
#include "usart.h"
#include "delay.h"
#include "IR.h"
#include "back.h"
#include "Mode.h"
#include "KeyMode.h"
#include "WIFI_Slave.h"
#include "oled.h"
#include "HCSR04.h"
#include "PID.h"

extern uint8_t buf[];

extern int M1,M2,M3,M4,M5;
extern uint8_t receivedData;
uint8_t Temp;

#define D1      GPIO_getInputPinValue(GPIO_PORT_P1,GPIO_PIN6)
#define D2      GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN2)
#define D3      GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN0)
#define D4      GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN1)
#define D5      GPIO_getInputPinValue(GPIO_PORT_P6,GPIO_PIN3)


extern uint8_t Temp;

int main(void)
{
    WDT_A_hold(WDT_A_BASE);

    SystemClock_Init();
//    GPIO_setAsOutputPin(GPIO_PORT_P1,GPIO_PIN0);

   UART_Init(USCI_A1_BASE,9600);         //初始化UART_A1
//    UART_Init(USCI_A0_BASE,115200);         //初始化UART_A0

    Car_Init();
    HCSR04_Init();
    Mode_Init();

    OLED_Init();
    OLED_Clear();
    OLED_Display_On();

    IR_Init();

//    WIFI_Slave();                                                   //开启从车WIFI
//    OLED_ShowString(0,0,"Distance:",15);
//    OLED_ShowString(0,2,"PID:",15);







    __bis_SR_register(GIE);

    while(1)
    {

        OLED_ShowNum(0,4,PID(),3,15);
        OLED_ShowNum(72,4,HCSR04_GetDistance(),3,15);
        OLED_ShowNum(0,6,receivedData,3,15);
//        Temp = receivedData;
        if(receivedData == 48)
        {
            OLED_ShowString(40,0,"Link On",15);
            Mode(0);
        }
        if(receivedData == 49)                  //1
        {
            OLED_ShowString(40,0,"One",15);
            Mode(1);
        }
        if(receivedData == 50)              //2
        {
            OLED_ShowString(40,0,"Two",15);
            Mode(3);
        }
        if(receivedData == 51)                      //3
        {
            OLED_ShowString(40,0,"Three",15);
            Mode(4);
        }
        if(receivedData == 52)
        {
            OLED_ShowString(40,0,"Four",15);
            Mode(5);
        }

//        left();

        if(receivedData == 53)
        {
            Mode(0);
        }



//        OLED_ShowNum(80,0,HCSR04_GetDistance(),3,15);
//               if(PID() < 0)
//               {
//                   OLED_ShowString(40,2,"-",15);
//                   OLED_ShowNum(48,2,PID(),2,15);
//               }
//               else
//               {
//                   OLED_ShowString(40,2,"+",15);
//                   OLED_ShowNum(48,2,PID(),2,15);
//               }
//
//             // Mode(1);
//                   //run();

    }
}


//#pragma vector=PORT2_VECTOR     // P2口中断源
//__interrupt
//void Port_2 (void)              // 声明一个中断服务程序，名为Port_2()
//{
//    //uint8_t temp,backflag;
//    if(GPIO_getInterruptStatus(GPIO_PORT_P2, GPIO_PIN1))
//    {
//       // temp=IR_StraightLine(void); //  temp等于函数IR_Room返回的值   这里函数数IR_Room的参数Number是摄像头读取到的字模
//       // backflag=temp;        //再把temp的值赋给函数Back，做回程   再在主函数里面调用函数Back(backflag);
////       i=Number;
////       Number=0;
//  //      k=4;
//        //i=room;
//  //      room=0;
//        GPIO_clearInterrupt(GPIO_PORT_P2, GPIO_PIN1);
//    }
//}

