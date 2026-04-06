/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   此文件提供所有使用的GPIO引脚的配置代码
  * @note    由STM32CubeMX自动生成，包含LED等外设引脚的初始化配置
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* 包含头文件 ----------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* 配置 GPIO                                                               */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** GPIO初始化函数（由main.c调用）
        * 支持以下模式：
        *   - 模拟模式（用于ADC采集）
        *   - 输入模式（浮空/上拉/下拉）
        *   - 输出模式（推挽/开漏）
        *   - 复用功能模式（用于外设引脚复用）
        *   - 外部中断/事件输出模式
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* 使能GPIO端口时钟 */
  __HAL_RCC_GPIOC_CLK_ENABLE();     // 使能GPIOC时钟（PC14/PC15: LSE晶振引脚）
  __HAL_RCC_GPIOD_CLK_ENABLE();     // 使能GPIOD时钟（PD0/PD1: HSE晶振引脚）
  __HAL_RCC_GPIOA_CLK_ENABLE();     // 使能GPIOA时钟（PA2: LED引脚）

  /* 设置LED引脚初始输出电平为低电平（LED熄灭状态）*/
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /* 配置LED引脚参数：推挽输出模式、无上下拉、低速 */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;      // 推挽输出模式
  GPIO_InitStruct.Pull = GPIO_NOPULL;              // 无内部上下拉电阻
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;     // 低速输出（LED不需要高速）
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct); // 初始化LED对应的GPIO

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
