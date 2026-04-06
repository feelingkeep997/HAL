#include "stm32f1xx_hal.h"
#include "WWDG.h"
#include "LED.h"

WWDG_HandleTypeDef g_hwwdg;  // 窗口看门狗句柄

// 窗口看门狗初始化函数
// tr:   计数器初始值（0x40-0x7F）
// wr:   窗口值（0x40-0x7F），必须在窗口内喂狗
// fpre: 预分频系数（WWDG_PRESCALER_1/2/4/8）
void WWDG_Init(uint8_t tr, uint8_t wr, uint32_t fpre)
{
    g_hwwdg.Instance = WWDG;
    g_hwwdg.Init.Counter = tr;             // 设置计数器初始值
    g_hwwdg.Init.Window = wr;              // 设置窗口值
    g_hwwdg.Init.Prescaler = fpre;         // 设置预分频器
    g_hwwdg.Init.EWIMode = WWDG_EWIMODE_ENABLE;  // 使能提前唤醒中断
    HAL_WWDG_Init(&g_hwwdg);               // 初始化窗口看门狗
    HAL_WWDG_Start_IT(&g_hwwdg);           // 启动窗口看门狗并使能中断
}

// 窗口看门狗底层初始化回调函数（配置时钟和中断）
void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg)
{
    __HAL_RCC_WWDG_CLK_ENABLE();           // 使能窗口看门狗时钟
    
    // 配置窗口看门狗中断优先级并使能
    HAL_NVIC_SetPriority(WWDG_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(WWDG_IRQn);
}

// 窗口看门狗中断服务函数
void WWDG_IRQHandler(void)
{
    HAL_WWDG_IRQHandler(&g_hwwdg);          // 调用HAL库中断处理函数
}

// 窗口看门狗提前唤醒回调函数
void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *hwwdg)
{
    HAL_WWDG_Refresh(&g_hwwdg);            // 喂狗，重置计数器
    led_Open();                             // 点亮LED作为提示
}
