/*
 * Ultrasonic.c
 *
 *  Created on: Oct 11, 2024
 *      Author: zeyad
 */

/*
 * Modules Includes
 */
#include "Ultrasonic.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/ICU/icu.h"
#include <util/delay.h>


/* ICU configuration structure */
ICU_ConfigType ICU_config = {.clock = F_CPU_8, .edge = RAISING };

/* Variables to store edge count and pulse duration */
uint8 edge_count = 0;
uint32 time_high = 0;


/* Initialize the ultrasonic sensor */
void Ultrasonic_init(Ultrasonic_t *Usonic) {
	ICU_init(&ICU_config); /* Initialize ICU with configuration */
	ICU_setCallBack(Ultrasonic_edgeProcessing); /* Set callback for edge processing */
	GPIO_setupPinDirection(Usonic->TRIGGER_PORT, Usonic->TRIGGER_PIN, PIN_OUTPUT); /* Set trigger pin as output */
}

/* Send trigger pulse to the ultrasonic sensor for 10 us */
void Ultrasonic_Trigger(Ultrasonic_t *Usonic) {
	GPIO_writePin(Usonic->TRIGGER_PORT, Usonic->TRIGGER_PIN, LOGIC_HIGH); /* Set the trigger pin */
	_delay_us(10); /* Wait for 10 microseconds */
	GPIO_writePin(Usonic->TRIGGER_PORT, Usonic->TRIGGER_PIN, LOGIC_LOW); /* clear the trigger pin */
}


uint16 Ultrasonic_readDistance(Ultrasonic_t *Usonic) {
	Ultrasonic_Trigger(Usonic);  /* Send 10µs trigger pulse */

	/* Wait for echo with timeout */
	uint16 timeout = 0;
	while (edge_count < 2 && timeout < ULTRASONIC_TIMEOUT_MS) {
		_delay_ms(1);
		timeout++;
	}

	if (edge_count < 2) {
		/* Echo not received — possibly out of range or blocked */
		edge_count = 0;
		return 0; /* Indicate failure */
	}

	edge_count = 0; /* Reset for next reading */

	/* Convert time_high (µs) to distance (cm) */
	return (uint16)((time_high + ERROR_MARGIN) * SPEED_CONVERSION_CM);
}
/* Handle the edge detection and timing for the ultrasonic sensor */
void Ultrasonic_edgeProcessing(void) {
	edge_count++; /* Increment edge count */
	if (edge_count == 1) {
		ICU_clearTimerValue(); /* Clear timer on first edge */
		ICU_setEdgeDetectionType(FALLING); /* Set edge detection to falling */
	} else if (edge_count == 2) {
		time_high = ICU_getInputCaptureValue(); /* Capture pulse duration */
		ICU_setEdgeDetectionType(RAISING); /* Set edge detection back to rising */
	}
}
