#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Delay.h"
#include "LED.h"

#include "Motor.h"
#include "Serial.h"
#include "Car.h"
#include "BT_HC06.h"
#include "Infrared.h"
#include "HCSR04.h"
#include "SG90.h"

#include "Car.h"
#include "Motor_Test.h"
#include "Serial_Test.h"

extern uint8_t Serial_RxFlag;
extern char Serial_RxData[100];

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	OLED_Init();
	LED_Emerald_Init();
	
	Motor_Init();
	Serial_Init();
	Infrared_Init();
	HCSR04_Init();
	SG90_PWMInit();

	while(1){
		if(Serial_RxFlag == 1){
			Serial_SendString("OK  ");
			Serial_SendString(Serial_RxData);
			Serial_RxFlag = 0;
			Serial_SendString("\n");
			
			switch(BT_GetInstructionValue(Serial_RxData)){
				
				case ManualMode:
					Car_ManualMode(&Serial_RxFlag, Serial_RxData);
					break;
				case AutoAvoid:
					
					break;
				case AutoWayfinding:
					
					break;
			}
		}	
//		Delay_ms(1000);
//		HCSR04_RangingStart();
//		OLED_ShowNum(1,1,HCSR04_GetDistance(),5);
//		OLED_ShowString(1,7,"mm");
//		OLED_ShowNum(1, 1, GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13), 2);
//		OLED_ShowNum(2, 1, GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14), 2);
//		OLED_ShowNum(3, 1, GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11), 2);
//		OLED_ShowNum(4, 1, GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12), 2);
	}
}
