#include "stm32f10x.h"                  // Device header
#include "Delay.h"
int main(void)
{	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure1;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	while(1)
	 {	
		 GPIO_Write(GPIOA,~0x0001);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		 Delay_ms(100);
		 GPIO_SetBits(GPIOB,GPIO_Pin_12);
		 Delay_ms(100);		 
			Delay_ms(500);
		 GPIO_Write(GPIOA,~0x0002);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		 Delay_ms(100);
		 GPIO_SetBits(GPIOB,GPIO_Pin_12);
		 Delay_ms(100);		 
		 Delay_ms(500);
		  GPIO_Write(GPIOA,~0x0004);
		 		 GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		 Delay_ms(100);
		 GPIO_SetBits(GPIOB,GPIO_Pin_12);
		 Delay_ms(100);		 
		 Delay_ms(500);
		  GPIO_Write(GPIOA,~0x0008);
		 		 GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		 Delay_ms(100);
		 GPIO_SetBits(GPIOB,GPIO_Pin_12);
		 Delay_ms(100);		 
		 Delay_ms(500);
		  GPIO_Write(GPIOA,~0x0010);
		  		 GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		 Delay_ms(100);
		 GPIO_SetBits(GPIOB,GPIO_Pin_12);
		 Delay_ms(100);		 
		 Delay_ms(500);
		  GPIO_Write(GPIOA,~0x0020);
		  		 GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		 Delay_ms(100);
		 GPIO_SetBits(GPIOB,GPIO_Pin_12);
		 Delay_ms(100);		 
		 Delay_ms(500);
		   GPIO_Write(GPIOA,~0x0040);
		   		 GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		 Delay_ms(100);
		 GPIO_SetBits(GPIOB,GPIO_Pin_12);
		 Delay_ms(100);		 
		 Delay_ms(500);
		  GPIO_Write(GPIOA,~0x0080);
		  		 GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		 Delay_ms(100);
		 GPIO_SetBits(GPIOB,GPIO_Pin_12);
		 Delay_ms(100);		 
		 Delay_ms(500);	 
	 }
}

