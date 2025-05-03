/*
 * Module: LDR
 *
 * File Name: LDR.c
 *
 * Created on: Oct 4, 2024
 *
 * Author: Zeyad Hisham
 */

#include "LDR.h"
#include "../../MCAL/ADC/ADC.h"

/* Function to calculate and return the Light Intensity */
uint8 LDR_getLightIntensity(LDR LDR_Channel)
{

	uint8 light_intensity = 0;
	uint16 ADC_value = 0;

	ADC_value = ADC_readChannel(LDR_Channel);
	light_intensity = (uint8) (((uint32) ADC_value
			* LDR_SENSOR_MAX_LIGHT_INTENSITY * ADC_REF_VOLT_VALUE)
			/ (ADC_MAXIMUM_VALUE * LDR_SENSOR_MAX_VOLT_VALUE));

	return light_intensity;
}
