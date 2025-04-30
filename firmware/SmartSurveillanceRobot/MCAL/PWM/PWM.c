/*
 * Module: PWM
 *
 * File Name: PWM.c
 *
 * Created on: Oct 4, 2024
 *
 * Author: Zeyad Hisham
 */

#include "PWM.h"
#include <avr/io.h>

/*
 *  Initializes Timer0 for PWM mode and sets the duty cycle.
 */
void PWM_Timer0_Start(uint8 duty_cycle) {
	DDRB |= (1 << PB3);  /* Set PB3 (OC0) as output for PWM */
	TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM01); /* Set Fast PWM mode and clear on compare match */
	TCCR0 = ((TCCR0 & PWM_RESET_PRESCALER_BITS) | PWM_F_CPU_64); /* Start Timer0 with prescaler of 1024 */
	OCR0 = (uint8) (((uint16) duty_cycle * 255) / 100); /* Set the duty cycle when the given is percentage (0/100)% */
}
