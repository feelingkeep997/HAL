#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "KEY.h"
#include "OLED.h"
#include "PWM.h"
#include "IC.h"
uint8_t a;
int main(void)
{	
	LED_Init();
	Key_Init();
	Key_GetNum();
	OLED_Init();
	PWM_Init();
	PWM_SetPrescaler(50);
	while(1)
	 {	
		 
	 }
}
