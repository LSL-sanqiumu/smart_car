#include "stm32f10x.h"                  // Device header
#include "Delay.h"

#include "Motor.h"

void Motor_test_KeyInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

uint8_t Motor_test_KeyStatus(void)
{
	Motor_test_KeyInit();
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == 0){
		Delay_ms(10);
		while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8) == 0);
		Delay_ms(10);
		return 1;
	}
	return 0;
}

void Motor_test(int16_t* speed)
{
	if(Motor_test_KeyStatus() == 1){
		*speed += 2;
		if(*speed > 0 && *speed > 100){
			*speed = -100;
		}
		if(*speed < 0 && *speed > -90){
			*speed = 90;
		}
	}
	Motor_SetSpeed_Left(*speed);
	Motor_SetSpeed_Right(*speed);
}
