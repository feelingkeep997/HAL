#include "LED.h"
#include "stm32f1xx_hal.h"

// LED初始化
void led_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;

    // 使能GPIOA时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // 配置LED对应的GPIO引脚
    gpio_init_struct.Pin = LED;
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;  // 推挽输出
    gpio_init_struct.Pull = GPIO_NOPULL;          // 无上下拉
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW; // 低速

    // 初始化GPIO
    HAL_GPIO_Init(LED_GPIO_Port, &gpio_init_struct);

    // 设置初始状态为低电平（LED关闭）
    HAL_GPIO_WritePin(LED_GPIO_Port, LED, GPIO_PIN_RESET);
}

// LED关闭（低电平熄灭）
void led_close(void)
{
    HAL_GPIO_WritePin(LED_GPIO_Port, LED, GPIO_PIN_RESET);
}

// LED打开（高电平点亮）
void led_Open(void)
{
    HAL_GPIO_WritePin(LED_GPIO_Port, LED, GPIO_PIN_SET);
}