#include "include.h"

#define KEY0  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)

#define KEY0_PRES	1		//KEY0 

//u8 KEY_Scan(u8 mode);
void KeyRead(void);
void KeyProc(void);