#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "KEY.h"
#include "OLED.h"
#include "PWM.h"
#include "Ic.h"
#include "AD.h"
uint8_t a;
int main(void)
{	
	LED_Init();
	Key_Init();
	Key_GetNum();
	OLED_Init();
	PWM_Init();
	IC_Init();
	AD_Init();
	OLED_ShowString(1, 1, "ADValue:");
	while(1)
	 {	
		 a=AD_GetValue();
		 OLED_ShowNum(1, 9, a, 4);
	 }
}
