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
#include "bsp_exti.h"

// void delay(int x)
// {
//     for (int i = 0; i < x; i++)
//     {
//         for (int j = 0; j < 1000; j++)
//             __NOP();
//     }
// }

int main()
{
    LED_GPIO_Config();
    EXTI_Key_Config();
    while (1)
    {
        
    }
    
}
