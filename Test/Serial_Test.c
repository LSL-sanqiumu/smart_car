#include "stm32f10x.h"                  // Device header

#include "Serial.h"

extern char Rx_DataPacket[100];
extern uint8_t Rx_DataFlag;

void Serial_SendStr_Test(char* str)
{
	Serial_SendString(str);
}

void Serial_RxDataPacket_Test(void)
{
	if(Rx_DataFlag == 1){
		Serial_SendString("OK  ");
		Serial_SendString(Rx_DataPacket);
		Rx_DataFlag = 0;
		Serial_SendString("\n");
	}
}



