#include "stm32f1xx_hal.h"
#include "OLED_Font.h"

/*引脚定义*/
#define OLED_SCL_PORT   GPIOB
#define OLED_SDA_PORT  GPIOB
#define OLED_SCL_PIN   GPIO_PIN_8
#define OLED_SDA_PIN   GPIO_PIN_9

#define OLED_SCL_HIGH()    HAL_GPIO_WritePin(OLED_SCL_PORT, OLED_SCL_PIN, GPIO_PIN_SET)
#define OLED_SCL_LOW()     HAL_GPIO_WritePin(OLED_SCL_PORT, OLED_SCL_PIN, GPIO_PIN_RESET)
#define OLED_SDA_HIGH()    HAL_GPIO_WritePin(OLED_SDA_PORT, OLED_SDA_PIN, GPIO_PIN_SET)
#define OLED_SDA_LOW()     HAL_GPIO_WritePin(OLED_SDA_PORT, OLED_SDA_PIN, GPIO_PIN_RESET)

#define I2C_DELAY()  for(volatile uint16_t i=0; i<50; i++)

void OLED_I2C_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Pin = OLED_SCL_PIN | OLED_SDA_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(OLED_SCL_PORT, &GPIO_InitStruct);

    OLED_SCL_HIGH();
    OLED_SDA_HIGH();
}

static void I2C_Start(void)
{
    OLED_SDA_HIGH(); I2C_DELAY();
    OLED_SCL_HIGH(); I2C_DELAY();
    OLED_SDA_LOW();  I2C_DELAY();
    OLED_SCL_LOW();  I2C_DELAY();
}

static void I2C_Stop(void)
{
    OLED_SDA_LOW();  I2C_DELAY();
    OLED_SCL_HIGH(); I2C_DELAY();
    OLED_SDA_HIGH(); I2C_DELAY();
}

static void I2C_SendByte(uint8_t Data)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        (Data & 0x80) ? OLED_SDA_HIGH() : OLED_SDA_LOW();
        I2C_DELAY();
        OLED_SCL_HIGH(); I2C_DELAY();
        OLED_SCL_LOW();  I2C_DELAY();
        Data <<= 1;
    }
    OLED_SDA_HIGH(); I2C_DELAY();
    OLED_SCL_HIGH(); I2C_DELAY();
    OLED_SCL_LOW();  I2C_DELAY();
}

static void OLED_WriteCmd(uint8_t Cmd)
{
    I2C_Start();
    I2C_SendByte(0x78);
    I2C_SendByte(0x00);
    I2C_SendByte(Cmd);
    I2C_Stop();
}

static void OLED_WriteDat(uint8_t Dat)
{
    I2C_Start();
    I2C_SendByte(0x78);
    I2C_SendByte(0x40);
    I2C_SendByte(Dat);
    I2C_Stop();
}

void OLED_SetCursor(uint8_t Y, uint8_t X)
{
    OLED_WriteCmd(0xB0 | Y);
    OLED_WriteCmd(0x10 | (X >> 4));
    OLED_WriteCmd(0x00 | (X & 0x0F));
}

void OLED_Clear(void)
{
    for (uint8_t j = 0; j < 8; j++)
    {
        OLED_SetCursor(j, 0);
        for (uint8_t i = 0; i < 128; i++)
            OLED_WriteDat(0x00);
    }
}

void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char)
{
    OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8);
    for (uint8_t i = 0; i < 8; i++)
        OLED_WriteDat(OLED_F8x16[Char - ' '][i]);

    OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8);
    for (uint8_t i = 0; i < 8; i++)
        OLED_WriteDat(OLED_F8x16[Char - ' '][i + 8]);
}

void OLED_ShowString(uint8_t Line, uint8_t Column, char *String)
{
    while (*String)
        OLED_ShowChar(Line, Column++, *String++);
}

static uint32_t OLED_Pow(uint8_t X, uint8_t Y)
{
    uint32_t Result = 1;
    while (Y--) Result *= X;
    return Result;
}

void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
    for (uint8_t i = 0; i < Length; i++)
    {
        uint8_t Digit = (Number / OLED_Pow(10, Length - i - 1)) % 10;
        OLED_ShowChar(Line, Column + i, '0' + Digit);
    }
}

void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length)
{
    if (Number >= 0)
    {
        OLED_ShowChar(Line, Column, '+');
    }
    else
    {
        OLED_ShowChar(Line, Column, '-');
        Number = -Number;
    }
    for (uint8_t i = 0; i < Length; i++)
    {
        uint8_t Digit = (Number / OLED_Pow(10, Length - i - 1)) % 10;
        OLED_ShowChar(Line, Column + i + 1, '0' + Digit);
    }
}

void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
    for (uint8_t i = 0; i < Length; i++)
    {
        uint8_t Digit = (Number / OLED_Pow(16, Length - i - 1)) % 16;
        OLED_ShowChar(Line, Column + i, Digit < 10 ? ('0' + Digit) : ('A' + Digit - 10));
    }
}

void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
    for (uint8_t i = 0; i < Length; i++)
    {
        uint8_t Digit = (Number / OLED_Pow(2, Length - i - 1)) % 2;
        OLED_ShowChar(Line, Column + i, '0' + Digit);
    }
}

void OLED_Init(void)
{
    for (volatile uint32_t i = 0; i < 1000; i++)
        for (volatile uint32_t j = 0; j < 1000; j++);

    OLED_I2C_Init();

    OLED_WriteCmd(0xAE);
    OLED_WriteCmd(0xD5); OLED_WriteCmd(0x80);
    OLED_WriteCmd(0xA8); OLED_WriteCmd(0x3F);
    OLED_WriteCmd(0xD3); OLED_WriteCmd(0x00);
    OLED_WriteCmd(0x40);
    OLED_WriteCmd(0xA1);
    OLED_WriteCmd(0xC8);
    OLED_WriteCmd(0xDA); OLED_WriteCmd(0x12);
    OLED_WriteCmd(0x81); OLED_WriteCmd(0xCF);
    OLED_WriteCmd(0xD9); OLED_WriteCmd(0xF1);
    OLED_WriteCmd(0xDB); OLED_WriteCmd(0x30);
    OLED_WriteCmd(0xA4);
    OLED_WriteCmd(0xA6);
    OLED_WriteCmd(0x8D); OLED_WriteCmd(0x14);
    OLED_WriteCmd(0xAF);

    OLED_Clear();
}
