/**
  ******************************************************************************
  * @文件    stm32f1xx_hal_def.h
  * @作者    MCD应用团队
  * @brief   本文件包含HAL通用定义、枚举、宏和结构体定义。
  ******************************************************************************
  * @注意
  *
  * <h2><center>&copy;版权所有 (c) 2017 STMicroelectronics。
  * 保留所有权利。</center></h2>
  *
  * 本软件组件根据BSD 3-Clause许可证获得许可，
  * "许可证"；除非遵守许可证，否则您不得使用此文件。
  * 您可以在以下位置获取许可证的副本：
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* 定义防止递归包含 -------------------------------------*/
#ifndef __STM32F1xx_HAL_DEF
#define __STM32F1xx_HAL_DEF

#ifdef __cplusplus
extern "C" {
#endif

/* 包含头文件 ----------------------------------------------------------------*/
#include "stm32f1xx.h"
#include "Legacy/stm32_hal_legacy.h"
#include <stddef.h>

/* 导出类型 ------------------------------------------------------------*/

/**
  * @brief  HAL状态结构体定义
  */
typedef enum
{
  HAL_OK       = 0x00U,
  HAL_ERROR    = 0x01U,
  HAL_BUSY     = 0x02U,
  HAL_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;

/**
  * @brief  HAL锁结构体定义
  */
typedef enum
{
  HAL_UNLOCKED = 0x00U,
  HAL_LOCKED   = 0x01U
} HAL_LockTypeDef;

/* 导出宏 ------------------------------------------------------------*/
#define HAL_MAX_DELAY      0xFFFFFFFFU

#define HAL_IS_BIT_SET(REG, BIT)         (((REG) & (BIT)) != 0U)
#define HAL_IS_BIT_CLR(REG, BIT)         (((REG) & (BIT)) == 0U)

#define __HAL_LINKDMA(__HANDLE__, __PPP_DMA_FIELD__, __DMA_HANDLE__)               \
                        do{                                                      \
                              (__HANDLE__)->__PPP_DMA_FIELD__ = &(__DMA_HANDLE__); \
                              (__DMA_HANDLE__).Parent = (__HANDLE__);             \
                          } while(0U)

#define UNUSED(X) (void)X      /* 避免gcc/g++警告 */

/** @brief  重置句柄的State字段。
  * @param  __HANDLE__ 指定外设句柄。
  * @note   此宏可用于以下目的：
  *          - 当句柄声明为局部变量时；在第一次将其作为参数
  *            传递给HAL_PPP_Init()之前，必须使用此宏
  *            将句柄的"State"字段设置为0。
  *            否则，"State"字段可能具有任何随机值，第一次调用函数
  *            HAL_PPP_Init()时，将错过低级硬件初始化
  *            （即HAL_PPP_MspInit()将不会被执行）。
  *          - 当需要重新配置低级硬件时：可以调用
  *            HAL_PPP_DeInit()然后HAL_PPP_Init()，用户可以调用此宏然后HAL_PPP_Init()。
  *            在后一个函数中，当句柄的"State"字段设置为0时，它将执行函数
  *            HAL_PPP_MspInit()，这将重新配置低级硬件。
  * @retval 无
  */
#define __HAL_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = 0U)

#if (USE_RTOS == 1U)
/* 保留以供将来使用 */
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

#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM编译器V6 */
#ifndef __weak
#define __weak  __attribute__((weak))
#endif
#ifndef __packed
#define __packed  __attribute__((packed))
#endif
#elif defined ( __GNUC__ ) && !defined (__CC_ARM) /* GNU编译器 */
#ifndef __weak
#define __weak   __attribute__((weak))
#endif /* __weak */
#ifndef __packed
#define __packed __attribute__((__packed__))
#endif /* __packed */
#endif /* __GNUC__ */


/* 用于获取4字节对齐变量的宏，对于__ICCARM__，必须使用"#pragma data_alignment=4"指令 */
#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM编译器V6 */
#ifndef __ALIGN_BEGIN
#define __ALIGN_BEGIN
#endif
#ifndef __ALIGN_END
#define __ALIGN_END      __attribute__ ((aligned (4)))
#endif
#elif defined ( __GNUC__ ) && !defined (__CC_ARM ) /* GNU编译器 */
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
#if defined   (__CC_ARM)      /* ARM编译器V5*/
#define __ALIGN_BEGIN    __align(4)
#elif defined (__ICCARM__)    /* IAR编译器 */
#define __ALIGN_BEGIN
#endif /* __CC_ARM */
#endif /* __ALIGN_BEGIN */
#endif /* __GNUC__ */


/**
  * @brief  __RAM_FUNC定义
  */
#if defined ( __CC_ARM   ) || (defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050))
/* ARM编译器V4/V5和V6
   --------------------------
   RAM函数使用工具链选项定义。
   应该在RAM中执行的函数应该放在单独的源模块中。
   使用"File Options"对话框，您可以简单地将模块的"Code / Const"
   区域更改为物理RAM中的存储空间。
   可用存储区域在"Options for Target"对话框的"Target"选项卡中声明。
*/
#define __RAM_FUNC

#elif defined ( __ICCARM__ )
/* ICCARM编译器
   ---------------
   RAM函数使用特定工具链关键字"__ramfunc"定义。
*/
#define __RAM_FUNC __ramfunc

#elif defined   (  __GNUC__  )
/* GNU编译器
   ------------
  RAM函数使用特定工具链属性
   "__attribute__((section(".RamFunc")))"定义。
*/
#define __RAM_FUNC __attribute__((section(".RamFunc")))

#endif

/**
  * @brief  __NOINLINE定义
  */
#if defined ( __CC_ARM   ) || (defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)) || defined   (  __GNUC__  )
/* ARM V4/V5和V6及GNU编译器
   -------------------------------
*/
#define __NOINLINE __attribute__ ( (noinline) )

#elif defined ( __ICCARM__ )
/* ICCARM编译器
   ---------------
*/
#define __NOINLINE _Pragma("optimize = no_inline")

#endif

#ifdef __cplusplus
}
#endif

#endif /* ___STM32F1xx_HAL_DEF */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
