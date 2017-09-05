#include "key.h"

/**
  * @brief  ����������
  * @param  mode=0����֧����������mode=1��֧��������
  * @retval ����ֵ
  */
//u8 KEY_Scan(u8 mode)
//{	 
//	static u8 key_up=1;
//	if(mode)key_up=1;  		  
//	if(key_up&&(KEY0==0))
//	{
//		Delay_1ms(10); 
//		key_up=0;
//		if(KEY0==0)return KEY0_PRES;	
//	}else if(KEY0==1)key_up=1; 	     
//	return 0;
//}

unsigned char Trg;
unsigned char Cont;
void KeyRead(void)
{
  unsigned char key = 0xff;
  
    if(KEY0 == 1)key = 0xff;
    else if(KEY0 == 0)key = 0xfe;
    
    unsigned char ReadData = key ^ 0xff;  // 1
    Trg = ReadData & (ReadData ^ Cont);    // 2
    Cont = ReadData;                       // 3
}
int i=0,cnt_plus=0;
void KeyProc(void)
{
    if (Trg) 
    {                    
        i++;
        LCD_GLASS_Clear();
        displayNumber(8,i);
        if(i==9)
          i=0;
    }
    if (Cont) // ������ӡ����������Ų���
    {
         cnt_plus++;       // ��ʱ
         if (cnt_plus > 100) // 20ms*100 = 2S ���ʱ�䵽
         {
            WWDG->CR|=0x80;
            WWDG->CR&=~0x40;
            cnt_plus=0;
         }
    }
}