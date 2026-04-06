#include "stm32f1xx_hal.h"
#include "USART.h"

/******************************************************************************************/
/* 以下代码用于支持printf函数重定向，无需选择使用MicroLIB库 */

#if 1

#if (__ARMCC_VERSION >= 6010050)
__asm(".global __use_no_semihosting\n\t");
__asm(".global __ARM_use_no_argv \n\t");

#else
#pragma import(__use_no_semihosting)

struct __FILE
{
    int handle;
};

#endif

int _ttywrch(int ch)
{
    ch = ch;
    return ch;
}

void _sys_exit(int x)
{
    x = x;
}

char *_sys_command_string(char *cmd, int len)
{
    return NULL;
}


FILE __stdout;

// printf输出重定向函数（将printf输出到串口）
int fputc(int ch, FILE *f)
{
    // 等待发送数据寄存器为空（TXE标志位置位）
    while ((USART_UX->SR & 0X40) == 0);

    USART_UX->DR = (uint8_t)ch;  // 写入数据到发送寄存器
    return ch;
}
#endif
/******************************************************************************************/

#if USART_EN_RX  // 如果使能了串口接收功能

// 串口接收缓冲区（存储接收到的数据）
uint8_t g_usart_rx_buf[USART_REC_LEN];

// 接收状态标志变量
// bit15: 接收完成标志（收到回车换行后置1）
// bit14: 收到0x0d（回车符\r）的标志
// bit13~0: 已接收到的有效数据个数
uint16_t g_usart_rx_sta = 0;

// 单字节接收缓冲区（中断接收时使用）
uint8_t g_rx_buffer[RXBUFFERSIZE];

// UART句柄（USART1实例）
UART_HandleTypeDef g_uart1_handle;

// 串口初始化函数
// baudrate: 波特率（如9600、115200等）
void usart_init(uint32_t baudrate)
{
    g_uart1_handle.Instance = USART_UX;           // 选择串口实例（默认为USART1）
    g_uart1_handle.Init.BaudRate = baudrate;     // 设置波特率
    g_uart1_handle.Init.WordLength = UART_WORDLENGTH_8B;   // 8位数据长度
    g_uart1_handle.Init.StopBits = UART_STOPBITS_1;        // 1位停止位
    g_uart1_handle.Init.Parity = UART_PARITY_NONE;         // 无校验位
    g_uart1_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;   // 无硬件流控
    g_uart1_handle.Init.Mode = UART_MODE_TX_RX;            // 收发模式
    HAL_UART_Init(&g_uart1_handle);              // 初始化串口

    // 开启串口接收中断（每接收一个字节触发一次中断）
    HAL_UART_Receive_IT(&g_uart1_handle, (uint8_t *)g_rx_buffer, RXBUFFERSIZE);
}

// UART底层初始化回调函数（配置GPIO引脚和时钟，由HAL_UART_Init自动调用）
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef gpio_init_struct;

    if (huart->Instance == USART_UX)             // 判断是否为配置的串口实例
    {
        // 使能时钟
        USART_TX_GPIO_CLK_ENABLE();              // 使能TX引脚的GPIO时钟
        USART_RX_GPIO_CLK_ENABLE();              // 使能RX引脚的GPIO时钟
        USART_UX_CLK_ENABLE();                   // 使能串口外设时钟

        // 配置TX引脚（PA9）为复用推挽输出
        gpio_init_struct.Pin = USART_TX_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;          // 复用推挽输出
        gpio_init_struct.Pull = GPIO_PULLUP;              // 上拉
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;    // 高速
        HAL_GPIO_Init(USART_TX_GPIO_PORT, &gpio_init_struct);
                
        // 配置RX引脚（PA10）为复用输入
        gpio_init_struct.Pin = USART_RX_GPIO_PIN;
        gpio_init_struct.Mode = GPIO_MODE_AF_INPUT;       // 复用输入模式
        HAL_GPIO_Init(USART_RX_GPIO_PORT, &gpio_init_struct);
        
#if USART_EN_RX
        // 配置串口接收中断
        HAL_NVIC_EnableIRQ(USART_UX_IRQn);               // 使能串口中断通道
        HAL_NVIC_SetPriority(USART_UX_IRQn, 3, 3);        // 设置中断优先级：抢占3，子优先级3
#endif
    }
}

// 串口接收完成回调函数（每接收到一个字节自动调用）
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART_UX)             // 判断是否为配置的串口实例
    {
        if ((g_usart_rx_sta & 0x8000) == 0)      // 尚未接收完成（bit15=0）
        {
            if (g_usart_rx_sta & 0x4000)          // 已收到回车符\r（bit14=1）
            {
                if (g_rx_buffer[0] != 0x0a)      // 判断当前字节是否为换行符\n
                {
                    g_usart_rx_sta = 0;           // 不是\n，接收错误，重新开始
                }
                else
                {
                    g_usart_rx_sta |= 0x8000;      // 是\n，标记接收完成（bit15=1）
                }
            }
            else                                 // 还没收到回车符
            {
                if (g_rx_buffer[0] == 0x0d)      // 当前字节是回车符\r
                    g_usart_rx_sta |= 0x4000;     // 标记已收到\r（bit14=1）
                else                             // 普通数据字符
                {
                    // 存储接收到的数据到缓冲区
                    g_usart_rx_buf[g_usart_rx_sta & 0X3FFF] = g_rx_buffer[0];
                    g_usart_rx_sta++;            // 数据计数加1

                    // 检查缓冲区是否溢出
                    if (g_usart_rx_sta > (USART_REC_LEN - 1))
                    {
                        g_usart_rx_sta = 0;      // 缓冲区溢出，重新开始接收
                    }
                }
            }
        }

        // 重新开启下一次接收中断（实现连续接收）
        HAL_UART_Receive_IT(&g_uart1_handle, (uint8_t *)g_rx_buffer, RXBUFFERSIZE);
    }
}

// 串口中断服务函数（硬件中断入口）
void USART_UX_IRQHandler(void)
{
    HAL_UART_IRQHandler(&g_uart1_handle);        // 调用HAL库统一处理函数
}

#endif  // USART_EN_RX
