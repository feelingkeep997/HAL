#ifndef __BTIM_H
#define __BTIM_H

#include "stm32f1xx_hal.h"
#include "../../../Inc/main.h"

// 基本定时器初始化函数
// psc: 预分频器值（0-65535）
// arr: 自动重载值，决定定时周期（0-65535）
void btim_init(uint16_t psc, uint16_t arr);

#endif
