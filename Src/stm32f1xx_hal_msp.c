/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file         stm32f1xx_hal_msp.c
  * @brief        此文件提供MSP（MCU Support Package）初始化和去初始化代码
  * @note         MSP层是HAL库与底层硬件之间的桥梁，负责时钟使能、GPIO配置、中断配置等
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

/* 包含头文件 ----------------------------------------------------------------*/
#include "main.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* 私有类型定义 -------------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* 私有定义 ------------------------------------------------------------------*/
/* USER CODE BEGIN Define */

/* USER CODE END Define */

/* 私有宏 --------------------------------------------------------------------*/
/* USER CODE BEGIN Macro */

/* USER CODE END Macro */

/* 私有变量 ------------------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* 私有函数原型 -------------------------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* 外部函数 ------------------------------------------------------------------*/
/* USER CODE BEGIN ExternalFunctions */

/* USER CODE END ExternalFunctions */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  全局MSP初始化函数（在HAL_Init()中被调用）
  *         负责系统级的底层硬件初始化，包括：
  *         - 复用功能时钟（AFIO）使能
  *         - 电源管理（PWR）时钟使能
  *         - NVIC中断优先级分组设置
  *         - JTAG/SWD调试接口重映射配置
  */
void HAL_MspInit(void)
{
  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  __HAL_RCC_AFIO_CLK_ENABLE();   // 使能AFIO复用功能时钟（用于引脚重映射和中断配置）
  __HAL_RCC_PWR_CLK_ENABLE();     // 使能PWR电源控制时钟

  // 设置NVIC中断优先级分组：抢占优先级2位，子优先级2位
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_2);

  /* 系统中断初始化*/

  /** NOJTAG: 禁用JTAG-DP调试端口，保留SW-DP串行调试端口
   *  这样可以释放PB3、PB4、PA15三个引脚作为普通GPIO使用
   */
  __HAL_AFIO_REMAP_SWJ_NOJTAG();

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
