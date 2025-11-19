#include "stm32f10x.h"                  // Device header

uint16_t MyDMA_Size;  // 全局变量，存储DMA传输数据量（用于重新启动传输时重置计数器）

void MyDMA_Init(uint32_t AddrA, uint32_t AddrB, uint16_t Size)
{
	MyDMA_Size = Size;  // 保存传输数据量到全局变量（供MyDMA_Transfer复用）
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);  // 使能DMA1时钟（AHB总线设备必需）[1](@ref)
	
	DMA_InitTypeDef DMA_InitStructure;  // 定义DMA配置结构体
	// 源地址配置（AddrA作为数据传输起点）
	DMA_InitStructure.DMA_PeripheralBaseAddr = AddrA;  
	// 源数据宽度：字节传输（可选Byte/HalfWord/Word）
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
	// 源地址自增：使能（每次传输后地址+1）
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;  
	// 目标地址配置（AddrB作为数据存储终点）
	DMA_InitStructure.DMA_MemoryBaseAddr = AddrB;  
	// 目标数据宽度：字节传输（需与源宽度一致）
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  
	// 目标地址自增：使能（每次传输后地址+1）
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
	// 传输方向：外设为源（AddrA → AddrB）
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  
	// 传输数据量（单位由数据宽度决定，此处为字节数）
	DMA_InitStructure.DMA_BufferSize = Size;  
	// 传输模式：单次模式（传输完成后停止）
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  
	// 传输类型：存储器到存储器（软件触发）
	DMA_InitStructure.DMA_M2M = DMA_M2M_Enable; 
	// 通道优先级：中等（多通道竞争时生效）
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;  
	// 应用配置到DMA1通道1
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);  
	
	// 初始化后禁用DMA（防止意外启动，等待MyDMA_Transfer显式使能）[1,2](@ref)
	DMA_Cmd(DMA1_Channel1, DISABLE);  
}

void MyDMA_Transfer(void)
{
	// 禁用DMA通道（安全操作：修改计数器前必须暂停DMA）[7,8](@ref)
	DMA_Cmd(DMA1_Channel1, DISABLE);  
	// 重置传输计数器（必须禁用状态下设置）[7](@ref)
	DMA_SetCurrDataCounter(DMA1_Channel1, MyDMA_Size);  
	// 使能DMA通道（启动传输）
	DMA_Cmd(DMA1_Channel1, ENABLE);  
	
	// 阻塞等待传输完成标志（TC1=1时跳出循环）[1,2](@ref)
	while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);  
	// 清除传输完成标志位（避免影响后续操作）[6](@ref)
	DMA_ClearFlag(DMA1_FLAG_TC1);  
}
