#ifndef __EXTI_H
#define __EXTI_H

#include "stm32f1xx_hal.h"

void exti_init(void);
void EXTI3_IRQHandler(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#endif