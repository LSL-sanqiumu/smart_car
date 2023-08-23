#ifndef __ULTRASONIC_H__
#define __ULTRASONIC_H__

void HCSR04_Init(void);
void HCSR04_RangingStart(void);
uint16_t HCSR04_GetDistance(void);

void Key_Init(void);
uint8_t Key_GetKeyValue(void);

void HCSR04_Test(void);

#endif
