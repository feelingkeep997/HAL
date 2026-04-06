#ifndef __LED_H
#define __LED_H

#include "stm32f1xx_hal.h"
#include "../../../Inc/main.h"

#define LED LED_Pin

void led_init(void);
void led_close(void);
void led_Open(void);

#endif
