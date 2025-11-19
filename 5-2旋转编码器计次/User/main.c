#include "stm32f10x.h"          // Device header
#include "Delay.h"
#include "LED.h"
#include "KEY.h"
#include "OLED.h"
#include "CountSensor.h"
#include "Buzzer.h"
#include "Encoder.h"

int16_t a;

int main(void)
{	
	LED_Init();
	Key_Init();
	Key_GetNum();
	OLED_Init();
	CountSensor_Init();
	Buzzer_Init();
	Encoder_Init();
	OLED_ShowString(1,1,"Num:");
	while(1)
	 {	
		 a +=Encoder_Get();
		OLED_ShowSignedNum(1,5,a,5);
	 } 
}
