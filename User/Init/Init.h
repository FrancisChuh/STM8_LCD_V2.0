/*************************************************************************
#   Copyright (C) 2017 Qw//krom Ltd. All rights reserved.
#      Filename: Init.h
#
#        Author: Francis· Chuh
#   Description: ---
#        Create: 2017-08-03 14:24:35
# Last Modified: 2017-08-03 14:24:35
*************************************************************************/

#ifndef __Init_H
#define __Init_H

#include "include.h"

#define USART_DMA_CHANNEL_TX   DMA1_Channel1
#define USART_DMA_FLAG_TCTX    (uint16_t)DMA1_FLAG_TC1
#define USART_DR_ADDRESS       (uint16_t)0x5231  /* USART1 Data register Address */
#define DATA_TO_TRANSFER       (countof(TxBuffer) - 1)
#define countof(a)             (sizeof(a) / sizeof(*(a)))

extern uint8_t TxBuffer[256];

void IO_Init(void);
void SYS_CLK_Init(void);
void SerialInit(void);
void DMA_Config(void);
#endif
