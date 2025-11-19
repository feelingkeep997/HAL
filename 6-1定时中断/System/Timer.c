#include "stm32f10x.h" 

extern uint16_t Num;

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	//时钟源选择 使用内部时钟源（72MHz主时钟）
	TIM_InternalClockConfig(TIM2);
	
	//时基配置
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstructre;
	TIM_TimeBaseInitstructre.TIM_ClockDivision = TIM_CKD_DIV1;     // 不分频滤波
	TIM_TimeBaseInitstructre.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式
	TIM_TimeBaseInitstructre.TIM_Period = 10000-1;                 // 自动重载值(ARR)
	TIM_TimeBaseInitstructre.TIM_Prescaler = 7200-1;                // 预分频值(PSC)
	
	TIM_TimeBaseInitstructre.TIM_RepetitionCounter = 0;             // 重复计数器(高级定时器专用)
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitstructre);

	//中断配置
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);       // 清除更新标志位
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);  // 使能更新中断

	NVIC_InitTypeDef NVIC_InitTypeDefstructure;
	NVIC_InitTypeDefstructure.NVIC_IRQChannel = TIM2_IRQn;          // TIM2中断通道
	NVIC_InitTypeDefstructure.NVIC_IRQChannelCmd = ENABLE;           // 使能中断
	NVIC_InitTypeDefstructure.NVIC_IRQChannelPreemptionPriority = 2; // 抢占优先级2
	NVIC_InitTypeDefstructure.NVIC_IRQChannelSubPriority = 1;        // 子优先级1
	NVIC_Init(&NVIC_InitTypeDefstructure);
	
	//启动定时器
	TIM_Cmd(TIM2, ENABLE);  // 使能TIM2计数器
}
//uint16_t Numreturn()
//{
//	uint16_t a;
//	a=Num;
//	
//	return a;
//}
void TIM2_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM2,TIM_IT_Update)==SET)
	{
		Num ++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}//中断函数可以放在使用的地方
