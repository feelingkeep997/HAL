#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f1xx_hal.h"

// 延时初始化函数
// sysclk: 系统时钟频率（单位：MHz）
void delay_init(uint16_t sysclk);

// 微秒级延时函数
// nus: 需要延时的微秒数
void delay_us(uint32_t nus);

// 毫秒级延时函数
// nms: 需要延时的毫秒数
void delay_ms(uint16_t nms);

#endif
