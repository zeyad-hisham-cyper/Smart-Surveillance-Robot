/******************************************************************************
 *
 * File Name: app_config.c
 *
 * Description: Configuration and initialization of ultrasonic sensors,
 *              DC motors, and other peripherals used in the Smart Surveillance Robot.
 *
 * Author: Amr & Zeyad
 *
 *******************************************************************************/

#include "app.h"

/*******************************************************************************
 *                           Ultrasonic Sensors Configuration                  *
 *******************************************************************************/

/*
 * Description:
 * Initialize the front ultrasonic sensor with its corresponding trigger and echo pins.
 */
Ultrasonic_t frontDistanceSensor = {
		.TRIGGER_PORT = ULTRASONIC_TRIGGER_1_2_PORT,
		.TRIGGER_PIN  = ULTRASONIC_FRONT_TRIGGER_PIN,
		.ECHO_PORT    = ULTRASONIC_ECHO_PORT,
		.ECHO_PIN     = ULTRASONIC_ECHO_PIN
};

/*
 * Description:
 * Initialize the left ultrasonic sensor with its corresponding trigger and echo pins.
 */
Ultrasonic_t leftDistanceSensor = {
		.TRIGGER_PORT = ULTRASONIC_TRIGGER_1_2_PORT,
		.TRIGGER_PIN  = ULTRASONIC_LEFT_TRIGGER_PIN,
		.ECHO_PORT    = ULTRASONIC_ECHO_PORT,
		.ECHO_PIN     = ULTRASONIC_ECHO_PIN
};

/*
 * Description:
 * Initialize the right ultrasonic sensor with its corresponding trigger and echo pins.
 */
Ultrasonic_t rightDistanceSensor = {
		.TRIGGER_PORT = ULTRASONIC_TRIGGER_3_PORT,
		.TRIGGER_PIN  = ULTRASONIC_RIGHT_TRIGGER_PIN,
		.ECHO_PORT    = ULTRASONIC_ECHO_PORT,
		.ECHO_PIN     = ULTRASONIC_ECHO_PIN
};

/*******************************************************************************
 *                           DC Motors Configuration                           *
 *******************************************************************************/

/*
 * Description:
 * Configure the right DC motor with direction and PWM control pins.
 */
DcMotor rightMotor = {
		.DcMotor_DIR_PORT = DCMOTORS_DIR_PORT,
		.DcMotor_DIR_PINA = DCMOTOR_R_DIR_PINA,
		.DcMotor_DIR_PINB = DCMOTOR_R_DIR_PINB,
		.DCMotor_EN_PORT  = DCMOTOR_PWM_PORT,
		.DcMotor_EN_PIN   = DCMOTOR_PWM_PIN
};

/*
 * Description:
 * Configure the left DC motor with direction and PWM control pins.
 */
DcMotor leftMotor = {
		.DcMotor_DIR_PORT = DCMOTORS_DIR_PORT,
		.DcMotor_DIR_PINA = DCMOTOR_L_DIR_PINA,
		.DcMotor_DIR_PINB = DCMOTOR_L_DIR_PINB,
		.DCMotor_EN_PORT  = DCMOTOR_PWM_PORT,
		.DcMotor_EN_PIN   = DCMOTOR_PWM_PIN
};

/*******************************************************************************
 *                           Flame Sensor Configuration                         *
 *******************************************************************************/

/*
 * Description:
 * Initialize the flame sensor with its assigned port and pin.
 */
FlameSensor flameSensor = {
		.PORT = FLAME_PORT,
		.PIN  = FLAME_PORT
};

/*******************************************************************************
 *                           Temperature and Light Sensors                      *
 *******************************************************************************/

/*
 * Description:
 * Configure the LM35 temperature sensor channel.
 */
LM35 tempSensor = TEMPERATURE_SENSOR_CHANNEL;

/*
 * Description:
 * Configure the LDR (Light Dependent Resistor) sensor channel.
 */
LDR LdrSensor = LDR_CHANNEL;

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

/*******************************************************************************
 *                              MQ2 Gas Sensor Configuration                    *
 *******************************************************************************/

/*
 * Description:
 * Initialize the MQ2 gas sensor in digital mode with the selected port and pin.
 */
MQ2_ConfigType gasSensor = {
		.mode = MQ2_MODE_DIGITAL,
		.connection.digital_pin = {
				MQ2_PORT,
				MQ2_CHANNEL
		}
};
