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
#include "dsp_usart.h"

int main()
{
    char ch;
    LED_GPIO_Config();
    USART_Config();
    LED_RED;
    printf("接受字符\n");
    while (1)
    {
        ch = getchar();
        printf("接受字符：%c\n",ch);

        switch (ch)
        {
        case '1':
            LED_RED;
            break;
        case '2':
            LED_GREEN;
            break;
        case '3':
            LED_YELLOW;
            break;
        case '4':
            LED_PURPLE;
            break;
        case '5':
            LED_YELLOW;
            break;
        
        default:
            LED_RGBOFF;
            break;
        }
    }
    
}
