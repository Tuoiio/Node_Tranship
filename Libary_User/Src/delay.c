#include <delay.h>


extern TIM_HandleTypeDef htim4;		/* Change "htim4" like htim1, htim2... according to which timer type(timer1 ,timer2...) you use, default is  timer4.*/
													// That TIM_HandleTypeDef htim4 come from main.c //
													


void Delay_us(uint16_t us){
	__HAL_TIM_SetCounter(&htim4, 0);
	while(__HAL_TIM_GET_COUNTER(&htim4) < us);
}

void Delay_ms(uint16_t ms){
	while(ms--){
		Delay_us(1000);
	}
}

