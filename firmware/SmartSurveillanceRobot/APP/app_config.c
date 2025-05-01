/******************************************************************************
 *
 * File Name: app_config.c
 *
 * Description: onfiguration and initialization of ultrasonic sensors and DC motors
 *              used in the Smart Surveillance Robot.
 * Author: Amr & zeyad
 *
 ******************************************************************************/
#include "app.h"


/* Ultrasonic sensor configuration structure */
Ultrasonic_t frontDistanceSensor = { .TRIGGER_PORT = ULTRASONIC_TRIGGER_1_2_PORT,
									 .TRIGGER_PIN  = ULTRASONIC_FRONT_TRIGGER_PIN,
									 .ECHO_PORT = ULTRASONIC_ECHO_PORT,
									 .ECHO_PIN = ULTRASONIC_ECHO_PIN};

Ultrasonic_t leftDistanceSensor = { .TRIGGER_PORT = ULTRASONIC_TRIGGER_1_2_PORT,
									 .TRIGGER_PIN  = ULTRASONIC_LEFT_TRIGGER_PIN,
									 .ECHO_PORT = ULTRASONIC_ECHO_PORT,
									 .ECHO_PIN = ULTRASONIC_ECHO_PIN};
Ultrasonic_t rightDistanceSensor = { .TRIGGER_PORT = ULTRASONIC_TRIGGER_3_PORT,
									 .TRIGGER_PIN  = ULTRASONIC_RIGHT_TRIGGER_PIN,
									 .ECHO_PORT = ULTRASONIC_ECHO_PORT,
									 .ECHO_PIN = ULTRASONIC_ECHO_PIN};

/* DC motor configuration structure */
DcMotor rightMotor = {
		.DcMotor_DIR_PORT = DCMOTORS_DIR_PORT,
		.DcMotor_DIR_PINA = DCMOTOR_R_DIR_PINA,
		.DcMotor_DIR_PINB = DCMOTOR_R_DIR_PINB,
		.DCMotor_EN_PORT = DCMOTOR_PWM_PORT,
		.DcMotor_EN_PIN = DCMOTOR_PWM_PIN};

DcMotor leftMotor = {
		.DcMotor_DIR_PORT = DCMOTORS_DIR_PORT,
		.DcMotor_DIR_PINA = DCMOTOR_L_DIR_PINA,
		.DcMotor_DIR_PINB = DCMOTOR_L_DIR_PINB,
		.DCMotor_EN_PORT = DCMOTOR_PWM_PORT,
		.DcMotor_EN_PIN = DCMOTOR_PWM_PIN};
