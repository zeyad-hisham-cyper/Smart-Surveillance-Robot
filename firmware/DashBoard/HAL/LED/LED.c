/*
 * Module: LED
 *
 * File Name: LED.c
 *
 * Created on: Oct 4, 2024
 *
 * Author: Zeyad Hisham
 */

#include "LED.h"
#include "../../MCAL/GPIO/gpio.h"

/*
 * Function to initialize the LED
 */
void LED_init(LED_ID *id) {
	GPIO_setupPinDirection(id->LED_PORT, id->LED_PIN, PIN_OUTPUT);
	LED_off(id);
}
/*
 * Function to Turn LED on
 */
void LED_on(LED_ID *id) {
	GPIO_writePin(id->LED_PORT, id->LED_PIN, (LOGIC_HIGH ^ id->STATE));
}
/*
 * Function to Turn LED off
 */
void LED_off(LED_ID *id) {
	GPIO_writePin(id->LED_PORT, id->LED_PIN, (LOGIC_LOW ^ id->STATE));
}
