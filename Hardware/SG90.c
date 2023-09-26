#include "stm32f10x.h"                  // Device header

#include "OLED.h"
void SG90_PWMInit(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 200 - 1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200 - 1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);
	
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;    
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 0;    //   CCR,PWM1：小于有效输出高，大于无效输出低
	TIM_OC3Init(TIM3, &TIM_OCInitStruct);
	
	TIM_Cmd(TIM3, ENABLE);
}
/* 20ms周期， 0.5ms=-90°(5)，1ms=-45°(10)，1.5ms=0°(15)，2ms=45°(20)，2.5ms=90°(25) */
void SG90_SetAngle(uint8_t angle)
{
	TIM_SetCompare3(TIM3, angle);
}

void SG90_AngleInit(void)
{
	SG90_SetAngle(15);
}

void SG90_Test(uint8_t angle)
{
	OLED_ShowSignedNum(1,1,angle,4);
	TIM_SetCompare3(TIM3, angle);
}
