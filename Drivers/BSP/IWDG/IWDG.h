#ifndef __IWDG_H
#define __IWDG_H

#include "stm32f1xx_hal.h"

extern IWDG_HandleTypeDef g_iwdg_handle;

// 独立看门狗初始化函数
// psc: 预分频系数（IWDG_PRESCALER_4/8/16/32/64/128/256）
// rlr: 重载值（0-4095），决定看门狗超时时间
void IWDG_Init(uint8_t psc, uint8_t rlr);

// 喂狗函数（重置看门狗计数器，防止系统复位）
void IWDG_Feed(void);

#endif
