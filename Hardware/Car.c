/*
**********************************************************
*
*	模块名称 : 小车功能实现模块
*	文件名称 : Car.c
*	版	本 : V1.0
*	说	明 : 小车运动基本功能实现
*	修改记录 : 
*		版本号     日期        作者        说明
*		v1.0	2023-08-22     lsl   实现小车的前进、后退、前左转向、前右转向、后左转向、后右转向
*                                    转向实现原理：
*                                        左转——左轮向后转、右轮向前转；
*									     右转——左轮往前转、右轮往后转
*
**********************************************************
*/
#include "stm32f10x.h"                  // Device header
#include "Motor.h"

#define VEER_SPEED 90

/* 前进 */
void Car_SetGoForwardSpeed(int16_t speed)
{
	Motor_SetSpeed_Left(speed);
	Motor_SetSpeed_Right(speed);
}
/* 后退 */
void Car_SetGoBackwardSpeed(int16_t speed)
{
	Motor_SetSpeed_Left(speed);
	Motor_SetSpeed_Right(speed);
}
/* 正向——左转 */
void Car_ForwardTurnLeft(void)
{
	Motor_SetSpeed_Left(-VEER_SPEED);
	Motor_SetSpeed_Right(VEER_SPEED);
}
/* 正向——右转 */
void Car_ForwardTurnRight(void)
{
	Motor_SetSpeed_Left(VEER_SPEED);
	Motor_SetSpeed_Right(-VEER_SPEED);
}
/* 逆向——左转 */
void Car_InverseTurnLeft(void)
{
	Motor_SetSpeed_Left(VEER_SPEED);
	Motor_SetSpeed_Right(-VEER_SPEED);
}
/* 逆向——右转 */
void Car_InverseTurnRight(void)
{
	Motor_SetSpeed_Left(-VEER_SPEED);
	Motor_SetSpeed_Right(VEER_SPEED);
}
