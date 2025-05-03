/*
 * Module: LDR
 *
 * File Name: LDR.h
 *
 * Created on: Oct 4, 2024
 *
 * Author: Zeyad Hisham
 */

#ifndef LDR_H_
#define LDR_H_

/* Includes Standard Types */
#include "../../MCAL/std_types.h"

/*
 * Definitions
 */

#define LDR_SENSOR_MAX_VOLT_VALUE 2.56
#define LDR_SENSOR_MAX_LIGHT_INTENSITY 100

/*
 * Create an LDR data type for LDR Channel
 * - This to increase the code readability
 */
typedef uint8 LDR;


/*Function to get the light intensity */
uint8 LDR_getLightIntensity(LDR LDR_Channel);

#endif /* LDR_H_ */
