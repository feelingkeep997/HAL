/**
  ******************************************************************************
  * @file    stm32f1xx_hal_def.h
  * @author  MCD Application Team
  * @brief   此文件包含HAL库通用定义、枚举、宏和结构体定义
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* 定义防止递归包含 -----------------------------------------------------------*/
#ifndef __STM32F1xx_HAL_DEF
#define __STM32F1xx_HAL_DEF

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx.h"
#include "Legacy/stm32_hal_legacy.h"
#include <stddef.h>

/* 导出类型 ------------------------------------------------------------------*/

/**
  * @brief  HAL状态结构体定义（函数返回值）
  */
typedef enum
{
  HAL_OK       = 0x00U,   // 操作成功完成
  HAL_ERROR    = 0x01U,   // 操作发生错误
  HAL_BUSY     = 0x02U,   // 外设正在忙（被占用）
  HAL_TIMEOUT  = 0x03U    // 操作超时
} HAL_StatusTypeDef;

/**
  * @brief  HAL锁状态结构体定义（用于防止多线程同时访问外设）
  */
typedef enum
{
  HAL_UNLOCKED = 0x00U,   // 未锁定状态（可访问）
  HAL_LOCKED   = 0x01U    // 已锁定状态（被占用）
} HAL_LockTypeDef;

/* 导出宏 --------------------------------------------------------------------*/
#define HAL_MAX_DELAY      0xFFFFFFFFU     // 最大延时值

#define HAL_IS_BIT_SET(REG, BIT)         (((REG) & (BIT)) != 0U)   // 检查某位是否为1
#define HAL_IS_BIT_CLR(REG, BIT)         (((REG) & (BIT)) == 0U)   // 检查某位是否为0

// 将DMA句柄链接到外设句柄（建立双向关联）
#define __HAL_LINKDMA(__HANDLE__, __PPP_DMA_FIELD__, __DMA_HANDLE__)               \
                        do{                                                      \
                              (__HANDLE__)->__PPP_DMA_FIELD__ = &(__DMA_HANDLE__); \
                              (__DMA_HANDLE__).Parent = (__HANDLE__);             \
                          } while(0U)

#define UNUSED(X) (void)X      /* 用于消除gcc/g++编译器警告 */

/** @brief 重置句柄的状态字段为初始值。
  * @param __HANDLE__ 指定外设句柄。
  * @note  此宏可用于以下场景：
  *          - 当句柄声明为局部变量时：在首次作为参数传递给HAL_PPP_Init()之前，
  *            必须使用此宏将句柄的"State"字段设置为0。
  *            否则，"State"字段可能包含随机值，导致第一次调用HAL_PPP_Init()时，
  *            底层硬件初始化会被跳过（即HAL_PPP_MspInit()不会被执行）。
  *          - 当需要重新配置底层硬件时：可以调用此宏然后调用HAL_PPP_Init()，
  *            而不需要先调用HAL_PPP_DeInit()。当句柄的"State"字段为0时，
  *            会执行HAL_PPP_MspInit()来重新配置底层硬件。
  * @retval 无返回值
  */
#define __HAL_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = 0U)

#if (USE_RTOS == 1U)
/* Reserved for future use */
#error "USE_RTOS should be 0 in the current HAL release"
#else
#define __HAL_LOCK(__HANDLE__)                                           \
                                do{                                        \
                                    if((__HANDLE__)->Lock == HAL_LOCKED)   \
                                    {                                      \
                                       return HAL_BUSY;                    \
                                    }                                      \
                                    else                                   \
                                    {                                      \
                                       (__HANDLE__)->Lock = HAL_LOCKED;    \
                                    }                                      \
                                  }while (0U)

#define __HAL_UNLOCK(__HANDLE__)                                          \
                                  do{                                       \
                                      (__HANDLE__)->Lock = HAL_UNLOCKED;    \
                                    }while (0U)
#endif /* USE_RTOS */

#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
#ifndef __weak
#define __weak  __attribute__((weak))
#endif
#ifndef __packed
#define __packed  __attribute__((packed))
#endif
#elif defined ( __GNUC__ ) && !defined (__CC_ARM) /* GNU Compiler */
#ifndef __weak
#define __weak   __attribute__((weak))
#endif /* __weak */
#ifndef __packed
#define __packed __attribute__((__packed__))
#endif /* __packed */
#endif /* __GNUC__ */


/* Macro to get variable aligned on 4-bytes, for __ICCARM__ the directive "#pragma data_alignment=4" must be used instead */
#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
#ifndef __ALIGN_BEGIN
#define __ALIGN_BEGIN
#endif
#ifndef __ALIGN_END
#define __ALIGN_END      __attribute__ ((aligned (4)))
#endif
#elif defined ( __GNUC__ ) && !defined (__CC_ARM) /* GNU Compiler */
#ifndef __ALIGN_END
#define __ALIGN_END    __attribute__ ((aligned (4)))
#endif /* __ALIGN_END */
#ifndef __ALIGN_BEGIN
#define __ALIGN_BEGIN
#endif /* __ALIGN_BEGIN */
#else
#ifndef __ALIGN_END
#define __ALIGN_END
#endif /* __ALIGN_END */
#ifndef __ALIGN_BEGIN
#if defined   (__CC_ARM)      /* ARM Compiler V5*/
#define __ALIGN_BEGIN    __align(4)
#elif defined (__ICCARM__)    /* IAR Compiler */
#define __ALIGN_BEGIN
#endif /* __CC_ARM */
#endif /* __ALIGN_BEGIN */
#endif /* __GNUC__ */


/**
  * @brief  __RAM_FUNC definition
  */
#if defined ( __CC_ARM   ) || (defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
/* ARM Compiler V4/V5 and V6
   --------------------------
   RAM functions are defined using the toolchain options.
   Functions that are executed in RAM should reside in a separate source module.
   Using the 'Options for File' dialog you can simply change the 'Code / Const'
   area of a module to a memory space in physical RAM.
   Available memory areas are declared in the 'Target' tab of the 'Options for Target'
   dialog.
*/
#define __RAM_FUNC

#elif defined ( __ICCARM__ )
/* ICCARM Compiler
   ---------------
   RAM functions are defined using a specific toolchain keyword "__ramfunc".
*/
#define __RAM_FUNC __ramfunc

#elif defined   (  __GNUC__  )
/* GNU Compiler
   ------------
  RAM functions are defined using a specific toolchain attribute
   "__attribute__((section(".RamFunc")))".
*/
#define __RAM_FUNC __attribute__((section(".RamFunc")))

#endif

/**
  * @brief  __NOINLINE definition
  */
#if defined ( __CC_ARM   ) || (defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)) || defined   (  __GNUC__  )
/* ARM V4/V5 and V6 & GNU Compiler
   -------------------------------
*/
#define __NOINLINE __attribute__ ( (noinline) )

#elif defined ( __ICCARM__ )
/* ICCARM Compiler
   ---------------
*/
#define __NOINLINE _Pragma("optimize = no_inline")

#endif

#ifdef __cplusplus
}
#endif

#endif /* ___STM32F1xx_HAL_DEF */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
