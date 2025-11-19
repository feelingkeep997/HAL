#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "Key.h"
uint64_t k=0;
int main(void)
{
	OLED_Init();
	Key_Init();
	Serial_Init();
	
/*	Serial_SendByte(0x41);
	
	uint8_t MyArray[] = {0x42, 0x43, 0x44, 0x45};
	Serial_SendArray(MyArray, 4);
	
	Serial_SendString("\r\nNum1=");
	
	Serial_SendNumber(111, 3);
	
	printf("\r\nNum2=%d", 222);
	
	char String[100];
	sprintf(String, "\r\nNum3=%d", 333);
	Serial_SendString(String);
	
	Serial_Printf("\r\nNum4=%d", 444);
	Serial_Printf("\r\n");
	Rx=Serial_Rxdate();*/
	
	Serial_TxPacket[0]=0x01;
	Serial_TxPacket[1]=0x02;
	Serial_TxPacket[2]=0x03;
	Serial_TxPacket[3]=0x04;
	Serial_SendPacket();
	
	
	 
	while (1)
	{
		k=0;
		k=Key_GetNum();
		USART1_IRQHandler();
		if(k==1){
			
			OLED_ShowHexNum(4, 1, Serial_RxPacket[0], 2);
			OLED_ShowHexNum(4, 4, Serial_RxPacket[1], 2);
			OLED_ShowHexNum(4, 7, Serial_RxPacket[2], 2);
			OLED_ShowHexNum(4, 10, Serial_RxPacket[3], 2);}
		
		//OLED_ShowHexNum(1,1,Rx,2);
		
	}
}
