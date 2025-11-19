#include "stm32f10x.h"     // 引入STM32F10x系列标准外设库

// PWM初始化函数（TIM2通道1 @ PA0）
void PWM_Init(void)
{
	/* 时钟使能配置 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);    // 使能APB1总线上的TIM2时钟（定时器属低速外设）
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   // 使能APB2总线上的GPIOA时钟（GPIO属高速外设）
	
	/* GPIO配置（复用推挽输出模式）*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         // 复用推挽输出（PWM信号需通过外设控制引脚）
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;               // 选择PA0引脚（TIM2_CH1默认复用功能[1,3](@ref)）
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       // 高速输出（确保PWM边沿陡峭）
	GPIO_Init(GPIOA, &GPIO_InitStructure);                 // 应用配置到GPIOA端口
	
	/* 定时器时钟源选择 */
	TIM_InternalClockConfig(TIM2);  // 明确使用内部72MHz时钟（默认源，但显式调用增强可读性）
	
	/* 时基单元配置（核心频率与周期设定）*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstructre;
	TIM_TimeBaseInitstructre.TIM_ClockDivision = TIM_CKD_DIV1;      // 时钟分频系数=1（滤波器时钟不分频）
	TIM_TimeBaseInitstructre.TIM_CounterMode = TIM_CounterMode_Up;  // 向上计数模式（PWM标准计数方式）
	TIM_TimeBaseInitstructre.TIM_Period = 100 - 1;                  // 自动重载值ARR（决定PWM周期）
	TIM_TimeBaseInitstructre.TIM_Prescaler = 720 - 1;               // 预分频器PSC（分频后计数频率）
	TIM_TimeBaseInitstructre.TIM_RepetitionCounter = 0;             // 重复计数器（仅高级定时器有效，此处填0）
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitstructre);              // 应用时基配置

	/* 关键频率计算[2,5](@ref)：
	   PWM频率 = 72MHz / (PSC+1) / (ARR+1) 
	           = 72MHz / 720 / 100 
	           = 1kHz
	*/

	/* 输出比较单元配置（PWM波形生成核心）*/
	TIM_OCInitTypeDef TIM_OC1InitStructure;
	TIM_OCStructInit(&TIM_OC1InitStructure);  // 初始化结构体为默认值（避免未定义成员导致异常）
	TIM_OC1InitStructure.TIM_OCMode = TIM_OCMode_PWM1;       // PWM模式1（CNT < CCR时输出有效电平）
	TIM_OC1InitStructure.TIM_OCPolarity = TIM_OCPolarity_High; // 有效电平=高（CNT < CCR时输出高电平）
	TIM_OC1InitStructure.TIM_OutputState = TIM_OutputState_Enable; // 使能通道输出
	TIM_OC1InitStructure.TIM_Pulse = 0;                      // 初始CCR值=0（占空比0%）
	TIM_OC1Init(TIM2, &TIM_OC1InitStructure);                 // 应用配置到TIM2通道1（OC1对应CH1）
	
	/* 高级优化配置（可选但推荐）*/
	TIM_ARRPreloadConfig(TIM2, ENABLE);  // 使能ARR预装载（避免更改周期时产生毛刺[4](@ref)）
	
	/* 启动定时器 */
	TIM_Cmd(TIM2, ENABLE);  // 开始计数并输出PWM
}

/* 设置占空比函数 
   Compare范围：0~100（对应0%~100%占空比） */
void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM2, Compare);  // 修改CCR1寄存器值（直接影响占空比[1](@ref)）
}

/* 设置预分频器（动态调整PWM频率） 
   计算公式：新频率 = 72MHz / (Prescaler+1) / (ARR+1) */
void PWM_SetPrescaler(uint16_t Prescaler)
{
	// 建议改为缓冲更新模式，避免即时生效导致波形抖动[4](@ref)
	TIM_PrescalerConfig(TIM2, Prescaler, TIM_PSCReloadMode_Update); 
}