#ifndef __KEY_H
#define __KEY_H

#include "stm32f1xx_hal.h"
#include "../../../Inc/main.h"

void key_init(void);
uint8_t key_scan(uint8_t mode);


#endif
