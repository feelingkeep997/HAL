/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.h
  * @brief   此文件包含中断处理程序的头文件（函数声明）
  * @note    声明了Cortex-M3内核异常和STM32外设中断的处理函数原型
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
#ifndef __STM32F1xx_IT_H
#define __STM32F1xx_IT_H

#ifdef __cplusplus
 extern "C" {
#endif

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
/* Cortex-M3 内核异常处理函数声明 */
void NMI_Handler(void);              // 不可屏蔽中断（NMI）处理函数
void HardFault_Handler(void);        // 硬故障（Hard Fault）处理函数
void MemManage_Handler(void);        // 内存管理故障（MemManage Fault）处理函数
void BusFault_Handler(void);         // 总线故障（Bus Fault）处理函数
void UsageFault_Handler(void);       // 用法故障（Usage Fault）处理函数
void SVC_Handler(void);              // 系统服务调用（SVCall/SVC）处理函数
void DebugMon_Handler(void);         // 调试监视器（Debug Monitor）处理函数
void PendSV_Handler(void);           // 可挂起系统服务请求（PendSV）处理函数
void SysTick_Handler(void);          // 系统滴答定时器（SysTick）中断处理函数

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /* __STM32F1xx_IT_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
