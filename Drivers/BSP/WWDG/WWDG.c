#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_uart.h"
#include "WWDG.h"
#include "LED.h"
UART_HandleTypeDef g_huart1;
void WWDG_Init(uint8_t tr, uint8_t wr,uint32_t fpre)
{
    g_hwwdg.Instance = WWDG;
    g_hwwdg.Init.Counter = tr;//tr初始值
    g_hwwdg.Init.Window = wr;//窗口值
    g_hwwdg.Init.Prescaler = fpre;//预分频器
    g_hwwdg.Init.EWIMode = WWDG_EWIMODE_ENABLE;//中断使能
    HAL_WWDG_Start(&g_hwwdg);
}
void WWDG_MspInit(void)
{
    __HAL_RCC_WWDG_CLK_ENABLE();
    HAL_NVIC_SetPriority(WWDG_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(WWDG_IRQn);
}
void WWDG_IRQHandler(void)
{
    HAL_WWDG_IRQHandler(&g_hwwdg);
}
void WWDG_EarltWakeupCallback(void)
{
    HAL_WWDG_Refresh(&g_hwwdg);
   led_Open();
}
