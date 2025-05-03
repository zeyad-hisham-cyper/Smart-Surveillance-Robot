/******************************************************************************
 *
 * Module: Gas Sensor (MQ2)
 *
 * File Name: mq2_sensor.c
 *
 * Description: Source file for the MQ2 Gas Sensor driver (Analog and Digital Modes)
 *
 * Author: Zeyad Hisham
 *
 ******************************************************************************/

#include "MQ2.h"
#include "../../MCAL/ADC/adc.h"
#include "../../MCAL/GPIO/gpio.h"

void MQ2_init(const MQ2_ConfigType *config_ptr) {
	if (config_ptr->mode == MQ2_MODE_DIGITAL) {
		GPIO_setupPinDirection(config_ptr->connection.digital_pin.port,
				config_ptr->connection.digital_pin.pin, PIN_INPUT);
	}
}
uint8 MQ2_getGasLevel(const MQ2_ConfigType *config_ptr) {
	if (config_ptr->mode == MQ2_MODE_ANALOG) {
		uint16 adc_val = ADC_readChannel(config_ptr->connection.analog_channel);

		return (uint8) (((uint32) adc_val * MQ2_SENSOR_MAX_LEVEL
				* ADC_REF_VOLT_VALUE)
				/ (ADC_MAXIMUM_VALUE * MQ2_SENSOR_MAX_VOLT_VALUE));
	}
	/* MQ2_MODE_DIGITAL */

	else {
		return GPIO_readPin(config_ptr->connection.digital_pin.port,
				config_ptr->connection.digital_pin.pin);
	}
}
