/*
 * Module: Flame Sensor
 *
 * File Name: Flame_Sensor.c
 *
 * Created on: Oct 4, 2024
 *
 * Author: Zeyad Hisham
 */



#include "../../MCAL/GPIO/gpio.h"
#include "Flame_Sensor.h"


/* Initialize the sensor */
void FlameSensor_init(FlameSensor *flame) {
	GPIO_setupPinDirection(flame->PORT, flame->PIN, PIN_INPUT);
}

/* return the value of the flame sensor */
uint8 FlameSensor_getValue(FlameSensor *flame) {
	return (GPIO_readPin(flame->PORT, flame->PIN));
}
