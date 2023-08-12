#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_usart_dma.h"

extern uint8_t SendBuff[SENDBUFF_SIZE];
static void Delay(__IO uint32_t nCount);
int main(void)
{
  USART_Config();

  USARTx_DMA_Config();

  LED_GPIO_Config();
  
  printf("测试串口->内存\n");
  
  USART_DMACmd(DEBUG_USARTx, USART_DMAReq_Rx, ENABLE);
  printf("from Sendbuff %s\n",SendBuff);
  
  while (1)
  {
    printf("from while %s\n",SendBuff);
    Delay(0xffffff);
    LED2_TOGGLE;
    Delay(0xfffff);
  }
  
}

static void Delay(__IO uint32_t nCount)	 //简单的延时函数
{
	for(; nCount != 0; nCount--);
}
