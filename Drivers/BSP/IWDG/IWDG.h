#ifndef __IWDG_H
#define __IWDG_H

#include "stm32f1xx_hal.h"

extern IWDG_HandleTypeDef g_iwdg_handle;

void IWDG_Init(uint8_t psc, uint8_t rlr);
void IWDG_Feed(void);

#endif
