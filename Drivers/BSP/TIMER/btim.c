#include "stm32f1xx_hal.h"
#include "btim.h"
#include "../LED/LED.h"

TIM_HandleTypeDef g_htim2;

void btim_init(uint16_t psc, uint16_t arr)
{
    g_htim2.Instance = TIM2;
    g_htim2.Init.Prescaler = psc;       // 设置预分频器值
    g_htim2.Init.Period = arr;           // 设置自动重载值（定时周期）
    g_htim2.Init.CounterMode = TIM_COUNTERMODE_UP;   // 向上计数模式
    g_htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_Base_Init(&g_htim2);         // 初始化定时器基础功能
    
    HAL_TIM_Base_Start_IT(&g_htim2);     // 启动定时器中断模式
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        __HAL_RCC_TIM2_CLK_ENABLE();     // 使能TIM2时钟
        
        // 配置定时器中断优先级并使能
        HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM2_IRQn);
    }
}

// 定时器中断服务函数
void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_htim2);        // 调用HAL库中断处理函数
}

// 定时器周期完成回调函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        LED_close();                     // 定时时间到，关闭LED
    }
}
