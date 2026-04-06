#include "stm32f1xx_hal.h"
#include "IWDG.h"

IWDG_HandleTypeDef g_iwdg_handle;  // 独立看门狗句柄

// 独立看门狗初始化函数
// psc: 预分频系数（IWDG_PRESCALER_4/8/16/32/64/128/256）
// rlr: 重载值（0-4095），决定看门狗超时时间
void IWDG_Init(uint8_t psc, uint8_t rlr)
{
    g_iwdg_handle.Instance = IWDG;
    g_iwdg_handle.Init.Prescaler = psc;   // 设置预分频系数
    g_iwdg_handle.Init.Reload = rlr;       // 设置重载值（决定超时时间）
    HAL_IWDG_Init(&g_iwdg_handle);         // 初始化独立看门狗
}

// 喂狗函数（重置看门狗计数器，防止系统复位）
void IWDG_Feed(void)
{
    HAL_IWDG_Refresh(&g_iwdg_handle);      // 重载计数器，防止超时复位
}
