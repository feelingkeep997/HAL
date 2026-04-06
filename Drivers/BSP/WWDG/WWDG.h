#ifndef __WWDG_H
#define __WWDG_H

#include "stm32f1xx_hal.h"

// 窗口看门狗初始化函数
// tr:   计数器初始值（0x40-0x7F）
// wr:   窗口值（0x40-0x7F），必须在窗口内喂狗
// fpre: 预分频系数（WWDG_PRESCALER_1/2/4/8）
void WWDG_Init(uint8_t tr, uint8_t wr, uint32_t fpre);

#endif
