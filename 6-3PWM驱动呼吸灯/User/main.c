#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "KEY.h"
#include "OLED.h"
#include "PWM.h"
uint8_t a;
int main(void)
{	
	LED_Init();
	Key_Init();
	Key_GetNum();
	OLED_Init();
	PWM_Init();
	while(1)
	 {	
		 for(int i =0;i<100;i++)
	{
			PWM_SetCompare1(i);
			Delay_ms(10);
	}
			 for(int i =0;i<100;i++)
	{
			PWM_SetCompare1(100-i);
			Delay_ms(10);
	}
	 }
}
