#ifndef _DHT22_H_
#define _DHT22_H_

#include <stm32f1xx_hal.h>
#include <delay.h>



static void Set_Pin_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

static void Set_Pin_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

uint8_t DHT22_Start(void);


void DHT22_Read(void);

float DHT22_Humidity(void);

float DHT22_Temperature(void);

#endif
