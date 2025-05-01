/******************************************************************************
 *
 * File Name: app.c
 *
 * Description: Main application logic for the Smart Surveillance Robot.
 *              Handles initialization, sensor reading, decision-making, and motor control
 *              to avoid obstacles using ultrasonic sensors.
 *
 * Author: Amr & zeyad
 *
 ******************************************************************************/
#include "app.h"

// ========== Static Function Prototypes ==========

// Reads distance from a specific ultrasonic sensor
static uint8 App_ReadUltrasonic(Ultrasonic_t *sensor);

// Displays the distance readings on the LCD screen
static void App_DisplayDistances(uint8 front, uint8 right, uint8 left);

// Determines the direction with the maximum available distance
static Direction_t App_getMaxDistance(uint8 front, uint8 right, uint8 left);

// Controls robot movement based on direction
static void Robot_MovementControl(Direction_t direction);

// Functions for controlling specific robot directions
static void Robot_Forward(void);
static void Robot_Right(void);
static void Robot_Left(void);
static void Robot_STOP(void);

// ========== Application Initialization ==========

void app_init(void) {
	// Initialize the LCD display
	LCD_init();

	// Initialize all three ultrasonic sensors
	Ultrasonic_init(&frontDistanceSensor);
	Ultrasonic_init(&leftDistanceSensor);
	Ultrasonic_init(&rightDistanceSensor);

	// Initialize both DC motors (right and left)
	DcMotor_init(&rightMotor);
	DcMotor_init(&leftMotor);
}

// ========== Main Application Loop ==========

void app_run(void) {
	uint8 frontDistance, rightDistance, leftDistance;
	while (1) {
		// Read distance from each sensor
		frontDistance = App_ReadUltrasonic(&frontDistanceSensor);
		rightDistance = App_ReadUltrasonic(&rightDistanceSensor);
		leftDistance = App_ReadUltrasonic(&leftDistanceSensor);

		// Display the distances on LCD
		App_DisplayDistances(frontDistance, rightDistance, leftDistance);

		// Determine movement direction and control robot accordingly
		Robot_MovementControl(
				App_getMaxDistance(frontDistance, rightDistance, leftDistance));
	}
}

static uint8 App_ReadUltrasonic(Ultrasonic_t *sensor) {
	// Send a trigger pulse to the ultrasonic sensor
	Ultrasonic_Trigger(sensor);

	// Wait a short time for the sensor to settle (avoid overlap)
	_delay_ms(SENSOR_SWITCHING_TIME);

	// Return the measured distance
	return Ultrasonic_readDistance(sensor);
}

// ========== LCD Display Function ==========

static void App_DisplayDistances(uint8 front, uint8 right, uint8 left) {
	// Display front distance
	LCD_MoveCursor(0, 2);
	LCD_DisplayString(LCD_STRING("F"));
	LCD_MoveCursor(1, 0);
	LCD_intgerToString(front);
	LCD_DisplayString(LCD_STRING("cm"));

	// Display right distance
	LCD_MoveCursor(0, 7);
	LCD_DisplayString(LCD_STRING("R"));
	LCD_MoveCursor(1, 5);
	LCD_intgerToString(right);
	LCD_DisplayString(LCD_STRING("cm"));

	// Display left distance
	LCD_MoveCursor(0, 12);
	LCD_DisplayString(LCD_STRING("L"));
	LCD_MoveCursor(1, 10);
	LCD_intgerToString(left);
	LCD_DisplayString(LCD_STRING("cm"));
}

// ========== Direction Decision Function ==========

static Direction_t App_getMaxDistance(uint8 front, uint8 right, uint8 left) {
	// Choose the direction with the greatest distance
	if (front >= right && front >= left) {
		return FORWARD;
	} else if (right >= left) {
		return RIGHT;
	} else if (left > right) {
		return LEFT;
	}
	// Default to STOP if distances are unclear
	return STOP;
}

// ========== Movement Control Logic ==========

static void Robot_MovementControl(Direction_t direction) {
	switch (direction) {
	case FORWARD:
		Robot_Forward(); // Move forward
		break;
	case RIGHT:
		Robot_Right();   // Turn right
		break;
	case LEFT:
		Robot_Left();    // Turn left
		break;
	case STOP:
		Robot_STOP();    // Stop the robot
		break;
	default:
		Robot_Forward(); // Default case: move forward
		break;
	}
}
// ========== Motor Control Functions ==========

// Move both motors forward
static void Robot_Forward(void) {
	DcMotor_Rotate(&rightMotor, Anti_Clock_Wise, DCMOTOR_SPEED);
	DcMotor_Rotate(&leftMotor, Anti_Clock_Wise, DCMOTOR_SPEED);
}

// Rotate right by reversing the right motor
static void Robot_Right(void) {
	DcMotor_Rotate(&rightMotor, Clock_Wise, DCMOTOR_SPEED);
	DcMotor_Rotate(&leftMotor, Anti_Clock_Wise, DCMOTOR_SPEED);
}

// Rotate left by reversing the left motor
static void Robot_Left(void) {
	DcMotor_Rotate(&rightMotor, Anti_Clock_Wise, DCMOTOR_SPEED);
	DcMotor_Rotate(&leftMotor, Clock_Wise, DCMOTOR_SPEED);
}

// Stop both motors
static void Robot_STOP(void) {
	DcMotor_STOP(&rightMotor);
	DcMotor_STOP(&leftMotor);
}
