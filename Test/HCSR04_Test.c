#include "stm32f10x.h"                  // Device header

#include "HCSR04.h"
#include "Delay.h"
#include "OLED.h"

void HCSR04_Test(void)
{
	HCSR04_Init();
	while(1){
		Delay_ms(2000);
		HCSR04_RangingStart();
		OLED_ShowNum(1,1,HCSR04_GetDistance(),5);
		OLED_ShowString(1,7,"mm");
	}
}




