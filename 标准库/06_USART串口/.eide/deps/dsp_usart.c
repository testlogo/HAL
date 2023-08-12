#include "dsp_usart.h"
/**
 * @brief 初始化串口 GPIO
 * 
 */
void USART_Config(void)
{
    GPIO_InitTypeDef    GPIO_InitStrcture;
    USART_InitTypeDef   USART_InitStrcture;

    //打开串口GPIO时钟
    DEBUG_UASRT_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);

    //打开串口外设时钟
    DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

    //Tx的GPIO配置为推挽模式
    GPIO_InitStrcture.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStrcture.GPIO_Pin  = DEBUG_UASRT_TX_GPIO_PIN;
    GPIO_InitStrcture.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(DEBUG_UASRT_TX_GPIO_PORT, &GPIO_InitStrcture);
    
    //Rx的GPIO配置为浮空输入模式
    GPIO_InitStrcture.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStrcture.GPIO_Pin  = DEBUG_UASRT_RX_GPIO_PIN;
    GPIO_Init(DEBUG_UASRT_RX_GPIO_PORT, &GPIO_InitStrcture);

    //配置串口工作参数
    //配置波特率
    USART_InitStrcture.USART_BaudRate = DEBUG_USART_BAUDRATE;
    //配置帧数据字长
    USART_InitStrcture.USART_WordLength = USART_WordLength_8b;
    //配置停止位
    USART_InitStrcture.USART_StopBits = USART_StopBits_1;
    //配置校验位
    USART_InitStrcture.USART_Parity = USART_Parity_No;
    //配置硬件流控制
    USART_InitStrcture.USART_HardwareFlowControl = 
    USART_HardwareFlowControl_None;
    //配置工作模式
    USART_InitStrcture.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(DEBUG_USARTx, &USART_InitStrcture);

    //使能串口
    USART_Cmd(DEBUG_USARTx, ENABLE);
}
/**
 * @brief 发送字符
 * 
 * @param pUSARTx 串口号
 * @param ch      要发送的字符
 */
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
    USART_SendData(pUSARTx, ch);

    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}
/**
 * @brief 发送字符串
 *  
 * @param pUSARTx 发送的串口
 * @param str      发送的字符串
 */
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
    unsigned int k=0;
    do
    {
        Usart_SendByte(pUSARTx, *(str + k) );
        k++;
    } while (*(str + k) != 0);
    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}
/**
 * @brief 重定向printf到串口
 * 
 */
int fputc(int ch, FILE *f)
{
    USART_SendData(DEBUG_USARTx, (uint8_t) ch);

    while(USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);

    return (ch);
}
/**
 * @brief 重定向scanf，getchar
 */
int fgetc(FILE *f)
{
    while(USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);

    return (int)USART_ReceiveData(DEBUG_USARTx);
}
