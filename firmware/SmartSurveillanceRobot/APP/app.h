/******************************************************************************
 *
 * File Name: app.h
 *
 * Description:Application layer header for the Smart Surveillance Robot.
 *              Defines macros, data types, and function prototypes.
 *
 * Author: Amr & zeyad
 *
 ******************************************************************************/
// Include necessary headers from MCAL and HAL layers
#include "../MCAL/GPIO/gpio.h"         // GPIO driver for digital pin control
#include "../MCAL/PWM/PWM.h"           // PWM driver for motor speed control
#include "../HAL/LCD/LCD.h"            // LCD driver for display output
#include "../HAL/Ultrasonic/Ultrasonic.h"  // Ultrasonic sensor driver for obstacle detection
#include "../HAL/DcMotor/Motor.h"      // DC Motor driver for robot movement
#include "../HAL/FlameSensor/Flame_Sensor.h"
#include "../HAL/LM35/lm35_sensor.h"
#include "../HAL/LDR/LDR.h"
#include "../HAL/LED/LED.h"
#include "../HAL/Buzzer/BUZZER.h"
#include <util/delay.h>                // AVR delay utility for timing

// Define the time in milliseconds to switch between ultrasonic sensors
#define SENSOR_SWITCHING_TIME 8

// Macro to convert string literals to LCD-compatible string format
#define LCD_STRING(str) ((const uint8 *)(str))

// Port definitions for ultrasonic sensor trigger pins
#define ULTRASONIC_TRIGGER_1_2_PORT PORTD_ID  // Trigger port for front and left sensors
#define ULTRASONIC_TRIGGER_3_PORT    PORTB_ID // Trigger port for right sensor

// Port and pin definitions for ultrasonic echo (common for all sensors)
#define ULTRASONIC_ECHO_PORT PORTD_ID // Echo pin port
#define ULTRASONIC_ECHO_PIN  PIN6_ID  // Echo pin number

// Specific trigger pin assignments for each direction
#define ULTRASONIC_FRONT_TRIGGER_PIN PIN4_ID  // Front sensor trigger
#define ULTRASONIC_LEFT_TRIGGER_PIN  PIN5_ID  // Left sensor trigger
#define ULTRASONIC_RIGHT_TRIGGER_PIN PIN0_ID  // Right sensor trigger

// Motor direction control pin definitions
#define DCMOTORS_DIR_PORT   PORTC_ID  // Motor direction control port
#define DCMOTOR_R_DIR_PINA  PIN2_ID   // Right motor direction A pin
#define DCMOTOR_R_DIR_PINB  PIN3_ID   // Right motor direction B pin
#define DCMOTOR_L_DIR_PINA  PIN4_ID   // Left motor direction A pin
#define DCMOTOR_L_DIR_PINB  PIN5_ID   // Left motor direction B pin

// PWM pin configuration for motor speed control
#define DCMOTOR_PWM_PORT PORTB_ID     // PWM port
#define DCMOTOR_PWM_PIN  PIN3_ID      // PWM pin for motor speed

// Default motor speed percentage (0 to 100)
#define DCMOTOR_SPEED 50

// Enum for possible movement directions
typedef enum {
	FORWARD,  // Move forward
	RIGHT,    // Turn right
	LEFT,     // Turn left
	STOP      // Stop movement
} Direction_t;


#define FLAME_PORT PORTD_ID
#define FLAME_PIN  PIN3_ID

#define TEMPERATURE_SENSOR_CHANNEL 1
#define LDR_CHANNEL 2

#define GREEN_LED_PORT PORTA_ID
#define GREEN_LED_PIN PIN4_ID

#define RED_LED_PORT PORTA_ID
#define RED_LED_PIN PIN3_ID

#define BUZZER_PORT PORTA_ID
#define BUZZER_PIN  PIN6_ID

// External declarations for sensor and motor instances (defined in app.c)
extern Ultrasonic_t frontDistanceSensor, leftDistanceSensor,
		rightDistanceSensor;
extern DcMotor rightMotor, leftMotor;

extern FlameSensor flameSensor;
extern LM35 tempSensor;
extern LDR LdrSensor;
extern LED_ID Green;
extern LED_ID Red;
extern BUZZER Alarm;
// Function to initialize all components and peripherals
void app_init(void);

// Function that runs the main application logic
void app_run(void);
