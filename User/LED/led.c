/*************************************************************************
#   Copyright (C) 2017 Qw//krom Ltd. All rights reserved.
#      Filename: led.c
#
#        Author: Francis· Chuh
#   Description: ---
#        Create: 2017-08-03 14:51:27
# Last Modified: 2017-08-03 14:51:27
*************************************************************************/

#include "led.h"

void Led_On(void)
{
    GPIO_ResetBits(GPIOF, GPIO_Pin_6);
}

void Led_Off(void)
{
    GPIO_SetBits(GPIOF, GPIO_Pin_6);
}
