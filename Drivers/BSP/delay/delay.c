#include "stm32f1xx_hal.h"
#include "delay.h"

static uint32_t g_fac_us = 0;  // 微秒延时倍频因子

// 延时初始化函数
// sysclk: 系统时钟频率（单位：MHz）
void delay_init(uint16_t sysclk)
{
    g_fac_us = sysclk;          // 保存系统时钟，用于微秒延时计算
}

// 微秒级延时函数
// nus: 需要延时的微秒数
void delay_us(uint32_t nus)
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 0;
    uint32_t reload = SysTick->LOAD;   // 获取SysTick重载值
    
    ticks = nus * g_fac_us;            // 计算需要的时钟周期数
    told = SysTick->VAL;               // 获取当前计数值
    
    while (1)
    {
        tnow = SysTick->VAL;           // 读取当前计数值
        if (tnow != told)              // 如果计数值发生变化
        {
            if (tnow < told)           // 如果新值小于旧值（未溢出）
            {
                tcnt += told - tnow;   // 计算经过的时钟数
            }
            else                       // 发生溢出（从0重新计数）
            {
                tcnt += reload - tnow + told;  // 加上溢出后的时钟数
            }
            told = tnow;               // 更新旧值
            if (tcnt >= ticks)         // 达到目标时钟数则退出
            {
                break;
            }
        }
    }
}

// 毫秒级延时函数
// nms: 需要延时的毫秒数
void delay_ms(uint16_t nms)
{
    delay_us((uint32_t)(nms * 1000));  // 转换为微秒调用
}

// HAL库延时函数重定义
// Delay: 需要延时的毫秒数
void HAL_Delay(uint32_t Delay)
{
    delay_ms(Delay);
}
