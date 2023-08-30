/*
****************************************************************************
*
*	ģ������ : �������ģ��
*	�ļ����� : Motor.c
*	��  �� : V1.0
*	˵	�� : ����TIM������Ƚ�ʵ��PWM���Ƶ��ת��
*	�޸ļ�¼ : 
*		�汾��     ����        ����        ˵��
*		v1.0	2023-08-022     lsl    PWM��������ҵ����ת�١�ת�����
*
****************************************************************************
*/
#include "stm32f10x.h"                  // Device header
#include "Delay.h"

#define POSITIVE_SPEED_MAX 100
#define POSITIVE_SPEED_MIN 90
#define NEGATIVE_SPEED_MAX -100
#define NEGATIVE_SPEED_MIN -90

/*
**********************************************************
*	������ �� PWM_Init()
*	��  �� �� PA1��PA2���PWM����
*	��  �� �� ��
*	��  �� �� ��
*	���ù�ϵ����
**********************************************************
*/
void PWM_Init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 100 - 1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200 - 1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0; 
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	TIM_OCInitTypeDef TIM_OCInitStruct;
	TIM_OCStructInit(&TIM_OCInitStruct);
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = 0;
	
	TIM_OC2Init(TIM2, &TIM_OCInitStruct);
	TIM_OC3Init(TIM2, &TIM_OCInitStruct);
	
	TIM_Cmd(TIM2, ENABLE);
	
}
/*
**********************************************************
*	������ �� Motor_Init()
*	��  �� �� IO�������ʼ����PWM�����ʼ��
*	��  �� �� ��
*	��  �� �� ��
*	���ù�ϵ������PWM_Init()ʹ���PWM����
**********************************************************
*/
void Motor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	PWM_Init();
	
}
/*
**********************************************************
*	������ �� Motor_SetSpeed_Left()
*	��  �� �� ͨ������PWM���ε�ռ�ձ���������ߵ����ת�ٺ�ת��
*	��  �� �� speed
*	��  �� �� ��
*	���ù�ϵ����
**********************************************************
*/
void Motor_SetSpeed_Left(int8_t speed)
{
	if(speed > 0){
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5);
		TIM_SetCompare3(TIM2, speed);
	}else{
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		TIM_SetCompare3(TIM2, -speed);
	}
}
/*
**********************************************************
*	������ �� Motor_SetSpeed_Right()
*	��  �� �� ͨ������PWM���ε�ռ�ձ��������ұߵ����ת�ٺ�ת��
*	��  �� �� speed
*	��  �� �� ��
*	���ù�ϵ����
**********************************************************
*/
void Motor_SetSpeed_Right(int8_t speed)
{
	if(speed > 0){
		GPIO_SetBits(GPIOA, GPIO_Pin_6);
		GPIO_ResetBits(GPIOA, GPIO_Pin_7);
		TIM_SetCompare2(TIM2, speed);
	}else{
		GPIO_SetBits(GPIOA, GPIO_Pin_7);
		GPIO_ResetBits(GPIOA, GPIO_Pin_6);
		TIM_SetCompare2(TIM2, -speed);
	}
}
