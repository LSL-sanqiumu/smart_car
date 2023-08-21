#ifndef __SERIAL_H__
#define __SERIAL_H__

void Serial_Init(void);
void Serial_SendByte(uint16_t byte);
void Serial_SendString(char* string);


#endif
