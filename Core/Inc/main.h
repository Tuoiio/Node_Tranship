/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Touch_1_Pin GPIO_PIN_0
#define Touch_1_GPIO_Port GPIOA

#define Touch_2_Pin GPIO_PIN_1
#define Touch_2_GPIO_Port GPIOA

#define Relay_1_Pin GPIO_PIN_8
#define Relay_1_GPIO_Port GPIOB

#define Relay_2_Pin GPIO_PIN_7
#define Relay_2_GPIO_Port GPIOB

#define SPI2_CS_Pin GPIO_PIN_8
#define SPI2_CS_GPIO_Port GPIOA

#define SPI2_CE_Pin GPIO_PIN_15
#define SPI2_CE_GPIO_Port GPIOA


#define Touch_Relay_1 HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)
#define Touch_Relay_2 HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
