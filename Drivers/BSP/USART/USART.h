#ifndef __USART_H
#define __USART_H

#include "stdio.h"
#include "stm32f1xx_hal.h"

/******************************************************************************************/
/* 串口引脚和实例定义
 * 默认配置为USART1（PA9-TX, PA10-RX）
 * 注意：通过修改以下宏定义，可以切换到USART1~UART5任意一个串口
 */
#define USART_TX_GPIO_PORT                  GPIOA       // TX引脚所在端口
#define USART_TX_GPIO_PIN                   GPIO_PIN_9  // TX引脚号（PA9）
#define USART_TX_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)  // TX端口时钟使能

#define USART_RX_GPIO_PORT                  GPIOA       // RX引脚所在端口
#define USART_RX_GPIO_PIN                   GPIO_PIN_10 // RX引脚号（PA10）
#define USART_RX_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)  // RX端口时钟使能

#define USART_UX                            USART1      // 串口外设实例
#define USART_UX_IRQn                       USART1_IRQn // 串口中断通道号
#define USART_UX_IRQHandler                 USART1_IRQHandler  // 串口中断服务函数名
#define USART_UX_CLK_ENABLE()               do{ __HAL_RCC_USART1_CLK_ENABLE(); }while(0)  // 串口时钟使能

/******************************************************************************************/

// 接收缓冲区最大长度（字节）
#define USART_REC_LEN               200

// 是否使能接收功能：1=使能，0=禁用
#define USART_EN_RX                 1

// 单次接收缓冲区大小（每次中断接收的字节数）
#define RXBUFFERSIZE   1

// 外部变量声明（供其他文件访问）
extern UART_HandleTypeDef g_uart1_handle;           // UART句柄
extern uint8_t  g_usart_rx_buf[USART_REC_LEN];     // 接收数据缓冲区
extern uint16_t g_usart_rx_sta;                     // 接收状态标志
extern uint8_t g_rx_buffer[RXBUFFERSIZE];           // 单字节接收缓冲区

// 串口初始化函数
// bound: 波特率值（如115200、9600等）
void usart_init(uint32_t bound);

#endif
