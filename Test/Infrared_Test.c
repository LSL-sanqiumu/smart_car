#include "stm32f10x.h"                  // Device header

#include "Infrared.h"

uint8_t Infrared_Test(void)
{
	
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
	
}







