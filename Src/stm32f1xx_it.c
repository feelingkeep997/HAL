/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   中断服务程序（Interrupt Service Routine）
  * @note    此文件包含Cortex-M3内核异常和STM32外设中断的处理函数
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
#include "stm32f1xx_it.h"
/* 私有包含 ------------------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* 私有类型定义 -------------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* 私有定义 ------------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* 私有宏 --------------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* 私有变量 ------------------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* 私有函数原型 -------------------------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* 私有用户代码 -------------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* 外部变量 ------------------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 处理器异常和系统中断处理程序                               */
/******************************************************************************/

/**
  * @brief  此函数处理不可屏蔽中断异常（Non-Maskable Interrupt）
  *         NMI是最高优先级的不可被屏蔽的中断，通常由硬件错误触发
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief  此函数处理硬故障异常（Hard Fault）
  *         由内存访问错误、非法指令、总线错误等严重故障触发
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief  此函数处理内存管理故障异常（Memory Management Fault）
  *         由MPU（内存保护单元）违规访问或非法内存访问触发
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief  此函数处理总线故障异常（Bus Fault）
  *         由预取指令断点、数据访问断点等总线相关错误触发
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief  此函数处理用法故障异常（Usage Fault）
  *         由未定义指令、非法状态切换、除零等错误触发
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief  此函数处理通过SVI指令触发的系统服务调用（Supervisor Call）
  *         用于从用户模式切换到特权模式，实现操作系统系统调用
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief  此函数处理调试监视器异常（Debug Monitor）
  *         在调试模式下由调试事件触发，用于软件断点和观察点
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief  此函数处理可挂起的系统服务请求（Pendable Service Request）
  *         用于操作系统上下文切换延迟到合适的时机执行
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief  此函数处理系统滴答定时器中断（SysTick）
  *         SysTick是Cortex-M3内核内置的定时器，用于产生周期性中断
  *         HAL库使用此中断来提供HAL_Delay()等延时功能的时间基准
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();   // 增加HAL库的Tick计数器（用于延时和超时功能）
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx 外设中断处理程序                                                */
/* 在此处添加所用外设的中断处理程序                                          */
/* 有关可用的外设中断处理程序名称，请参考启动文件 (startup_stm32f103xb.s)       */
/******************************************************************************/

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
