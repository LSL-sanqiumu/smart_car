#ifndef __CAR_H__
#define __CAR_H__

void Car_SetGoForwardSpeed(int16_t speed);
void Car_SetGoBackwardSpeed(int16_t speed);

void Car_ForwardTurnLeft(void);
void Car_ForwardTurnRight(void);

void Car_InverseTurnLeft(void);
void Car_InverseTurnRight(void);

void Car_ManualMode(uint8_t* flag, char* command);

#endif
