#ifndef __OLED_H
#define __OLED_H

#include <stdint.h>

// OLED初始化函数（配置SSD1306芯片参数）
void OLED_Init(void);

// 清屏函数（将整个屏幕清空为黑色）
void OLED_Clear(void);

// 在指定位置显示一个ASCII字符（16x16字体）
// Line:   行号（1-4）
// Column: 列号（1-16）
// Char:   要显示的字符
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);

// 在指定位置显示字符串
// Line:   行号（1-4）
// Column: 起始列号（1-16）
// String: 要显示的字符串
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);

// 在指定位置显示无符号整数（十进制）
// Length: 显示的位数
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

// 在指定位置显示有符号整数（带正负号）
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);

// 在指定位置显示十六进制数
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

// 在指定位置显示二进制数
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

#endif
