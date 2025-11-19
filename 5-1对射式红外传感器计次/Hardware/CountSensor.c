#include "stm32f10x.h" 
#include "Delay.h" 
uint16_t CountSensor_Count;

/**
  * @brief  计数器传感器硬件初始化
  * @note   配置PB14引脚为下降沿触发的外部中断，用于脉冲计数检测
  * @param  无
  * @retval 无
  * @warning 需自行实现 EXTI15_10_IRQHandler 中断服务函数处理计数逻辑
  */
void CountSensor_Init(void)
{
    /* 1. 外设时钟使能 ------------------------------------*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  // 使能GPIOB时钟  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   // 使能复用功能时钟（必要中断映射）

    /* 2. GPIO配置 ----------------------------------------*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         // 上拉输入模式（检测高电平->下降沿）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;           // 选择PB14引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     // 高速响应信号变化
    GPIO_Init(GPIOB, &GPIO_InitStructure);                // 应用配置

    /* 3. 中断线映射 --------------------------------------*/
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);  // 绑定PB14到EXTI14

    /* 4. 外部中断配置 ------------------------------------*/
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line14;           // 选择中断线14
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;             // 使能中断线
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;   // 中断模式（非事件）
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; // 上降沿触发（传感器脉冲下降沿计数）
    EXTI_Init(&EXTI_InitStructure);                       // 应用配置

    /* 5. NVIC中断控制器配置 ------------------------------*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);        // 设置优先级分组（2位抢占优先级）
    
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;     // 选择EXTI10-15中断通道
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;          // 使能中断通道
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; // 抢占优先级1
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;       // 子优先级1
    NVIC_Init(&NVIC_InitStruct);                           // 应用配置
}
uint16_t CountSensor_Get(void)
{
	return CountSensor_Count;
}
void EXTI15_10_IRQHandler(void)
	{
		if(EXTI_GetITStatus(EXTI_Line14)==SET)
		{
			Delay_ms(500);
			CountSensor_Count ++;
			EXTI_ClearITPendingBit(EXTI_Line14);
		}
			
	} 
	