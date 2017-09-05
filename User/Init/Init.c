/*************************************************************************
#   Copyright (C) 2017 Qw//krom Ltd. All rights reserved.
#      Filename: Init.c
#
#        Author: Francis· Chuh
#   Description: ---
#        Create: 2017-08-03 11:13:47
# Last Modified: 2017-08-03 11:13:47
*************************************************************************/

#include "include.h"

void IO_Init(void)
{

//************************** comment start ******************************
//  Initialize the GPIO of LCD
//************************** comment end   ******************************
//    GPIO_Init(GPIOA, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Fast);    // COM0
//    GPIO_Init(GPIOA, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Fast);    // COM1
//    GPIO_Init(GPIOA, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Fast);    // COM2
//    GPIO_Init(GPIOD, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Fast);    // COM3
//    GPIO_Init(GPIOA, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Fast);    // SEG0
//    GPIO_Init(GPIOE, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Fast);    // SEG1
//    GPIO_Init(GPIOE, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Fast);    // SEG2
//    GPIO_Init(GPIOE, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Fast);    // SEG3
//    GPIO_Init(GPIOE, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Fast);    // SEG4
//    GPIO_Init(GPIOE, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Fast);    // SEG5
//    GPIO_Init(GPIOE, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Fast);    // SEG6
//    GPIO_Init(GPIOD, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Fast);    // SEG7
//    GPIO_Init(GPIOD, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Fast);    // SEG8
//    GPIO_Init(GPIOD, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Fast);    // SEG9
//    GPIO_Init(GPIOB, GPIO_Pin_0, GPIO_Mode_Out_PP_Low_Fast);    // SEG10
//    GPIO_Init(GPIOB, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Fast);    // SEG11
//    GPIO_Init(GPIOB, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Fast);    // SEG12
//    GPIO_Init(GPIOB, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Fast);    // SEG13
//    GPIO_Init(GPIOB, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Fast);    // SEG14
//    GPIO_Init(GPIOB, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Fast);    // SEG15
//    GPIO_Init(GPIOB, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Fast);    // SEG16
//    GPIO_Init(GPIOB, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Fast);    // SEG17

//************************** comment start ******************************
//  Initialize the GPIO of LED
//************************** comment end   ******************************
    GPIO_Init(GPIOF, GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Fast);
    Led_Off();
    
//************************** comment start ******************************
//  Initialize the GPIO of BEEP
//************************** comment end   ******************************
    GPIO_Init(GPIOE, GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Fast);
    GPIO_SetBits(GPIOE, GPIO_Pin_7);    //beep off
    
//************************** comment start ******************************
//  Initialize the GPIO of IC_Card
//************************** comment end   ******************************
    GPIO_Init(GPIOF, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Fast);    //IC_POW
    GPIO_Init(GPIOG, GPIO_Pin_1, GPIO_Mode_Out_PP_Low_Fast);    //IC_RST
    GPIO_Init(GPIOC, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Fast);    //IC_SCL
    GPIO_Init(GPIOG, GPIO_Pin_3, GPIO_Mode_Out_PP_Low_Fast);    //IC_SDA
    GPIO_Init(GPIOA, GPIO_Pin_2, GPIO_Mode_Out_PP_Low_Fast);    //IC_STA

//************************** comment start ******************************
//  Initialize the GPIO of KEY
//************************** comment end   ******************************    
    GPIO_Init(GPIOD, GPIO_Pin_6, GPIO_Mode_In_PU_No_IT);
    
//************************** comment start ******************************
//  Initialize the GPIO of GPRS_EN,GPRS_PWR
//************************** comment end   ****************************** 
    GPIO_Init(GPIOG, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Fast);//GPRS_EN
    GPIO_Init(GPIOG, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Fast);//GPRS_PWR
}

/***********************************************************
SYS_CLK_Init
系统时钟初始化函数
**********************************************************/
void SYS_CLK_Init(void)
{
    CLK_DeInit();
    
    CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);
//  CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_LSE);
    CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_4);

    while (CLK_GetSYSCLKSource() != CLK_SYSCLKSource_HSI);
      /*Enable DMA clock */
//    CLK_PeripheralClockConfig(CLK_Peripheral_DMA1, ENABLE);
}

/***********************************************************
SerialInit
串口初始化函数
**********************************************************/
void SerialInit(void)
{
    USART_DeInit(USART1);
	
    CLK_PeripheralClockConfig(CLK_Peripheral_USART1, ENABLE);

    GPIO_ExternalPullUpConfig(GPIOC, GPIO_Pin_2, ENABLE);
    GPIO_ExternalPullUpConfig(GPIOC, GPIO_Pin_3, ENABLE);
	
    USART_Init(USART1, 19200, USART_WordLength_8b, 
               USART_StopBits_1, USART_Parity_No, 
               (USART_Mode_TypeDef)(USART_Mode_Tx | USART_Mode_Rx));
    

  /* Enable general interrupts */
  //enableInterrupts();

  //允许接收，发送，开接收中断
  USART1->CR2=0x2c;
  
  /* Enable USART */
  USART_Cmd(USART1, ENABLE);
    
}

void DMA_Config(void)
{
  /* Deinitialize DMA channels */
  DMA_GlobalDeInit();

  DMA_DeInit(DMA1_Channel1);

 
  /* DMA channel Tx of USART Configuration */
  DMA_Init(USART_DMA_CHANNEL_TX, (uint16_t)TxBuffer, (uint16_t)USART_DR_ADDRESS,
           DATA_TO_TRANSFER, DMA_DIR_MemoryToPeripheral, DMA_Mode_Normal,
           DMA_MemoryIncMode_Inc, DMA_Priority_High, DMA_MemoryDataSize_Byte);

  /* Enable the USART Tx/Rx DMA requests */
  USART_DMACmd(USART1, USART_DMAReq_TX, ENABLE);
 
  /* Global DMA Enable */
  DMA_GlobalCmd(ENABLE);

  /* Enable the USART Tx DMA channel */
  DMA_Cmd(USART_DMA_CHANNEL_TX, ENABLE);
         
}
