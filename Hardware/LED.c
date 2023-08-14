#include "stm32f10x.h"                  // Device header

#include "Delay.h"

void LED_Emerald_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	
}

void LED_Emerald_Open(void)
{
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);
	Delay_ms(800);
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	Delay_ms(800);
}




