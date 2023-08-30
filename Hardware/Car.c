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
#include "OLED.h"

#define SPEED_NONE   0
#define SPEED_MIN    60
#define SPEED_MIDDLE 90
#define SPEED_MAX    100

#define OBSTACLE_SET 1
#define OBSTACLE_RESET 0

#define DISTANCE_VALUE_MAX 30      /* ��λ��mm */

/* ǰ�� */
void Car_SetGoForwardSpeed(uint8_t speed)
{
	Motor_SetSpeed_Left(speed);
	Motor_SetSpeed_Right(speed);
}
/* ���� */
void Car_SetGoBackwardSpeed(uint8_t speed)
{
	Motor_SetSpeed_Left(-speed);
	Motor_SetSpeed_Right(-speed);
}
/* ���򡪡���ת */
void Car_ForwardTurnLeft(uint8_t veer_speed)
{
	Motor_SetSpeed_Left(-veer_speed);
	Motor_SetSpeed_Right(veer_speed);
}

/* ���򡪡���ת */
void Car_ForwardTurnRight(uint8_t veer_speed)
{
	Motor_SetSpeed_Left(veer_speed);
	Motor_SetSpeed_Right(-veer_speed);
}

/* ���򡪡���ת */
void Car_InverseTurnLeft(uint8_t veer_speed)
{
	Motor_SetSpeed_Left(veer_speed);
	Motor_SetSpeed_Right(-veer_speed);
}
/* ���򡪡���ת */
void Car_InverseTurnRight(uint8_t veer_speed)
{
	Motor_SetSpeed_Left(-veer_speed);
	Motor_SetSpeed_Right(veer_speed);
}

void Car_ModeMsg(uint8_t* flag, char* command)
{
	if(*flag == 1){
		Serial_SendString("OK  ");
		Serial_SendString(command);
		*flag = 0;
		Serial_SendString("\n");
	}
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
				Car_SetGoForwardSpeed(SPEED_MIDDLE);
				break;
			case Stop:
				Car_SetGoForwardSpeed(SPEED_NONE);
				break;
			case GoForward:
				Car_SetGoBackwardSpeed(SPEED_MIDDLE);
				Delay_ms(200);
				Car_SetGoBackwardSpeed(SPEED_NONE);
				break;
			case GoBackward:
				Car_SetGoBackwardSpeed(SPEED_MIDDLE);
				Delay_ms(200);
				Car_SetGoBackwardSpeed(SPEED_NONE);
				break;
			case TurnLeft:
				Car_ForwardTurnLeft(SPEED_MIDDLE);
				Delay_ms(200);
				Car_SetGoForwardSpeed(SPEED_NONE);
				break;
			case TurnRight:
				Car_ForwardTurnRight(SPEED_MIDDLE);
				Delay_ms(200);
				Car_SetGoForwardSpeed(SPEED_NONE);
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

uint8_t Car_ObstacleFlag(void)
{
	uint16_t avg = HCSR04_GetAvgValue(4);
	OLED_ShowNum(1,8,avg,6);
	if( avg <= DISTANCE_VALUE_MAX){
		return OBSTACLE_SET;
	}
	return OBSTACLE_RESET;
}
/* 25���� 15���� 5����*/
void Car_AutoAvoid(uint8_t* flag, char* command)
{
	SG90_SetAngle(15);
	Car_SetGoForwardSpeed(SPEED_MIN);
	while(1){
		if(Car_ObstacleFlag() == OBSTACLE_SET)
		{
			Car_SetGoForwardSpeed(SPEED_NONE);
			Delay_ms(500);
			SG90_SetAngle(25);
			/* �����ϰ��� */
			if(Car_ObstacleFlag() == OBSTACLE_SET){
				SG90_SetAngle(15);
				Delay_ms(500);
				SG90_SetAngle(5);
				if(Car_ObstacleFlag() == OBSTACLE_SET){
					Delay_ms(500);
					SG90_SetAngle(15);
//					Car_SetGoBackwardSpeed(SPEED_MIN);
//					Delay_ms(1000);

				}else{
					Delay_ms(500);
					SG90_SetAngle(15);
					/* ��ת */
					Car_ForwardTurnRight(SPEED_MIN);
					Delay_ms(1000);
					Car_SetGoForwardSpeed(SPEED_MIN);
				}
			}else {
				Delay_ms(500);
				SG90_SetAngle(15);
				/* ��ת */
				Car_ForwardTurnLeft(SPEED_MIN);
				Delay_ms(1000);
				Car_SetGoForwardSpeed(SPEED_MIN);
			}
		}else {
			Car_SetGoForwardSpeed(60);
			SG90_SetAngle(15);
		}
		Car_ModeMsg(flag, command);
		if(BT_GetInstructionValue(command) == AutoAvoid_Exit){
			Car_SetGoForwardSpeed(0);
			return;
		}
//		if(*flag == 1){
//			Serial_SendString("OK  ");
//			Serial_SendString(command);
//			*flag = 0;
//			Serial_SendString("\n");
//			if(BT_GetInstructionValue(command) == AutoAvoid_Exit){
//				Car_SetGoForwardSpeed(0);
//				return;
//			}
//		}
	}
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
			Car_SetGoForwardSpeed(SPEED_MIN);
		}
		if(left && !middle){
			Car_ForwardTurnLeft(SPEED_MIN);
		}
		
		if(right && !middle){
			Car_ForwardTurnRight(SPEED_MIN);
		}
		if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) &&
			!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) && !left && !right){
			Car_SetGoForwardSpeed(SPEED_NONE);
		}
		Car_ModeMsg(flag, command);
		if(BT_GetInstructionValue(command) == AutoWayfinding_Exit){
			Car_SetGoForwardSpeed(0);
			return;
		}
//		if(*flag == 1){
//			Serial_SendString("OK  ");
//			Serial_SendString(command);
//			*flag = 0;
//			Serial_SendString("\n");
//			if(BT_GetInstructionValue(command) == AutoWayfinding_Exit){
//				Car_SetGoForwardSpeed(0);
//				return;
//			}
//		}
	}
}

/* ԭ����ת */



