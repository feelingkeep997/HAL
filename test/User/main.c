#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "KEY.h"
#include "OLED.h"
#include "Serial.h"
#include "MyRTC.h"

uint8_t a;


int main(void)
{	
	OLED_Init();
	Key_Init();
	/*LED_Init();
	
	Key_GetNum();
	
	Serial_Init();
	OLED_ShowString(1,3,"aaa");
	Serial_SendByte(0x41);
	*/
	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP,ENABLE);
//	
//	PWR_BackupAccessCmd(ENABLE);
//	BKP_WriteBackupRegister(BKP_DR1,0x1233);
//	OLED_ShowHexNum(1,1,BKP_ReadBackupRegister(BKP_DR1),4);
		//MyRTC_Init();
	OLED_ShowString(1,1,"hello");
	
	if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST)==SET)
		{
		OLED_ShowString(2,1,"IDogRES");
		Delay_ms(600);
		OLED_ShowString(2, 1, "       ");
		Delay_ms(200);
		RCC_ClearFlag();
		}
		else
		{
		OLED_ShowString(3,1,"RST");
		Delay_ms(200);
		OLED_ShowString(3, 1, "       ");
		Delay_ms(600);
		}
		

/*
			if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == SET)	//如果是独立看门狗复位
	{
		OLED_ShowString(2, 1, "IWDGRST");			//OLED闪烁IWDGRST字符串
		Delay_ms(500);
		OLED_ShowString(2, 1, "       ");
		Delay_ms(100);
		
		RCC_ClearFlag();							//清除标志位
	}
	else											//否则，即为其他复位
	{
		OLED_ShowString(3, 1, "RST");				//OLED闪烁RST字符串
		Delay_ms(500);
		OLED_ShowString(3, 1, "   ");
		Delay_ms(100);
	}
		*/

 IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
 IWDG_SetPrescaler(IWDG_Prescaler_16);
 IWDG_SetReload(2499);
 IWDG_ReloadCounter();
 IWDG_Enable();
 //IWDG_GetFlagStatus( );
	

	
	
	while(1)
	{
		Key_GetNum();
		
		IWDG_ReloadCounter();
		OLED_ShowString(4,1,"FEED");
		Delay_ms(500);
		
		OLED_ShowString(4,1,"    ");Delay_ms(200);
	 }
}