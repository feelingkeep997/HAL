#include "stm32f10x.h"  
#include "PWM.h"

void Servo_Init(void)
{
	PWM_Init();
}
void Servo_SetAngle(float Angele)
{
	PWM_SetCompare2(Angele/180*2000+500);
}