#ifndef _MQ135_H_
#define _MQ135_H_

#include "stm32f1xx_hal.h"

#define MQ135_PORT GPIOA
#define MQ135_PIN GPIO_PIN_1

// The load resistance on the board
#define RLOAD 10.0

// Calibarition resistance at atmosoheric CO2 level
#define RZERO 76.63

/// Parameters for calculating ppm of CO2 from sensor resistance
#define PARA 116.6020682
#define PARB 2.769034857

/// Parameters to model temperature and humidity dependence
#define CORA 0.00035
#define CORB 0.02718
#define CORC 1.39538
#define CORD 0.0018

/// Atmospheric CO2 level for calibration purposes
#define ATMOCO2 397.13

float MQ135_GetCorrectionFactor(float t,	 float h);

float MQ135_GetResistance(void);

float MQ135_GetCorrectedResistance(float t, float h);

float MQ135_GetPPM(void);

float MQ135_GetCorrectedPPM(float t, float h);

float MQ135_GetRZero(void);

float MQ135_GetCorrectedRZero(float t, float h);

#endif
