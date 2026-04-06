#include "main.h"
#include "gpio.h"
#include "../Drivers/BSP/LED/LED.h"
#include "../Drivers/BSP/OLED/OLED.h"
#include "../Drivers/BSP/IWDG/IWDG.h"
#include "../Drivers/BSP/delay/delay.h"

// 系统时钟配置函数（配置为72MHz）
void SystemClock_Config(void);

int main(void)
{
    HAL_Init();                           // 初始化HAL库
    SystemClock_Config();                 // 配置系统时钟

    led_init();                           // 初始化LED
    OLED_Init();                          // 初始化OLED显示屏
    delay_init(72);                       // 初始化延时函数（系统时钟72MHz）

    OLED_ShowString(1, 1, "hungry ");     // 显示欢迎信息

    // 初始化独立看门狗
    // 预分频32，重载值1250 → 超时时间 = (1250*32)/40KHz ≈ 1秒
    IWDG_Init(IWDG_PRESCALER_32, 1250);

    while (1)
    {
        IWDG_Feed();                      // 喂狗，防止看门狗复位系统
        delay_ms(10);                     // 延时10ms
        OLED_ShowString(1, 1, "etaing "); // 显示运行状态
    }
}

// 系统时钟配置函数（HSE外部晶振 + PLL倍频 = 72MHz）
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    // 配置振荡器源：使用外部高速晶振（HSE）
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;                    // 使能HSE
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;      // HSE预分频1分频
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;                 // 使能PLL锁相环
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;         // PLL源选择HSE
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;                  // PLL倍频系数9倍（8MHz×9=72MHz）
    
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)         // 配置振荡器
    {
        Error_Handler();                                         // 配置失败进入错误处理
    }

    // 配置系统总线时钟
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;   // 系统时钟源选择PLL输出
    RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;            // AHB总线不分频（72MHz）
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;            // APB1总线2分频（36MHz）
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;            // APB2总线不分频（72MHz）

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)  // 配置时钟树
    {
        Error_Handler();                                         // 配置失败进入错误处理
    }
}

// 错误处理函数（死循环，用于调试定位问题）
void Error_Handler(void)
{
    __disable_irq();                       // 关闭所有中断
    while (1)                             // 死循环，程序卡在这里
    {
    }
}
