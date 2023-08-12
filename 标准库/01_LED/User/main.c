#include "stm32f10x.h"   // 相当于51单片机中的  #include <reg51.h>
#include "bsp_led.h"
#define SOFT_DELAY Delay(0x0FFFFF);

void Delay(__IO u32 nCount);
int main(void)
{
	// 来到这里的时候，系统的时钟已经被配置成72M。

	/* LED 端口初始化 */
    LED_GPIO_Config();

    while (1)
    {
        LED1_ON;              // 亮
        SOFT_DELAY;
        LED1_OFF;          // 灭

        LED2_ON;             // 亮
        SOFT_DELAY;
        LED2_OFF;          // 灭

        LED3_ON;             // 亮
        SOFT_DELAY;
        LED3_OFF;          // 灭

        /*轮流显示 红绿蓝黄紫青白 颜色*/
        LED_RED;
        SOFT_DELAY;

        LED_GREEN;
        SOFT_DELAY;

        LED_BLUE;
        SOFT_DELAY;

        LED_YELLOW;
        SOFT_DELAY;

        LED_PURPLE;
        SOFT_DELAY;

        LED_CYAN;
        SOFT_DELAY;

        LED_WHITE;
        SOFT_DELAY;

        LED_RGBOFF;
        SOFT_DELAY;
    }
}
void Delay(__IO uint32_t nCount)     //简单的延时函数
{
    for (; nCount != 0; nCount--);
}

