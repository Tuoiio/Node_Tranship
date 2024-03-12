#include <DHT22.h>

#define DHT22_PIN GPIO_PIN_9
#define DHT22_PORT GPIOB
#define Read_Pin HAL_GPIO_ReadPin (DHT22_PORT, DHT22_PIN)

static uint8_t  DHT22_Data[5];
static uint16_t pMillis, cMillis;

static void Set_Pin_Output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

static void Set_Pin_Input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

uint8_t DHT22_Start (void){
  uint8_t Response = 0;
  Set_Pin_Output(DHT22_PORT, DHT22_PIN);
  HAL_GPIO_WritePin (DHT22_PORT, DHT22_PIN, GPIO_PIN_RESET); 
  Delay_us(1500); 
  HAL_GPIO_WritePin (DHT22_PORT, DHT22_PIN, GPIO_PIN_SET);
  Delay_us(30); 
	
  Set_Pin_Input(DHT22_PORT, DHT22_PIN);
  Delay_us(40);
  if (!(Read_Pin)){
    Delay_us(80);
    if (Read_Pin) Response = 1;
  }
  pMillis = HAL_GetTick();
  cMillis = HAL_GetTick();
  while (Read_Pin && pMillis + 2 > cMillis)	cMillis = HAL_GetTick();
  return Response;
}

void DHT22_Read(void){
	uint8_t i, Shift = 0, Count = 0;
  for (i = 0; i < 40; i++){
	if(i % 8 == 0 && i != 0) { Count++, Shift = 0; }
	pMillis = HAL_GetTick();
    cMillis = HAL_GetTick();
    while (!(Read_Pin) && pMillis + 2 > cMillis)	cMillis = HAL_GetTick();
    Delay_us(35);
    if (!(Read_Pin))   // if the pin is low
      DHT22_Data[Count] = DHT22_Data[Count] & ~(1 << (7 - Shift));
    else
      DHT22_Data[Count] = DHT22_Data[Count] | (1 << (7 - Shift));
	Shift++;
    pMillis = HAL_GetTick();
    cMillis = HAL_GetTick();
    while (Read_Pin && pMillis + 2 > cMillis)		cMillis = HAL_GetTick();
  }
}


float DHT22_Humidity(void){
	int Temp;
	Temp = (DHT22_Data[0] << 8) | DHT22_Data[1];
	return (float)(Temp / 10.0);
}

float DHT22_Temperature(void){
	int Temp;
	Temp = (DHT22_Data[2] << 8) | DHT22_Data[3];
	if(Temp & 0x8000){
		Temp &= 0x7FFF;
		return (float)(Temp / -10.0);
	} else {
		return (float)(Temp / 10.0);
	}
}
