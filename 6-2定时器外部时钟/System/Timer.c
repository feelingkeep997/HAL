#include "stm32f10x.h" 

extern uint16_t Num;

/**
 * @brief 初始化TIM2定时器并配置外部时钟模式2（ETR引脚输入）
 * @note  使用PA0引脚（TIM2_ETR）作为外部时钟源，启用定时器更新中断
 * @param 无
 * @retval 无
 */
void Timer_Init(void)
{
    /* 1. 外设时钟使能 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); // 启用TIM2时钟（APB1总线）
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 启用GPIOA时钟（APB2总线）

    /* 2. 配置PA0引脚（TIM2_ETR功能）*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;      // 上拉输入模式（因ETR为信号输入）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;          // 选择PA0引脚（TIM2_ETR映射引脚）
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   // 高速模式确保信号采集稳定
    GPIO_Init(GPIOA, &GPIO_InitStructure);              // 应用GPIO配置

    /* 3. 配置TIM2外部时钟模式 */
    // 参数说明：
    // TIM2: 定时器2
    // TIM_ExtTRGPSC_OFF: 外部触发预分频器关闭（1分频）
    // TIM_ExtTRGPolarity_NonInverted: ETR上升沿有效
    // 0x00: 外部触发滤波器关闭（不滤波）
    TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x00);

    /* 4. 配置定时器时基参数 */
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstructre;
    TIM_TimeBaseInitstructre.TIM_ClockDivision = TIM_CKD_DIV1;     // 时钟分频系数=1
    TIM_TimeBaseInitstructre.TIM_CounterMode = TIM_CounterMode_Up;  // 向上计数模式
    TIM_TimeBaseInitstructre.TIM_Period = 10 - 1;                  // 自动重装载值ARR=9
    TIM_TimeBaseInitstructre.TIM_Prescaler = 1 - 1;                // 预分频器PSC=0（时钟不分频）
    TIM_TimeBaseInitstructre.TIM_RepetitionCounter = 0;            // 重复计数器（高级定时器专用）
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitstructre);             // 应用时基配置

    /* 5. 中断配置 */
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);               // 清除更新中断标志位
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);          // 使能定时器更新中断

    /* 6. NVIC中断控制器配置 */
    NVIC_InitTypeDef NVIC_InitTypeDefstructure;
    NVIC_InitTypeDefstructure.NVIC_IRQChannel = TIM2_IRQn;         // TIM2全局中断
    NVIC_InitTypeDefstructure.NVIC_IRQChannelCmd = ENABLE;         // 使能中断通道
    NVIC_InitTypeDefstructure.NVIC_IRQChannelPreemptionPriority = 2; // 抢占优先级2
    NVIC_InitTypeDefstructure.NVIC_IRQChannelSubPriority = 1;      // 子优先级1
    NVIC_Init(&NVIC_InitTypeDefstructure);                         // 应用NVIC配置

    /* 7. 启动定时器 */
    TIM_Cmd(TIM2, ENABLE);  // 使能TIM2计数器
}
uint16_t Timer_GetCounter()
{
	
	return TIM_GetCounter(TIM2);
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
