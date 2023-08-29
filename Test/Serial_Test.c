#include "stm32f10x.h"                  // Device header

#include "Serial.h"

extern char Serial_RxData[100];
extern uint8_t Serial_RxFlag;

void Serial_SendStr_Test(char* str)
{
	Serial_SendString(str);
}

void Serial_RxDataPacket_Test(void)
{
	if(Serial_RxFlag == 1){
		Serial_SendString("OK  ");
		Serial_SendString(Serial_RxData);
		Serial_RxFlag = 0;
		Serial_SendString("\n");
	}
}



