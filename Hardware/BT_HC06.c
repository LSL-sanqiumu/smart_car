/*
**********************************************************
*
*	ģ������ : ����ģ��
*	�ļ����� : Bluetooth.c
*	��	�� : V1.0
*	˵	�� : ����ָ��������յ����������ͳ���ָ����Ϣ
*	�޸ļ�¼ : 
*		�汾��     ����        ����        ˵��
*		v1.0	2023-08-22     lsl    ָ�������ӳ��
*
**********************************************************
*/

#include "stm32f10x.h"                  // Device header
#include "string.h"
#include "BT_HC06.h"
/*
ָ�
	@Car_Startup    ������С����ʼ��ǰ��
	@Car_Stop       ֹͣ
	
	@Car_ManualMode �ֶ�ģʽ���ð�ť����С��ǰ����ת��
	@Car_GoForward  ǰ��
	@Car_GoBackward ����
	@Car_TurnLeft   ��ת
	@Car_TurnRight  ��ת
	
	 
	@Car_AutoAvoid      �Զ�����
	@Car_AutoWayfinding �Զ�Ѱ��
*/
/* 
ָ��ӳ�䣺
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
*	������ �� BT_GetInstructionValue()
*	��  �� �� ��ָ�����ӳ��
*	��  �� �� command��ָ���ַ�
*	��  �� �� uint8_t��ӳ��ֵ
*	���ù�ϵ����
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





