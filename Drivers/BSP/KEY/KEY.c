#include "stm32f1xx_hal.h"

// 按键引脚读取宏定义
#define KEY HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)

// 按键初始化
void key_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;

    // 使能GPIOA时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // 配置按键对应的GPIO引脚
    gpio_init_struct.Pin = GPIO_PIN_3;
    gpio_init_struct.Mode = GPIO_MODE_INPUT;      // 输入模式
    gpio_init_struct.Pull = GPIO_PULLUP;          // 上拉
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH; // 高速
    HAL_GPIO_Init(GPIOA, &gpio_init_struct);
}

// 按键扫描函数
// mode: 1为单次扫描，0为连续扫描
// 返回值: 1表示按键按下，0表示未按下
uint8_t key_scan(uint8_t mode)
{
    static uint8_t key_up = 1;  // 按键释放标志
    uint8_t keyval = 0;

    if (mode)
        key_up = 1;  // 支持单次按压

    // 当按键释放且按键被按下
    if (key_up && (KEY == 0))
    {
        HAL_Delay(10);  // 消抖延迟
        key_up = 0;

        if (KEY == 0)
            keyval = 1;
    }
    // 如果按键释放，更新状态
    else if (KEY == 1)
    {
        key_up = 1;
    }

    return keyval;  // 返回按键值
}