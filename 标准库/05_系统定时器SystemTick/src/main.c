/*
 * ************************************************
 * 
 * STM32 blink demo
 * 
 * CPU:     STM32F103C8
 * PIN:     PA1
 * 
 * ************************************************
*/

#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_SysTick.h"
int main()
{
    LED_GPIO_Config();

    SysTick_Init();
    while (1)
    {
        SysTick_Delay_Ms(10000);
        LED1_TOGGLE;
        SysTick_Delay_Ms(10000);
        LED2_TOGGLE;
        SysTick_Delay_Ms(10000);
        LED3_TOGGLE;
    }
    
}
