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


/* �Զ�Ѱ�� */
/*  */


/* ԭ����ת */



