#ifndef __KEY_H
#define __KEY_H

#include "stm32f1xx_hal.h"
#include "../../../Inc/main.h"

// 按键初始化函数（配置PA3为输入模式，内部上拉）
void key_init(void);

// 按键扫描函数（支持消抖处理）
// mode: 扫描模式，1=单次扫描（按一次只返回一次），0=连续扫描
// 返回值: 1表示按键被按下，0表示按键未按下
uint8_t key_scan(uint8_t mode);

#endif
