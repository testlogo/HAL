
#include "bsp_SysTick.h"

/**
 * @brief 启动系统滴答计时器
 * 
 */
void SysTick_Init(void)
{
    // 72M / 100000 = 720 就是720次中断一下，而AHB=72M,所以需要1/100000 s,也就是10 us
    /**
     * SystemFrequency / 1000       1ms中断1次
     * SystemFrequency / 100000     10us中断1次
     * SystemFrequency / 1000000    1us中断1次
     */
    if(SysTick_Config(SystemCoreClock / 1000000)){
        while(1);
    }
}
/**
 * @brief 1us为单位延时，总延时为 us * 1us
 * 
 * @param us 输入us * 1us =总延时 
 */
void SysTick_Delay_Us(__IO uint32_t us)
{
    SysTick_Config(SystemCoreClock / 1000000);
    for (uint32_t i = 0 ; i < us ; i++)
    {
        while(!((SysTick->CTRL) & (1<<16)));
    }
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

/**
 * @brief 1ms为单位延时，总延时为 ms * 1ms
 * 
 * @param ms 输入ms * 1ms =总延时 
 */
void SysTick_Delay_Ms(__IO uint32_t ms)
{
    SysTick_Config(SystemCoreClock / 1000);
    for (uint32_t i = 0 ; i < ms ; i++)
    {
        while(!((SysTick->CTRL) & (1<<16)));
    }
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}


