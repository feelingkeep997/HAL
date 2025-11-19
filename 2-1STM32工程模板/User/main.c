#include "stm32f10x.h"                  // Device header
int main(void)
{	
	// GPIO通用输入输出口
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);/* 启用GPIOC端口的时钟 */
	GPIO_InitTypeDef GPIO_InitStructure;/* 声明GPIO初始化结构体 */
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;/* 配置GPIO模式为推挽输出 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;/* 选择要控制的引脚：PC13 */
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;/* 设置GPIO速度：50MHz (高速模式) */
	GPIO_Init(GPIOC,&GPIO_InitStructure);/* 应用配置到GPIOC端口 */
	//GPIO_SetBits(GPIOC,GPIO_Pin_13);// 设置PC13为高电平（置位）
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);// 设置PC13为低电平（复位）
	while(1)
	 {
	 
	 }
}
	