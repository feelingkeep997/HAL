#include "PWM.h"

TIM_HandleTypeDef gtim_pwn_chy_handle;
TIM_OC_InitTypeDef timx_oc_pwm_chy;

void gtim_pwn_chy_init(uint16_t arr, uint16_t psc)
{
    gtim_pwn_chy_handle.Instance = TIM2;
    gtim_pwn_chy_handle.Init.Period = arr;
    gtim_pwn_chy_handle.Init.Prescaler = psc;
    gtim_pwn_chy_handle.Init.CounterMode = TIM_COUNTERMODE_UP;

    HAL_TIM_PWM_Init(&gtim_pwn_chy_handle);

    timx_oc_pwm_chy.Pulse = arr / 2;
    timx_oc_pwm_chy.OCMode = TIM_OCMODE_PWM1;
    timx_oc_pwm_chy.OCPolarity = TIM_OCPOLARITY_HIGH; // 共阴极：高电平点亮，占空比越大越亮
    HAL_TIM_PWM_ConfigChannel(&gtim_pwn_chy_handle, &timx_oc_pwm_chy, TIM_CHANNEL_2);

    HAL_TIM_PWM_Start(&gtim_pwn_chy_handle, TIM_CHANNEL_2);
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        __TIM2_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_AFIO_CLK_ENABLE();

        GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Pin = GPIO_PIN_3;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

        // PB3默认是JTDO引脚，需要关闭JTAG才能作为普通或复用IO使用 (保留SWD供下载)
        __HAL_AFIO_REMAP_SWJ_NOJTAG();
        __HAL_AFIO_REMAP_TIM2_PARTIAL_1();
    }
}
