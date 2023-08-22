/*
**********************************************************
*
*	模块名称 : 蓝牙模块
*	文件名称 : Bluetooth.c
*	版	本 : V1.0
*	说	明 : 解析指令，解析接收到的蓝牙发送出的指令信息
*	修改记录 : 
*		版本号     日期        作者        说明
*		v1.0	2023-08-22     lsl    指令解析与映射
*
**********************************************************
*/

#include "stm32f10x.h"                  // Device header
#include "string.h"

/*
指令：
	@Car_Startup    启动，小车开始向前跑
	@Car_Stop       停止
	
	@Car_ManualMode 手动模式，用按钮控制小车前进与转向
	@Car_GoForward  前进
	@Car_GoBackward 后退
	@Car_TurnLeft   左转
	@Car_TurnRight  右转
	
	 
	@Car_AutoAvoid      自动避障
	@Car_AutoWayfinding 自动寻迹
*/
/* 
指令映射：
	#define Startup         1
	#define Stop            2
	#define ManualMode      3
	#define GoForward       4
	#define GoBackward      5
	#define TurnLeft        6
	#define TurnRight       7
	#define AutoAvoid       8
	#define AutoWayfinding  9
*/

/*
**********************************************************
*	函数名 ： BT_GetInstructionValue()
*	功  能 ： 对指令进行映射
*	输  入 ： command，指令字符
*	输  出 ： uint8_t，映射值
*	调用关系：无
**********************************************************
*/
uint8_t BT_GetInstructionValue(char* command)
{
	if(strcmp(command,"Car_Startup") == 0){
		return 1;
	}
	if(strcmp(command,"Car_Stop") == 0){
		return 2;
	}
	if(strcmp(command,"Car_ManualMode") == 0){
		return 3;
	}
	if(strcmp(command,"Car_GoForward") == 0){
		return 4;
	}
	if(strcmp(command,"Car_GoBackward") == 0){
		return 5;
	}
	if(strcmp(command,"Car_TurnLeft") == 0){
		return 6;
	}
	if(strcmp(command,"Car_TurnRight") == 0){
		return 7;
	}
	if(strcmp(command,"Car_AutoAvoid") == 0){
		return 8;
	}
	if(strcmp(command,"Car_AutoWayfinding") == 0){
		return 9;
	}
	return 0;
}





