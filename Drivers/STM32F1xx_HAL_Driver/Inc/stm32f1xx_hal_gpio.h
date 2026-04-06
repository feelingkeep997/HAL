/**
  ******************************************************************************
  * @文件    stm32f1xx_hal_gpio.h
  * @作者    MCD应用团队
  * @brief   GPIO HAL模块头文件。
  ******************************************************************************
  * @注意
  *
  * <h2><center>&copy;版权所有 (c) 2016 STMicroelectronics。
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

/** @addtogroup GPIO
  * @{
  */

/* 导出类型 ------------------------------------------------------------*/
/** @defgroup GPIO_Exported_Types GPIO导出类型
  * @{
  */

/**
  * @brief GPIO初始化结构体定义
  */
typedef struct
{
  uint32_t Pin;       /*!< 指定要配置的GPIO引脚。
                           此参数可以是@ref GPIO_pins_define的任何值 */

  uint32_t Mode;      /*!< 指定所选引脚的工作模式。
                           此参数可以是@ref GPIO_mode_define的值 */

  uint32_t Pull;      /*!< 指定所选引脚的上拉或下拉激活。
                           此参数可以是@ref GPIO_pull_define的值 */

  uint32_t Speed;     /*!< 指定所选引脚的速度。
                           此参数可以是@ref GPIO_speed_define的值 */
} GPIO_InitTypeDef;

/**
  * @brief  GPIO引脚设置和复位枚举
  */
typedef enum
{
  GPIO_PIN_RESET = 0u,
  GPIO_PIN_SET
} GPIO_PinState;
/**
  * @}
  */

/* 导出常量 --------------------------------------------------------*/

/** @defgroup GPIO_Exported_Constants GPIO导出常量
  * @{
  */

/** @defgroup GPIO_pins_define GPIO引脚定义
  * @{
  */
#define GPIO_PIN_0                 ((uint16_t)0x0001)  /* 引脚0已选择    */
#define GPIO_PIN_1                 ((uint16_t)0x0002)  /* 引脚1已选择    */
#define GPIO_PIN_2                 ((uint16_t)0x0004)  /* 引脚2已选择    */
#define GPIO_PIN_3                 ((uint16_t)0x0008)  /* 引脚3已选择    */
#define GPIO_PIN_4                 ((uint16_t)0x0010)  /* 引脚4已选择    */
#define GPIO_PIN_5                 ((uint16_t)0x0020)  /* 引脚5已选择    */
#define GPIO_PIN_6                 ((uint16_t)0x0040)  /* 引脚6已选择    */
#define GPIO_PIN_7                 ((uint16_t)0x0080)  /* 引脚7已选择    */
#define GPIO_PIN_8                 ((uint16_t)0x0100)  /* 引脚8已选择    */
#define GPIO_PIN_9                 ((uint16_t)0x0200)  /* 引脚9已选择    */
#define GPIO_PIN_10                ((uint16_t)0x0400)  /* 引脚10已选择   */
#define GPIO_PIN_11                ((uint16_t)0x0800)  /* 引脚11已选择   */
#define GPIO_PIN_12                ((uint16_t)0x1000)  /* 引脚12已选择   */
#define GPIO_PIN_13                ((uint16_t)0x2000)  /* 引脚13已选择   */
#define GPIO_PIN_14                ((uint16_t)0x4000)  /* 引脚14已选择   */
#define GPIO_PIN_15                ((uint16_t)0x8000)  /* 引脚15已选择   */
#define GPIO_PIN_All               ((uint16_t)0xFFFF)  /* 所有引脚已选择 */

#define GPIO_PIN_MASK              0x0000FFFFu /* 用于断言测试的引脚掩码 */
/**
  * @}
  */

/** @defgroup GPIO_mode_define GPIO模式定义
  * @brief GPIO配置模式
  *        元素值约定: 0xX0yz00YZ
  *           - X  : GPIO模式或EXTI模式
  *           - y  : 外部IT或事件触发检测
  *           - z  : 外部IT或事件的IO配置
  *           - Y  : 输出类型（推挽或开漏）
  *           - Z  : IO方向模式（输入、输出、复用或模拟）
  * @{
  */
#define  GPIO_MODE_INPUT                        0x00000000u   /*!< 输入浮空模式                   */
#define  GPIO_MODE_OUTPUT_PP                    0x00000001u   /*!< 输出推挽模式                 */
#define  GPIO_MODE_OUTPUT_OD                    0x00000011u   /*!< 输出开漏模式                */
#define  GPIO_MODE_AF_PP                        0x00000002u   /*!< 复用功能推挽模式     */
#define  GPIO_MODE_AF_OD                        0x00000012u   /*!< 复用功能开漏模式    */
#define  GPIO_MODE_AF_INPUT                     GPIO_MODE_INPUT          /*!< 复用功能输入模式         */

#define  GPIO_MODE_ANALOG                       0x00000003u   /*!< 模拟模式  */

#define  GPIO_MODE_IT_RISING                    0x10110000u   /*!< 外部中断模式，带上升沿触发检测          */
#define  GPIO_MODE_IT_FALLING                   0x10210000u   /*!< 外部中断模式，带下降沿触发检测         */
#define  GPIO_MODE_IT_RISING_FALLING            0x10310000u   /*!< 外部中断模式，带上升/下降沿触发检测  */

#define  GPIO_MODE_EVT_RISING                   0x10120000u   /*!< 外部事件模式，带上升沿触发检测               */
#define  GPIO_MODE_EVT_FALLING                  0x10220000u   /*!< 外部事件模式，带下降沿触发检测              */
#define  GPIO_MODE_EVT_RISING_FALLING           0x10320000u   /*!< 外部事件模式，带上升/下降沿触发检测       */

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

/** @defgroup GPIO_pull_define GPIO上下拉定义
  * @brief GPIO上拉或下拉激活
  * @{
  */
#define  GPIO_NOPULL        0x00000000u   /*!< 无上拉或下拉激活  */
#define  GPIO_PULLUP        0x00000001u   /*!< 上拉激活                  */
#define  GPIO_PULLDOWN      0x00000002u   /*!< 下拉激活                */
/**
  * @}
  */

/**
  * @}
  */

/* 导出宏 ------------------------------------------------------------*/
/** @defgroup GPIO_Exported_Macros GPIO导出宏
  * @{
  */

/**
  * @brief  检查指定的EXTI行标志是否已设置。
  * @param  __EXTI_LINE__: 指定要检查的EXTI行标志。
  *         此参数可以是GPIO_PIN_x，其中x可以是(0..15)
  * @retval __EXTI_LINE__的新状态(SET或RESET)。
  */
#define __HAL_GPIO_EXTI_GET_FLAG(__EXTI_LINE__) (EXTI->PR & (__EXTI_LINE__))

/**
  * @brief  清除EXTI行的挂起标志。
  * @param  __EXTI_LINE__: 指定要清除的EXTI行标志。
  *         此参数可以是GPIO_PIN_x的任何组合，其中x可以是(0..15)
  * @retval 无
  */
#define __HAL_GPIO_EXTI_CLEAR_FLAG(__EXTI_LINE__) (EXTI->PR = (__EXTI_LINE__))

/**
  * @brief  检查指定的EXTI行是否被触发。
  * @param  __EXTI_LINE__: 指定要检查的EXTI行。
  *          此参数可以是GPIO_PIN_x，其中x可以是(0..15)
  * @retval __EXTI_LINE__的新状态(SET或RESET)。
  */
#define __HAL_GPIO_EXTI_GET_IT(__EXTI_LINE__) (EXTI->PR & (__EXTI_LINE__))

/**
  * @brief  清除EXTI行的挂起位。
  * @param  __EXTI_LINE__: 指定要清除的EXTI行。
  *          此参数可以是GPIO_PIN_x的任何组合，其中x可以是(0..15)
  * @retval 无
  */
#define __HAL_GPIO_EXTI_CLEAR_IT(__EXTI_LINE__) (EXTI->PR = (__EXTI_LINE__))

/**
  * @brief  在选定的EXTI行上生成软件中断。
  * @param  __EXTI_LINE__: 指定要操作的EXTI行。
  *          此参数可以是GPIO_PIN_x，其中x可以是(0..15)
  * @retval 无
  */
#define __HAL_GPIO_EXTI_GENERATE_SWIT(__EXTI_LINE__) (EXTI->SWIER |= (__EXTI_LINE__))
/**
  * @}
  */

/* 包含GPIO HAL扩展模块 */
#include "stm32f1xx_hal_gpio_ex.h"

/* 导出函数 --------------------------------------------------------*/
/** @addtogroup GPIO_Exported_Functions
  * @{
  */

/** @addtogroup GPIO_Exported_Functions_Group1
  * @{
  */
/* 初始化和去初始化函数 *****************************/
void  HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init);
void  HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin);
/**
  * @}
  */

/** @addtogroup GPIO_Exported_Functions_Group2
  * @{
  */
/* IO操作函数 *****************************************************/
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
/* 私有类型 -------------------------------------------------------------*/
/* 私有变量 ---------------------------------------------------------*/
/* 私有常量 ---------------------------------------------------------*/
/** @defgroup GPIO_Private_Constants GPIO私有常量
  * @{
  */

/**
  * @}
  */

/* 私有宏 ------------------------------------------------------------*/
/** @defgroup GPIO_Private_Macros GPIO私有宏
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

/* 私有函数 ---------------------------------------------------------*/
/** @defgroup GPIO_Private_Functions GPIO私有函数
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
