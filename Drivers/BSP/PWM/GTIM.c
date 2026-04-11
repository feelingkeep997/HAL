#include "GTIM.h"
#include "../Drivers/BSP/OLED/OLED.h"
// 定时器输入捕获句柄和配置结构体
TIM_HandleTypeDef g_timx_cap_handle;
TIM_IC_InitTypeDef g_timx_ic_init;

// 捕获状态标志位 (bit7:捕获完成标志, bit6:捕获到第一个上升沿标志)
volatile uint8_t g_timx_cap_sta = 0;
volatile uint16_t g_timx_cap_val = 0;      // 两次捕获值之差
volatile uint16_t g_timx_cap_val1 = 0;      // 第一次捕获的值
volatile uint16_t g_timx_cap_val2 = 0;      // 第二次捕获的值
volatile float g_freq_hz = 0.0f;            // 计算得到的频率值(Hz)

/**
 * @brief  通用定时器输入捕获初始化
 * @param  arr: 自动重装载值
 * @param  psc: 预分频系数
 * @note   配置为上升沿触发，测量输入信号的频率
 */
void gtim_timx_cap_init(uint16_t arr, uint16_t psc)
{
    GTIM_TIMX_CAP_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GTIM_TIMX_CAP_GPIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GTIM_TIMX_CAP_GPIO_PORT, &GPIO_InitStruct);

    g_timx_cap_handle.Instance = GTIM_TIMX_CAP;
    g_timx_cap_handle.Init.Prescaler = psc;
    g_timx_cap_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    g_timx_cap_handle.Init.Period = arr;
    HAL_TIM_IC_Init(&g_timx_cap_handle);

    g_timx_ic_init.ICPolarity = TIM_ICPOLARITY_RISING;
    g_timx_ic_init.ICSelection = TIM_ICSELECTION_DIRECTTI;
    g_timx_ic_init.ICPrescaler = TIM_ICPSC_DIV1;
    g_timx_ic_init.ICFilter = 0;
    HAL_TIM_IC_ConfigChannel(&g_timx_cap_handle, &g_timx_ic_init, GTIM_TIMX_CAP_CHY);

    HAL_NVIC_SetPriority(GTIM_TIMX_CAP_IRQn, 1, 3);
    HAL_NVIC_EnableIRQ(GTIM_TIMX_CAP_IRQn);

    HAL_TIM_IC_Start_IT(&g_timx_cap_handle, GTIM_TIMX_CAP_CHY);
}

/**
 * @brief  定时器3中断服务函数
 * @note   统一调用HAL库的中断处理函数
 */
void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_timx_cap_handle);
}

/**
 * @brief  定时器输入捕获中断回调函数
 * @param  *htim: 定时器句柄指针
 * @note   实现频率测量: 通过测量两个上升沿之间的时间间隔来计算频率
 *         状态机: 等待第一个上升沿(bit6置位) -> 等待第二个上升沿 -> 计算频率(bit7置位)
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == GTIM_TIMX_CAP)
    {
        // 检查是否未完成捕获(bit7=0表示未完成)
        if ((g_timx_cap_sta & 0x80) == 0)
        {
            // 检查是否已捕获到第一个上升沿(bit6=1)
            if (g_timx_cap_sta & 0x40)
            {
                // 读取第二次捕获值
                g_timx_cap_val2 = HAL_TIM_ReadCapturedValue(&g_timx_cap_handle, GTIM_TIMX_CAP_CHY);

                // 计算两次捕获值的差值(考虑计数器溢出情况)
                if (g_timx_cap_val2 >= g_timx_cap_val1)
                {
                    // 未发生溢出，直接相减
                    g_timx_cap_val = g_timx_cap_val2 - g_timx_cap_val1;
                }
                else
                {
                    // 发生溢出，计算补偿
                    g_timx_cap_val = (g_timx_cap_handle.Init.Period + 1 - g_timx_cap_val1) + g_timx_cap_val2;
                }

                // 计算输入信号的频率
                // STM32F1: APB1 定时器时钟 = PCLK1 * 2 (因为 APB1 prescaler != 1)
                uint32_t timer_clock = HAL_RCC_GetPCLK1Freq() * 2;
                g_freq_hz = (float)timer_clock / (float)(g_timx_cap_handle.Init.Prescaler + 1) / (float)g_timx_cap_val;
                OLED_ShowNum(3, 1, g_timx_cap_val, 5);
                g_timx_cap_sta |= 0x80;
                g_timx_cap_sta &= ~0x40;
            }
            else
            {
                // 捕获第一个上升沿
                g_timx_cap_val1 = HAL_TIM_ReadCapturedValue(&g_timx_cap_handle, GTIM_TIMX_CAP_CHY);
                // 标记已捕获到第一个上升沿(bit6=1)
                g_timx_cap_sta |= 0x40;
            }
        }
    }
}