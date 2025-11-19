#include "stm32f10x.h" 
#include "Delay.h" 
int16_t Encoder_Count;
void Encoder_Init(void)
{
    /* 1. 外设时钟使能 ------------------------------------*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  // 使能GPIOB时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);   // 使能复用功能时钟（必要中断映射）

    /* 2. GPIO配置 ----------------------------------------*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         // 上拉输入模式（检测高电平->下降沿）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 |GPIO_Pin_0;           // 选择PB14引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;     // 高速响应信号变化
    GPIO_Init(GPIOB, &GPIO_InitStructure);                // 应用配置

    /* 3. 中断线映射 --------------------------------------*/
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);  // 绑定PB14到EXTI14
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
	
    /* 4. 外部中断配置 ------------------------------------*/
    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line1;           // 选择中断线14
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;             // 使能中断线
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;   // 中断模式（非事件）
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // 下降沿触发（传感器脉冲下降沿计数）
    EXTI_Init(&EXTI_InitStructure);                       // 应用配置

    /* 5. NVIC中断控制器配置 ------------------------------*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);        // 设置优先级分组（2位抢占优先级）
    
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;     // 选择EXTI10-15中断通道
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;          // 使能中断通道
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; // 抢占优先级1
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;       // 子优先级1
    NVIC_Init(&NVIC_InitStruct);	// 应用配置

	 NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;     // 选择EXTI10-15中断通道
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;          // 使能中断通道
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; // 抢占优先级1
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;       // 子优先级1
    NVIC_Init(&NVIC_InitStruct);  
}
int16_t Encoder_Get(void)
{
	int16_t Temp;
	Temp=Encoder_Count;
	Encoder_Count=0;
	return Temp;
}
/* EXTI0中断服务函数：处理外部中断线0（如PA0/PB0等） */
void EXTI0_IRQHandler(void)
{
    /* 检查EXTI0中断标志位是否被置位 */
    if(EXTI_GetITStatus(EXTI_Line0)==SET)
    {
        /* 二次验证PB0引脚实际电平（防抖动误触发） */
        if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)
        {
            /* 延时消抖：消除机械开关抖动（约100ms）*/
            Delay_ms(100);
            /* 编码器逆时针旋转：计数器递减 */
            Encoder_Count--; 
        }
        /* 清除EXTI0中断挂起标志（防止重复进入中断）[1,2](@ref) */
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}

/* EXTI1中断服务函数：处理外部中断线1（如PA1/PB1等） */
void EXTI1_IRQHandler(void)
{
    /* 检查EXTI1中断标志位是否被置位 */
    if(EXTI_GetITStatus(EXTI_Line1)==SET)
    {
        /* 二次验证PB1引脚实际电平（防抖动误触发） */
        if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
        {
            /* 延时消抖：消除机械开关抖动（约100ms）*/
            Delay_ms(100);
            /* 编码器顺时针旋转：计数器递增 */
            Encoder_Count++;
        }
        /* 清除EXTI1中断挂起标志（防止重复进入中断）[1,2](@ref) */
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}