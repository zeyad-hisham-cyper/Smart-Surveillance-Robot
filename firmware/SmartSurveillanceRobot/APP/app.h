/******************************************************************************
 *
 * Module: Application
 *
 * File Name: app.h
 *
 * Description: Application layer header for the Smart Surveillance Robot.
 *              Contains macro definitions, type declarations, and function
 *              prototypes for system initialization and main loop control.
 *
 * Author: Amr & Zeyad Hisham
 *
 ******************************************************************************/

#ifndef APP_H_
#define APP_H_

/*******************************************************************************
 *                              Includes                                       *
 ******************************************************************************/

#include "../MCAL/GPIO/gpio.h"
#include "../MCAL/ADC/ADC.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/Ultrasonic/Ultrasonic.h"
#include "../HAL/DcMotor/Motor.h"
#include "../HAL/FlameSensor/Flame_Sensor.h"
#include "../HAL/LM35/lm35_sensor.h"
#include "../HAL/LDR/LDR.h"
#include "../HAL/LED/LED.h"
#include "../HAL/Buzzer/BUZZER.h"
#include "../HAL/MQ2/MQ2.h"
#include <util/delay.h>

/*******************************************************************************
 *                                Definitions                                  *
 ******************************************************************************/

#define SENSOR_SWITCHING_TIME 8  /* Time (ms) to switch between ultrasonic sensors */

#define LCD_STRING(str) ((const uint8 *)(str)) /* Macro to cast strings to LCD-compatible format */

/* Ultrasonic sensor trigger pin configurations */
#define ULTRASONIC_TRIGGER_1_2_PORT PORTD_ID
#define ULTRASONIC_TRIGGER_3_PORT   PORTB_ID

/* Ultrasonic sensor echo pin configuration (shared among sensors) */
#define ULTRASONIC_ECHO_PORT PORTD_ID
#define ULTRASONIC_ECHO_PIN  PIN6_ID

/* Specific ultrasonic trigger pin mapping */
#define ULTRASONIC_FRONT_TRIGGER_PIN PIN4_ID
#define ULTRASONIC_LEFT_TRIGGER_PIN  PIN5_ID
#define ULTRASONIC_RIGHT_TRIGGER_PIN PIN0_ID

/* DC motor direction control pins */
#define DCMOTORS_DIR_PORT    PORTC_ID
#define DCMOTOR_R_DIR_PINA   PIN2_ID
#define DCMOTOR_R_DIR_PINB   PIN3_ID
#define DCMOTOR_L_DIR_PINA   PIN4_ID
#define DCMOTOR_L_DIR_PINB   PIN5_ID

/* PWM pin configuration for speed control */
#define DCMOTOR_PWM_PORT     PORTB_ID
#define DCMOTOR_PWM_PIN      PIN3_ID
#define DCMOTOR_SPEED        50 /* Default speed percentage */

/* Movement direction enum */
typedef enum {
	FORWARD,
	RIGHT,
	LEFT,
	STOP
} Direction_t;

/* Flame sensor configuration */
#define FLAME_PORT PORTD_ID
#define FLAME_PIN  PIN3_ID

/* LM35 temperature sensor ADC channel */
#define TEMPERATURE_SENSOR_CHANNEL 1

/* LDR sensor ADC channel */
#define LDR_CHANNEL 2

/* Green LED configuration */
#define GREEN_LED_PORT PORTA_ID
#define GREEN_LED_PIN  PIN4_ID

/* Red LED configuration */
#define RED_LED_PORT   PORTA_ID
#define RED_LED_PIN    PIN3_ID

/* Buzzer configuration */
#define BUZZER_PORT    PORTA_ID
#define BUZZER_PIN     PIN6_ID

/* MQ-2 gas sensor configuration */
#define MQ2_PORT       PORTA_ID
#define MQ2_CHANNEL    PIN0_ID

/*******************************************************************************
 *                           External Variables                                *
 ******************************************************************************/

/* Ultrasonic sensor objects */
extern Ultrasonic_t frontDistanceSensor, leftDistanceSensor, rightDistanceSensor;

/* DC motor instances */
extern DcMotor rightMotor, leftMotor;

/* Flame sensor instance */
extern FlameSensor flameSensor;

/* LM35 temperature sensor instance */
extern LM35 tempSensor;

/* LDR sensor instance */
extern LDR LdrSensor;

/* LED instances */
extern LED_ID Green, Red;

/* Buzzer instance */
extern BUZZER Alarm;

/* MQ-2 gas sensor configuration */
extern MQ2_ConfigType gasSensor;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 ******************************************************************************/

/*
 * Description :
 * Initializes all hardware modules used in the application including:
 * sensors (ultrasonic, flame, gas, light, temperature),
 * actuators (DC motors, buzzer, LEDs),
 * and user interfaces (LCD).
 */
void app_init(void);

/*
 * Description :
 * Main application function responsible for:
 * - Reading sensor values
 * - Making decisions based on environment
 * - Controlling actuators and displaying information
 */
void app_run(void);

#endif /* APP_H_ */
