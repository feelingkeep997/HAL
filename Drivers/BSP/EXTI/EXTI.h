#ifndef __EXTI_H
#define __EXTI_H

#include "stm32f1xx_hal.h"

// 外部中断初始化函数（配置PA3引脚为双边沿触发外部中断）
void exti_init(void);

// EXTI3中断服务函数（硬件中断入口）
void EXTI3_IRQHandler(void);

// GPIO外部中断回调函数（HAL库回调，用户在此编写业务逻辑）
// GPIO_Pin: 触发中断的引脚号
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif
