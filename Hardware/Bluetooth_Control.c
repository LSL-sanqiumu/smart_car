#include "stm32f10x.h"                  // Device header
#include "string.h"



/**
	@Car_Startup    启动，小车开始向前跑
	@Car_Stop       停止
	
	@Car_ManualMode 手动模式，用按钮控制小车前进与转向
	@Car_GoForward  前进
	@Car_GoBackward 后退
	@Car_TurnLeft   左转
	@Car_TurnRight  右转
	
	 
	@Car_AutoAvoid      自动避障
	@Car_AutoWayfinding 自动寻迹
**/
/* 根据指令返回一个值 */
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





