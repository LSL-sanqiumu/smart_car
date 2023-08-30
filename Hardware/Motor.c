/*
****************************************************************************
*
*	模块名称 : 电机驱动模块
*	文件名称 : Motor.c
*	版  本 : V1.0
*	说	明 : 利用TIM的输出比较实现PWM控制电机转速
*	修改记录 : 
*		版本号     日期        作者        说明
*		v1.0	2023-08-022     lsl    PWM输出与左右电机的转速、转向控制
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
*	函数名 ： PWM_Init()
*	功  能 ： PA1、PA2输出PWM波形
*	输  入 ： 无
*	输  出 ： 无
*	调用关系：无
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
*	函数名 ： Motor_Init()
*	功  能 ： IO口输出初始化和PWM输出初始化
*	输  入 ： 无
*	输  出 ： 无
*	调用关系：调用PWM_Init()使输出PWM波形
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
*	函数名 ： Motor_SetSpeed_Left()
*	功  能 ： 通过设置PWM波形的占空比来设置左边电机的转速和转向
*	输  入 ： speed
*	输  出 ： 无
*	调用关系：无
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
*	函数名 ： Motor_SetSpeed_Right()
*	功  能 ： 通过设置PWM波形的占空比来设置右边电机的转速和转向
*	输  入 ： speed
*	输  出 ： 无
*	调用关系：无
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
