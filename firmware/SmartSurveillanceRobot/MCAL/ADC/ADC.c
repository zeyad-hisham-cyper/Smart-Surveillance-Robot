/*
 * Module: ADC
 *
 * File Name: ADC.c
 *
 * Created on: Oct 4, 2024
 *
 * Author: Zeyad Hisham
 */

#include "ADC.h"
#include "../common_macros.h"
#include "avr/io.h"

void ADC_init(void) {
	/* Set reference voltage to internal 2.56V */
	SET_BIT(ADMUX, REFS0);
	SET_BIT(ADMUX, REFS1);

	/* Right Adjust Result */
	CLEAR_BIT(ADMUX, ADLAR);

	/* Enable ADC */
	SET_BIT(ADCSRA, ADEN);

	/* Set ADC pre-scaler to 128 */
	SET_BIT(ADCSRA, ADPS0);
	SET_BIT(ADCSRA, ADPS1);
	SET_BIT(ADCSRA, ADPS2);
}

uint16 ADC_readChannel(ADC_Channel channel) {
	/* Clear the previous channel selection and set the required channel */
	ADMUX = (ADMUX & 0xE0) | (channel & 0x07);

	/* Start conversion */
	SET_BIT(ADCSRA, ADSC);

	/* Wait for conversion to complete (ADIF = 1) */
	while (BIT_IS_CLEAR(ADCSRA, ADIF));

	/* Clear ADIF by writing '1' */
	SET_BIT(ADCSRA, ADIF);

	/* Return the digital result */
	return ADC;
}
