#include "stm32f10x.h"  // 引入STM32F10x系列标准外设库头文件

void IC_Init(void)
{
	/* 时钟使能配置 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  // 使能TIM3时钟（挂载在APB1总线）
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能GPIOA时钟（挂载在APB2总线）
	
	/* GPIO初始化（PA6配置为输入模式）*/
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;        // 上拉输入模式（抗干扰）
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;            // 选择PA6引脚（TIM3_CH1复用功能）
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     // 高速模式（确保快速信号捕获）
	GPIO_Init(GPIOA, &GPIO_InitStructure);                // 应用配置到GPIOA端口[1,3,5](@ref)
	
	/* 定时器时钟源选择 */
	TIM_InternalClockConfig(TIM3);  // 显式选择内部时钟（默认源，增强代码可读性）
	
	/* 时基单元配置（核心频率与测量范围设定）*/
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;     // 时钟分频系数=1（滤波器时钟不分频）
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式
	TIM_TimeBaseInitStructure.TIM_Period = 65536 - 1;               // ARR=65535（最大计数范围）
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;               // PSC=71（72MHz/72 = 1MHz计数频率）
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;            // 高级定时器参数，通用定时器填0
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);             // 应用时基配置[1,4,7](@ref)
	
	/* 输入捕获通道配置 */
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;          // 选择通道1（对应PA6）
	TIM_ICInitStructure.TIM_ICFilter = 0xF;                  // 滤波器等级15（最强滤波，抗信号抖动）
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; // 上升沿触发捕获
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;     // 捕获不分频（每个边沿都触发）
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; // 直连模式（非交叉）
	TIM_ICInit(TIM3, &TIM_ICInitStructure);                   // 应用输入捕获配置[2,4,11](@ref)
	TIM_PWMIConfig(TIM3,&TIM_ICInitStructure);
	
	/* 主从触发模式配置（实现硬件自动复位）*/
	TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);  // 触发源=通道1滤波后信号
	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset); // 从模式=复位模式（上升沿清零CNT）[1,6](@ref)
	
	/* 启动定时器 */
	TIM_Cmd(TIM3, ENABLE);  // 使能TIM3，开始捕获信号
}

/* 频率计算函数（测周法）*/
uint32_t IC_GetFreq(void)
{
	/* 公式：频率 = 标准频率 / 捕获值 
	   PSC配置使计数频率=1MHz（72MHz/(71+1)=1MHz）
	   CCR捕获值N表示两个上升沿间的计数值
	   实际频率 = 1,000,000Hz / (N+1) [6,7](@ref) */
	return 1000000 / (TIM_GetCapture1(TIM3) + 1); 
	
}

uint32_t IC_GetDuty(void)
{
	return (TIM_GetCapture2(TIM3) + 1) * 100 / (TIM_GetCapture1(TIM3) + 1);
}	
