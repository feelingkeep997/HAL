#include "stm32f1xx_hal.h"
#include "EXTI.h"
#include "../LED/LED.h"

void exti_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;

    // 使能GPIOA时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // 配置按键对应的GPIO引脚（PA3）
    gpio_init_struct.Pin = GPIO_PIN_3;
    gpio_init_struct.Mode = GPIO_MODE_IT_RISING_FALLING;  // 双边沿触发（按下和松开都触发）
    gpio_init_struct.Pull = GPIO_PULLUP;                 // 上拉电阻
    HAL_GPIO_Init(GPIOA, &gpio_init_struct);             // 初始化GPIO
    
    // 设置中断优先级并使能
    HAL_NVIC_SetPriority(EXTI3_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);
}

void EXTI3_IRQHandler(void)//中断服务函数
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);//中断处理公共函数
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)//数据处理回调函数
{
    if(GPIO_Pin == GPIO_PIN_3)
    {
        // 检测按键状态：按下为低电平，松开为高电平
        if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3) == GPIO_PIN_RESET)
        {
            // 按下按键，点亮LED
            led_Open();
        }
        else
        {
            // 松开按键，熄灭LED
            led_close();
        }
    }
}