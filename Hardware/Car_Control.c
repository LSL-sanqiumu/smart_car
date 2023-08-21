#include "stm32f10x.h"                  // Device header
#include "Motor.h"
// turn right   turn left   revolve

void Car_SetGoForwardSpeed(int16_t speed)
{
	Motor_SetSpeed_Left(speed);
	Motor_SetSpeed_Right(speed);
}
void Car_SetGoBackwardSpeed(int16_t speed)
{
	Motor_SetSpeed_Left(speed);
	Motor_SetSpeed_Right(speed);
}
void Car_ForwardTurnLeft(void)
{
	Motor_SetSpeed_Left(-90);
	Motor_SetSpeed_Right(90);
}
void Car_ForwardTurnRight(void)
{
	Motor_SetSpeed_Left(90);
	Motor_SetSpeed_Right(-90);
}

void Car_InverseTurnLeft(void)
{
	Motor_SetSpeed_Left(90);
	Motor_SetSpeed_Right(-90);
}
void Car_InverseTurnRight(void)
{
	Motor_SetSpeed_Left(-90);
	Motor_SetSpeed_Right(90);
}



