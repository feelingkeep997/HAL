#include "stm32f1xx_hal.h"
#include "OLED_Font.h"

/* OLED引脚定义（使用软件模拟I2C）*/
#define OLED_SCL_PORT   GPIOB
#define OLED_SDA_PORT   GPIOB
#define OLED_SCL_PIN     GPIO_PIN_8       // I2C时钟引脚（SCL）
#define OLED_SDA_PIN     GPIO_PIN_9       // I2C数据引脚（SDA）

// I2C引脚电平控制宏
#define OLED_SCL_HIGH()  HAL_GPIO_WritePin(OLED_SCL_PORT, OLED_SCL_PIN, GPIO_PIN_SET)
#define OLED_SCL_LOW()   HAL_GPIO_WritePin(OLED_SCL_PORT, OLED_SCL_PIN, GPIO_PIN_RESET)
#define OLED_SDA_HIGH()  HAL_GPIO_WritePin(OLED_SDA_PORT, OLED_SDA_PIN, GPIO_PIN_SET)
#define OLED_SDA_LOW()   HAL_GPIO_WritePin(OLED_SDA_PORT, OLED_SDA_PIN, GPIO_PIN_RESET)

#define I2C_DELAY()      for(volatile uint16_t i=0; i<50; i++)  // I2C时序延时

// OLED的I2C接口初始化函数
void OLED_I2C_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOB_CLK_ENABLE();         // 使能GPIOB时钟

    // 配置I2C引脚为开漏输出模式
    GPIO_InitStruct.Pin = OLED_SCL_PIN | OLED_SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;   // 开漏输出（I2C需要）
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(OLED_SCL_PORT, &GPIO_InitStruct);

    OLED_SCL_HIGH();                     // 初始状态：SCL高电平
    OLED_SDA_HIGH();                     // 初始状态：SDA高电平
}

// I2C起始信号
static void I2C_Start(void)
{
    OLED_SDA_HIGH(); I2C_DELAY();
    OLED_SCL_HIGH(); I2C_DELAY();
    OLED_SDA_LOW();  I2C_DELAY();
    OLED_SCL_LOW();  I2C_DELAY();
}

// I2C停止信号
static void I2C_Stop(void)
{
    OLED_SDA_LOW();  I2C_DELAY();
    OLED_SCL_HIGH(); I2C_DELAY();
    OLED_SDA_HIGH(); I2C_DELAY();
}

// I2C发送一个字节数据
// Data: 要发送的数据（8位）
static void I2C_SendByte(uint8_t Data)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        (Data & 0x80) ? OLED_SDA_HIGH() : OLED_SDA_LOW();  // 先发高位
        I2C_DELAY();
        OLED_SCL_HIGH(); I2C_DELAY();        // 时钟上升沿，从机采样数据
        OLED_SCL_LOW();  I2C_DELAY();
        Data <<= 1;                          // 左移一位，准备下一位
    }
    OLED_SDA_HIGH(); I2C_DELAY();            // 释放数据线（等待应答）
    OLED_SCL_HIGH(); I2C_DELAY();
    OLED_SCL_LOW();  I2C_DELAY();
}

// 向OLED写入命令字节
// Cmd: 命令代码
static void OLED_WriteCmd(uint8_t Cmd)
{
    I2C_Start();
    I2C_SendByte(0x78);                    // OLED设备地址（写模式）
    I2C_SendByte(0x00);                    // 发送命令标志位（0x00表示命令）
    I2C_SendByte(Cmd);                     // 发送命令内容
    I2C_Stop();
}

// 向OLED写入数据字节
// Dat: 要显示的数据
static void OLED_WriteDat(uint8_t Dat)
{
    I2C_Start();
    I2C_SendByte(0x78);                    // OLED设备地址（写模式）
    I2C_SendByte(0x40);                    // 发送数据标志位（0x40表示数据）
    I2C_SendByte(Dat);                     // 发送数据内容
    I2C_Stop();
}

// 设置光标位置（显示坐标）
// Y: 行号（0-7），对应屏幕上的8个页（每页8像素高）
// X: 列号（0-127），对应屏幕上的128列像素点
void OLED_SetCursor(uint8_t Y, uint8_t X)
{
    OLED_WriteCmd(0xB0 | Y);              // 设置页地址（Y轴）
    OLED_WriteCmd(0x10 | (X >> 4));       // 设置列地址高4位
    OLED_WriteCmd(0x00 | (X & 0x0F));     // 设置列地址低4位
}

// 清屏函数（将整个屏幕清空为黑色）
void OLED_Clear(void)
{
    for (uint8_t j = 0; j < 8; j++)        // 遍历8页
    {
        OLED_SetCursor(j, 0);
        for (uint8_t i = 0; i < 128; i++)  // 遍历每页的128列
            OLED_WriteDat(0x00);           // 写入0x00（黑色/熄灭）
    }
}

// 在指定位置显示一个ASCII字符（16x16字体）
// Line:   行号（1-4）
// Column: 列号（1-16）
// Char:   要显示的字符（ASCII码）
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char)
{
    OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8);  // 设置上半部分位置
    for (uint8_t i = 0; i < 8; i++)
        OLED_WriteDat(OLED_F8x16[Char - ' '][i]);       // 写入字符上半部字模

    OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8);  // 设置下半部分位置
    for (uint8_t i = 0; i < 8; i++)
        OLED_WriteDat(OLED_F8x16[Char - ' '][i + 8]);     // 写入字符下半部字模
}

// 在指定位置显示字符串
// Line:   行号（1-4）
// Column: 起始列号（1-16）
// String: 要显示的字符串指针
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String)
{
    while (*String)
        OLED_ShowChar(Line, Column++, *String++);  // 逐个字符显示，列号自动递增
}

// 计算X的Y次方（用于数字显示时的位数计算）
static uint32_t OLED_Pow(uint8_t X, uint8_t Y)
{
    uint32_t Result = 1;
    while (Y--) Result *= X;
    return Result;
}

// 在指定位置显示无符号整数（十进制）
// Line:   行号（1-4）
// Column: 起始列号（1-16）
// Number: 要显示的数字
// Length: 显示的位数（不足补前导空格）
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
    for (uint8_t i = 0; i < Length; i++)
    {
        uint8_t Digit = (Number / OLED_Pow(10, Length - i - 1)) % 10;  // 提取每一位数字
        OLED_ShowChar(Line, Column + i, '0' + Digit);                 // 转换为ASCII并显示
    }
}

// 在指定位置显示有符号整数（带正负号）
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length)
{
    if (Number >= 0)
    {
        OLED_ShowChar(Line, Column, '+');          // 正数显示加号
    }
    else
    {
        OLED_ShowChar(Line, Column, '-');          // 负数显示减号
        Number = -Number;                           // 取绝对值
    }
    for (uint8_t i = 0; i < Length; i++)
    {
        uint8_t Digit = (Number / OLED_Pow(10, Length - i - 1)) % 10;
        OLED_ShowChar(Line, Column + i + 1, '0' + Digit);
    }
}

// 在指定位置显示十六进制数
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
    for (uint8_t i = 0; i < Length; i++)
    {
        uint8_t Digit = (Number / OLED_Pow(16, Length - i - 1)) % 16;
        OLED_ShowChar(Line, Column + i, Digit < 10 ? ('0' + Digit) : ('A' + Digit - 10));
    }
}

// 在指定位置显示二进制数
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
    for (uint8_t i = 0; i < Length; i++)
    {
        uint8_t Digit = (Number / OLED_Pow(2, Length - i - 1)) % 2;
        OLED_ShowChar(Line, Column + i, '0' + Digit);
    }
}

// OLED初始化函数（配置寄存器参数）
void OLED_Init(void)
{
    // 上电延时，等待OLED就绪
    for (volatile uint32_t i = 0; i < 1000; i++)
        for (volatile uint32_t j = 0; j < 1000; j++);

    OLED_I2C_Init();                        // 初始化I2C接口

    // 发送初始化命令序列（SSD1306芯片标准初始化流程）
    OLED_WriteCmd(0xAE);                    // 关闭显示（休眠模式）
    OLED_WriteCmd(0xD5); OLED_WriteCmd(0x80);// 设置显示时钟分频比
    OLED_WriteCmd(0xA8); OLED_WriteCmd(0x3F);// 设置多路复用率（1/64 duty）
    OLED_WriteCmd(0xD3); OLED_WriteCmd(0x00);// 设置显示偏移量
    OLED_WriteCmd(0x40);                    // 设置显示起始行（第0行）
    OLED_WriteCmd(0xA1);                    // 设置段重映射（左右翻转）
    OLED_WriteCmd(0xC8);                    // 设置COM扫描方向（上下翻转）
    OLED_WriteCmd(0xDA); OLED_WriteCmd(0x12);// 设置COM硬件引脚配置
    OLED_WriteCmd(0x81); OLED_WriteCmd(0xCF);// 设置对比度控制
    OLED_WriteCmd(0xD9); OLED_WriteCmd(0xF1);// 设置预充电周期
    OLED_WriteCmd(0xDB); OLED_WriteCmd(0x30);// 设置VCOMH去电平
    OLED_WriteCmd(0xA4);                    // 设置全屏显示输出（非跟随RAM）
    OLED_WriteCmd(0xA6);                    // 设置正常显示（非反色显示）
    OLED_WriteCmd(0x8D); OLED_WriteCmd(0x14);// 使能电荷泵（内置DC-DC）
    OLED_WriteCmd(0xAF);                    // 开启显示（正常工作模式）

    OLED_Clear();                           // 清屏
}
