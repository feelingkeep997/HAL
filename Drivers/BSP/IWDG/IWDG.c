#include "stm32f1xx_hal.h"
#include "IWDG.h"

IWDG_HandleTypeDef g_iwdg_handle;   /* 独立看门狗句柄 */

void IWDG_Init(uint8_t psc, uint8_t rlr)
{
    g_iwdg_handle.Instance = IWDG;
    g_iwdg_handle.Init.Prescaler = psc; /* 设置IWDG分频系数 */
    g_iwdg_handle.Init.Reload = rlr;     /* 重装载值 */
    HAL_IWDG_Init(&g_iwdg_handle);       /* 初始化IWDG并启动 */
}

void IWDG_Feed(void)
{
    HAL_IWDG_Refresh(&g_iwdg_handle); /* 重装载计数器 */
}