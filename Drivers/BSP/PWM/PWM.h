#ifndef __PWM_H
#define __PWM_H

#include "stm32f1xx_hal.h"

extern TIM_HandleTypeDef gtim_pwn_chy_handle;
extern TIM_OC_InitTypeDef timx_oc_pwm_chy;

void gtim_pwn_chy_init(uint16_t arr, uint16_t psc);
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim);

#endif
