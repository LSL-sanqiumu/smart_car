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
#include "BT_HC06.h"
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
	
	#define ManualMode_Exit 10
	#define AutoAvoid_Exit  11
	#define AutoWayfinding_Exit  12
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
#define COMMAND_NUM 12
const char* BT_Command[COMMAND_NUM] = {
"Car_Startup","Car_Stop","Car_ManualMode",
"Car_GoForward","Car_GoBackward","Car_TurnLeft",
"Car_TurnRight","Car_AutoAvoid","Car_AutoWayfinding",
"ManualMode_Exit","AutoAvoid_Exit","AutoWayfinding_Exit"
};
uint8_t BT_GetInstructionValue(char* command)
{
	uint8_t i;
	for(i = 0; i < COMMAND_NUM; i++){
		if(strcmp(command, BT_Command[i]) == 0){
			return i + 1;
		}
	}
//	if(strcmp(command,"Car_Startup") == 0){
//		return Startup;
//	}
//	if(strcmp(command,"Car_Stop") == 0){
//		return Stop;
//	}
//	if(strcmp(command,"Car_ManualMode") == 0){
//		return ManualMode;
//	}
//	if(strcmp(command,"Car_GoForward") == 0){
//		return GoForward;
//	}
//	if(strcmp(command,"Car_GoBackward") == 0){
//		return GoBackward;
//	}
//	if(strcmp(command,"Car_TurnLeft") == 0){
//		return TurnLeft;
//	}
//	if(strcmp(command,"Car_TurnRight") == 0){
//		return TurnRight;
//	}
//	if(strcmp(command,"Car_AutoAvoid") == 0){
//		return AutoAvoid;
//	}
//	if(strcmp(command,"Car_AutoWayfinding") == 0){
//		return AutoWayfinding;
//	}
	return 0;
}





