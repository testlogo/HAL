#include "stm32f10x.h"
void Key_GPIO_Config(void);
//  引脚定义
#define    KEY1_GPIO_CLK     RCC_APB2Periph_GPIOA
#define    KEY1_GPIO_PORT    GPIOA
#define    KEY1_GPIO_PIN     GPIO_Pin_0

#define    KEY2_GPIO_CLK     RCC_APB2Periph_GPIOC
#define    KEY2_GPIO_PORT    GPIOC
#define    KEY2_GPIO_PIN     GPIO_Pin_13


