/**
  ******************************************************************************
  * @文件    stm32_assert.h
  * @作者    MCD应用团队
  * @brief   STM32断言模板文件。
  *          该文件应复制到应用程序文件夹并重命名为
  *          stm32_assert.h。
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
#ifndef __STM32_ASSERT_H
#define __STM32_ASSERT_H

#ifdef __cplusplus
extern "C" {
#endif

/* 导出类型 ------------------------------------------------------------*/
/* 导出常量 --------------------------------------------------------*/
/* 包含头文件 ----------------------------------------------------------------*/
/* 导出宏 ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT
/**
  * @brief  assert_param宏用于函数参数检查。
  * @param  expr 如果expr为false，则调用assert_failed函数
  *         该函数报告源文件名和调用失败的源
  *         行号。
  *         如果expr为true，则不返回值。
  * @retval 无
  */
#define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
/* 导出函数 ------------------------------------------------------- */
void assert_failed(uint8_t* file, uint32_t line);
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

#ifdef __cplusplus
}
#endif

#endif /* __STM32_ASSERT_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
