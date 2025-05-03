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

#include "../std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ADC_MAXIMUM_VALUE    1023U
#define ADC_REF_VOLT_VALUE   2.56

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum {
	ADC_CHANNEL_0,
	ADC_CHANNEL_1,
	ADC_CHANNEL_2,
	ADC_CHANNEL_3,
	ADC_CHANNEL_4,
	ADC_CHANNEL_5,
	ADC_CHANNEL_6,
	ADC_CHANNEL_7
} ADC_Channel;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Function to initialize the ADC:
 * 1. Use AVCC = 2.56V internal reference
 * 2. Enable ADC
 * 3. Set pre-scaler = F_CPU/128
 */
void ADC_init(void);

/*
 * Description :
 * Function to read the analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(ADC_Channel channel);

#endif /* ADC_H_ */
