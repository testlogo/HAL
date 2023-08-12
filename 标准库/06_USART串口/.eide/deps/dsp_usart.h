#ifndef __DSP_USART_H
#define __DSP_USART_H

#include "stm32f10x.h"
#include <stdio.h>
/**
 * @brief 串口定义
 *
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

#define DEBUG_UASRT_IRQ                 USART1_IRQn
#define DEBUG_UASRT_IRQHandler          DEBUG_USART_IRQHandler

void USART_Config(void);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
#endif // __DSP_USART_H
