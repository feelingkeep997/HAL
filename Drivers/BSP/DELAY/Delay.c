#include "Delay.h"

/**
  * @brief  微秒级延时，基于 SysTick 当前值实现，不破坏 HAL 库的时间基准
  * @param  us 延时时长 (单位: 微秒)
  * @retval 无
  */
void Delay_us(uint32_t us)
{
    uint32_t ticks = us * (HAL_RCC_GetHCLKFreq() / 1000000);
    uint32_t told = SysTick->VAL;
    uint32_t tnow;
    uint32_t tcnt = 0;
    uint32_t reload = SysTick->LOAD;

    while (tcnt < ticks)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)
            {
                tcnt += told - tnow;
            }
            else
            {
                tcnt += reload - tnow + told;
            }
            told = tnow;
        }
    }
}

/**
  * @brief  毫秒级延时，直接调用 HAL_Delay 以兼容工程的 HAL 架构
  * @param  ms 延时时长 (单位: 毫秒)
  * @retval 无
  */
void Delay_ms(uint32_t ms)
{
    HAL_Delay(ms);
}

/**
  * @brief  秒级延时，通过调用 HAL_Delay 实现
  * @param  s 延时时长 (单位: 秒)
  * @retval 无
  */
void Delay_s(uint32_t s)
{
    HAL_Delay(s * 1000);
}
