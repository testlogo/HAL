#include "bsp_ili9341_lcd.h"
uint8_t LCD_SCAN_MODE = 6;
uint16_t LCD_X_LENGTH = ILI9341_LESS_PIXEL;
uint16_t LCD_Y_LENGTH = ILI9341_MORE_PIXEL;
static uint16_t CurrentTextColor   = BLACK;//前景色
static uint16_t CurrentBackColor   = WHITE;//背景色
static __INLINE void ILI9341_Write_Cmd(uint16_t usCmd);
static __INLINE void ILI9341_Write_Data(uint16_t usData);
static __INLINE uint16_t ILI9341_Read_Data(void);

__INLINE void ILI9341_Write_Cmd(uint16_t usCmd)
{
    *FSMC_Addr_ILI9341_CMD = usCmd;
}
__INLINE void ILI9341_Write_Data(uint16_t usData)
{
    *FSMC_Addr_ILI9341_DATA = usData;
}
__INLINE uint16_t ILI9341_Read_Data(void)
{
    return (*(FSMC_Addr_ILI9341_DATA));
}

void LCD_SetColors(uint16_t TextColor, uint16_t BackColor) 
{
  CurrentTextColor = TextColor; 
  CurrentBackColor = BackColor;
}

static void ILI9341_Delay(__IO uint32_t nCount)
{
    for (; nCount != 0; nCount--)
        ;
}

static void ILI9341_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(/*控制信号*/
                           ILI9341_CS_CLK | ILI9341_DC_CLK | ILI9341_WR_CLK |
                               ILI9341_RD_CLK | ILI9341_BK_CLK | ILI9341_RST_CLK |
                               /*数据信号*/
                               ILI9341_D0_CLK | ILI9341_D1_CLK | ILI9341_D2_CLK |
                               ILI9341_D3_CLK | ILI9341_D4_CLK | ILI9341_D5_CLK |
                               ILI9341_D6_CLK | ILI9341_D7_CLK | ILI9341_D8_CLK |
                               ILI9341_D9_CLK | ILI9341_D10_CLK | ILI9341_D11_CLK |
                               ILI9341_D12_CLK | ILI9341_D13_CLK | ILI9341_D14_CLK |
                               ILI9341_D15_CLK,
                           ENABLE);

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	
    GPIO_InitStructure.GPIO_Pin = ILI9341_D0_PIN;
	GPIO_Init ( ILI9341_D0_PORT, & GPIO_InitStructure );

    GPIO_InitStructure.GPIO_Pin = ILI9341_D1_PIN;
	GPIO_Init ( ILI9341_D1_PORT, & GPIO_InitStructure );
	
    GPIO_InitStructure.GPIO_Pin = ILI9341_D2_PIN;
	GPIO_Init ( ILI9341_D2_PORT, & GPIO_InitStructure );
	
    GPIO_InitStructure.GPIO_Pin = ILI9341_D3_PIN;
	GPIO_Init ( ILI9341_D3_PORT, & GPIO_InitStructure );
	
    GPIO_InitStructure.GPIO_Pin = ILI9341_D4_PIN;
	GPIO_Init ( ILI9341_D4_PORT, & GPIO_InitStructure );
	
    GPIO_InitStructure.GPIO_Pin = ILI9341_D5_PIN;
	GPIO_Init ( ILI9341_D5_PORT, & GPIO_InitStructure );
	
    GPIO_InitStructure.GPIO_Pin = ILI9341_D6_PIN;
	GPIO_Init ( ILI9341_D6_PORT, & GPIO_InitStructure );
	
    GPIO_InitStructure.GPIO_Pin = ILI9341_D7_PIN;
	GPIO_Init ( ILI9341_D7_PORT, & GPIO_InitStructure );
	
    GPIO_InitStructure.GPIO_Pin = ILI9341_D8_PIN;
	GPIO_Init ( ILI9341_D8_PORT, & GPIO_InitStructure );
	
    GPIO_InitStructure.GPIO_Pin = ILI9341_D9_PIN;
	GPIO_Init ( ILI9341_D9_PORT, & GPIO_InitStructure );
	
    GPIO_InitStructure.GPIO_Pin = ILI9341_D10_PIN;
	GPIO_Init ( ILI9341_D10_PORT, & GPIO_InitStructure );
	
    GPIO_InitStructure.GPIO_Pin = ILI9341_D11_PIN;
	GPIO_Init ( ILI9341_D11_PORT, & GPIO_InitStructure );

    GPIO_InitStructure.GPIO_Pin = ILI9341_D12_PIN;
	GPIO_Init ( ILI9341_D12_PORT, & GPIO_InitStructure );	
	
    GPIO_InitStructure.GPIO_Pin = ILI9341_D13_PIN;
	GPIO_Init ( ILI9341_D13_PORT, & GPIO_InitStructure );
	
    GPIO_InitStructure.GPIO_Pin = ILI9341_D14_PIN;
	GPIO_Init ( ILI9341_D14_PORT, & GPIO_InitStructure );
	
    GPIO_InitStructure.GPIO_Pin = ILI9341_D15_PIN;
	GPIO_Init ( ILI9341_D15_PORT, & GPIO_InitStructure );
	

	
    /* 配置FSMC相对应的控制线
     * FSMC_NOE   :LCD-RD
     * FSMC_NWE   :LCD-WR
     * FSMC_NE1   :LCD-CS
     * FSMC_A16   :LCD-DC
     */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;
	
    GPIO_InitStructure.GPIO_Pin = ILI9341_RD_PIN;
	GPIO_Init (ILI9341_RD_PORT, & GPIO_InitStructure );
	
    GPIO_InitStructure.GPIO_Pin = ILI9341_WR_PIN;
	GPIO_Init (ILI9341_WR_PORT, & GPIO_InitStructure );
	
    GPIO_InitStructure.GPIO_Pin = ILI9341_CS_PIN;
	GPIO_Init ( ILI9341_CS_PORT, & GPIO_InitStructure );  
	
    GPIO_InitStructure.GPIO_Pin = ILI9341_DC_PIN;
	GPIO_Init ( ILI9341_DC_PORT, & GPIO_InitStructure );
	

  /* 配置LCD复位RST控制管脚*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
    GPIO_InitStructure.GPIO_Pin = ILI9341_RST_PIN;
	GPIO_Init ( ILI9341_RST_PORT, & GPIO_InitStructure );
	
	
	/* 配置LCD背光控制管脚BK*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
    GPIO_InitStructure.GPIO_Pin = ILI9341_BK_PIN;
	GPIO_Init ( ILI9341_BK_PORT, & GPIO_InitStructure );
}


 /**
  * @brief  LCD  FSMC 模式配置
  * @param  无
  * @retval 无
  */
static void ILI9341_FSMC_Config ( void )
{
    FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStructure = {0};
    FSMC_NORSRAMTimingInitTypeDef readWriteTiming     = {0};
    /* 使能FSMC时钟*/
	RCC_AHBPeriphClockCmd ( RCC_AHBPeriph_FSMC, ENABLE );

    // 地址建立时间（ADDSET）为1个HCLK 2/72M=28ns
    readWriteTiming.FSMC_AddressSetupTime = 0x01; // 地址建立时间
    // 数据保持时间（DATAST）+ 1个HCLK = 5/72M=70ns
    readWriteTiming.FSMC_DataSetupTime = 0x04; // 数据建立时间
    // 选择控制的模式
    // 模式B,异步NOR FLASH模式，与ILI9341的8080时序匹配
    readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_B;

    /*以下配置与模式B无关*/
    // 地址保持时间（ADDHLD）模式A未用到
    readWriteTiming.FSMC_AddressHoldTime = 0x00; // 地址保持时间
    // 设置总线转换周期，仅用于复用模式的NOR操作
    readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
    // 设置时钟分频，仅用于同步类型的存储器
    readWriteTiming.FSMC_CLKDivision = 0x00;
    // 数据保持时间，仅用于同步型的NOR
    readWriteTiming.FSMC_DataLatency = 0x00;

    FSMC_NORSRAMInitStructure.FSMC_Bank                  = FSMC_Bank1_NORSRAMx;
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux        = FSMC_DataAddressMux_Disable;
    FSMC_NORSRAMInitStructure.FSMC_MemoryType            = FSMC_MemoryType_NOR;
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth       = FSMC_MemoryDataWidth_16b;
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode       = FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity    = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode              = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive      = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation        = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal            = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode          = FSMC_ExtendedMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst            = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct     = &readWriteTiming;

    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

    /* 使能 FSMC_Bank1_NORSRAM4 */
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAMx, ENABLE);
}

static void ILI9341_REG_Config(void)
{
    /*  Power control B (CFh)  */
    DEBUG_DELAY();
    ILI9341_Write_Cmd(0xCF);
    ILI9341_Write_Data(0x00);
    ILI9341_Write_Data(0x81);
    ILI9341_Write_Data(0x30);

    /*  Power on sequence control (EDh) */
    DEBUG_DELAY();
    ILI9341_Write_Cmd(0xED);
    ILI9341_Write_Data(0x64);
    ILI9341_Write_Data(0x03);
    ILI9341_Write_Data(0x12);
    ILI9341_Write_Data(0x81);

    /*  Driver timing control A (E8h) */
    DEBUG_DELAY();
    ILI9341_Write_Cmd(0xE8);
    ILI9341_Write_Data(0x85);
    ILI9341_Write_Data(0x10);
    ILI9341_Write_Data(0x78);

    /*  Power control A (CBh) */
    DEBUG_DELAY();
    ILI9341_Write_Cmd(0xCB);
    ILI9341_Write_Data(0x39);
    ILI9341_Write_Data(0x2C);
    ILI9341_Write_Data(0x00);
    ILI9341_Write_Data(0x34);
    // ILI9341_Write_Data ( 0x02 );
    ILI9341_Write_Data(0x06); // 原来是0x02改为0x06可防止液晶显示白屏时有条纹的情况

    /* Pump ratio control (F7h) */
    DEBUG_DELAY();
    ILI9341_Write_Cmd(0xF7);
    ILI9341_Write_Data(0x20);

    /* Driver timing control B */
    DEBUG_DELAY();
    ILI9341_Write_Cmd(0xEA);
    ILI9341_Write_Data(0x00);
    ILI9341_Write_Data(0x00);

    /* Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
    DEBUG_DELAY();
    ILI9341_Write_Cmd(0xB1);
    ILI9341_Write_Data(0x00);
    ILI9341_Write_Data(0x1B);

    /*  Display Function Control (B6h) */
    DEBUG_DELAY();
    ILI9341_Write_Cmd(0xB6);
    ILI9341_Write_Data(0x0A);
    ILI9341_Write_Data(0xA2);

    /* Power Control 1 (C0h) */
    DEBUG_DELAY();
    ILI9341_Write_Cmd(0xC0);
    ILI9341_Write_Data(0x35);

    /* Power Control 2 (C1h) */
    DEBUG_DELAY();
    ILI9341_Write_Cmd(0xC1);
    ILI9341_Write_Data(0x11);

    /* VCOM Control 1 (C5h) */
    ILI9341_Write_Cmd(0xC5);
    ILI9341_Write_Data(0x45);
    ILI9341_Write_Data(0x45);

    /*  VCOM Control 2 (C7h)  */
    ILI9341_Write_Cmd(0xC7);
    ILI9341_Write_Data(0xA2);

    /* Enable 3G (F2h) */
    ILI9341_Write_Cmd(0xF2);
    ILI9341_Write_Data(0x00);

    /* Gamma Set (26h) */
    ILI9341_Write_Cmd(0x26);
    ILI9341_Write_Data(0x01);
    DEBUG_DELAY();

    /* Positive Gamma Correction */
    ILI9341_Write_Cmd(0xE0); // Set Gamma
    ILI9341_Write_Data(0x0F);
    ILI9341_Write_Data(0x26);
    ILI9341_Write_Data(0x24);
    ILI9341_Write_Data(0x0B);
    ILI9341_Write_Data(0x0E);
    ILI9341_Write_Data(0x09);
    ILI9341_Write_Data(0x54);
    ILI9341_Write_Data(0xA8);
    ILI9341_Write_Data(0x46);
    ILI9341_Write_Data(0x0C);
    ILI9341_Write_Data(0x17);
    ILI9341_Write_Data(0x09);
    ILI9341_Write_Data(0x0F);
    ILI9341_Write_Data(0x07);
    ILI9341_Write_Data(0x00);

    /* Negative Gamma Correction (E1h) */
    ILI9341_Write_Cmd(0XE1); // Set Gamma
    ILI9341_Write_Data(0x00);
    ILI9341_Write_Data(0x19);
    ILI9341_Write_Data(0x1B);
    ILI9341_Write_Data(0x04);
    ILI9341_Write_Data(0x10);
    ILI9341_Write_Data(0x07);
    ILI9341_Write_Data(0x2A);
    ILI9341_Write_Data(0x47);
    ILI9341_Write_Data(0x39);
    ILI9341_Write_Data(0x03);
    ILI9341_Write_Data(0x06);
    ILI9341_Write_Data(0x06);
    ILI9341_Write_Data(0x30);
    ILI9341_Write_Data(0x38);
    ILI9341_Write_Data(0x0F);

    /* memory access control set */
    DEBUG_DELAY();
    ILI9341_Write_Cmd(0x36);
    ILI9341_Write_Data(0xC8); /*竖屏  左上角到 (起点)到右下角 (终点)扫描方式*/
    DEBUG_DELAY();

    /* column address control set */
    ILI9341_Write_Cmd(CMD_SetCoordinateX);
    ILI9341_Write_Data(0x00);
    ILI9341_Write_Data(0x00);
    ILI9341_Write_Data(0x00);
    ILI9341_Write_Data(0xEF);

    /* page address control set */
    DEBUG_DELAY();
    ILI9341_Write_Cmd(CMD_SetCoordinateY);
    ILI9341_Write_Data(0x00);
    ILI9341_Write_Data(0x00);
    ILI9341_Write_Data(0x01);
    ILI9341_Write_Data(0x3F);

    /*  Pixel Format Set (3Ah)  */
    DEBUG_DELAY();
    ILI9341_Write_Cmd(0x3a);
	
    ILI9341_Write_Data(0x55);

    /* Sleep Out (11h)  */
    ILI9341_Write_Cmd(0x11);
    ILI9341_Delay(0xAFFf << 2);
    DEBUG_DELAY();

    /* Display ON (29h) */
    ILI9341_Write_Cmd(0x29);
}

void ILI9341_Init ( void )
{
	ILI9341_GPIO_Config ();
	ILI9341_FSMC_Config ();
	
	ILI9341_BackLed_Control ( ENABLE );      //点亮LCD背光灯
	ILI9341_Rst ();
	ILI9341_REG_Config ();
	
	//设置默认扫描方向，其中 6 模式为大部分液晶例程的默认显示方向  
	ILI9341_GramScan(LCD_SCAN_MODE);
}

void ILI9341_Rst ( void )
{			
	GPIO_ResetBits ( ILI9341_RST_PORT, ILI9341_RST_PIN );	 //低电平复位

	ILI9341_Delay ( 0xAFF ); 					   

	GPIO_SetBits ( ILI9341_RST_PORT, ILI9341_RST_PIN );		 	 

	ILI9341_Delay ( 0xAFF ); 	
	
}

void ILI9341_BackLed_Control ( FunctionalState enumState )
{
	if ( enumState )
		GPIO_ResetBits ( ILI9341_BK_PORT, ILI9341_BK_PIN );	
	else
		GPIO_SetBits ( ILI9341_BK_PORT, ILI9341_BK_PIN );
		
}

void ILI9341_OpenWindow(uint16_t usX, uint16_t usY, uint16_t usWidth, uint16_t usHeight)
{
    ILI9341_Write_Cmd(CMD_SetCoordinateX);
    ILI9341_Write_Data(usX >> 8);
    ILI9341_Write_Data(usX & 0xff);
    ILI9341_Write_Data((usX + usWidth - 1) >> 8);
    ILI9341_Write_Data((usX + usWidth - 1) & 0xff);

    ILI9341_Write_Cmd(CMD_SetCoordinateY);
    ILI9341_Write_Data(usY >> 8);
    ILI9341_Write_Data(usY & 0xff);
    ILI9341_Write_Data((usY + usHeight - 1) >> 8);
    ILI9341_Write_Data((usY + usHeight - 1) & 0xff);
}

static void ILI9341_SetCursor ( uint16_t usX, uint16_t usY )	
{
	ILI9341_OpenWindow ( usX, usY, 1, 1 );
}

static __inline void ILI9341_FillColor ( uint32_t ulAmout_Point, uint16_t usColor )
{
	uint32_t i = 0;
	
	
	/* memory write */
	ILI9341_Write_Cmd ( CMD_SetPixel );	
		
	for ( i = 0; i < ulAmout_Point; i ++ )
		ILI9341_Write_Data ( usColor );
		
	
}

void ILI9341_SetPointPixel ( uint16_t usX, uint16_t usY )
{
    if( ( usX < LCD_X_LENGTH ) && ( usY < LCD_Y_LENGTH ))
    {
        ILI9341_SetCursor( usX, usY );
        ILI9341_FillColor( 1, CurrentTextColor );
    }
}

void ILI9341_DrawLine ( uint16_t usX1, uint16_t usY1, uint16_t usX2, uint16_t usY2 )
{
	uint16_t us; 
	uint16_t usX_Current, usY_Current;
	
	int32_t lError_X = 0, lError_Y = 0, lDelta_X, lDelta_Y, lDistance; 
	int32_t lIncrease_X, lIncrease_Y; 	
	
	
	lDelta_X = usX2 - usX1; //计算坐标增量 
	lDelta_Y = usY2 - usY1; 
	
	usX_Current = usX1; 
	usY_Current = usY1; 
	
	
	if ( lDelta_X > 0 ) 
		lIncrease_X = 1; //设置单步方向 
	
	else if ( lDelta_X == 0 ) 
		lIncrease_X = 0;//垂直线 
	
	else 
  { 
    lIncrease_X = -1;
    lDelta_X = - lDelta_X;
  } 

	
	if ( lDelta_Y > 0 )
		lIncrease_Y = 1; 
	
	else if ( lDelta_Y == 0 )
		lIncrease_Y = 0;//水平线 
	
	else 
  {
    lIncrease_Y = -1;
    lDelta_Y = - lDelta_Y;
  } 

	
	if (  lDelta_X > lDelta_Y )
		lDistance = lDelta_X; //选取基本增量坐标轴 
	
	else 
		lDistance = lDelta_Y; 

	
	for ( us = 0; us <= lDistance + 1; us ++ )//画线输出 
	{  
		ILI9341_SetPointPixel ( usX_Current, usY_Current );//画点 
		
		lError_X += lDelta_X ; 
		lError_Y += lDelta_Y ; 
		
		if ( lError_X > lDistance ) 
		{ 
			lError_X -= lDistance; 
			usX_Current += lIncrease_X; 
		}  
		
		if ( lError_Y > lDistance ) 
		{ 
			lError_Y -= lDistance; 
			usY_Current += lIncrease_Y; 
		} 
		
	}  
	
	
}

void ILI9341_GramScan ( uint8_t ucOption )
{	
	//参数检查，只可输入0-7
	if(ucOption >7 )
		return;
	
	//根据模式更新LCD_SCAN_MODE的值，主要用于触摸屏选择计算参数
	LCD_SCAN_MODE = ucOption;
	
	//根据模式更新XY方向的像素宽度
	if(ucOption%2 == 0)	
	{
		//0 2 4 6模式下X方向像素宽度为240，Y方向为320
		LCD_X_LENGTH = ILI9341_LESS_PIXEL;
		LCD_Y_LENGTH =	ILI9341_MORE_PIXEL;
	}
	else				
	{
		//1 3 5 7模式下X方向像素宽度为320，Y方向为240
		LCD_X_LENGTH = ILI9341_MORE_PIXEL;
		LCD_Y_LENGTH =	ILI9341_LESS_PIXEL; 
	}

	//0x36命令参数的高3位可用于设置GRAM扫描方向	
	ILI9341_Write_Cmd ( 0x36 );

    ILI9341_Write_Data ( 0x08 |(ucOption<<5));//根据ucOption的值设置LCD参数，共0-7种模式

	ILI9341_Write_Cmd ( CMD_SetCoordinateX ); 
	ILI9341_Write_Data ( 0x00 );		/* x 起始坐标高8位 */
	ILI9341_Write_Data ( 0x00 );		/* x 起始坐标低8位 */
	ILI9341_Write_Data ( ((LCD_X_LENGTH-1)>>8)&0xFF ); /* x 结束坐标高8位 */	
	ILI9341_Write_Data ( (LCD_X_LENGTH-1)&0xFF );				/* x 结束坐标低8位 */

	ILI9341_Write_Cmd ( CMD_SetCoordinateY ); 
	ILI9341_Write_Data ( 0x00 );		/* y 起始坐标高8位 */
	ILI9341_Write_Data ( 0x00 );		/* y 起始坐标低8位 */
	ILI9341_Write_Data ( ((LCD_Y_LENGTH-1)>>8)&0xFF );	/* y 结束坐标高8位 */	 
	ILI9341_Write_Data ( (LCD_Y_LENGTH-1)&0xFF );				/* y 结束坐标低8位 */

	/* write gram start */
	ILI9341_Write_Cmd ( CMD_SetPixel );	
}

void ILI9341_Clear ( uint16_t usX, uint16_t usY, uint16_t usWidth, uint16_t usHeight )
{
	ILI9341_OpenWindow ( usX, usY, usWidth, usHeight );

	ILI9341_FillColor ( usWidth * usHeight, CurrentBackColor );		
	
}

void LCD_SetTextColor(uint16_t Color)
{
  CurrentTextColor = Color;
}
