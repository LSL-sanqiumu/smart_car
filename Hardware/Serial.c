/*
**********************************************************
*
*	模块名称 : 串口模块
*	文件名称 : Serial.c
*	版	本 : V1.0
*	说	明 : 串口实现：字符发送、数据包接收
*	修改记录 : 
*		版本号     日期        作者        说明
*		v1.0	2023-08-022     lsl    利用DHT11的单总线协议实现驱动
*
**********************************************************
*/

#include "stm32f10x.h"                  // Device header

uint8_t Rx_DataFlag;
char Rx_DataPacket[100];

void Serial_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = 9600;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART3, &USART_InitStruct);
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStruct);
	
	USART_Cmd(USART3, ENABLE);
}

void Serial_SendByte(uint16_t byte)
{
	USART_SendData(USART3, byte);
	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
}

void Serial_SendString(char* string)
{
	uint16_t i;
	for(i = 0; string[i] != '\0';i++){
		Serial_SendByte(string[i]);
	}
}

void USART3_IRQHandler(void)
{
	static uint8_t rx_state = 0;
	static uint8_t rx_data_index = 0;
	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET){
		uint16_t rx_data = USART_ReceiveData(USART3);
		if(rx_state == 0){
			if(rx_data == '@' && Rx_DataFlag == 0){
				rx_state = 1;
				rx_data_index = 0;
			}
		}else if(rx_state == 1){
			if(rx_data == '\r'){
				rx_state = 2;
			}else{
				Rx_DataPacket[rx_data_index] = rx_data;
				rx_data_index++;
			}
		}else if(rx_state == 2){
			if(rx_data == '\n'){
				rx_state = 0;
				Rx_DataPacket[rx_data_index] = '\0';
				Rx_DataFlag = 1;
			}
		}
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
	}
}


