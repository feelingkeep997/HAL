#ifndef __GTIM_H
#define __GTIM_H

#include "stm32f1xx_hal.h"
#include "../Drivers/BSP/OLED/OLED.h"

extern TIM_HandleTypeDef g_timx_cap_handle;
extern volatile uint8_t g_timx_cap_sta;
extern volatile uint16_t g_timx_cap_val;
extern volatile float g_freq_hz;

#define GTIM_TIMX_CAP TIM3
#define GTIM_TIMX_CAP_CHY TIM_CHANNEL_1
#define GTIM_TIMX_CAP_IRQn TIM3_IRQn

#define GTIM_TIMX_CAP_CLK_ENABLE() do { \
    __HAL_RCC_TIM3_CLK_ENABLE(); \
    __HAL_RCC_GPIOA_CLK_ENABLE(); \
} while(0)

#define GTIM_TIMX_CAP_GPIO_PORT GPIOA
#define GTIM_TIMX_CAP_GPIO_PIN GPIO_PIN_6

void gtim_timx_cap_init(uint16_t arr, uint16_t psc);
void TIM3_IRQHandler(void);

#endif