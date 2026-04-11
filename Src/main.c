

#include "main.h"
#include "gpio.h"
#include <math.h>
#include <stdio.h>
#include "../Drivers/BSP/LED/LED.h"
#include "../Drivers/BSP/KEY/KEY.h"
#include "../Drivers/BSP/EXTI/EXTI.h"
#include "../Drivers/BSP/OLED/OLED.h"
#include "../Drivers/BSP/PWM/PWM.h"
#include "../Drivers/BSP/Delay/Delay.h"
#include "../Drivers/BSP/PWM/GTIM.h"

void SystemClock_Config(void);

int main(void)
{
  // 初始化HAL库
  HAL_Init();

  // 配置系统时钟
  SystemClock_Config();

  // 初始化LED和EXTI
  led_init();
  exti_init(); // 初始化外部中断
  
  // 初始化OLED并显示测试字符
  OLED_Init();
  OLED_ShowString(1, 1, "cwh");
  // 初始化PWM (ARR=499, PSC=71 → TIM2时钟1MHz, PWM频率2kHz)
  gtim_pwn_chy_init(500 - 1, 72 - 1);
  gtim_timx_cap_init(65535 - 1, 71);

  uint16_t pwm_val = 0;
  float angle = 0;
  char freq_str[16];

  while (1)
  {
    sprintf(freq_str, "fx = %.1f", g_freq_hz);
    OLED_ShowString(2, 1, freq_str);

    pwm_val = (uint16_t)(300 * (sin(angle) + 1.0f) / 2.0f);
    __HAL_TIM_SET_COMPARE(&gtim_pwn_chy_handle, TIM_CHANNEL_2, pwm_val);

    angle += 0.05f;
    Delay_ms(20);
  }
}

/**
  * @brief 系统时钟配置
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** 根据指定的参数初始化 RCC 振荡器
  * 在 RCC_OscInitTypeDef 结构中
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** 初始化 CPU、AHB 和 APB 总线时钟
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  发生错误时执行的函数
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* 用户可以添加自己的实现来报告 HAL 错误返回状态 */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
