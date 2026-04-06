#ifndef __LED_H
#define __LED_H

#include "stm32f1xx_hal.h"
#include "../../../Inc/main.h"

// LED引脚宏定义（使用CubeMX生成的引脚定义）
#define LED LED_Pin

// LED初始化函数（配置GPIO为推挽输出模式，初始状态为熄灭）
void led_init(void);

// 关闭LED函数（输出低电平，LED熄灭）
void led_close(void);

// 打开LED函数（输出高电平，LED点亮）
void led_Open(void);

#endif
