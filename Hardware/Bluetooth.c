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





