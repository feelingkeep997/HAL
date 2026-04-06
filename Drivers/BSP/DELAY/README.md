# DELAY (延迟功能模块)

## 模块说明
本模块为基于 STM32 HAL 库的延时工具库，用于提供精准的微秒级、毫秒级与秒级延时功能。

> **⚠️ 环境说明与注意事项**：
> 1. 本项目为**基于 C 语言的 STM32 嵌入式工程**（采用 HAL 库），而非 Node.js/TypeScript 环境。
> 2. 原代码基于标准库(Standard Peripheral Library)编写，直接修改了 `SysTick` 寄存器。这种操作会破坏 HAL 库原本的 1ms 时基中断（`HAL_GetTick()`）。
> 3. 重构后的版本放弃了对 `SysTick` 控制寄存器的强制改写，改为**安全地轮询 SysTick 当前计数值**（实现 `Delay_us`），并且完全复用 `HAL_Delay()`（实现 `Delay_ms` 与 `Delay_s`）。
> 4. 此改动确保了微秒级延迟的精度（误差在几微秒内），且不会引发 `HAL_Delay()` 阻塞或系统时钟异常。

## 接入示例

在需要使用延时功能的 C 文件中引入头文件：

```c
#include "Delay.h"

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    while(1)
    {
        // 延时 500 毫秒
        Delay_ms(500);

        // 延时 10 微秒
        Delay_us(10);
        
        // 延时 2 秒
        Delay_s(2);
    }
}
```

## API 规范与文档 (Doxygen 注释)

模块中所有函数均使用标准的 Doxygen 注释，保证文档的完整性，并兼容大部分 C 语言 IDE（如 Keil, VSCode + C/C++ 等）的代码提示功能：

- `void Delay_us(uint32_t us)`: 微秒级精准延时（基于 SysTick 轮询，不产生中断冲突）。
- `void Delay_ms(uint32_t ms)`: 毫秒级延时（封装 `HAL_Delay`）。
- `void Delay_s(uint32_t s)`: 秒级延时（封装 `HAL_Delay`）。

## 变更日志 (CHANGELOG)

### v2.0.0 (HAL 重构版)
- **Refactor**: 移除标准库依赖 `#include "stm32f10x.h"`，统一使用 `#include "stm32f1xx_hal.h"`。
- **Fix**: 重构 `Delay_us` 逻辑。放弃重写 `SysTick->CTRL` 和 `SysTick->LOAD`，改为读取 `SysTick->VAL` 的差值进行轮询计时，解决了老版本延时与 `HAL_Delay()` 的冲突（由于 HAL 架构要求 `SysTick` 作为 1ms 时基）。
- **Refactor**: 重构 `Delay_ms` 和 `Delay_s`，直接调用 `HAL_Delay()`，确保项目内的时间片统一且符合 HAL 库规范。
- **Docs**: 添加符合规范的 API 注释（Doxygen），替代 TypeScript/JSDoc 需求，确保静态类型语言 C 的规范一致性。
