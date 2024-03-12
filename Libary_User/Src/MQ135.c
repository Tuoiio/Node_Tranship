#include "MQ135.h"
#include <math.h>

extern uint16_t Buffer_ADC;
float MQ135_GetCorrectionFactor(float t, float h){
	return CORA * t * t - CORB * t + CORC - (h - 33.0f) *CORD;
}


float MQ135_GetResistance(void)
{
	int val = Buffer_ADC;
	return ((4095.0f / (float)val) * 5.0f - 1.0f) * RLOAD;
}

float MQ135_GetCorrectedResistance(float t, float h)
{
	return MQ135_GetResistance() / MQ135_GetCorrectionFactor(t,h);
}

float MQ135_GetPPM()
{
	return PARA * pow((MQ135_GetResistance() / RZERO), -PARB);
}



float MQ135_GetCorrectedPPM(float t, float h)
{
	return PARA * pow((MQ135_GetCorrectedResistance(t, h) / RZERO), -PARB);
}

float MQ135_GetRZero(void)
{
	  return MQ135_GetResistance() * pow((ATMOCO2 / PARA), (1.0f / PARB));
}


float MQ135_GetCorrectedRZero(float t, float h)
{
	return MQ135_GetCorrectedResistance(t, h) * pow((ATMOCO2 / PARA), (1.0f / PARB));
}
