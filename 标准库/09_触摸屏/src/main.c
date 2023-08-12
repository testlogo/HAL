

#include "stm32f10x.h"
#include "usart/bsp_usart.h"
#include "lcd/bsp_ili9341_lcd.h"
#include "lcd/bsp_xpt2046_lcd.h"
#include "flash/bsp_spi_flash.h"
#include "led/bsp_led.h"
#include "palette.h"
#include <string.h>

int main()
{
    ILI9341_Init();

    XPT2046_Init();

    Calibrate_or_Get_TouchParaWithFlash(3,1);

    USART_Config();
    LED_GPIO_Config();

    ILI9341_GramScan( 3 );

    Palette_Init(LCD_SCAN_MODE);

    while (1)
    {
        XPT2046_TouchEvenHandler();
    }
    
}
