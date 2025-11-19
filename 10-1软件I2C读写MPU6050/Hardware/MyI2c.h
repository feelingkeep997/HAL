#ifndef __MYI2C_H
#define __MYI2C_H

void MyI2C_W_SCL(uint8_t BitValue);
void MyI2C_W_SDA(uint8_t BitValue);
uint8_t MyI2C_R_SDA(void);
void MyI2C_Init(void);
void MyI2C_Start(void);
void MyI2C_End(void);
void MyI2c_SendByte(uint16_t Byte);
uint16_t MyI2c_ReceiveByte(void);
void MyI2C_SendAck(uint8_t AckBit);
uint8_t MyI2C_ReceiveAck(void);

#endif
