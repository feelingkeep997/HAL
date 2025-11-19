#include "stm32f10x.h"          // Device header
#include "Delay.h"
#include "LED.h"
#include "KEY.h"
#include "OLED.h"
#include "CountSensor.h"
#include "Buzzer.h"
uint16_t a;
int main(void)
{	
	LED_Init();
	Key_Init();
	Key_GetNum();
	OLED_Init();
	CountSensor_Init();
	Buzzer_Init();
	OLED_ShowString(1,1,"Count:");
	a=CountSensor_Get();
	while(1)
	 {	
		OLED_ShowNum(1,7,CountSensor_Get(),5);
	 } 
}
