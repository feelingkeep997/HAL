#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "KEY.h"
#include "OLED.h"
#include "PWM.h"
#include "Motor.h"
uint8_t a;
int8_t b=50;
int main(void)
{	
	LED_Init();
	Key_Init();
	Key_GetNum();
	OLED_Init();
	PWM_Init();
	Motor_Init();
	Motor_SetSpeed(b);
	while(1)
	{
//			a=Key_GetNum();
//			if(a==1)
//			{
//				b+=30;
//				
//			}	
	}
}
