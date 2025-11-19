#include "stm32f10x.h"     
void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//时钟源选择 使用内部时钟源（72MHz主时钟）
	TIM_InternalClockConfig(TIM2);
	
	//时基配置
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstructre;
	TIM_TimeBaseInitstructre.TIM_ClockDivision = TIM_CKD_DIV1;     // 不分频滤波
	TIM_TimeBaseInitstructre.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式
	TIM_TimeBaseInitstructre.TIM_Period = 100-1;                 // 自动重载值(ARR)
	TIM_TimeBaseInitstructre.TIM_Prescaler = 36-1;                // 预分频值(PSC)
	TIM_TimeBaseInitstructre.TIM_RepetitionCounter = 0;             // 重复计数器(高级定时器专用)
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitstructre);

	TIM_OCInitTypeDef TIM_OC1InitStructure;
	TIM_OCStructInit(&TIM_OC1InitStructure);
	TIM_OC1InitStructure.TIM_OCMode=TIM_OCMode_PWM1 ;
	TIM_OC1InitStructure.TIM_OCPolarity= TIM_OCPolarity_High;
	TIM_OC1InitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC1InitStructure.TIM_Pulse=50;//CCR
	TIM_OC1Init(TIM2,&TIM_OC1InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
	
}
void PWM_SetCompare3(uint16_t Compare)
{
		TIM_SetCompare3(TIM2,Compare);
}