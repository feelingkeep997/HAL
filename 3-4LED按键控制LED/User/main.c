#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "KEY.h"
uint8_t a;
int main(void)
{	
	LED_Init();
	Key_Init();
	Key_GetNum();
	while(1)
	 {	
		a=Key_GetNum();
		 if(a==1)
		 {
			LED1_turn();
		 }
		 if(a==2)
		 {
			 LED2_turn();
		 }
	 }
}
