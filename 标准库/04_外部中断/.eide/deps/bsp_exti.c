/**
 * @file bsp_exti.c 
 * @author zhan (zhan.2@qq.com)
 * @brief 外部中断测试
 * @version 0.1
 * @date 2023-07-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "bsp_exti.h"
/**
 * @brief 配置嵌套向量中断控制器NVIC
 * 
 */
static void NVIC_Configuration(void)
{

    NVIC_InitTypeDef NVIC_InitStructure;

    /*  配置NVIC为优先组1 */
        /*  NVIC_PriorityGroupConfig() 在整个工程只需要调用一次*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    /*  配置中断源：按键1 */
    NVIC_InitStructure.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;
    /*  配置抢占优先级 */
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    /*  配置子优先级 */
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    /* 使能中断通道 */
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* 配置中断源：按键2，其他配置使用以上*/
    NVIC_InitStructure.NVIC_IRQChannel = KEY2_INT_EXTI_IRQ;
    NVIC_Init(&NVIC_InitStructure);
}
/**
 * @brief 配置 io为EXTI中断口，并设置优先级
 * 
 */
void EXTI_Key_Config(void)
{   
    /*定义一个GPIO_InitTypeDef类型的结构体*/
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;

    /*开启按键相关的GPIO外设时钟*/
    RCC_APB2PeriphClockCmd( KEY1_INT_GPIO_CLK|KEY2_INT_GPIO_CLK, ENABLE);
    
    /*配置 NVIC 中断*/
    NVIC_Configuration();
/*-----------------------------------KEY1配置------------------------------------*/
    /*选择要控制的GPIO引脚*/
    GPIO_InitStructure.GPIO_Pin = KEY1_INT_GPIO_PIN;	

    /*设置引脚模式为浮空输入*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   

    /*调用库函数，初始化GPIO*/
    GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure);	
    
    /*选择EXTI信号源*/
    GPIO_EXTILineConfig(KEY1_INT_EXTI_PORTSOURCE,KEY1_INT_EXTI_PINSOURCE);
    EXTI_InitStructure.EXTI_Line = KEY1_INT_EXTI_LINE;

    /*EXTI为中断模式*/
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;

    /*上升沿中断*/
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;

    /*使能中断*/
    EXTI_Init(&EXTI_InitStructure);
    
/*-----------------------------------KEY2配置------------------------------------*/
    /*选择要控制的GPIO引脚*/
    GPIO_InitStructure.GPIO_Pin = KEY2_INT_GPIO_PIN;	

    /*设置引脚模式为浮空输入*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   

    /*调用库函数，初始化GPIO*/
    GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_InitStructure);	
    
    /*选择EXTI信号源*/
    GPIO_EXTILineConfig(KEY2_INT_EXTI_PORTSOURCE,KEY2_INT_EXTI_PINSOURCE);
    EXTI_InitStructure.EXTI_Line = KEY2_INT_EXTI_LINE;

    /*EXTI为中断模式*/
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;

    /*上升沿中断*/
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;

    /*使能中断*/
    EXTI_Init(&EXTI_InitStructure);

}
