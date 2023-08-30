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
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;      // echo
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;     // trig
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource15);
	
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = EXTI_Line15;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_InitStruct);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
}


/* 触发测距 */
void HCSR04_RangingStart(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_8);
	Delay_us(20);
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);
}

uint16_t HCSR04_GetDistance(void)
{
	/* 距离计算：(xs * 340 m/s)/2 将x换算为us， 则距离 = 17Counter mm */
	/* 单位：mm */
	return hscr04_time * 17;
}

uint16_t HCSR04_GetAvgValue(uint8_t num)
{
	uint16_t total = 0; 
	uint8_t i;
	for(i = 0; i < num; i++){
		HCSR04_RangingStart();
		Delay_ms(60);
		total += HCSR04_GetDistance();
	}
	return total / num;
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line15) == SET){
		if(hscr04_flag == 0){
			TIM_Cmd(TIM4, ENABLE);
			hscr04_flag = 1;
		}else if(hscr04_flag == 1){
			hscr04_time = TIM_GetCounter(TIM4);
//			OLED_ShowNum(3,1,hscr04_time,6);
			TIM_Cmd(TIM4, DISABLE);
			TIM_SetCounter(TIM4,0);
			hscr04_flag = 0;
		}
		EXTI_ClearITPendingBit(EXTI_Line15);
	}
}
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) == SET){
		hscr04_flag = 0;
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}



