#include <usart.h>
#include "OLED.h"
#include "driverlib.h"
void UART_printf(uint16_t baseAddress, const char *format,...)
{
    uint32_t length;
    va_list args;
    uint32_t i;
    char TxBuffer[128] = {0};

    va_start(args, format);
    length = vsnprintf((char*)TxBuffer, sizeof(TxBuffer)+1, (char*)format, args);
    va_end(args);

    for(i = 0; i < length; i++)
        USCI_A_UART_transmitData(baseAddress, TxBuffer[i]);
}

bool UART_Init(uint16_t baseAddress, uint32_t Baudrate)
{
    float UART_Temp = 0;
    USCI_A_UART_initParam huart = {0};

    if(baseAddress == USCI_A0_BASE)                      //P3.3, P3.4 = USCI_A0 TXD/RXD
    {
        GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P3, GPIO_PIN3);
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3, GPIO_PIN4);
    }
    else if(baseAddress == USCI_A1_BASE)    //P4.4, P4.5 = USCI_A1 TXD/RXD
    {
        GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P4, GPIO_PIN4);
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN5);
    }

    if(Baudrate <= 9600)
    {
        huart.selectClockSource = USCI_A_UART_CLOCKSOURCE_ACLK;
        UART_Temp = (float)UCS_getACLK()/Baudrate;
    }
    else
    {
        huart.selectClockSource = USCI_A_UART_CLOCKSOURCE_SMCLK;
        UART_Temp = (float)UCS_getSMCLK()/Baudrate;
    }

    if(UART_Temp < 16)
        huart.overSampling = USCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;
    else
    {
        huart.overSampling = USCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION;
        UART_Temp /= 16;
    }

    huart.clockPrescalar = (int)UART_Temp;

    if(huart.overSampling == USCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION)
    {
        huart.secondModReg = (int)((UART_Temp - huart.clockPrescalar) * 8);
    }
    else
    {
        huart.firstModReg = (int)((UART_Temp - huart.clockPrescalar) * 16);
    }

    huart.parity = USCI_A_UART_NO_PARITY;
    huart.msborLsbFirst = USCI_A_UART_LSB_FIRST;
    huart.numberofStopBits = USCI_A_UART_ONE_STOP_BIT;
    huart.uartMode = USCI_A_UART_MODE;

    if (STATUS_FAIL == USCI_A_UART_init(baseAddress, &huart))
    {
        return STATUS_FAIL;
    }


    USCI_A_UART_enable(baseAddress);


    USCI_A_UART_clearInterrupt(baseAddress, USCI_A_UART_RECEIVE_INTERRUPT);
    USCI_A_UART_enableInterrupt(baseAddress, USCI_A_UART_RECEIVE_INTERRUPT);

    return STATUS_SUCCESS;
}


//uint8_t Temp;
//uint8_t receivedData;
//uint8_t buf[];                                                               //buf[4]是接收到的数据
//uint16_t i,j = 0;
//extern uint8_t Status;
//#pragma vector=USCI_A0_VECTOR
//__interrupt void USCI_A0_ISR (void)
//{
//
//    switch (__even_in_range(UCA0IV,4))
//    {
//        case 2:
//            if(Status == 1)                                                         //每次接收到WIFI的数据都进入中断,但是忽略了AT指令的响应
//            {
//                receivedData = USCI_A_UART_receiveData(USCI_A0_BASE);               //接收WIFI通过串口发送的CIP数据
//                buf[i] = receivedData;                                            //CIP数据依次保存在buf数组中
//                i++;
////                if(i == 10)
////                {
////                    i = 0;
////                }
//            }
//            break;
//        default:
//            break;
//    }
//}


uint8_t receivedData;
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR (void)
{
    switch (__even_in_range(UCA1IV,4))
    {
        case 2:
                 receivedData = USCI_A_UART_receiveData(USCI_A1_BASE);

//                 if(receivedData == 49)
//                 {
////                     OLED_ShowString(0,4,"OK",15);
//                 }
//                 UART_printf(USCI_A1_BASE,"%d",receivedData);
//            if( receivedData==49)
//            {
//                     GPIO_setOutputHighOnPin(GPIO_PORT_P1,GPIO_PIN0);
//            }
//            if( receivedData==50)
//                       {
//                    GPIO_setOutputLowOnPin(GPIO_PORT_P1,GPIO_PIN0);
//                       }
            break;
        default:
            break;
    }
}
