# STM32F103 多功能学习项目

一个基于 STM32F103C8 微控制器的综合学习项目，集成了 LED、按键、外部中断、OLED 显示屏、PWM 控制等多个外围设备模块。

## 📋 项目概述

本项目采用模块化设计思想，包含完整的硬件驱动代码和应用示例，适合嵌入式开发学习和实验。

**核心特性：**
- STM32F103C8 微控制器（ARM Cortex-M3 内核）
- 64KB SRAM + 64KB Flash
- 系统时钟配置为 72MHz
- 完整的 HAL 库支持

## 🏗️ 项目结构

```
Test/
├── Src/                    # 源代码文件
│   ├── main.c             # 主程序入口
│   ├── gpio.c             # GPIO 配置
│   ├── stm32f1xx_hal_msp.c # HAL 库初始化
│   └── ...
├── Inc/                    # 头文件目录
│   ├── main.h
│   ├── gpio.h
│   └── stm32f1xx_hal_conf.h
├── Drivers/
│   ├── BSP/               # 板级支持包
│   │   ├── LED/          # LED 驱动模块
│   │   ├── KEY/          # 按键驱动模块
│   │   ├── EXTI/         # 外部中断模块
│   │   ├── OLED/         # OLED 显示屏模块
│   │   ├── PWM/          # PWM 和定时器模块
│   │   └── DELAY/        # 延时模块
│   ├── CMSIS/            # CMSIS 库
│   └── STM32F1xx_HAL_Driver/ # STM32 HAL 库
├── MDK-ARM/              # Keil MDK 5 工程文件
└── README.md             # 本文件
```

## 🔧 硬件功能模块

### 1. LED 模块 (`Drivers/BSP/LED/`)
- 提供 LED 点亮、熄灭等基本控制函数
- **接口函数：**
  - `led_init()` - LED 初始化
  - `led_Open()` - 打开 LED
  - `led_close()` - 关闭 LED

### 2. 按键模块 (`Drivers/BSP/KEY/`)
- 支持按键扫描和中断处理
- 按键防抖处理

### 3. 外部中断模块 (`Drivers/BSP/EXTI/`)
- 外部中断初始化和配置
- 中断回调处理
- **函数：**
  - `exti_init()` - 初始化外部中断

### 4. OLED 显示屏模块 (`Drivers/BSP/OLED/`)
- 128×64 OLED 屏驱动（I2C 接口）
- 支持多种显示功能
- **主要接口：**
  - `OLED_Init()` - 初始化 OLED
  - `OLED_ShowString(line, col, string)` - 显示字符串
  - `OLED_ShowNum(line, col, number, len)` - 显示数字
  - `OLED_Clear()` - 清屏

### 5. PWM 和定时器模块 (`Drivers/BSP/PWM/`)
- 通用定时器 PWM 输出
- 输入捕获功能（频率测量）
- 配置参数：
  - PWM 频率：2kHz
  - ARR (重装载值)：499
  - PSC (分频系数)：71
  - TIM2 时钟：1MHz

### 6. 延时模块 (`Drivers/BSP/DELAY/`)
- 毫秒级延时函数
- **函数：**
  - `Delay_ms(ms)` - 延时指定毫秒数

## 📝 主程序功能

[main.c](Src/main.c) 主要功能包括：

1. **系统初始化**
   - HAL 库初始化
   - 系统时钟配置（72MHz）
   - GPIO 和外设初始化

2. **OLED 显示测试**
   - 显示字符串 "cwh"
   - 实时显示频率信息

3. **PWM 正弦波输出**
   - 使用正弦函数生成 PWM 调制信号
   - 角度逐帧增加 0.05 弧度
   - 更新周期 20ms

4. **输入捕获**
   - 使用定时器捕获功能测量信号频率
   - 频率信息通过 `g_freq_hz` 全局变量提供

```c
// 主循环中的关键操作
while (1) {
    // 显示测量的频率
    sprintf(freq_str, "fx = %.1f", g_freq_hz);
    OLED_ShowString(2, 1, freq_str);
    
    // 生成正弦波 PWM 信号
    pwm_val = (uint16_t)(300 * (sin(angle) + 1.0f) / 2.0f);
    __HAL_TIM_SET_COMPARE(&gtim_pwn_chy_handle, TIM_CHANNEL_2, pwm_val);
    
    angle += 0.05f;
    Delay_ms(20);
}
```

## 🛠️ 编译和烧写

### 开发工具
- **IDE**：Keil MDK-ARM 5.x
- **编译器**：ARMCC (ARM 编译器)
- **调试器**：ST-Link v2

### 编译步骤
1. 打开 `MDK-ARM/test.uvprojx` 项目文件
2. 在 Keil MDK 中点击 **Build** 编译项目
3. 构建输出文件：`MDK-ARM/test/test.axf`

### 烧写步骤
1. 连接 ST-Link 调试器到开发板
2. 在 Keil MDK 中点击 **Download** 烧写程序
3. 烧写完成后程序自动运行

### 快速清理构建文件
运行 `keilkill.bat` 脚本清理临时构建文件

## 💻 系统配置

### 时钟配置
- **外部晶振 (HSE)**：8MHz
- **PLL 倍频**：9 倍
- **系统时钟 (SYSCLK)**：72MHz
- **APB1 时钟**：36MHz
- **APB2 时钟**：72MHz

### 内存配置
- **IRAM**：0x20000000 - 0x20004FFF (64KB)
- **IROM**：0x8000000 - 0x800FFFF (64KB)

## 📚 学习内容

本项目涵盖以下嵌入式开发重点内容：

1. ✅ STM32 HAL 库使用
2. ✅ GPIO 配置和控制
3. ✅ 定时器和 PWM 输出
4. ✅ 外部中断处理
5. ✅ I2C 通讯（OLED 驱动）
6. ✅ 模块化程序设计
7. ✅ 硬件驱动开发

## 🔗 相关资源

- [STM32F103 数据手册](https://www.st.com/resource/en/datasheet/stm32f103c8.pdf)
- [STM32F1xx HAL 库文档](https://www.st.com/resource/en/user_manual/dm00135183-stm32f10xxx-and-stm32f20xxx-cortex-m3-programming-manual-stmicroelectronics.pdf)
- [Keil MDK 官网](https://www2.keil.com/mdk5)

## 📄 许可证

本项目为学习交流使用。

## ✍️ 作者

Created for embedded systems learning and development.

---

**最后更新**: 2026年4月
