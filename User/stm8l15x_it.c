/**
  ******************************************************************************
  * @file    Project/STM8L15x_StdPeriph_Template/stm8l15x_it.c
  * @author  MCD Application Team
  * @version V1.6.0
  * @date    28-June-2013
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all peripherals interrupt service routine.
  ******************************************************************************
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x_it.h"
#include "string.h"
/** @addtogroup STM8L15x_StdPeriph_Template
  * @{
  */
	
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
    uint8_t TxBuffer[];
    uint8_t TxCounter = 0;
    
    uint8_t* UartSendBuffer = 0;
    uint8_t  UartSendDataLength = 0;
    
    u16 USART_RX_STA=0;//接收状态标记
    u8 USART_RX_BUF[USART_REC_LEN];//接收缓冲，最大USART_REC_LEN字节
    u8 USART_RX_BUF0[USART_REC_NUM][USART_REC_LEN];
    unsigned int num_rx=0;//GPRS返回数据第num_rx+1个数据
    
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

#ifdef _COSMIC_
/**
  * @brief Dummy interrupt routine
  * @par Parameters:
  * None
  * @retval 
  * None
*/
INTERRUPT_HANDLER(NonHandledInterrupt,0)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}
#endif

/**
  * @brief TRAP interrupt routine
  * @par Parameters:
  * None
  * @retval 
  * None
*/
INTERRUPT_HANDLER_TRAP(TRAP_IRQHandler)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}
/**
  * @brief FLASH Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(FLASH_IRQHandler,1)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}
/**
  * @brief DMA1 channel0 and channel1 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(DMA1_CHANNEL0_1_IRQHandler,2)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}
/**
  * @brief DMA1 channel2 and channel3 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(DMA1_CHANNEL2_3_IRQHandler,3)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}
/**
  * @brief RTC / CSS_LSE Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(RTC_CSSLSE_IRQHandler,4)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}
/**
  * @brief External IT PORTE/F and PVD Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTIE_F_PVD_IRQHandler,5)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}

/**
  * @brief External IT PORTB / PORTG Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTIB_G_IRQHandler,6)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}

/**
  * @brief External IT PORTD /PORTH Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTID_H_IRQHandler,7)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}

/**
  * @brief External IT PIN0 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI0_IRQHandler,8)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);  
}

/**
  * @brief External IT PIN1 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI1_IRQHandler,9)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}

/**
  * @brief External IT PIN2 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI2_IRQHandler,10)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}

/**
  * @brief External IT PIN3 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI3_IRQHandler,11)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}

/**
  * @brief External IT PIN4 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI4_IRQHandler,12)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}

/**
  * @brief External IT PIN5 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI5_IRQHandler,13)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}

/**
  * @brief External IT PIN6 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI6_IRQHandler,14)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}

/**
  * @brief External IT PIN7 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI7_IRQHandler,15)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}
/**
  * @brief LCD /AES Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(LCD_AES_IRQHandler,16)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}
/**
  * @brief CLK switch/CSS/TIM1 break Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(SWITCH_CSS_BREAK_DAC_IRQHandler,17)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}

/**
  * @brief ADC1/Comparator Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(ADC1_COMP_IRQHandler,18)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}

/**
  * @brief TIM2 Update/Overflow/Trigger/Break /USART2 TX Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM2_UPD_OVF_TRG_BRK_USART2_TX_IRQHandler,19)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}

/**
  * @brief Timer2 Capture/Compare / USART2 RX Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM2_CC_USART2_RX_IRQHandler,20)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}


/**
  * @brief Timer3 Update/Overflow/Trigger/Break Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM3_UPD_OVF_TRG_BRK_USART3_TX_IRQHandler,21)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}
/**
  * @brief Timer3 Capture/Compare /USART3 RX Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM3_CC_USART3_RX_IRQHandler,22)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}
/**
  * @brief TIM1 Update/Overflow/Trigger/Commutation Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM1_UPD_OVF_TRG_COM_IRQHandler,23)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}
/**
  * @brief TIM1 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM1_CC_IRQHandler,24)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}

/**
  * @brief TIM4 Update/Overflow/Trigger Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM4_UPD_OVF_TRG_IRQHandler,25)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}
/**
  * @brief SPI1 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(SPI1_IRQHandler,26)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}

/**
  * @brief USART1 TX / TIM5 Update/Overflow/Trigger/Break Interrupt  routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(USART1_TX_TIM5_UPD_OVF_TRG_BRK_IRQHandler,27)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
  u8 status=USART1->SR;
  if(status & (1<<7)){
    if(UartSendDataLength!=0){
      USART1->DR=*UartSendBuffer;
      UartSendBuffer++;
      UartSendDataLength--;
    }else{
      USART1->CR2&=~(1<<7);
    }
  }
}

/**
  * @brief USART1 RX / Timer5 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
//u8 num_0d=0;
INTERRUPT_HANDLER(USART1_RX_TIM5_CC_IRQHandler,28)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */

      uint8_t  Res;
//      //uint8_t  even_0d = 0;
//
////    /* Read one byte from the receive data register and send it back */
////    Res = (USART_ReceiveData8(USART1));
////    if(Res == 0x31)UART1_SendBuffer("ok\r\n");
//
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  
//	{
//            Res =USART_ReceiveData8(USART1);	
//            if(USART_RX_STA&0xC000)
//            {	
//
//                memcpy(USART_RX_BUF0[num_rx],USART_RX_BUF,USART_RX_STA&0X3FFF);
//                //for(int i=0; i<((USART_RX_STA&0X3FFF)+1); i++)
//                //USART_RX_BUF [i] = 0;
//                num_rx ++ ;
//                if(num_rx<3)
//                USART_RX_STA = 0;
//		if((USART_RX_STA&0x8000)==0)
//                {
//			if(USART_RX_STA&0x4000)
//			{
//				if(Res!=0x0a)
//                                { 
//                                  USART_RX_STA=0;
//                                }
//				else 
//                                  {
//                                    USART_RX_STA|=0x8000;
//                                    num_0d = 0;
//                                    //even_0d = 1;
//                                  }
//				}
//			else 
//			{					
//                                  if((Res==0x0d)&&(num_0d==1))
//                                    USART_RX_STA|=0x4000;
//				  else
//				  {
//					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
//                                        USART_RX_STA++;
//                                        if((Res==0x0d)&&(num_0d==0))
//                                          num_0d = 1;
//                                        //if(even_0d==0) num_0d = 0;
//					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;	  
//				  }		 
//			}
//		}
//
//            }
//            if((USART_RX_STA&0x8000)==0)
//	    {
//			if(USART_RX_STA&0x4000)
//		        {
//				if(Res!=0x0a)
//                                { 
//                                  USART_RX_STA=0;
//                                }
//				else 
//                                {
//                                    USART_RX_STA|=0x8000;
//                                    num_0d = 0;
//                                }
//			}
//			else 
//                        {					
//                                  if((Res==0x0d)&&(num_0d==1))
//                                    USART_RX_STA|=0x4000;
//				  else
//				  {
//					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
//                                        USART_RX_STA++;
//                                        if((Res==0x0d)&&(num_0d==0))
//                                          num_0d = 1;
//					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;	  
//				  }		 
//			}
//	    }
//        }
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
		{
		Res =USART_ReceiveData8(USART1);
//            if((USART_RX_STA&0xC000)||((USART_RX_STA&0x8000)==0))
//            {	
//
//                memcpy(USART_RX_BUF0[num_rx],USART_RX_BUF,USART_RX_STA&0X3FFF);
//                //for(int i=0; i<((USART_RX_STA&0X3FFF)+1); i++)
//                //USART_RX_BUF [i] = 0;
//                num_rx ++ ;
//                if(num_rx<3)
//                USART_RX_STA = 0;
		if((USART_RX_STA&0x8000)==0)
			{
			if(USART_RX_STA&0x4000)
				{
				if(Res!=0x0a)USART_RX_STA=0;
				else USART_RX_STA|=0x8000;
				}
			else 
				{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
					{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;	  
					}		 
				}
                        if((USART_RX_STA&0x8000))
                                {	

                                    memcpy(USART_RX_BUF0[num_rx],USART_RX_BUF,USART_RX_STA&0X3FFF);
                                    //for(int i=0; i<((USART_RX_STA&0X3FFF)+1); i++)
                                    //USART_RX_BUF [i] = 0;
                                    num_rx ++ ;
                //                    if(num_rx<3)
                //                    USART_RX_STA = 0;
                                }
			}
                 else if((USART_RX_STA&0x8000))
			{
                        USART_RX_STA=0;
			if(USART_RX_STA&0x4000)
				{
				if(Res!=0x0a)USART_RX_STA=0;
				else USART_RX_STA|=0x8000;
				}
			else 
				{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
					{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;	  
					}		 
				}
                        if((USART_RX_STA&0x8000))
                                {	

                                    memcpy(USART_RX_BUF0[num_rx],USART_RX_BUF,USART_RX_STA&0X3FFF);
                                    //for(int i=0; i<((USART_RX_STA&0X3FFF)+1); i++)
                                    //USART_RX_BUF [i] = 0;
                                    num_rx ++ ;
                //                    if(num_rx<3)
                //                    USART_RX_STA = 0;
                                }
			}
     }           
        
}

/**
  * @brief I2C1 / SPI2 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(I2C1_SPI2_IRQHandler,29)
{
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
    while(1);
}
/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
void UART1_SendBuffer(uint8_t* buffer){
  UartSendBuffer=buffer;
  UartSendDataLength=strlen((const char*)buffer);
  USART1->CR2|=(1<<7);
}
