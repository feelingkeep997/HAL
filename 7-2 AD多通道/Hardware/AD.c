#include "stm32f10x.h"                  // 引入STM32F10x设备头文件

// ADC初始化函数
void AD_Init(void)
{
    // 1. 时钟使能配置
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);   // 开启ADC1时钟（APB2总线）
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  // 开启GPIOA时钟（用于ADC引脚）
    
    // 2. ADC时钟分频配置（72MHz主频6分频→12MHz）
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);  // ADC时钟=APB2时钟/6，符合ADC最大14MHz限制[1,6](@ref)
    
    // 3. GPIO初始化（模拟输入模式）
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;         // 设置为模拟输入模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3; // 使能PA0-PA3引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      // 速度参数（模拟输入模式下实际无效）
    GPIO_Init(GPIOA, &GPIO_InitStructure);                // 应用GPIO配置[1,5](@ref)
    
    // 4. ADC基础参数配置
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;       // 独立模式（单ADC工作）
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;   // 数据右对齐（12位数据存于16位寄存器低12位）
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 软件触发（无外部触发）
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;     // 单次转换模式（非连续转换）
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;           // 非扫描模式（仅转换单一通道）
    ADC_InitStructure.ADC_NbrOfChannel = 1;                 // 通道数为1（与扫描模式禁用一致）
    ADC_Init(ADC1, &ADC_InitStructure);                      // 应用ADC配置[2,7](@ref)
    
    // 5. 使能ADC模块
    ADC_Cmd(ADC1, ENABLE);  // 启动ADC1硬件
    
    // 6. ADC校准流程（提高精度）
    ADC_ResetCalibration(ADC1);                             // 复位校准寄存器
    while (ADC_GetResetCalibrationStatus(ADC1) == SET);     // 等待复位完成
    ADC_StartCalibration(ADC1);                             // 启动校准
    while (ADC_GetCalibrationStatus(ADC1) == SET);          // 等待校准完成（约需10个时钟周期）[2,5](@ref)
}

// ADC数值读取函数
uint16_t AD_GetValue(uint8_t ADC_Channel)
{
    // 1. 配置目标通道（每次读取前动态设置）
    ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_55Cycles5); 
    // 参数说明：
    //   ADC1：目标ADC
    //   ADC_Channel：通道号（如ADC_Channel_0对应PA0）
    //   1：规则组序列位置（非扫描模式下仅序列1有效）
    //   ADC_SampleTime_55Cycles5：55.5周期采样时间（平衡速度与精度）[1,6](@ref)
    
    // 2. 启动转换并等待完成
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);                 // 软件触发转换
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET); // 等待转换结束（EOC标志置位）
    
    // 3. 读取转换结果（12位有效数据，0-4095）
    return ADC_GetConversionValue(ADC1);  // 返回ADC_DR寄存器值[4,7](@ref)
}