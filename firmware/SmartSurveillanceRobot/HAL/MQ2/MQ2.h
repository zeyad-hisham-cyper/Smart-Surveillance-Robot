/******************************************************************************
 *
 * Module: Gas Sensor (MQ2)
 *
 * File Name: mq2_sensor.h
 *
 * Description: Header file for the MQ2 Gas Sensor driver (Analog and Digital Modes)
 *
 * Author: Zeyad Hisham
 *
 ******************************************************************************/

#ifndef MQ2_SENSOR_H_
#define MQ2_SENSOR_H_

#include "../../MCAL/std_types.h"

/*******************************************************************************
 *                                Configurations                               *
 *******************************************************************************/

#define MQ2_SENSOR_MAX_VOLT_VALUE      1.5
#define MQ2_SENSOR_MAX_LEVEL           100  // Scale from 0 to 100 (percentage or arbitrary)

/*******************************************************************************
 *                                Types                                        *
 *******************************************************************************/

typedef enum {
    MQ2_MODE_ANALOG,
    MQ2_MODE_DIGITAL
} MQ2_Mode;

typedef struct {
    MQ2_Mode mode;
    union {
        uint8 analog_channel; // ADC channel number
        struct {
            uint8 port;
            uint8 pin;
        } digital_pin;
    } connection;
} MQ2_ConfigType;

/*******************************************************************************
 *                             Function Prototypes                             *
 *******************************************************************************/


/*
 * Description:
 * Initialize MQ2 sensor based on the selected mode.
 */
void MQ2_init(const MQ2_ConfigType* config_ptr);
/*
 * Description:
 * Get gas reading based on mode:
 * - Analog: returns gas level (0–100)
 * - Digital: returns HIGH/LOW (1/0)
 */
uint8 MQ2_getGasLevel(const MQ2_ConfigType* config_ptr);

#endif /* MQ2_SENSOR_H_ */
