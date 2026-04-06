/**
  ******************************************************************************
  * @file    stm32f1xx_hal_gpio.h
  * @author  MCD Application Team
  * @brief   GPIO HAL模块头文件（通用输入输出外设驱动）
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
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
#ifndef STM32F1xx_HAL_GPIO_H
#define STM32F1xx_HAL_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* 包含头文件 ----------------------------------------------------------------*/
#include "stm32f1xx_hal_def.h"

/** @addtogroup STM32F1xx_HAL_Driver
  * @{
  */

/** @addtogroup GPIO GPIO通用输入输出
  * @{
  */

/* 导出类型 ------------------------------------------------------------------*/
/** @defgroup GPIO_Exported_Types GPIO导出类型
  * @{
  */

/**
  * @brief GPIO初始化结构体定义
  */
typedef struct
{
  uint32_t Pin;       /*!< 指定需要配置的GPIO引脚。
                           此参数可取 @ref GPIO_pins_define 中的任意值 */

  uint32_t Mode;      /*!< 指定所选引脚的工作模式。
                           此参数可取 @ref GPIO_mode_define 中的值 */

  uint32_t Pull;      /*!< 指定所选引脚的上拉或下拉激活方式。
                           此参数可取 @ref GPIO_pull_define 中的值 */

  uint32_t Speed;     /*!< 指定所选引脚的输出速度。
                           此参数可取 @ref GPIO_speed_define 中的值 */
} GPIO_InitTypeDef;

/**
  * @brief  GPIO位设置和位复位枚举（引脚电平状态）
  */
typedef enum
{
  GPIO_PIN_RESET = 0u,   // 引脚复位/低电平
  GPIO_PIN_SET           // 引脚置位/高电平
} GPIO_PinState;
/**
  * @}
  */

/* 导出常量 ------------------------------------------------------------------*/

/** @defgroup GPIO_Exported_Constants GPIO导出常量
  * @{
  */

/** @defgroup GPIO_pins_define GPIO引脚定义
  * @{
  */
#define GPIO_PIN_0                 ((uint16_t)0x0001)  /* 选择引脚0    */
#define GPIO_PIN_1                 ((uint16_t)0x0002)  /* 选择引脚1    */
#define GPIO_PIN_2                 ((uint16_t)0x0004)  /* 选择引脚2    */
#define GPIO_PIN_3                 ((uint16_t)0x0008)  /* 选择引脚3    */
#define GPIO_PIN_4                 ((uint16_t)0x0010)  /* 选择引脚4    */
#define GPIO_PIN_5                 ((uint16_t)0x0020)  /* 选择引脚5    */
#define GPIO_PIN_6                 ((uint16_t)0x0040)  /* 选择引脚6    */
#define GPIO_PIN_7                 ((uint16_t)0x0080)  /* 选择引脚7    */
#define GPIO_PIN_8                 ((uint16_t)0x0100)  /* 选择引脚8    */
#define GPIO_PIN_9                 ((uint16_t)0x0200)  /* 选择引脚9    */
#define GPIO_PIN_10                ((uint16_t)0x0400)  /* 选择引脚10   */
#define GPIO_PIN_11                ((uint16_t)0x0800)  /* 选择引脚11   */
#define GPIO_PIN_12                ((uint16_t)0x1000)  /* 选择引脚12   */
#define GPIO_PIN_13                ((uint16_t)0x2000)  /* 选择引脚13   */
#define GPIO_PIN_14                ((uint16_t)0x4000)  /* 选择引脚14   */
#define GPIO_PIN_15                ((uint16_t)0x8000)  /* 选择引脚15   */
#define GPIO_PIN_All               ((uint16_t)0xFFFF)  /* 选择所有引脚 */

#define GPIO_PIN_MASK              0x0000FFFFu /* 引脚断言测试掩码 */
/**
  * @}
  */

/** @defgroup GPIO_mode_define GPIO模式定义
  * @brief GPIO配置模式
  *        元素值约定：0xX0yz00YZ
  *           - X  : GPIO模式或EXTI外部中断模式
  *           - y  : 外部中断或事件触发检测方式
  *           - z  : 外部中断或事件时的IO配置
  *           - Y  : 输出类型（推挽或开漏）
  *           - Z  : IO方向模式（输入、输出、复用或模拟）
  * @{
  */
#define  GPIO_MODE_INPUT                        0x00000000u   /*!< 浮空输入模式                   */
#define  GPIO_MODE_OUTPUT_PP                    0x00000001u   /*!< 推挽输出模式                 */
#define  GPIO_MODE_OUTPUT_OD                    0x00000011u   /*!< 开漏输出模式                */
#define  GPIO_MODE_AF_PP                        0x00000002u   /*!< 复用功能推挽模式     */
#define  GPIO_MODE_AF_OD                        0x00000012u   /*!< 复用功能开漏模式    */
#define  GPIO_MODE_AF_INPUT                     GPIO_MODE_INPUT          /*!< 复用功能输入模式         */

#define  GPIO_MODE_ANALOG                       0x00000003u   /*!< 模拟模式  */

#define  GPIO_MODE_IT_RISING                    0x10110000u   /*!< 外部中断模式，上升沿触发检测          */
#define  GPIO_MODE_IT_FALLING                   0x10210000u   /*!< 外部中断模式，下降沿触发检测         */
#define  GPIO_MODE_IT_RISING_FALLING            0x10310000u   /*!< 外部中断模式，双边沿（上升+下降）触发检测  */

#define  GPIO_MODE_EVT_RISING                   0x10120000u   /*!< 外部事件模式，上升沿触发检测               */
#define  GPIO_MODE_EVT_FALLING                  0x10220000u   /*!< 外部事件模式，下降沿触发检测              */
#define  GPIO_MODE_EVT_RISING_FALLING           0x10320000u   /*!< 外部事件模式，双边沿（上升+下降）触发检测       */

/**
  * @}
  */

/** @defgroup GPIO_speed_define  GPIO速度定义
  * @brief GPIO输出最大频率
  * @{
  */
#define  GPIO_SPEED_FREQ_LOW              (GPIO_CRL_MODE0_1) /*!< 低速 */
#define  GPIO_SPEED_FREQ_MEDIUM           (GPIO_CRL_MODE0_0) /*!< 中速 */
#define  GPIO_SPEED_FREQ_HIGH             (GPIO_CRL_MODE0)   /*!< 高速 */

/**
  * @}
  */

/** @defgroup GPIO_pull_define GPIO pull define
  * @brief GPIO Pull-Up or Pull-Down Activation
  * @{
  */
#define  GPIO_NOPULL        0x00000000u   /*!< No Pull-up or Pull-down activation  */
#define  GPIO_PULLUP        0x00000001u   /*!< Pull-up activation                  */
#define  GPIO_PULLDOWN      0x00000002u   /*!< Pull-down activation                */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup GPIO_Exported_Macros GPIO Exported Macros
  * @{
  */

/**
  * @brief  Checks whether the specified EXTI line flag is set or not.
  * @param  __EXTI_LINE__: specifies the EXTI line flag to check.
  *         This parameter can be GPIO_PIN_x where x can be(0..15)
  * @retval The new state of __EXTI_LINE__ (SET or RESET).
  */
#define __HAL_GPIO_EXTI_GET_FLAG(__EXTI_LINE__) (EXTI->PR & (__EXTI_LINE__))

/**
  * @brief  Clears the EXTI's line pending flags.
  * @param  __EXTI_LINE__: specifies the EXTI lines flags to clear.
  *         This parameter can be any combination of GPIO_PIN_x where x can be (0..15)
  * @retval None
  */
#define __HAL_GPIO_EXTI_CLEAR_FLAG(__EXTI_LINE__) (EXTI->PR = (__EXTI_LINE__))

/**
  * @brief  Checks whether the specified EXTI line is asserted or not.
  * @param  __EXTI_LINE__: specifies the EXTI line to check.
  *          This parameter can be GPIO_PIN_x where x can be(0..15)
  * @retval The new state of __EXTI_LINE__ (SET or RESET).
  */
#define __HAL_GPIO_EXTI_GET_IT(__EXTI_LINE__) (EXTI->PR & (__EXTI_LINE__))

/**
  * @brief  Clears the EXTI's line pending bits.
  * @param  __EXTI_LINE__: specifies the EXTI lines to clear.
  *          This parameter can be any combination of GPIO_PIN_x where x can be (0..15)
  * @retval None
  */
#define __HAL_GPIO_EXTI_CLEAR_IT(__EXTI_LINE__) (EXTI->PR = (__EXTI_LINE__))

/**
  * @brief  Generates a Software interrupt on selected EXTI line.
  * @param  __EXTI_LINE__: specifies the EXTI line to check.
  *          This parameter can be GPIO_PIN_x where x can be(0..15)
  * @retval None
  */
#define __HAL_GPIO_EXTI_GENERATE_SWIT(__EXTI_LINE__) (EXTI->SWIER |= (__EXTI_LINE__))
/**
  * @}
  */

/* Include GPIO HAL Extension module */
#include "stm32f1xx_hal_gpio_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @addtogroup GPIO_Exported_Functions
  * @{
  */

/** @addtogroup GPIO_Exported_Functions_Group1
  * @{
  */
/* Initialization and de-initialization functions *****************************/
void  HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);
void  HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin);
/**
  * @}
  */

/** @addtogroup GPIO_Exported_Functions_Group2
  * @{
  */
/* IO operation functions *****************************************************/
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
HAL_StatusTypeDef HAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

/**
  * @}
  */

/**
  * @}
  */
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup GPIO_Private_Constants GPIO Private Constants
  * @{
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup GPIO_Private_Macros GPIO Private Macros
  * @{
  */
#define IS_GPIO_PIN_ACTION(ACTION) (((ACTION) == GPIO_PIN_RESET) || ((ACTION) == GPIO_PIN_SET))
#define IS_GPIO_PIN(PIN)           (((((uint32_t)PIN) & GPIO_PIN_MASK ) != 0x00u) && ((((uint32_t)PIN) & ~GPIO_PIN_MASK) == 0x00u))
#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_MODE_INPUT)              ||\
                            ((MODE) == GPIO_MODE_OUTPUT_PP)          ||\
                            ((MODE) == GPIO_MODE_OUTPUT_OD)          ||\
                            ((MODE) == GPIO_MODE_AF_PP)              ||\
                            ((MODE) == GPIO_MODE_AF_OD)              ||\
                            ((MODE) == GPIO_MODE_IT_RISING)          ||\
                            ((MODE) == GPIO_MODE_IT_FALLING)         ||\
                            ((MODE) == GPIO_MODE_IT_RISING_FALLING)  ||\
                            ((MODE) == GPIO_MODE_EVT_RISING)         ||\
                            ((MODE) == GPIO_MODE_EVT_FALLING)        ||\
                            ((MODE) == GPIO_MODE_EVT_RISING_FALLING) ||\
                            ((MODE) == GPIO_MODE_ANALOG))
#define IS_GPIO_SPEED(SPEED) (((SPEED) == GPIO_SPEED_FREQ_LOW) || \
                              ((SPEED) == GPIO_SPEED_FREQ_MEDIUM) || ((SPEED) == GPIO_SPEED_FREQ_HIGH))
#define IS_GPIO_PULL(PULL) (((PULL) == GPIO_NOPULL) || ((PULL) == GPIO_PULLUP) || \
                            ((PULL) == GPIO_PULLDOWN))
/**
  * @}
  */

/* Private functions ---------------------------------------------------------*/
/** @defgroup GPIO_Private_Functions GPIO Private Functions
  * @{
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32F1xx_HAL_GPIO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
