#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "KEY.h"
#include "OLED.h"
#include "PWM.h"
#include "Servo.h"
uint8_t a;
float Angle;
int main(void)
{	
	LED_Init();
	Key_Init();
	Key_GetNum();
	OLED_Init();
	PWM_Init();
	Servo_Init();
	OLED_ShowString(1,1,"Angle:");
	
	while(1)
	 {	
		a= Key_GetNum();
		 if(a==1)
		 {
			 Angle+=30;
			  if(Angle==180)
		 {
				Angle=0;
			 
		 }
		 }
		 Servo_SetAngle(Angle);
		 OLED_ShowNum(1,7,Angle,3);
	 }
}
