#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "KEY.h"
#include "Buzzer.h"
#include "LightSensor.h"
uint8_t a;
int main(void)
{	
	LED_Init();
	Key_Init();
	Key_GetNum();
	Buzzer_Init();
	LightSensor_Init();
	while(1)
	 {	
		 a=Key_GetNum();
		 if(a==1)
		 {
			GPIO_ResetBits(GPIOA,GPIO_Pin_1);
			 Delay_ms(100);
			 GPIO_SetBits(GPIOA,GPIO_Pin_1);
			 Delay_ms(100);
		 }
		 if(a==2)
         {	
			 GPIO_ResetBits(GPIOA,GPIO_Pin_2);
			 Delay_ms(100);
			 GPIO_SetBits(GPIOA,GPIO_Pin_2);
			  Delay_ms(100);
         }
		 if(LightSensor_Get()==1)
		 {
			 Buzzer_OFF();
			
		
		 }else
         {	
			 Buzzer_ON();
			
			
         }
		
	 }
}
