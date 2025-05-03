/*
 * Module: ADC
 *
 * File Name: ADC.h
 *
 * Created on: Oct 4, 2024
 *
 * Author: Zeyad Hisham
 */

#ifndef ADC_H_
#define ADC_H_

//#define ADC_INTERRUPT_ENABLE  /* Uncomment to enable ADC interrupt mode */

#include "../std_types.h"

/* ADC Configuration Definitions */
#define ADC_MAXIMUM_VALUE    1023  /* Maximum ADC value for 10-bit resolution */
#define ADC_REF_VOLT_VALUE   5     /* Reference voltage in volts (for calculations) */

/* Enum for reference voltage options */
typedef enum {
    ADC_REF_VOLT_AREF,       /* External reference */
    ADC_REF_VOLT_AVCC,       /* AVcc reference */
    ADC_REF_VOLT_RESERVED,    /* Reserved */
    ADC_REF_VOLT_INTERNAL     /* Internal reference */
} ADC_REF_VOLT;

/* Enum for available ADC channels */
typedef enum {
    /* Single-ended channels */
    ADC_CHANNEL_0,
    ADC_CHANNEL_1,
    ADC_CHANNEL_2,
    ADC_CHANNEL_3,
    ADC_CHANNEL_4,
    ADC_CHANNEL_5,
    ADC_CHANNEL_6,
    ADC_CHANNEL_7,

    /* Differential channels */
    ADC_DIFF_CHANNEL_ADC0_ADC0_G10,
    ADC_DIFF_CHANNEL_ADC1_ADC0_G10,
    ADC_DIFF_CHANNEL_ADC0_ADC0_G200,
    ADC_DIFF_CHANNEL_ADC1_ADC0_G200,
    ADC_DIFF_CHANNEL_ADC2_ADC2_G10,
    ADC_DIFF_CHANNEL_ADC3_ADC2_G10,
    ADC_DIFF_CHANNEL_ADC2_ADC2_G200,
    ADC_DIFF_CHANNEL_ADC3_ADC2_G200,
    ADC_DIFF_CHANNEL_ADC0_ADC1_G1,
    ADC_DIFF_CHANNEL_ADC1_ADC1_G1,
    ADC_DIFF_CHANNEL_ADC2_ADC1_G1,
    ADC_DIFF_CHANNEL_ADC3_ADC1_G1,
    ADC_DIFF_CHANNEL_ADC4_ADC1_G1,
    ADC_DIFF_CHANNEL_ADC5_ADC1_G1,
    ADC_DIFF_CHANNEL_ADC6_ADC1_G1,
    ADC_DIFF_CHANNEL_ADC7_ADC1_G1,
    ADC_DIFF_CHANNEL_ADC0_ADC2_G1,
    ADC_DIFF_CHANNEL_ADC1_ADC2_G1,
    ADC_DIFF_CHANNEL_ADC2_ADC2_G1,
    ADC_DIFF_CHANNEL_ADC3_ADC2_G1,
    ADC_DIFF_CHANNEL_ADC4_ADC2_G1,
    ADC_DIFF_CHANNEL_ADC5_ADC2_G1,

    /* Additional channels */
    ADC_CHANNEL_VBG,
    ADC_CHANNEL_GND
} ADC_CHANNEL;

/* Enum for ADC prescaler options */
typedef enum {
    ADC_PRE_SCALER_2 = 1,
    ADC_PRE_SCALER_4,
    ADC_PRE_SCALER_8,
    ADC_PRE_SCALER_16,
    ADC_PRE_SCALER_32,
    ADC_PRE_SCALER_64,
    ADC_PRE_SCALER_128
} ADC_PRESCALER;

/* Structure to hold ADC configuration parameters */
typedef struct {
    ADC_REF_VOLT REF_Volt : 2;   /* Reference voltage selection */
    ADC_PRESCALER Pre_scaler : 3; /* Prescaler selection */
} ADC_t;

extern ADC_t ADC_object; /* ADC object for configuration */

#ifdef ADC_INTERRUPT_ENABLE
extern volatile uint16 ADC_result; /* ADC result variable for interrupt mode */
#endif

/*************
 * Functions *
 *************/
/* Function to initialize the ADC with specified configuration */
void ADC_init(ADC_t *ADC_OBJECT);

/* Function to read the analog signal from a given channel.
 * Returns the ADC value for the selected channel.
 */
uint16 ADC_readChannel(ADC_CHANNEL ch_num);

#endif /* ADC_H_ */
