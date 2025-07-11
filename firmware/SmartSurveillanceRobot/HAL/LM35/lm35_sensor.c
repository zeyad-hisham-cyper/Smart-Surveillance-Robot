/******************************************************************************
 *
 * Module: Temperature Sensor
 *
 * File Name: lm35_sensor.h
 *
 * Description: source file for the LM35 Temperature Sensor driver
 *
 * Author: Zeyad Hisham
 *
 *******************************************************************************/

#include "lm35_sensor.h"
#include "../../MCAL/ADC/adc.h"

/*
 * Description :
 * Function responsible for calculate the temperature from the ADC digital value.
 */

uint8 LM35_getTemperature(LM35 channel_num) {
	uint8 temp_value = 0;

	uint16 adc_value = 0;

	/* Read ADC channel where the temperature sensor is connected */
	adc_value = ADC_readChannel(channel_num);

	/* Calculate the temperature from the ADC value*/
	temp_value = (uint8) (((uint32) adc_value * SENSOR_MAX_TEMPERATURE
					* ADC_REF_VOLT_VALUE)
					/ (ADC_MAXIMUM_VALUE * SENSOR_MAX_VOLT_VALUE));

	return temp_value;
}

