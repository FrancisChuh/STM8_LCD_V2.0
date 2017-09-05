/**
  ******************************************************************************
  * @file    Simple Meter LCD.c
  * @author  TOMEN Alfred
  * @version V1.0
  * @date    12/2012
  * @brief   This file includes driver for the glass LCD Module mounted on 
  *          STM8L152R8 & STM8L052R8 Simple Meter board.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2013 TOMEN Electronics(SZ) Ltd. </center></h2>
  */ 
#include "stm8l15x_lcd.h"
#include "LCD.h"


void LCD_GLASS_Init(void)
{
// Enable LCD/RTC clock 
  CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);
  CLK_PeripheralClockConfig(CLK_Peripheral_LCD, ENABLE);
  
//  #ifdef USE_LSE
    CLK_RTCClockConfig(CLK_RTCCLKSource_LSE, CLK_RTCCLKDiv_1);
//  #else
//    CLK_RTCClockConfig(CLK_RTCCLKSource_LSI, CLK_RTCCLKDiv_1);
//  #endif
//  LCD->CR1 = 0XDE;
//  LCD->CR2 = 0X91;
//  LCD->FRQ = 0X30;
  // Initialize the LCD 
  LCD_Init(LCD_Prescaler_8, LCD_Divider_16, LCD_Duty_1_4, 
              LCD_Bias_1_3, LCD_VoltageSource_External);
  
  //Mask register
  //For declare the segements used.
  //in the Discovery we use 0 & (2 to 17) & 19 & 20 segments. 
  LCD_PortMaskConfig(LCD_PortMaskRegister_0, 0xFF);
  LCD_PortMaskConfig(LCD_PortMaskRegister_1, 0xFF);
  LCD_PortMaskConfig(LCD_PortMaskRegister_2, 0x03);
  
//  LCD_BlinkConfig(LCD_BlinkMode_AllSEG_AllCOM, LCD_BlinkFrequency_Div8);
//  LCD->CR2 |= 0X11;
  // To set contrast to mean value 
//  LCD_ContrastConfig(LCD_Contrast_Level_7);
  
  LCD_DeadTimeConfig(LCD_DeadTime_0);
  LCD_PulseOnDurationConfig(LCD_PulseOnDuration_1);
  
  // Enable LCD peripheral
  LCD_Cmd(ENABLE);  
}


 

/**
  * @brief  This function Clear the whole LCD RAM.
  * @param  None
  * @retval None
  */
void LCD_GLASS_Clear(void)
{
//  LCD->RAM[LCD_RAMRegister_0] = 0x00;
//  LCD->RAM[LCD_RAMRegister_1] = 0x00;
//  LCD->RAM[LCD_RAMRegister_2] = 0x00;
//
//  LCD->RAM[LCD_RAMRegister_3] = 0x00;
//  LCD->RAM[LCD_RAMRegister_4] = 0x00;
//  LCD->RAM[LCD_RAMRegister_5] = 0x00;
//
//  LCD->RAM[LCD_RAMRegister_7] = 0x00;
//  LCD->RAM[LCD_RAMRegister_8] = 0x00;
//  LCD->RAM[LCD_RAMRegister_9] &= 0x02;
//
//  LCD->RAM[LCD_RAMRegister_10] &= 0x40;
//  LCD->RAM[LCD_RAMRegister_11] &= 0x05;
//  LCD->RAM[LCD_RAMRegister_12] = 0x00;
  
  uint8_t counter = 0;
  for (counter = 0; counter <= LCD_RAMRegister_12; counter++)
  {
    LCD->RAM[counter] = LCD_RAM_RESET_VALUE;
  }
}


void LCD_Display_All(void)
{
  LCD->RAM[LCD_RAMRegister_0] = 0xff;
  LCD->RAM[LCD_RAMRegister_1] = 0xff;
  LCD->RAM[LCD_RAMRegister_2] = 0x03;

  LCD->RAM[LCD_RAMRegister_3] = 0xf0;
  LCD->RAM[LCD_RAMRegister_4] = 0xff;
  LCD->RAM[LCD_RAMRegister_5] = 0x3f;

  LCD->RAM[LCD_RAMRegister_7] = 0xff;
  LCD->RAM[LCD_RAMRegister_8] = 0xff;
  LCD->RAM[LCD_RAMRegister_9] = 0x03;

  LCD->RAM[LCD_RAMRegister_10] = 0xf0;
  LCD->RAM[LCD_RAMRegister_11] = 0xff;
  LCD->RAM[LCD_RAMRegister_12] = 0x3f;
}

void displayNumber(unsigned char Position, unsigned char Number)
{
	switch(Position){
	case 1:
		switch(Number)
                {
                    case 1:
                            B1 &= 0xfd;B1 |= 0x02;
                            C1 &= 0xdf;C1 |= 0x20;
                            break;
                    case 2:
                            A1 &= 0xdf;A1 |= 0x20;
                            B1 &= 0xfd;B1 |= 0x02;
                            G1 &= 0xbf;G1 |= 0x40;
                            E1 &= 0xfb;E1 |= 0x04;
                            D1 &= 0xfd;D1 |= 0x02;
                            break;
                    case 3:
                            A1 &= 0xdf;A1 |= 0x20;
                            B1 &= 0xfd;B1 |= 0x02;
                            G1 &= 0xbf;G1 |= 0x40;
                            C1 &= 0xdf;C1 |= 0x20;
                            D1 &= 0xfd;D1 |= 0x02;
                            break;
                    case 4:
                            F1 &= 0xfb;F1 |= 0x04;
                            G1 &= 0xbf;G1 |= 0x40;
                            B1 &= 0xfd;B1 |= 0x02;
                            C1 &= 0xdf;C1 |= 0x20;
                            break;
                    case 5:
                            A1 &= 0xdf;A1 |= 0x20;
                            C1 &= 0xdf;C1 |= 0x20;
                            D1 &= 0xfd;D1 |= 0x02;
                            F1 &= 0xfb;F1 |= 0x04;
                            G1 &= 0xbf;G1 |= 0x40;
                            break;
                    case 6:
                            A1 &= 0xdf;A1 |= 0x20;
                            C1 &= 0xdf;C1 |= 0x20;
                            D1 &= 0xfd;D1 |= 0x02;
                            E1 &= 0xfb;E1 |= 0x04;
                            F1 &= 0xfb;F1 |= 0x04;
                            G1 &= 0xbf;G1 |= 0x40;
                            break;
                    case 7:
                            A1 &= 0xdf;A1 |= 0x20;
                            B1 &= 0xfd;B1 |= 0x02;
                            C1 &= 0xdf;C1 |= 0x20;
                            break;
                    case 8:
                            A1 &= 0xdf;A1 |= 0x20;
                            B1 &= 0xfd;B1 |= 0x02;
                            C1 &= 0xdf;C1 |= 0x20;
                            D1 &= 0xfd;D1 |= 0x02;
                            E1 &= 0xfb;E1 |= 0x04;
                            F1 &= 0xfb;F1 |= 0x04;
                            G1 &= 0xbf;G1 |= 0x40;
                            break;
                    case 9:
                            A1 &= 0xdf;A1 |= 0x20;
                            B1 &= 0xfd;B1 |= 0x02;
                            C1 &= 0xdf;C1 |= 0x20;
                            D1 &= 0xfd;D1 |= 0x02;
                            F1 &= 0xfb;F1 |= 0x04;
                            G1 &= 0xbf;G1 |= 0x40;
                            break;
                    case 0:
                            A1 &= 0xdf;A1 |= 0x20;
                            B1 &= 0xfd;B1 |= 0x02;
                            C1 &= 0xdf;C1 |= 0x20;
                            D1 &= 0xfd;D1 |= 0x02;
                            E1 &= 0xfb;E1 |= 0x04;
                            F1 &= 0xfb;F1 |= 0x04;
                            break;
                    case 10:
                            G1 &= 0xbf;G1 |= 0x40;
			    break;
                    case 11:
                            A1 &= 0xdf;
                            B1 &= 0xfd;
                            C1 &= 0xdf;
                            D1 &= 0xfd;
                            E1 &= 0xfb;
                            F1 &= 0xfb;
                            G1 &= 0xbf;
                            break;
		}
		break;
	case 2:
		switch(Number)
                {
                    case 1:
                            B2 &= 0xf7;B2 |= 0x08;
                            C2 &= 0x7f;C2 |= 0x80;
                            break;
                    case 2:
                            A2 &= 0x7f;A2 |= 0x80;
                            B2 &= 0xf7;B2 |= 0x08;
                            D2 &= 0xf7;D2 |= 0x08;
                            E2 &= 0xef;E2 |= 0x10;
                            G2 &= 0xfe;G2 |= 0x01;
                            break;
                    case 3:
                            A2 &= 0x7f;A2 |= 0x80;
                            B2 &= 0xf7;B2 |= 0x08;
                            C2 &= 0x7f;C2 |= 0x80;
                            D2 &= 0xf7;D2 |= 0x08;
                            G2 &= 0xfe;G2 |= 0x01;
                            break;
                    case 4:
                            B2 &= 0xf7;B2 |= 0x08;
                            C2 &= 0x7f;C2 |= 0x80;
                            F2 &= 0xef;F2 |= 0x10;
                            G2 &= 0xfe;G2 |= 0x01;
                            break;
                    case 5:
                            A2 &= 0x7f;A2 |= 0x80;
                            C2 &= 0x7f;C2 |= 0x80;
                            D2 &= 0xf7;D2 |= 0x08;
                            F2 &= 0xef;F2 |= 0x10;
                            G2 &= 0xfe;G2 |= 0x01;
                            break;
                    case 6:
                            A2 &= 0x7f;A2 |= 0x80;
                            B2 &= 0xf7;C2 |= 0x80;
                            D2 &= 0xf7;D2 |= 0x08;
                            E2 &= 0xef;E2 |= 0x10;
                            F2 &= 0xef;F2 |= 0x10;
                            G2 &= 0xfe;G2 |= 0x01;
                            break;
                    case 7:
                            A2 &= 0x7f;A2 |= 0x80;
                            B2 &= 0xf7;B2 |= 0x08;
                            C2 &= 0x7f;C2 |= 0x80;
                            break;
                    case 8:
                            A2 &= 0x7f;A2 |= 0x80;
                            B2 &= 0xf7;B2 |= 0x08;
                            C2 &= 0x7f;C2 |= 0x80;
                            D2 &= 0xf7;D2 |= 0x08;
                            E2 &= 0xef;E2 |= 0x10;
                            F2 &= 0xef;F2 |= 0x10;
                            G2 &= 0xfe;G2 |= 0x01;
                            break;
                    case 9:
                            A2 &= 0x7f;A2 |= 0x80;
                            B2 &= 0xf7;B2 |= 0x08;
                            C2 &= 0x7f;C2 |= 0x80;
                            D2 &= 0xf7;D2 |= 0x08;
                            F2 &= 0xef;F2 |= 0x10;
                            G2 &= 0xfe;G2 |= 0x01;
                            break;
                    case 0:
                            A2 &= 0x7f;A2 |= 0x80;
                            B2 &= 0xf7;B2 |= 0x08;
                            C2 &= 0x7f;C2 |= 0x80;
                            D2 &= 0xf7;D2 |= 0x08;
                            E2 &= 0xef;E2 |= 0x10;
                            F2 &= 0xef;F2 |= 0x10;
                            break;
                    case 10:
                            G2 &= 0xfe;G2 |= 0x01;
			    break;
                    case 11:
                            A2 &= 0x7f;
                            B2 &= 0xf7;
                            C2 &= 0x7f;
                            D2 &= 0xf7;
                            E2 &= 0xef;
                            F2 &= 0xef;
                            G2 &= 0xfe;
                            break;
                    case 12: //H
                            B2 &= 0xf7;B2 |= 0x08;
                            C2 &= 0x7f;C2 |= 0x80;
                            E2 &= 0xef;E2 |= 0x10;
                            F2 &= 0xef;F2 |= 0x10;
                            G2 &= 0xfe;G2 |= 0x01;
                            break;
                    case 13://E
                            A2 &= 0x7f;A2 |= 0x80;
                            D2 &= 0xf7;D2 |= 0x08;
                            E2 &= 0xef;E2 |= 0x10;
                            F2 &= 0xef;F2 |= 0x10;
                            G2 &= 0xfe;G2 |= 0x01;
                            break;
		}
		break;
	case 3:
		switch(Number){
		case 1:
                        B3 &= 0xdf;B3 |= 0x20;
                        C3 &= 0xfd;C3 |= 0x02;
			break;
		case 2:
                        A3 &= 0xfd;A3 |= 0x02;
                        B3 &= 0xdf;B3 |= 0x20;
                        D3 &= 0xdf;D3 |= 0x20;
                        E3 &= 0xbf;E3 |= 0x40;
                        G3 &= 0xfb;G3 |= 0x04;
			break;
		case 3:
                        A3 &= 0xfd;A3 |= 0x02;
                        B3 &= 0xdf;B3 |= 0x20;
                        C3 &= 0xfd;C3 |= 0x02;
                        D3 &= 0xdf;D3 |= 0x20;
                        G3 &= 0xfb;G3 |= 0x04;
			break;
		case 4:
                        B3 &= 0xdf;B3 |= 0x20;
                        C3 &= 0xfd;C3 |= 0x02;
                        F3 &= 0xbf;F3 |= 0x40;
                        G3 &= 0xfb;G3 |= 0x04;
			break;
		case 5:
                        A3 &= 0xfd;A3 |= 0x02;
                        C3 &= 0xfd;C3 |= 0x02;
                        D3 &= 0xdf;D3 |= 0x20;
                        F3 &= 0xbf;F3 |= 0x40;
                        G3 &= 0xfb;G3 |= 0x04;
			break;
		case 6:
                        A3 &= 0xfd;A3 |= 0x02;
                        C3 &= 0xfd;C3 |= 0x02;
                        D3 &= 0xdf;D3 |= 0x20;
                        E3 &= 0xbf;E3 |= 0x40;
                        F3 &= 0xbf;F3 |= 0x40;
                        G3 &= 0xfb;G3 |= 0x04;
			break;
		case 7:
                        A3 &= 0xfd;A3 |= 0x02;
                        B3 &= 0xdf;B3 |= 0x20;
                        C3 &= 0xfd;C3 |= 0x02;
			break;
		case 8:
                        A3 &= 0xfd;A3 |= 0x02;
                        B3 &= 0xdf;B3 |= 0x20;
                        C3 &= 0xfd;C3 |= 0x02;
                        D3 &= 0xdf;D3 |= 0x20;
                        E3 &= 0xbf;E3 |= 0x40;
                        F3 &= 0xbf;F3 |= 0x40;
                        G3 &= 0xfb;G3 |= 0x04;
			break;
		case 9:
                        A3 &= 0xfd;A3 |= 0x02;
                        B3 &= 0xdf;B3 |= 0x20;
                        C3 &= 0xfd;C3 |= 0x02;
                        D3 &= 0xdf;D3 |= 0x20;
                        F3 &= 0xbf;F3 |= 0x40;
                        G3 &= 0xfb;G3 |= 0x04;
			break;
		case 0:
                        A3 &= 0xfd;A3 |= 0x02;
                        B3 &= 0xdf;B3 |= 0x20;
                        C3 &= 0xfd;C3 |= 0x02;
                        D3 &= 0xdf;D3 |= 0x20;
                        E3 &= 0xbf;E3 |= 0x40;
                        F3 &= 0xbf;F3 |= 0x40;
			break;
		case 10:               
                        G3 &= 0xfb;G3 |= 0x04;
			break;
                case 11:
                        A3 &= 0xfd;
                        B3 &= 0xdf;
                        C3 &= 0xfd;
                        D3 &= 0xdf;
                        E3 &= 0xbf;
                        F3 &= 0xbf;
                        G3 &= 0xfb;
			break;
                case 12://E
                        A3 &= 0xfd;A3 |= 0x02;
                        D3 &= 0xdf;D3 |= 0x20;
                        E3 &= 0xbf;E3 |= 0x40;
                        F3 &= 0xbf;F3 |= 0x40;
                        G3 &= 0xfb;G3 |= 0x04;
			break;        
                case 13://r                       
                        E3 &= 0xbf;E3 |= 0x40;
                        G3 &= 0xfb;G3 |= 0x04;
			break;    
		}
		break;
	case 4:
		switch(Number){
		case 1:
                        B4 &= 0x7f;B4 |= 0x80;
                        C4 &= 0xf7;C4 |= 0x08;
			break;
		case 2:
                        A4 &= 0xf7;A4 |= 0x08;
                        B4 &= 0x7f;B4 |= 0x80;
                        D4 &= 0x7f;D4 |= 0x80;
                        E4 &= 0xfe;E4 |= 0x01;
                        G4 &= 0xef;G4 |= 0x10;
			break;
		case 3:
                        A4 &= 0xf7;A4 |= 0x08;
                        B4 &= 0x7f;B4 |= 0x80;
                        C4 &= 0xf7;C4 |= 0x08;
                        D4 &= 0x7f;D4 |= 0x80;
                        G4 &= 0xef;G4 |= 0x10;
			break;
		case 4:
                        B4 &= 0x7f;B4 |= 0x80;
                        C4 &= 0xf7;C4 |= 0x08;
                        F4 &= 0xfe;F4 |= 0x01;
                        G4 &= 0xef;G4 |= 0x10;
			break;
		case 5:
                        A4 &= 0xf7;A4 |= 0x08;
                        C4 &= 0xf7;C4 |= 0x08;
                        D4 &= 0x7f;D4 |= 0x80;
                        F4 &= 0xfe;F4 |= 0x01;
                        G4 &= 0xef;G4 |= 0x10;
			break;
		case 6:
                        A4 &= 0xf7;A4 |= 0x08;
                        C4 &= 0xf7;C4 |= 0x08;
                        D4 &= 0x7f;D4 |= 0x80;
                        E4 &= 0xfe;E4 |= 0x01;
                        F4 &= 0xfe;F4 |= 0x01;
                        G4 &= 0xef;G4 |= 0x10;
			break;
		case 7:
                        A4 &= 0xf7;A4 |= 0x08;
                        B4 &= 0x7f;B4 |= 0x80;
                        C4 &= 0xf7;C4 |= 0x08;
			break;
		case 8:
			A4 &= 0xf7;A4 |= 0x08;
                        B4 &= 0x7f;B4 |= 0x80;
                        C4 &= 0xf7;C4 |= 0x08;
                        D4 &= 0x7f;D4 |= 0x80;
                        E4 &= 0xfe;E4 |= 0x01;
                        F4 &= 0xfe;F4 |= 0x01;
                        G4 &= 0xef;G4 |= 0x10;
			break;
		case 9:
                        A4 &= 0xf7;A4 |= 0x08;
                        B4 &= 0x7f;B4 |= 0x80;
                        C4 &= 0xf7;C4 |= 0x08;
                        D4 &= 0x7f;D4 |= 0x80;
                        F4 &= 0xfe;F4 |= 0x01;
                        G4 &= 0xef;G4 |= 0x10;
			break;
		case 0:
                        A4 &= 0xf7;A4 |= 0x08;
                        B4 &= 0x7f;B4 |= 0x80;
                        C4 &= 0xf7;C4 |= 0x08;
                        D4 &= 0x7f;D4 |= 0x80;
                        E4 &= 0xfe;E4 |= 0x01;
                        F4 &= 0xfe;F4 |= 0x01;
			break;
		case 10:
                        G4 &= 0xef;
                        G4 |= 0x10;
			 break;
                case 11:
			A4 &= 0xf7;
                        B4 &= 0x7f;
                        C4 &= 0xf7;
                        D4 &= 0x7f;
                        E4 &= 0xfe;
                        F4 &= 0xfe;
                        G4 &= 0xef;
			break;
                case 12://L			
                        D4 &= 0x7f;D4 |= 0x80;
                        E4 &= 0xfe;E4 |= 0x01;
                        F4 &= 0xfe;F4 |= 0x01;
			break;
                case 13://r                        
                        E4 &= 0xfe;E4 |= 0x01;
                        G4 &= 0xef;G4 |= 0x10;
                        break;
                case 14://E
                        A4 &= 0xf7;A4 |= 0x08;
                        E4 &= 0xfe;E4 |= 0x01;
                        D4 &= 0x7f;D4 |= 0x80;
                        F4 &= 0xfe;F4 |= 0x01;
                        G4 &= 0xef;G4 |= 0x10;
			break;
                case 15://o
                        C4 &= 0xf7;C4 |= 0x08;
                        D4 &= 0x7f;D4 |= 0x80;
                        E4 &= 0xfe;E4 |= 0x01;
                        G4 &= 0xef;G4 |= 0x10;
                        break;
		}
		break;
	case 5:
		switch(Number){
		case 1:
                        B5 &= 0xfd;B5 |= 0x02;
                        C5 &= 0xdf;C5 |= 0x20;
			break;
		case 2:
                        A5 &= 0xdf;A5 |= 0x20;
                        B5 &= 0xfd;B5 |= 0x02;
                        D5 &= 0xfd;D5 |= 0x02;
                        E5 &= 0xfb;E5 |= 0x04;
                        G5 &= 0xbf;G5 |= 0x40;
			break;
		case 3:
                        A5 &= 0xdf;A5 |= 0x20;
                        B5 &= 0xfd;B5 |= 0x02;
                        C5 &= 0xdf;C5 |= 0x20;
                        D5 &= 0xfd;D5 |= 0x02;
                        G5 &= 0xbf;G5 |= 0x40;
			break;
		case 4:
                        B5 &= 0xfd;B5 |= 0x02;
                        C5 &= 0xdf;C5 |= 0x20;
                        F5 &= 0xfb;F5 |= 0x04;
                        G5 &= 0xbf;G5 |= 0x40;
			break;
		case 5:
                        A5 &= 0xdf;A5 |= 0x20;
                        C5 &= 0xdf;C5 |= 0x20;
                        D5 &= 0xfd;D5 |= 0x02;
                        F5 &= 0xfb;F5 |= 0x04;
                        G5 &= 0xbf;G5 |= 0x40;
			break;
		case 6:
                        A5 &= 0xdf;A5 |= 0x20;
                        C5 &= 0xdf;C5 |= 0x20;
                        D5 &= 0xfd;D5 |= 0x02;
                        E5 &= 0xfb;E5 |= 0x04;
                        F5 &= 0xfb;F5 |= 0x04;
                        G5 &= 0xbf;G5 |= 0x40;
			break;
		case 7:
                        A5 &= 0xdf;A5 |= 0x20;
                        B5 &= 0xfd;B5 |= 0x02;
                        C5 &= 0xdf;C5 |= 0x20;
			break;
		case 8:
			A5 &= 0xdf;A5 |= 0x20;
                        B5 &= 0xfd;B5 |= 0x02;
                        C5 &= 0xdf;C5 |= 0x20;
                        D5 &= 0xfd;D5 |= 0x02;
                        E5 &= 0xfb;E5 |= 0x04;
                        F5 &= 0xfb;F5 |= 0x04;
                        G5 &= 0xbf;G5 |= 0x40;
			break;
		case 9:
                        A5 &= 0xdf;A5 |= 0x20;
                        B5 &= 0xfd;B5 |= 0x02;
                        C5 &= 0xdf;C5 |= 0x20;
                        D5 &= 0xfd;D5 |= 0x02;
                        F5 &= 0xfb;F5 |= 0x04;
                        G5 &= 0xbf;G5 |= 0x40;
			break;
		case 0:
                        A5 &= 0xdf;A5 |= 0x20;
                        B5 &= 0xfd;B5 |= 0x02;
                        C5 &= 0xdf;C5 |= 0x20;
                        D5 &= 0xfd;D5 |= 0x02;
                        E5 &= 0xfb;E5 |= 0x04;
                        F5 &= 0xfb;F5 |= 0x04;
			break;
		case 10:
                        G5 &= 0xbf;
			G5 |= 0x40;
			break;
                case 12://L	
                        D5 &= 0xfd;D5 |= 0x02;
                        E5 &= 0xfb;E5 |= 0x04;
                        F5 &= 0xfb;F5 |= 0x04;
			break;
                case 13://o
                        C5 &= 0xdf;C5 |= 0x20;
                        D5 &= 0xfd;D5 |= 0x02;
                        E5 &= 0xfb;E5 |= 0x04;
                        G5 &= 0xbf;G5 |= 0x40;
                        break;
		}
		break;
	case 6:
		switch(Number){
		case 1:
                        B6 &= 0xf7;B6 |= 0x08;
                        C6 &= 0x7f;C6 |= 0x80;
			break;
		case 2:
                        A6 &= 0x7f;A6 |= 0x80;
                        B6 &= 0xf7;B6 |= 0x08;
                        D6 &= 0xf7;D6 |= 0x08;
                        E6 &= 0xef;E6 |= 0x10;
                        G6 &= 0xfe;G6 |= 0x01;
			break;
		case 3:
                        A6 &= 0x7f;A6 |= 0x80;
                        B6 &= 0xf7;B6 |= 0x08;
                        C6 &= 0x7f;C6 |= 0x80;
                        D6 &= 0xf7;D6 |= 0x08;
                        G6 &= 0xfe;G6 |= 0x01;
			break;
		case 4:
                        B6 &= 0xf7;B6 |= 0x08;
                        C6 &= 0x7f;C6 |= 0x80;
                        F6 &= 0xef;F6 |= 0x10;
                        G6 &= 0xfe;G6 |= 0x01;
			break;
		case 5:
                        A6 &= 0x7f;A6 |= 0x80;
                        C6 &= 0x7f;C6 |= 0x80;
                        D6 &= 0xf7;D6 |= 0x08;
                        F6 &= 0xef;F6 |= 0x10;
                        G6 &= 0xfe;G6 |= 0x01;
			break;
		case 6:
                        A6 &= 0x7f;A6 |= 0x80;
                        C6 &= 0x7f;C6 |= 0x80;
                        D6 &= 0xf7;D6 |= 0x08;
                        E6 &= 0xef;E6 |= 0x10;
                        F6 &= 0xef;F6 |= 0x10;
                        G6 &= 0xfe;G6 |= 0x01;
			break;
		case 7:
                        A6 &= 0x7f;A6 |= 0x80;
                        B6 &= 0xf7;B6 |= 0x08;
                        C6 &= 0x7f;C6 |= 0x80;
			break;
		case 8:
			A6 &= 0x7f;A6 |= 0x80;
                        B6 &= 0xf7;B6 |= 0x08;
                        C6 &= 0x7f;C6 |= 0x80;
                        D6 &= 0xf7;D6 |= 0x08;
                        E6 &= 0xef;E6 |= 0x10;
                        F6 &= 0xef;F6 |= 0x10;
                        G6 &= 0xfe;G6 |= 0x01;
			break;
		case 9:
                        A6 &= 0x7f;A6 |= 0x80;
                        B6 &= 0xf7;B6 |= 0x08;
                        C6 &= 0x7f;C6 |= 0x80;
                        D6 &= 0xf7;D6 |= 0x08;
                        F6 &= 0xef;F6 |= 0x10;
                        G6 &= 0xfe;G6 |= 0x01;
			break;
		case 0:
                        A6 &= 0x7f;A6 |= 0x80;
                        B6 &= 0xf7;B6 |= 0x08;
                        C6 &= 0x7f;C6 |= 0x80;
                        D6 &= 0xf7;D6 |= 0x08;
                        E6 &= 0xef;E6 |= 0x10;
                        F6 &= 0xef;F6 |= 0x10;
			break;
                case 10:
                        G6 &= 0xfe;
                        G6 |= 0x01;
			break;
                case 13://r                       
                        E6 &= 0xef;E6 |= 0x10;
                        G6 &= 0xfe;G6 |= 0x01;
                        break;
                case 14://T
                        A6 &= 0x7f;A6 |= 0x80;
                        E6 &= 0xef;E6 |= 0x10;
                        F6 &= 0xef;F6 |= 0x10;
                        break;
                case 15://d
                        B6 &= 0xf7;B6 |= 0x08;
                        C6 &= 0x7f;C6 |= 0x80;
                        D6 &= 0xf7;D6 |= 0x08;
                        E6 &= 0xef;E6 |= 0x10;
                        G6 &= 0xfe;G6 |= 0x01;
                        break;
		}
		break;
	case 7:
		switch(Number){
		case 1:
                        B7 &= 0xdf;B7 |= 0x20;
                        C7 &= 0xfd;C7 |= 0x02;
                        break;
		case 2:
                        A7 &= 0xfd;A7 |= 0x02;
                        B7 &= 0xdf;B7 |= 0x20;
                        D7 &= 0xdf;D7 |= 0x20;
                        E7 &= 0xbf;E7 |= 0x40;
                        G7 &= 0xfb;G7 |= 0x04;
			break;
		case 3:
                        A7 &= 0xfd;A7 |= 0x02;
                        B7 &= 0xdf;B7 |= 0x20;
                        C7 &= 0xfd;C7 |= 0x02;
                        D7 &= 0xdf;D7 |= 0x20;
                        G7 &= 0xfb;G7 |= 0x04;
			break;
		case 4:
                        B7 &= 0xdf;B7 |= 0x20;
                        C7 &= 0xfd;C7 |= 0x02;
                        F7 &= 0xbf;F7 |= 0x40;
                        G7 &= 0xfb;G7 |= 0x04;
			break;
		case 5:
                        A7 &= 0xfd;A7 |= 0x02;
                        C7 &= 0xfd;C7 |= 0x02;
                        D7 &= 0xdf;D7 |= 0x20;
                        F7 &= 0xbf;F7 |= 0x40;
                        G7 &= 0xfb;G7 |= 0x04;
			break;
		case 6:
                        A7 &= 0xfd;A7 |= 0x02;
                        C7 &= 0xfd;C7 |= 0x02;
                        D7 &= 0xdf;D7 |= 0x20;
                        E7 &= 0xbf;E7 |= 0x40;
                        F7 &= 0xbf;F7 |= 0x40;
                        G7 &= 0xfb;G7 |= 0x04;
			break;
		case 7:
                        A7 &= 0xfd;A7 |= 0x02;
                        B7 &= 0xdf;B7 |= 0x20;
                        C7 &= 0xfd;C7 |= 0x02;
			break;
		case 8:
			A7 &= 0xfd;A7 |= 0x02;
                        B7 &= 0xdf;B7 |= 0x20;
                        C7 &= 0xfd;C7 |= 0x02;
                        D7 &= 0xdf;D7 |= 0x20;
                        E7 &= 0xbf;E7 |= 0x40;
                        F7 &= 0xbf;F7 |= 0x40;
                        G7 &= 0xfb;G7 |= 0x04;
			break;
		case 9:
                        A7 &= 0xfd;A7 |= 0x02;
                        B7 &= 0xdf;B7 |= 0x20;
                        C7 &= 0xfd;C7 |= 0x02;
                        D7 &= 0xdf;D7 |= 0x20;
                        F7 &= 0xbf;F7 |= 0x40;
                        G7 &= 0xfb;G7 |= 0x04;
			break;
		case 0:
                        A7 &= 0xfd;A7 |= 0x02;
                        B7 &= 0xdf;B7 |= 0x20;
                        C7 &= 0xfd;C7 |= 0x02;
                        D7 &= 0xdf;D7 |= 0x20;
                        E7 &= 0xbf;E7 |= 0x40;
                        F7 &= 0xbf;F7 |= 0x40;
			break;
                case 10:
                        G7 &= 0xfb;
                        G7 |= 0x04;
			break;
		}
		break;
	case 8:
		switch(Number){
		case 1:
                        B8 &= 0x7f;B8 |= 0x80;
                        C8 &= 0xf7;C8 |= 0x08;
			break;
		case 2:
                        A8 &= 0xf7;A8 |= 0x08;
                        B8 &= 0x7f;B8 |= 0x80;
                        D8 &= 0x7f;D8 |= 0x80;
                        E8 &= 0xfe;E8 |= 0x01;
                        G8 &= 0xef;G8 |= 0x10;
			break;
		case 3:
                        A8 &= 0xf7;A8 |= 0x08;
                        B8 &= 0x7f;B8 |= 0x80;
                        C8 &= 0xf7;C8 |= 0x08;
                        D8 &= 0x7f;D8 |= 0x80;
                        G8 &= 0xef;G8 |= 0x10;
			break;
		case 4:
                        B8 &= 0x7f;B8 |= 0x80;
                        C8 &= 0xf7;C8 |= 0x08;
                        F8 &= 0xfe;F8 |= 0x01;
                        G8 &= 0xef;G8 |= 0x10;
			break;
		case 5:
                        A8 &= 0xf7;A8 |= 0x08;
                        C8 &= 0xf7;C8 |= 0x08;
                        D8 &= 0x7f;D8 |= 0x80;
                        F8 &= 0xfe;F8 |= 0x01;
                        G8 &= 0xef;G8 |= 0x10;
			break;
		case 6:
                        A8 &= 0xf7;A8 |= 0x08;
                        C8 &= 0xf7;C8 |= 0x08;
                        D8 &= 0x7f;D8 |= 0x80;
                        E8 &= 0xfe;E8 |= 0x01;
                        F8 &= 0xfe;F8 |= 0x01;
                        G8 &= 0xef;G8 |= 0x10;
			break;
		case 7:
                        A8 &= 0xf7;A8 |= 0x08;
                        B8 &= 0x7f;B8 |= 0x80;
                        C8 &= 0xf7;C8 |= 0x08;
			break;
		case 8:
			A8 &= 0xf7;A8 |= 0x08;
                        B8 &= 0x7f;B8 |= 0x80;
                        C8 &= 0xf7;C8 |= 0x08;
                        D8 &= 0x7f;D8 |= 0x80;
                        E8 &= 0xfe;E8 |= 0x01;
                        F8 &= 0xfe;F8 |= 0x01;
                        G8 &= 0xef;G8 |= 0x10;
			break;
		case 9:
                        A8 &= 0xf7;A8 |= 0x08;
                        B8 &= 0x7f;B8 |= 0x80;
                        C8 &= 0xf7;C8 |= 0x08;
                        D8 &= 0x7f;D8 |= 0x80;
                        F8 &= 0xfe;F8 |= 0x01;
                        G8 &= 0xef;G8 |= 0x10;
			break;
		case 0:
                        A8 &= 0xf7;A8 |= 0x08;
                        B8 &= 0x7f;B8 |= 0x80;
                        C8 &= 0xf7;C8 |= 0x08;
                        D8 &= 0x7f;D8 |= 0x80;
                        E8 &= 0xfe;E8 |= 0x01;
                        F8 &= 0xfe;F8 |= 0x01;
			break;
                case 10:
                        G8 &= 0xef;
                        G8 |= 0x10;
			break;
		}
		break;
        case 9:
                switch(Number)
                {
                case 1:
                        Point4 &= 0xfb;
                        Point4 |= 0x04;
                        break;
                case 2:
                        Point5 &= 0xef;
                        Point5 |= 0x10;
                        break;
                }
                break;
        case PRICE:
                switch(Number)
                {
                case 0:
                      X1 &= 0xEF;
                      break;
                case 1:
                      X1 &= 0xEF;
                      X1 |= 0x10;
                      break;
                }
                break;
        case SY:
                switch(Number)
                {
                case 0:
                      X2 &= 0xFE;
                      break;
                case 1:
                      X2 &= 0xFE;
                      X2 |= 0x01;
                      break;
                }
                break;
        case USED:
                switch(Number)
                {
                case 0:
                      X3 &= 0xEF;
                      break;
                case 1:
                      X3 &= 0xEF;
                      X3 |= 0x10;
                      break;
                }
                break;
        case BUY:
                switch(Number)
                {
                case 0:
                      X4 &= 0xFE;
                      break;
                case 1:
                      X4 &= 0xFE;
                      X4 |= 0x01;
                      break;
                }
                break;
        case Valve_OFF:
                switch(Number)
                {
                case 0:
                      X5 &= 0xBF;
                      break;
                case 1:
                      X5 &= 0xBF;
                      X5 |= 0x40;
                      break;
                }
                break;
        case Valve_ON:
                switch(Number)
                {
                case 0:
                      X6 &= 0xFE;
                      break;
                case 1:
                      X6 &= 0xFE;
                      X6 |= 0x01;
                      break;
                }
                break;
        case BATTERY:
                switch(Number)
                {
                case 0:
                      X7 &= 0xFB;
                      break;
                case 1:
                      X7 &= 0xFB;
                      X7 |= 0x04;
                      break;
                }
                break;
        case READ_IC:
                switch(Number)
                {
                case 0:
                      X8 &= 0xEF;
                      break;
                case 1:
                      X8 &= 0xEF;
                      X8 |= 0x10;
                      break;
                }
                break;
	  case M3:
                switch(Number)
                {
                case 0:
                      X12 &= 0xFD;
                      break;
                case 1:
                      X12 &= 0xFD;
                      X12 |= 0x02;
                      break;
                }
                break;
	  case YUAN:
                switch(Number)
                {
                case 0:
                      X10 &= 0xDF;
                      break;
                case 1:
                      X10 &= 0xDF;
                      X10 |= 0x20;
                      break;
                }
                break;
	  case CHARGE:
                switch(Number)
                {
                case 0:
                      X11 &= 0xfd;
                      break;
                case 1:
                      X11 &= 0xfd;
                      X11 |= 0x02;
                      break;
                }
                break;
	  case BAD:
                switch(Number)
                {
                case 0:
                      X9 &= 0xDF;
                      break;
                case 1:
                      X9 &= 0xDF;
                      X9 |= 0x20;
                      break;
                }
                break;
	}
}

void display_TEST(void)
{
    //display TEST
    displayNumber(3,7);
    displayNumber(4,14);
    displayNumber(5,5);
    displayNumber(6,14);
}

void display_Good(void)
{
    displayNumber(3,6);
    displayNumber(4,15);
    displayNumber(5,13);
    displayNumber(6,15);
}

void display_Error(void)
{
    displayNumber(2,13);
    displayNumber(3,13);
    displayNumber(4,13);
    displayNumber(5,13);
    displayNumber(6,13);
}

