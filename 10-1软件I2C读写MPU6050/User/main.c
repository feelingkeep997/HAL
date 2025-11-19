#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "Key.h"
#include "MPU6050.h"
#include "MyI2c.h"

uint8_t KeyNum;

int main(void)
{
	OLED_Init();
	MPU6050_Init();
	MPU6050_WriteReg(0x6B,0x00);
	MPU6050_WriteReg(0x19,0x97);
	uint16_t Id=MPU6050_ReadReg(0x19);
	OLED_ShowHexNum(1,1,Id,2);
	/*	
	MyI2C_Start();
	MyI2c_SendByte(0xD0);
	uint16_t Id=MyI2C_ReceiveAck();
	MyI2C_End();
	OLED_ShowNum(1,1,Id,3);*/
	while (1)
	{

	}
}
