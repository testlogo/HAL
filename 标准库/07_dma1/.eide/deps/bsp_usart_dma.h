#ifndef __BSD_USART_DMA_H
#define __BSD_USART_DMA_H

#include "stm32f10x.h"
#include <stdio.h>
// 串口对应的DMA请求通道
#define  USART_TX_DMA_CHANNEL     DMA1_Channel5
// 外设寄存器地址
#define  USART_DR_ADDRESS        (USART1_BASE+0x04)
// 一次发送的数据量
#define  SENDBUFF_SIZE            5000
/**
 * @brief 串口定义
 */

// 串口1-USART1
#define DEBUG_USARTx                    USART1
#define DEBUG_USART_CLK                 RCC_APB2Periph_USART1
#define DEBUG_USART_APBxClkCmd          RCC_APB2PeriphClockCmd
#define DEBUG_USART_BAUDRATE            115200

// USART GPIO 引脚宏定义    
#define DEBUG_USART_GPIO_CLK            (RCC_APB2Periph_GPIOA)
#define DEBUG_UASRT_GPIO_APBxClkCmd     RCC_APB2PeriphClockCmd

#define DEBUG_UASRT_TX_GPIO_PORT        GPIOA
#define DEBUG_UASRT_TX_GPIO_PIN         GPIO_Pin_9
#define DEBUG_UASRT_RX_GPIO_PORT        GPIOB
#define DEBUG_UASRT_RX_GPIO_PIN         GPIO_Pin_10

void USART_Config(void);
void USARTx_DMA_Config(void);

#endif // __BSD_USART_DMA_H
/*---------------------------------end of file----------------------------------*/
