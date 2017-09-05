#include "Z102L.h"

u16 flag = 0;
void GPRS_TEST(void)
{
  switch(flag)
  {
  case 0:
    GPIO_ResetBits(GPIOG, GPIO_Pin_5);
    Delay_1ms(100);
    GPIO_SetBits(GPIOG, GPIO_Pin_5);    //enable GPRS
    GPRS_ReStart();
    flag = 1;
    break;
  case 1:
    {      
      for(int i=0; i<num_rx; i++)//等待 +SIMIND: 1
      {
        if(strstr((const char*)USART_RX_BUF0[i], "+SIMIND: 1"))
        {
          LCD_GLASS_Clear();
          display_Good();
          displayNumber(8,1);
          flag = 2;
          break;
        }
        if(i == num_rx)
        {
          LCD_GLASS_Clear();
          display_Error();
          displayNumber(8,1);
          flag = 0;
          break;
        }
      }
    } break;
  case 2://设置全速模式
    {
      while(GPRS_send_cmd("AT+CFUN=1\r\n", "OK", 100))
      {
          LCD_GLASS_Clear();
          display_Error();
          displayNumber(8,2);
          //flag = 0;
          //break;
      }
          LCD_GLASS_Clear();
          display_Good();
          displayNumber(8,2);
          flag = 3;
    } break;
  case 3://关闭回显
    {
      while(GPRS_send_cmd("ATE0\r\n", "OK", 100))
      {
          LCD_GLASS_Clear();
          display_Error();
          displayNumber(8,3);
      }
          LCD_GLASS_Clear();
          display_Good();
          displayNumber(8,3);
          flag = 4;
    } break;
  case 4://搜网注册
    {
      while(GPRS_send_cmd("AT+SFUN=4\r\n", "+CTZV", 2000))
      {
          LCD_GLASS_Clear();
          display_Error();
          displayNumber(8,4);
          //flag = 0;
          //break;
      }
          LCD_GLASS_Clear();
          display_Good();
          displayNumber(8,4);
          flag = 5;    
    } break;
  case 5://发起GPRS附着
    {
      while(GPRS_send_cmd("AT+CGATT=1\r\n", "+CTZV", 1000))
      {
          LCD_GLASS_Clear();
          display_Error();
          displayNumber(8,5);
          //flag = 0;
          //break;
      }
          LCD_GLASS_Clear();
          display_Good();
          displayNumber(8,5);
          flag = 6;    
    } break;
  case 6://创建GPRS profile
    {
      while(GPRS_send_cmd("AT^IPNET=0,\"conType\",\"GPRS0\"\r\n", "OK", 100))
      {
          LCD_GLASS_Clear();
          display_Error();
          displayNumber(8,6);
      }
          LCD_GLASS_Clear();
          display_Good();
          displayNumber(8,6);
          flag = 7;      
    } break;
  case 7://设置profile的APN参数 AT^IPNET=0,"apn","cmnet"
    {
      while(GPRS_send_cmd("AT^IPNET=0,\"apn\",\"cmnet\"\r\n", "OK", 100))
      {
          LCD_GLASS_Clear();
          display_Error();
          displayNumber(8,7);
      }
          LCD_GLASS_Clear();
          display_Good();
          displayNumber(8,7);
          flag = 8;      
    } break;
  case 8://设置profile的类型（socket）
    {
      while(GPRS_send_cmd("AT^IPSRV=0,\"srvType\",\"socket\"\r\n", "OK", 100))
      {
          LCD_GLASS_Clear();
          display_Error();
          displayNumber(8,8);
      }
          LCD_GLASS_Clear();
          display_Good();
          displayNumber(8,8);
          flag = 9;    
    } break;
  case 9://设置远程服务器地址 echo_IP: 139.196.172.214:12345
    {
      while(GPRS_send_cmd("AT^IPSRV=0,\"address\",\"socktcp://139.196.172.214:12345\"\r\n", "OK", 100))
      {
          LCD_GLASS_Clear();
          display_Error();
          displayNumber(8,9);
      }
          LCD_GLASS_Clear();
          display_Good();
          displayNumber(8,9);
          flag = 10;     
    } break;
  case 10://打开profile socket端口，并连接到远程服务器
    {
      while(GPRS_send_cmd("AT^IPSTART=0\r\n", "^IPSWR:", 300))
      {
          LCD_GLASS_Clear();
          display_Error();
          displayNumber(7,1);
          displayNumber(8,0);
      }
          LCD_GLASS_Clear();
          display_Good();
          displayNumber(7,1);
          displayNumber(8,0);
          flag = 11;     
    } break;
  case 11://设置发送10个字节到远程服务器
    {
      //UART1_SendBuffer("AT^IPSWR=0,10\r\n");
      //Delay_1ms(1000);
      while(GPRS_send_cmd("AT^IPSWR=0,10\r\n", "^IPSWR: 0,10,10", 100))
      {
          LCD_GLASS_Clear();
          display_Error();
          displayNumber(7,1);
          displayNumber(8,1);
      }
          LCD_GLASS_Clear();
          display_Good();
          displayNumber(7,1);
          displayNumber(8,1);
          flag = 12;     
    } break;
  case 12://发送10个字节
    {
      while(GPRS_send_cmd("1234567890\r\n", "^IPSRD: 0,1", 1000))
      {
          LCD_GLASS_Clear();
          display_Error();
          displayNumber(7,1);
          displayNumber(8,2);
          flag = 0;
          break;
      }
          LCD_GLASS_Clear();
          display_Good();
          displayNumber(7,1);
          displayNumber(8,2);
          flag = 13;     
    } break;
  case 13://读取服务器上10个字节
    {
      Delay_1ms(1000);
      while(GPRS_send_cmd("AT^IPSRD=0,10\r\n", "OK", 10))
      {
          LCD_GLASS_Clear();
          display_Error();
          displayNumber(7,1);
          displayNumber(8,3);
      }
          LCD_GLASS_Clear();
          display_Good();
          displayNumber(7,1);
          displayNumber(8,3);
          Delay_1ms(500);
          LCD_GLASS_Clear();
          displayNumber(1,1);
          displayNumber(2,2);
          displayNumber(3,3);
          displayNumber(4,4);
          displayNumber(5,5);
          displayNumber(6,6);
          displayNumber(7,7);
          displayNumber(8,8);
          flag = 14;     
    } break;
      
  default :
    break;
  }
      
}

void GPRS_ReStart(void)
{
    GPIO_SetBits(GPIOG, GPIO_Pin_4);//GPRS_PWR
    Delay_1ms(2000);
    GPIO_ResetBits(GPIOG, GPIO_Pin_4);//GPRS_PWR
    Delay_1ms(140);
}
//char *strx=0;
u8* GPRS_check_cmd(u8 *str)
{
	char *strx=0;
	if(USART_RX_STA&0X8000)		
	{ 
		//USART2_RX_BUF[USART2_RX_STA&0X7FFF]=0;
		//strx=strstr((const char*)USART_RX_BUF,(const char*)str);
//                for(int i=0; i<num_rx; i++)
//                {
                  strx=strstr((const char*)USART_RX_BUF0[num_rx-1], (const char*)str);
//                }
	} 
	return (u8*)strx;
}

u8 GPRS_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
{
	u8 res=0; 
	//USART_RX_STA=0;
	//if((u32)cmd<=0XFF)//判断发送数字还是发送字符串，cmd<=0XFF为发送数字
	//{
		//while(USART1->SR & (1<<7));	
		UART1_SendBuffer(cmd);
	//}else UART1_SendBuffer(cmd);
	if(ack && waittime)		
	{
		while(--waittime)	
		{
			Delay_1ms(100);
			if(USART_RX_STA&0X8000)
			{
				if(GPRS_check_cmd(ack))break;
				USART_RX_STA=0;
			} 
		}
		if(waittime==0)res=1; 
	}
	return res;//得到期望应答为0，超时为1
} 