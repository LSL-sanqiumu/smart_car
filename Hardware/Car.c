/*
**********************************************************
*
*	ģ������ : С������ʵ��ģ��
*	�ļ����� : Car.c
*	��	�� : V1.0
*	˵	�� : С���˶���������ʵ��
*	�޸ļ�¼ : 
*		�汾��     ����        ����        ˵��
*		v1.0	2023-08-22     lsl   ʵ��С����ǰ�������ˡ�ǰ��ת��ǰ��ת�򡢺���ת�򡢺���ת��
*                                    ת��ʵ��ԭ��
*                                        ��ת�����������ת��������ǰת��
*									     ��ת����������ǰת����������ת
*
**********************************************************
*/
#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "Serial.h"
#include "BT_HC06.h"
#include "Infrared.h"
#include "HCSR04.h"
#include "SG90.h"
#include "Delay.h"

#define VEER_SPEED1 90
#define VEER_SPEED2 80
#define VEER_SPEED3 70

/* ǰ�� */
void Car_SetGoForwardSpeed(int16_t speed)
{
	Motor_SetSpeed_Left(speed);
	Motor_SetSpeed_Right(speed);
}
/* ���� */
void Car_SetGoBackwardSpeed(int16_t speed)
{
	Motor_SetSpeed_Left(speed);
	Motor_SetSpeed_Right(speed);
}
/* ���򡪡���ת */
void Car_ForwardTurnLeft(void)
{
	Motor_SetSpeed_Left(-VEER_SPEED1);
	Motor_SetSpeed_Right(VEER_SPEED1);
}
void Car_ForwardTurnLeft60(void)
{
	Motor_SetSpeed_Left(-60);
	Motor_SetSpeed_Right(60);
}
/* ���򡪡���ת */
void Car_ForwardTurnRight(void)
{
	Motor_SetSpeed_Left(VEER_SPEED1);
	Motor_SetSpeed_Right(-VEER_SPEED1);
}
void Car_ForwardTurnRight60(void)
{
	Motor_SetSpeed_Left(60);
	Motor_SetSpeed_Right(-60);
}
/* ���򡪡���ת */
void Car_InverseTurnLeft(void)
{
	Motor_SetSpeed_Left(VEER_SPEED1);
	Motor_SetSpeed_Right(-VEER_SPEED1);
}
/* ���򡪡���ת */
void Car_InverseTurnRight(void)
{
	Motor_SetSpeed_Left(-VEER_SPEED1);
	Motor_SetSpeed_Right(VEER_SPEED1);
}

/* �ֶ� */
void Car_ManualMode(uint8_t* flag, char* command)
{
	while(1){
		if(*flag == 1){
		Serial_SendString("OK  ");
		Serial_SendString(command);
		*flag = 0;
		Serial_SendString("\n");
		switch(BT_GetInstructionValue(command)){
			case Startup:
				Car_SetGoForwardSpeed(90);
				break;
			case Stop:
				Car_SetGoForwardSpeed(0);
				break;
			case GoForward:
				Car_SetGoBackwardSpeed(90);
				Delay_ms(200);
				Car_SetGoBackwardSpeed(0);
				break;
			case GoBackward:
				Car_SetGoBackwardSpeed(-90);
				Delay_ms(200);
				Car_SetGoBackwardSpeed(0);
				break;
			case TurnLeft:
				Car_ForwardTurnLeft();
				Delay_ms(200);
				Car_SetGoForwardSpeed(0);
				break;
			case TurnRight:
				Car_ForwardTurnRight();
				Delay_ms(200);
				Car_SetGoForwardSpeed(0);
				break;
			case ManualMode_Exit:
				return;
			}
		}
	}
}


/* �Զ����� */
/* ÿ��һ��ʱ�䷢�ͳ������������⵽�ھ�����һ����Χ�������ǰ�����ϰ���
	���ϰ��ת�����������󷽡��ҷ��Ƿ����ϰ��û���������תȻ��ǰ��
*/
void Car_AutoAvoid(void)
{
	
}

/* �Զ�Ѱ��  B14��  A11�� */
/* ����״̬��ֱ��  ��ת  ��ת */
/*
ֱ�ߣ��м�Ϊ1������Ϊ0
��ת������Ϊ0�����Һ���Ϊ1
��ת������Ϊ0���������Ϊ1
*/
void Car_AutoWayfinding(uint8_t* flag, char* command)
{
	uint8_t left = 0;
	uint8_t middle = 0;
	uint8_t right = 0;
	while(1){
		left = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12);
		right = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13); 
		middle = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) & GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14);
		if(middle){
			Car_SetGoForwardSpeed(60);
		}
		if(left && !middle){
			Car_ForwardTurnLeft60();
		}
		
		if(right && !middle){
			Car_ForwardTurnRight60();
		}
		if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) &&
			!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) && !left && !right){
			Car_SetGoForwardSpeed(0);
		}
		
		if(*flag == 1){
			Serial_SendString("OK  ");
			Serial_SendString(command);
			*flag = 0;
			Serial_SendString("\n");
			if(BT_GetInstructionValue(command) == AutoWayfinding_Exit){
				Car_SetGoForwardSpeed(0);
				return;
			}
		}
	}
}

/* ԭ����ת */



