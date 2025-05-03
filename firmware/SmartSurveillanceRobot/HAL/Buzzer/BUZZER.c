/*
 * Module: Buzzer
 *
 * File Name: Buzzer.c
 *
 * Created on: Oct 4, 2024
 *
 * Author: Zeyad Hisham
 */

#include "BUZZER.h"
#include "../../MCAL/GPIO/gpio.h"


/* Set the buzzer pin as output */
void Buzzer_init(BUZZER *buzz) {
    GPIO_setupPinDirection(buzz->PORT, buzz->PIN, PIN_OUTPUT);
    Buzzer_off(buzz);
}


/* Turn on the buzzer */
void Buzzer_on(BUZZER *buzz) {
    GPIO_writePin(buzz->PORT, buzz->PIN, (LOGIC_HIGH ^ buzz->state));
}

/* Turn off the buzzer */
void Buzzer_off(BUZZER *buzz) {
    GPIO_writePin(buzz->PORT, buzz->PIN, (LOGIC_LOW ^ buzz->state));
}
