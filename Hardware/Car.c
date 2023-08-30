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
#include "OLED.h"

#define SPEED_NONE   0
#define SPEED_MIN    60
#define SPEED_MIDDLE 90
#define SPEED_MAX    100

#define OBSTACLE_SET 1
#define OBSTACLE_RESET 0

#define DISTANCE_VALUE_MAX 30      /* 单位：mm */

/* 前进 */
void Car_SetGoForwardSpeed(uint8_t speed)
{
	Motor_SetSpeed_Left(speed);
	Motor_SetSpeed_Right(speed);
}
/* 后退 */
void Car_SetGoBackwardSpeed(uint8_t speed)
{
	Motor_SetSpeed_Left(-speed);
	Motor_SetSpeed_Right(-speed);
}
/* 正向——左转 */
void Car_ForwardTurnLeft(uint8_t veer_speed)
{
	Motor_SetSpeed_Left(-veer_speed);
	Motor_SetSpeed_Right(veer_speed);
}

/* 正向——右转 */
void Car_ForwardTurnRight(uint8_t veer_speed)
{
	Motor_SetSpeed_Left(veer_speed);
	Motor_SetSpeed_Right(-veer_speed);
}

/* 逆向——左转 */
void Car_InverseTurnLeft(uint8_t veer_speed)
{
	Motor_SetSpeed_Left(veer_speed);
	Motor_SetSpeed_Right(-veer_speed);
}
/* 逆向——右转 */
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


/* 自动避障 */
/* 每隔一段时间发送超声波，如果检测到在距离在一定范围内则代表前方有障碍物
	有障碍物：转动舵机，检测左方、右方是否有障碍物，没有杂物就左转然后前进
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
/* 25—左 15—中 5—右*/
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
			/* 左方有障碍物 */
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
					/* 右转 */
					Car_ForwardTurnRight(SPEED_MIN);
					Delay_ms(1000);
					Car_SetGoForwardSpeed(SPEED_MIN);
				}
			}else {
				Delay_ms(500);
				SG90_SetAngle(15);
				/* 左转 */
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

/* 原地旋转 */



