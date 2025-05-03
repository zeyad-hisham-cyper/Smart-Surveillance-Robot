/*
 * Module: ADC
 *
 * File Name: ADC.c
 *
 * Created on: Oct 4, 2024
 *
 * Author: Zeyad Hisham
 */

#include "../common_macros.h"
#include "../GPIO/gpio.h"
#include "ADC.h"
#include "avr/io.h"
#ifdef ADC_INTERRUPT_ENABLE
#include "avr/interrupt.h"
#endif

/* ADC object with default reference voltage and prescaler */
ADC_t ADC_object = { .REF_Volt = ADC_REF_VOLT_AREF, .Pre_scaler = ADC_PRE_SCALER_8 };

#ifdef ADC_INTERRUPT_ENABLE
/* ADC result variable for interrupt mode */
volatile uint16 ADC_result = 0;

/* ISR to handle ADC conversion complete interrupt */
ISR(ADC_vect) {
	ADC_result = ADC;  /* Store the ADC result */
}
#endif

/* Function to initialize the ADC with reference voltage and prescaler */
void ADC_init(ADC_t *ADC_OBJECT) {
	/* Set reference voltage */
	ADMUX = (ADMUX & 0x3F) | (ADC_OBJECT->REF_Volt);

	/* Enable ADC */
	SET_BIT(ADCSRA, ADEN);

	/* Set the prescaler value */
	ADCSRA = (ADCSRA & 0xF8) | (ADC_OBJECT->Pre_scaler);

#ifdef ADC_INTERRUPT_ENABLE
	/* Enable ADC interrupt and global interrupt */
	SET_BIT(ADCSRA, ADIE);
	sei();
#endif
}

/* Function to read the ADC value from a specific channel */
uint16 ADC_readChannel(uint8 ch_num) {
	/* Select the ADC channel */
	ADMUX = (ADMUX & 0xE0) | (ch_num & 0x1F);

	/* Start conversion */
	SET_BIT(ADCSRA, ADSC);

#ifdef ADC_INTERRUPT_ENABLE
	/* Return the result stored by the interrupt */
	return ADC_result;
#else
	/* Wait until conversion is complete */
	while (GET_BIT(ADCSRA, ADIF) == 0);

	/* Clear the ADC interrupt flag */
	SET_BIT(ADCSRA, ADIF);

	/* Return the ADC result */
	return ADC;
#endif
}
