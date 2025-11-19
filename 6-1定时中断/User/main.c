#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "KEY.h"
#include "OLED.h"
#include "Timer.h"
uint16_t Num;

int main(void)
{	
	LED_Init();
	Key_Init();
	Key_GetNum();
	OLED_Init();
	OLED_ShowString(1,1,"Num:");
	Timer_Init();
//	 uint16_t a=0;
	while(1)
	 {	
//		 a=Numreturn();
		OLED_ShowNum(1,5,Num,5);
		 OLED_ShowNum(2,5,TIM_GetCapture1(TIM2),5);
	 }
}
