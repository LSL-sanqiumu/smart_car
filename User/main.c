#include "stm32f10x.h"                  // Device header

#include "Delay.h"
#include "LED.h"
#include "Motor.h"
#include "Motor_Test.h"
#include "OLED.h"
int16_t speed = 90;
int main(void)
{
//	OLED_Init();
	LED_Emerald_Init();
	Motor_Init();
	
	while(1){

//		
//		LED_Emerald_Open();
		
		Motor_test(&speed);
//		OLED_ShowSignedNum(1,1,speed,3);
		
	}

}
