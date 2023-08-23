#include "stm32f10x.h"                  // Device header

#include "Delay.h"
#include "OLED.h"

uint8_t hscr04_flag;
uint8_t hscr04_time;

void TIM4_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 660 - 1;      // 66ms Timer
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200 - 1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStruct);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	NVIC_InitStruct.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStruct);
	TIM_Cmd(TIM4, DISABLE);
}


void HCSR04_Init(void)
{
	TIM4_Init();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;      // echo
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;     // trig
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_ResetBits(GPIOA, GPIO_Pin_11);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource9);
	
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line9;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_InitStruct);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
}

void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;     
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}
uint8_t Key_GetKeyValue(void)
{
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0){
		Delay_us(10);
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 0);
		Delay_us(10);
		return 1;
	}
	return 0;
}
/* ¥•∑¢≤‚æ‡ */
void HCSR04_RangingStart(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_11);
	Delay_us(20);
	GPIO_ResetBits(GPIOA, GPIO_Pin_11);
}

uint16_t HCSR04_GetDistance(void)
{
	// æ‡¿Îº∆À„£∫(xs * 340 m/s)/2 Ω´xªªÀ„Œ™us£¨ ‘Úæ‡¿Î = 17Counter mm
	return hscr04_time * 17;
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line9) == SET){
		if(hscr04_flag == 0){
			TIM_Cmd(TIM4, ENABLE);
			hscr04_flag = 1;
		}else if(hscr04_flag == 1){
			hscr04_time = TIM_GetCounter(TIM4);
			OLED_ShowNum(3,1,hscr04_time,6);
			TIM_Cmd(TIM4, DISABLE);
			TIM_SetCounter(TIM4,0);
			hscr04_flag = 0;
		}
		EXTI_ClearITPendingBit(EXTI_Line9);
	}
}
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) == SET){
		hscr04_flag = 0;
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}



