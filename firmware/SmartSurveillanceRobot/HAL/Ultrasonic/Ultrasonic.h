/*
 * Ultrasonic.h
 *
 *  Created on: Oct 11, 2024
 *      Author: zeyad
 */

#ifndef HAL_ULTRASONIC_ULTRASONIC_H_
#define HAL_ULTRASONIC_ULTRASONIC_H_

#include "../../MCAL/std_types.h"



/* Define an error margin for distance calculation, this value needs calibration */
#define ERROR_MARGIN 95

/* Structure to hold ultrasonic sensor pin configurations */
typedef struct {
	uint8 TRIGGER_PORT :2;
	uint8 TRIGGER_PIN :3;
	uint8 ECHO_PORT :2;
	uint8 ECHO_PIN :3;
} Ultrasonic_t;


/* Function prototypes */
void Ultrasonic_init(Ultrasonic_t *Usonic); /* Initialize ultrasonic sensor */
void Ultrasonic_Trigger(Ultrasonic_t *Usonic); /* Trigger ultrasonic sensor */
uint16 Ultrasonic_readDistance(Ultrasonic_t *Usonic); /* Read distance measured */
void Ultrasonic_edgeProcessing(void); /* Handle edge processing for echo signal */

#endif /* HAL_ULTRASONIC_ULTRASONIC_H_ */
