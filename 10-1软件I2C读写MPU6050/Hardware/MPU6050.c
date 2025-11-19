#include "stm32f10x.h"                  // Device header
#include "MyI2c.h" 
#include "Delay.h" 

#define MPU6050_ADDRESS 0xD0

void MPU6050_WriteReg(uint8_t RegAddress,uint8_t Data)
{
	MyI2C_Start();
	MyI2c_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2c_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	MyI2c_SendByte(Data);
	MyI2C_ReceiveAck();
	MyI2C_End();
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
	uint8_t Data;
	
	MyI2C_Start();
	MyI2c_SendByte(MPU6050_ADDRESS);
	MyI2C_ReceiveAck();
	MyI2c_SendByte(RegAddress);
	MyI2C_ReceiveAck();
	
	MyI2C_Start();
	MyI2c_SendByte(MPU6050_ADDRESS|0x01);
	MyI2C_ReceiveAck();
	Data=MyI2c_ReceiveByte();
	MyI2C_SendAck(1);//0表示应答，1表示非应答，在读的时候最后才发生ack
	MyI2C_End();
	
	return Data;
}

void MPU6050_Init(void) {
    MyI2C_Init();
    Delay_ms(100); // 上电延时，非常重要[6](@ref)

    // 关键步骤：清除睡眠位，唤醒传感器
    MPU6050_WriteReg(0x6B, 0x00);
    Delay_ms(100); // 等待传感器稳定
}
