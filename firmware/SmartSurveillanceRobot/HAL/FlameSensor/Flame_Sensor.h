/*
 * Module: Flame Sensor
 *
 * File Name: Flame_Sensor.h
 *
 * Created on: Oct 4, 2024
 *
 * Author: Zeyad Hisham
 */

#ifndef FLAME_SENSOR_H_
#define FLAME_SENSOR_H_

/* Include Standard Types */
#include "../../MCAL/std_types.h"

/* Struct for flame sensor configuration: port, pin, and active state */
typedef struct {
	uint8 PORT :2; /* Port number (0-3) */
	uint8 PIN :3;  /* Pin number (0-7) */
} FlameSensor;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Initialize Sensor Pin */
void FlameSensor_init(FlameSensor *flame);
/* Get the Value of the sensor */
uint8 FlameSensor_getValue(FlameSensor *flame);

#endif /* FLAME_SENSOR_H_ */
