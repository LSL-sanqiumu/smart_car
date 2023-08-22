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

#define VEER_SPEED 90

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
	Motor_SetSpeed_Left(-VEER_SPEED);
	Motor_SetSpeed_Right(VEER_SPEED);
}
/* ���򡪡���ת */
void Car_ForwardTurnRight(void)
{
	Motor_SetSpeed_Left(VEER_SPEED);
	Motor_SetSpeed_Right(-VEER_SPEED);
}
/* ���򡪡���ת */
void Car_InverseTurnLeft(void)
{
	Motor_SetSpeed_Left(VEER_SPEED);
	Motor_SetSpeed_Right(-VEER_SPEED);
}
/* ���򡪡���ת */
void Car_InverseTurnRight(void)
{
	Motor_SetSpeed_Left(-VEER_SPEED);
	Motor_SetSpeed_Right(VEER_SPEED);
}
