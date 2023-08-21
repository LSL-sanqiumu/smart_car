#include "stm32f10x.h"                  // Device header
#include "string.h"



/**
	@Car_Startup    ������С����ʼ��ǰ��
	@Car_Stop       ֹͣ
	
	@Car_ManualMode �ֶ�ģʽ���ð�ť����С��ǰ����ת��
	@Car_GoForward  ǰ��
	@Car_GoBackward ����
	@Car_TurnLeft   ��ת
	@Car_TurnRight  ��ת
	
	 
	@Car_AutoAvoid      �Զ�����
	@Car_AutoWayfinding �Զ�Ѱ��
**/
/* ����ָ���һ��ֵ */
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





