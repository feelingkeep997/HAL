#include "stm32f10x.h"                  // STM32F10x系列微控制器头文件
#include <stdio.h>                       // 标准输入输出库，用于printf函数重定向
#include <stdarg.h>                      // 可变参数支持，用于Serial_Printf函数

uint16_t Rxdate;                         // 接收到的单字节数据临时存储变量
uint8_t Serial_TxPacket[4];              // 发送数据包缓冲区（格式：FF 01 02 03 04 FE）
uint8_t Serial_RxPacket[4];              // 接收数据包缓冲区
uint8_t Serial_RxFlag;                   // 接收完成标志（1表示收到完整数据包）
uint8_t RxFlag;                          // 单字节接收标志

/**
  * @brief  串口初始化函数
  * @param  无
  * @retval 无
  * @note   配置USART1为9600波特率，8位数据位，1位停止位，无校验位
  *          使用PA9(TX)为推挽输出，PA10(RX)为上拉输入
  *          使能接收中断，配置NVIC中断优先级组2
  */
void Serial_Init(void)
{
    // 1. 使能USART1和GPIOA的时钟[1,3](@ref)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    // 2. 配置GPIO引脚[1,2](@ref)
    GPIO_InitTypeDef GPIO_InitStructure;
    // TX引脚(PA9)配置为复用推挽输出[3](@ref)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;        // 复用推挽输出模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;              // 选择引脚9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       // 最大输出速率50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // RX引脚(PA10)配置为上拉输入[5](@ref)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;           // 上拉输入模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;              // 选择引脚10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // 3. 配置USART串口参数[1,2](@ref)
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600;               // 波特率9600
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 无硬件流控制
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; // 使能发送和接收模式
    USART_InitStructure.USART_Parity = USART_Parity_No;      // 无奇偶校验位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;   // 1位停止位
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 8位数据长度
    USART_Init(USART1, &USART_InitStructure);                // 应用配置到USART1
    
    // 4. 使能接收中断[1,5](@ref)
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);          // 使能RXNE（接收寄存器非空）中断
    
    // 5. 配置NVIC（嵌套向量中断控制器）[1,5](@ref)
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);         // 设置优先级分组为组2（2位抢占优先级，2位子优先级）
    
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;        // USART1中断通道
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;          // 使能该中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // 抢占优先级为1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;       // 子优先级为1
    NVIC_Init(&NVIC_InitStructure);                          // 应用NVIC配置
    
    // 6. 使能USART1[1,2](@ref)
    USART_Cmd(USART1, ENABLE);
}

/**
  * @brief  发送单字节数据
  * @param  Byte: 要发送的字节数据
  * @retval 无
  * @note   阻塞式发送，等待发送完成
  */
void Serial_SendByte(uint8_t Byte)
{
    USART_SendData(USART1, Byte);                           // 将数据写入发送数据寄存器
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); // 等待发送完成（TXE标志置位）[2](@ref)
}

/**
  * @brief  发送字节数组
  * @param  Array: 要发送的数组首地址
  * @param  Length: 数组长度
  * @retval 无
  */
void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
    uint16_t i;
    for (i = 0; i < Length; i ++)
    {
        Serial_SendByte(Array[i]);                          // 逐字节发送数组内容
    }
}

/**
  * @brief  发送字符串
  * @param  String: 要发送的字符串首地址
  * @retval 无
  */
void Serial_SendString(char *String)
{
    uint8_t i;
    for (i = 0; String[i] != '\0'; i ++)                   // 遍历字符串直到结束符'\0'
    {
        Serial_SendByte(String[i]);                        // 逐字符发送
    }
}

/**
  * @brief  计算X的Y次幂
  * @param  X: 底数
  * @param  Y: 指数
  * @retval 计算结果
  * @note   用于数字显示时的位数计算
  */
uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
    uint32_t Result = 1;
    while (Y --)                                           // 循环Y次
    {
        Result *= X;                                       // 累乘计算幂
    }
    return Result;
}

/**
  * @brief  发送指定长度的数字
  * @param  Number: 要发送的数字
  * @param  Length: 数字显示长度
  * @retval 无
  * @note   将数字按指定长度分解为单个数字字符发送
  */
void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
    uint8_t i;
    for (i = 0; i < Length; i ++)
    {
        // 提取每一位数字并转换为ASCII码发送[2](@ref)
        Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
    }
}

/**
  * @brief  printf函数重定向支持
  * @param  ch: 要发送的字符
  * @param  f: 文件指针（未使用）
  * @retval 发送的字符
  * @note   使printf函数通过串口输出
  */
int fputc(int ch, FILE *f)
{
    Serial_SendByte(ch);                                   // 将字符通过串口发送
    return ch;
}

/**
  * @brief  格式化输出函数（类似printf）
  * @param  format: 格式化字符串
  * @param  ...: 可变参数列表
  * @retval 无
  */
void Serial_Printf(char *format, ...)
{
    char String[100];                                      // 格式化结果缓冲区
    va_list arg;                                           // 定义可变参数列表指针
    va_start(arg, format);                                 // 初始化可变参数列表
    vsprintf(String, format, arg);                         // 格式化字符串到缓冲区
    va_end(arg);                                           // 结束可变参数获取
    Serial_SendString(String);                             // 发送格式化后的字符串
}

/**
  * @brief  获取单字节接收标志状态
  * @param  无
  * @retval 1: 有新数据收到 0: 无新数据
  * @note   读取后自动清除接收标志
  */
uint8_t Serial_GetRxFlag(void)
{
    if(RxFlag == 1)                                        // 检查接收标志
    {
        RxFlag = 0;                                        // 清除接收标志
        return 1;                                          // 返回有数据状态
    }
    return 0;                                              // 返回无数据状态
}

/**
  * @brief  获取接收到的单字节数据
  * @param  无
  * @retval 接收到的字节数据
  */
uint8_t Serial_GetRxData(void)
{
    return Rxdate;                                         // 返回最近接收的字节
}

/**
  * @brief  发送数据包
  * @param  无
  * @retval 无
  * @note   数据包格式：0xFF + 4字节数据 + 0xFE
  */
void Serial_SendPacket(void)
{
    Serial_SendByte(0xFF);                                 // 发送包头标志
    Serial_SendArray(Serial_TxPacket, 4);                   // 发送4字节数据
    Serial_SendByte(0xFE);                                 // 发送包尾标志
}

/**
  * @brief  USART1中断服务函数
  * @param  无
  * @retval 无
  * @note   处理接收中断，实现数据包解析（状态机模式）
  */
void USART1_IRQHandler(void)
{
    static uint8_t RxState = 0;                            // 接收状态机状态（0:等待包头 1:接收数据 2:等待包尾）
    static uint8_t pRxPacket = 0;                          // 数据包接收位置索引
    
    // 检查RXNE（接收寄存器非空）标志位[1,5](@ref)
    if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
    {
        Rxdate = USART_ReceiveData(USART1);                // 读取接收到的数据[5](@ref)
        
        // 状态机实现数据包解析
        if(RxState == 0 && Rxdate == 0xFF)                // 状态0：等待包头0xFF
        {
            RxState = 1;                                   // 切换到数据接收状态
            pRxPacket = 0;                                 // 重置数据包索引
        }
        else if(RxState == 1)                              // 状态1：接收数据内容
        {
            Serial_RxPacket[pRxPacket] = Rxdate;           // 存储接收到的数据字节
            pRxPacket++;                                   // 索引位置递增
            if(pRxPacket >= 4)                             // 已接收4字节数据
            {
                RxState = 2;                               // 切换到等待包尾状态
            }
        }
        else if(RxState == 2 && Rxdate == 0xFE)           // 状态2：等待包尾0xFE
        {
            RxState = 0;                                   // 重置状态机，准备接收下一包
            Serial_RxFlag = 1;                             // 设置数据包接收完成标志
        }
        
        RxFlag = 1;                                        // 设置单字节接收标志
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);    // 清除中断挂起标志[5](@ref)
    }
}