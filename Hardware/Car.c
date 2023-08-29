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
#include "Serial.h"
#include "BT_HC06.h"
#include "Infrared.h"
#include "HCSR04.h"
#include "SG90.h"
#include "Delay.h"

#define VEER_SPEED1 90
#define VEER_SPEED2 80
#define VEER_SPEED3 70

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
	Motor_SetSpeed_Left(-VEER_SPEED1);
	Motor_SetSpeed_Right(VEER_SPEED1);
}
void Car_ForwardTurnLeft60(void)
{
	Motor_SetSpeed_Left(-60);
	Motor_SetSpeed_Right(60);
}
/* 正向——右转 */
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
/* 逆向——左转 */
void Car_InverseTurnLeft(void)
{
	Motor_SetSpeed_Left(VEER_SPEED1);
	Motor_SetSpeed_Right(-VEER_SPEED1);
}
/* 逆向——右转 */
void Car_InverseTurnRight(void)
{
	Motor_SetSpeed_Left(-VEER_SPEED1);
	Motor_SetSpeed_Right(VEER_SPEED1);
}

/* 手动 */
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


/* 自动避障 */
/* 每隔一段时间发送超声波，如果检测到在距离在一定范围内则代表前方有障碍物
	有障碍物：转动舵机，检测左方、右方是否有障碍物，没有杂物就左转然后前进
*/
void Car_AutoAvoid(void)
{
	
}

/* 自动寻迹  B14右  A11左 */
/* 三种状态：直走  左转  右转 */
/*
直走：中间为1，左右为0
右转：中左为0，中右和右为1
左转：中右为0，中左和左为1
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

/* 原地旋转 */



