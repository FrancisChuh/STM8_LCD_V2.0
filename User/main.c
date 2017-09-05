/*************************************************************************
#   Copyright (C) 2017 Qw//krom Ltd. All rights reserved.
#      Filename: main.c
#
#        Author: Francis· Chuh
#   Description: ---
#        Create: 2017-07-31 09:03:55
# Last Modified: 2017-07-31 09:03:55
*************************************************************************/

	
/* Includes ------------------------------------------------------------------*/
#include "include.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void Delay(uint16_t nCount);
void Delay_1ms(unsigned int count);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */



void main(void)
{
    SYS_CLK_Init();
    IO_Init();
    
    GPRS_ReStart();
            
    SerialInit();
    //DMA_Config();
    LCD_GLASS_Init();
    LCD_Display_All();
    LCD_GLASS_Clear();
    display_TEST();
    rim();

    //while (DMA_GetFlagStatus((DMA_FLAG_TypeDef)USART_DMA_FLAG_TCTX) == RESET);
    //UART1_SendBuffer("GPRS_TEST\r\n");
    while (1)
     {     
        KeyRead();
        KeyProc();
        GPRS_TEST();
        Delay_1ms(20);
        //UART1_SendBuffer("at\r\n");
      //p=strstr(USART_RX_BUF, "+SIMIND: 1");
      //while(strstr(USART_RX_BUF, "+SIMIND: 1"))
      //display_Good();

        
     }
}

/* Private functions ---------------------------------------------------------*/
void Delay(__IO uint16_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}

void Delay_1ms(unsigned int count)
{
    unsigned int i;
    for(;count!=0;count--)
    {   
        IWDG_ReloadCounter();               //喂狗操作
        for(i=0;i!=400;i++)
        {
            nop();
            nop();
            nop();
            nop();
            nop();
        }
    }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}

#endif

/**
  * @}
  */

/************************ (C) COPYRIGHT 2017 Qw//krom Ltd. *****END OF FILE****/
