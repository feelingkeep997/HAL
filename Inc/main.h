/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : main.c文件的头文件
  *                   此文件包含应用程序的通用定义（引脚宏定义、函数声明等）
  * @note           由STM32CubeMX自动生成，用户可在USER CODE区域添加自定义内容
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
/* USER CODE END Header */

/* 定义以防止递归包含 -------------------------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* 包含头文件 ----------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* 私有包含 ------------------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* 导出类型 ------------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* 导出常量 ------------------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* 导出宏 --------------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* 导出函数原型 --------------------------------------------------------------*/
// 错误处理函数（当系统发生不可恢复的错误时调用）
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* 私有定义 ------------------------------------------------------------------*/
// LED引脚宏定义（由STM32CubeMX根据配置自动生成）
#define LED_Pin GPIO_PIN_2       // LED使用的GPIO引脚号（PA2）
#define LED_GPIO_Port GPIOA      // LED所在的GPIO端口（GPIOA）

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
