/*************************************************************************
#   Copyright (C) 2017 Qw//krom Ltd. All rights reserved.
#      Filename: include.h
#
#        Author: Francis· Chuh
#   Description: ---
#        Create: 2017-08-03 14:46:05
# Last Modified: 2017-08-03 14:46:05
*************************************************************************/
#ifndef __INCLUDE_H
#define __INCLUDE_H

#include "stm8l15x.h"
#include "stm8l15x_it.h"
#include "../User/Init/Init.h"
#include "../User/LED/Led.h"
#include "../User/LCD/LCD.h"
#include "../User/KEY/key.h"
#include "../User/Z102L/Z102L.h"
#include "string.h"

#define TX_BUFFER_SIZE       (countof(TxBuffer) - 1)
#define USART_REC_LEN   40 //最大接收字节数
#define USART_REC_NUM   90

extern u16 flag;
extern u8 USART_RX_BUF0[USART_REC_NUM][USART_REC_LEN];
extern u8 USART_RX_BUF[USART_REC_LEN];
extern u16 USART_RX_STA;//接收状态标记
extern unsigned int num_rx;//GPRS返回数据第num_rx+1个数据

extern void Delay_1ms(unsigned int count);
extern void Delay(uint16_t nCount);
extern void UART1_SendBuffer(uint8_t* buffer);

#endif