// update relay and touch sensor
#include "main.h"
#include "MY_NRF24.h"

SPI_HandleTypeDef hspi2;

typedef struct {
	char ID;
	float nhietDo;
	float doAm;
	float CO2;
} Data_Air_t;

typedef struct {
	char ID;
	uint8_t Button1;
	uint8_t Button2;
}Data_Button_t;

uint64_t Address_GateWay = 0x1122334411;
uint64_t Address_NodeAir = 0x1122334422;

//Sau khi mat dien se tu dong gui lai den gateway de dong bo voi Inventor
_Bool Click_On = 1;
_Bool ReTransmit = 1;


Data_Air_t Value_Air;
Data_Button_t Value_Button;

static uint32_t TimeOut1, TimeOut2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI2_Init(void);
/* USER CODE BEGIN PFP */
void Read_And_Control(void);
/* USER CODE END PFP */


/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)

{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_SPI2_Init();
  
	NRF24_Begin(hspi2, GPIOA, SPI2_CS_Pin, SPI2_CE_Pin);
	NRF24_OpenWritingPipe(Address_GateWay);
	NRF24_OpenReadingPipe(1, Address_GateWay);
	NRF24_OpenReadingPipe(2, Address_NodeAir);
	NRF24_SetChannel(52);
	NRF24_SetDataRate(RF24_250KBPS);
	NRF24_SetPALevel(RF24_PA_0dB);
	NRF24_EnableDynamicPayloads();
	NRF24_SetAutoAck(true);
	NRF24_SetRetries(10,15);
	NRF24_StartListening();
	
	

	TimeOut1 = HAL_GetTick();
	
  while (1)
  {
    /* USER CODE END WHILE */
		// Wait GateWay send data
		if(NRF24_Available()){
			uint8_t u8Length;
			u8Length = NRF24_GetDynamicPayloadSize();
			char *myRX_Data = (char*)calloc(u8Length, sizeof(char));
			
			if( myRX_Data != NULL) {
				NRF24_Read(myRX_Data, u8Length);
			
				if(myRX_Data[0] == 'D') {	// From GateWay
					HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
					if(myRX_Data[1] == 1) HAL_GPIO_WritePin(Relay_1_GPIO_Port, Relay_1_Pin, GPIO_PIN_RESET);
					else 							HAL_GPIO_WritePin(Relay_1_GPIO_Port, Relay_1_Pin, GPIO_PIN_SET);
				
					if(myRX_Data[2] == 1) HAL_GPIO_WritePin(Relay_2_GPIO_Port, Relay_2_Pin, GPIO_PIN_RESET);
					else							HAL_GPIO_WritePin(Relay_2_GPIO_Port, Relay_2_Pin, GPIO_PIN_SET);

				}
				if(myRX_Data[0] == 'C'){	// From Node Air
					memcpy(&Value_Air, myRX_Data, sizeof(Value_Air));
					HAL_Delay(5);
					Value_Air.ID = 'B';
					NRF24_StopListening();
					NRF24_Write(&Value_Air, sizeof(Value_Air));
					NRF24_StartListening();	
				}
			}
			free(myRX_Data);
		}
		// Neu node 1 co dien nhung node gateway chua co dien thi bien ReTransmit se bang 0 va se gui lai trong 500ms
		if( (Click_On == 1 || ReTransmit == 0) && ((uint32_t)(HAL_GetTick() - TimeOut2 > 500)) ){
			Value_Button.ID = 'D';
			NRF24_StopListening();
			ReTransmit = NRF24_Write(&Value_Button, sizeof(Value_Button));
			NRF24_StartListening();
			Click_On = 0;
			TimeOut2 = HAL_GetTick();
		}
		
		Read_And_Control();

	
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
 __HAL_RCC_GPIOC_CLK_ENABLE();
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, Relay_1_Pin|Relay_2_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SPI2_CS_Pin|SPI2_CE_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : Touch_1_Pin Touch_2_Pin */
  GPIO_InitStruct.Pin = Touch_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  
    GPIO_InitStruct.Pin = Touch_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : Relay_1_Pin Relay_2_Pin */
  GPIO_InitStruct.Pin = Relay_1_Pin|Relay_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  
  /*Configure GPIO pins : SPI2_CS_Pin SP2_CE_Pin */
  GPIO_InitStruct.Pin = SPI2_CS_Pin|SPI2_CE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void Read_And_Control(void)
{
	static _Bool States_Old_Button_1, States_Old_Button_2;
	if(Touch_Relay_1){
		if(Touch_Relay_1 && !States_Old_Button_1){
			// Reverse Relay 1
			HAL_GPIO_TogglePin(Relay_1_GPIO_Port, Relay_1_Pin);
			if( HAL_GPIO_ReadPin(Relay_1_GPIO_Port, Relay_1_Pin) == 0){
				Value_Button.Button1 = 1;
			} else {
				Value_Button.Button1 = 0;
			}
			Click_On = 1;
		}
	}
	States_Old_Button_1 = Touch_Relay_1;
	
	if(Touch_Relay_2){
		if(Touch_Relay_2 && !States_Old_Button_2){
			// Reverse Relay 2
			HAL_GPIO_TogglePin(Relay_2_GPIO_Port, Relay_2_Pin);
			if( HAL_GPIO_ReadPin(Relay_2_GPIO_Port, Relay_2_Pin) == 0){
				Value_Button.Button2 = 1;
			} else {
				Value_Button.Button2 = 0;
			}
			Click_On = 1;
		}
	}
	States_Old_Button_2 = Touch_Relay_2;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
