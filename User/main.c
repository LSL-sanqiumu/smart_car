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

#include "Motor_Test.h"
#include "Serial_Test.h"

extern uint8_t Rx_DataFlag;
extern char Rx_DataPacket[100];

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	OLED_Init();
	LED_Emerald_Init();
	Motor_Init();
	Serial_Init();
//	Infrared_Init();
//	HCSR04_Init();
////	Key_Init();
	while(1){
		if(Rx_DataFlag == 1){
			Serial_SendString("OK  ");
			Serial_SendString(Rx_DataPacket);
			Rx_DataFlag = 0;
			Serial_SendString("\n");
			
			switch(BT_GetInstructionValue(Rx_DataPacket)){
				case Startup:
					Car_SetGoForwardSpeed(90);
					break;
				case Stop:
					Car_SetGoForwardSpeed(0);
					break;
				case GoForward:
					Car_SetGoBackwardSpeed(90);
					Delay_ms(200);
					Car_SetGoBackwardSpeed(0);
					break;
				case GoBackward:
					Car_SetGoBackwardSpeed(-90);
					Delay_ms(200);
					Car_SetGoBackwardSpeed(0);
					break;
				case TurnLeft:
					Car_ForwardTurnLeft();
					break;
				case TurnRight:
					Car_ForwardTurnRight();
					break;
			}
		}	

	}

}
