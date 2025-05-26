/*
 * dash.h
 *
 *  Created on: May 26, 2025
 *      Author: zeyad
 */

#ifndef DASH_H_
#define DASH_H_


#include "MCAL/UART/uart.h"
#include "HAL/LCD/LCD.h"
#include "HAL/LED/LED.h"
#include "HAL/Buzzer/BUZZER.h"
#include "MCAL/GPIO/gpio.h"
#include "MCAL/std_types.h"
#include "MCAL/common_macros.h"
#include "util/delay.h"

#define TEMP_THRESHOLD   35
#define STOPING_TIME_MS	 1000
#define LIGHT_THRESHOLD  15
#define READY 0xAA
#define DONE 0xFF

/* Green LED configuration */
#define GREEN_LED_PORT PORTC_ID
#define GREEN_LED_PIN  PIN1_ID

/* Red LED configuration */
#define RED_LED_PORT   PORTC_ID
#define RED_LED_PIN    PIN0_ID

/* Buzzer configuration */
#define BUZZER_PORT    PORTC_ID
#define BUZZER_PIN     PIN5_ID


/*******************************************************************************
 *                                  LEDs Configuration                          *
 *******************************************************************************/

/*
 * Description:
 * Initialize the Green LED with its port, pin, and active mode.
 */
LED_ID Green = {
		.LED_PORT = GREEN_LED_PORT,
		.LED_PIN  = GREEN_LED_PIN,
		ACTIVE_HIGH
};

/*
 * Description:
 * Initialize the Red LED with its port, pin, and active mode.
 */
LED_ID Red = {
		.LED_PORT = RED_LED_PORT,
		.LED_PIN  = RED_LED_PIN,
		ACTIVE_HIGH
};

/*******************************************************************************
 *                             Buzzer Configuration                             *
 *******************************************************************************/

/*
 * Description:
 * Initialize the buzzer with its port, pin, and active mode.
 */
BUZZER Alarm = {
		.PORT  = BUZZER_PORT,
		.PIN   = BUZZER_PIN,
		.state = BUZZER_ACTIVE_HIGH
};

#endif /* DASH_H_ */
