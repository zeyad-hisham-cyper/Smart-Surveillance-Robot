/******************************************************************************
 *
 * File Name: app.c
 *
 * Description: Main application logic for the Smart Surveillance Robot.
 *              Handles initialization, sensor reading, decision-making, and motor control
 *              to avoid obstacles using ultrasonic sensors.
 *
 * Author: Amr & Zeyad
 *
 ******************************************************************************/

#include "app.h"

/*******************************************************************************
 *                           Static Function Prototypes                        *
 ******************************************************************************/

/*
 * Description:
 * Reads the distance from the given ultrasonic sensor.
 */
static uint8 App_ReadUltrasonic(Ultrasonic_t *sensor);

/*
 * Description:
 * Displays the distances from the front, right, and left ultrasonic sensors on the LCD.
 */
static void App_DisplayDistances(uint8 front, uint8 right, uint8 left);

/*
 * Description:
 * Determines the direction that has the maximum distance (free path).
 */
static Direction_t App_getMaxDistance(uint8 front, uint8 right, uint8 left);

/*
 * Description:
 * Controls the robot movement based on the direction decision.
 */
static void Robot_MovementControl(Direction_t direction);

/*
 * Description:
 * Makes the robot move forward.
 */
static void Robot_Forward(void);

/*
 * Description:
 * Makes the robot turn right.
 */
static void Robot_Right(void);

/*
 * Description:
 * Makes the robot turn left.
 */
static void Robot_Left(void);

/*
 * Description:
 * Stops the robot.
 */
static void Robot_STOP(void);

static void APP_scanEnvironment(void);
static void App_DisplayReadings(void);
static void APP_handleAlerts(void);
/*******************************************************************************
 *                           Application Initialization                        *
 ******************************************************************************/

void app_init(void) {
	/* Initialize the LCD display */
	LCD_init();
	ADC_init();

	/* Initialize the ultrasonic sensors */
	Ultrasonic_init(&frontDistanceSensor);
	Ultrasonic_init(&leftDistanceSensor);
	Ultrasonic_init(&rightDistanceSensor);

	/* Initialize the DC motors */
	DcMotor_init(&rightMotor);
	DcMotor_init(&leftMotor);

	/* Initialize Sensors and Indicators */
	FlameSensor_init(&flameSensor);
	MQ2_init(&gasSensor);
	Buzzer_init(&Alarm);
	LED_init(&Red);
	LED_init(&Green);
	/* Display welcome message */
	LCD_DisplayStringRowColumn(0, 0, LCD_STRING("   Smart Robot   "));
	LCD_DisplayStringRowColumn(1, 0, LCD_STRING(" Initializing... "));
	_delay_ms(1000);

}

uint8 tempValue = 0;
uint8 gasValue = 0;
uint8 flameStatus = 0;
uint8 lightLevel = 0;

#define TEMP_THRESHOLD   30
#define STOPING_TIME_MS	 1000
#define LIGHT_THRESHOLD  15

/*******************************************************************************
 *                           Main Application Logic                            *
 ******************************************************************************/

void app_run(void) {
	uint8 frontDistance, rightDistance, leftDistance;

	while (1) {
		/* Read distance values from the ultrasonic sensors */
		frontDistance = App_ReadUltrasonic(&frontDistanceSensor);
		rightDistance = App_ReadUltrasonic(&rightDistanceSensor);
		leftDistance = App_ReadUltrasonic(&leftDistanceSensor);
		//App_DisplayDistances(frontDistance, rightDistance, leftDistance);

		/* Determine optimal movement direction and execute it */
		Robot_MovementControl(App_getMaxDistance(frontDistance, rightDistance, leftDistance));
		App_DisplayReadings();
		APP_scanEnvironment();
		APP_handleAlerts();
	}
}

/*******************************************************************************
 *                           Ultrasonic Read Function                          *
 ******************************************************************************/

static uint8 App_ReadUltrasonic(Ultrasonic_t *sensor) {
	/* Trigger the ultrasonic sensor */
	Ultrasonic_Trigger(sensor);

	/* Delay to avoid overlapping triggers */
	_delay_ms(SENSOR_SWITCHING_TIME);

	/* Read and return the measured distance */
	return Ultrasonic_readDistance(sensor);
}

/*******************************************************************************
 *                           LCD Display Function                              *
 ******************************************************************************/

static void App_DisplayDistances(uint8 front, uint8 right, uint8 left) {
	/* Display front sensor distance */
	LCD_MoveCursor(0, 2);
	LCD_DisplayString(LCD_STRING("F"));
	LCD_MoveCursor(1, 0);
	LCD_intgerToString(front);
	LCD_DisplayString(LCD_STRING("cm"));

	/* Display right sensor distance */
	LCD_MoveCursor(0, 7);
	LCD_DisplayString(LCD_STRING("R"));
	LCD_MoveCursor(1, 5);
	LCD_intgerToString(right);
	LCD_DisplayString(LCD_STRING("cm"));

	/* Display left sensor distance */
	LCD_MoveCursor(0, 12);
	LCD_DisplayString(LCD_STRING("L"));
	LCD_MoveCursor(1, 10);
	LCD_intgerToString(left);
	LCD_DisplayString(LCD_STRING("cm"));
}

/*******************************************************************************
 *                       Direction Decision Logic                              *
 ******************************************************************************/

static Direction_t App_getMaxDistance(uint8 front, uint8 right, uint8 left) {
	if (front >= right && front >= left) {
		return FORWARD;
	} else if (right >= left) {
		return RIGHT;
	} else if (left > right) {
		return LEFT;
	}
	/* Fallback in case of invalid values */
	return STOP;
}

/*******************************************************************************
 *                        Movement Control Logic                               *
 ******************************************************************************/

static void Robot_MovementControl(Direction_t direction) {
	switch (direction) {
	case FORWARD:
		Robot_Forward(); /* Move forward */
		break;
	case RIGHT:
		Robot_Right(); /* Turn right */
		break;
	case LEFT:
		Robot_Left(); /* Turn left */
		break;
	case STOP:
		Robot_STOP(); /* Stop movement */
		break;
	default:
		Robot_Forward(); /* Default: move forward */
		break;
	}
}

/*******************************************************************************
 *                        Motor Control Functions                              *
 ******************************************************************************/

/* Move both motors forward */
static void Robot_Forward(void) {
	DcMotor_Rotate(&rightMotor, Anti_Clock_Wise, DCMOTOR_SPEED);
	DcMotor_Rotate(&leftMotor, Anti_Clock_Wise, DCMOTOR_SPEED);
}

/* Turn right by reversing the right motor */
static void Robot_Right(void) {
	DcMotor_Rotate(&rightMotor, Clock_Wise, DCMOTOR_SPEED);
	DcMotor_Rotate(&leftMotor, Anti_Clock_Wise, DCMOTOR_SPEED);
}

/* Turn left by reversing the left motor */
static void Robot_Left(void) {
	DcMotor_Rotate(&rightMotor, Anti_Clock_Wise, DCMOTOR_SPEED);
	DcMotor_Rotate(&leftMotor, Clock_Wise, DCMOTOR_SPEED);
}

/* Stop both motors */
static void Robot_STOP(void) {
	DcMotor_STOP(&rightMotor);
	DcMotor_STOP(&leftMotor);
}

/*******************************************************************************
 *                          Environment Functions                              *
 ******************************************************************************/

/*
 * Function: App_DisplayReadings
 *
 * Description:
 * 		Read all environment sensors and reset alerts
 * 		Reset all alarms and indicators
 */
static void APP_scanEnvironment(void) {
	tempValue = LM35_getTemperature(tempSensor);
	gasValue = MQ2_getGasLevel(&gasSensor);
	flameStatus = FlameSensor_getValue(&flameSensor);
	lightLevel = LDR_getLightIntensity(LdrSensor);

	/* Reset alarms and indicators */

	LED_off(&Red);
	Buzzer_off(&Alarm);
	LED_on(&Green);
}

/*
 * Function: App_DisplayReadings
 *
 * Description:
 * 		Display all sensors data on the LCD
 */

static void App_DisplayReadings(void) {
	LCD_MoveCursor(0, 0);
	LCD_DisplayString(LCD_STRING("T:"));
	LCD_intgerToString(tempValue);
	LCD_DisplayString(LCD_STRING(" G:"));
	LCD_intgerToString(gasValue);
	LCD_DisplayString(LCD_STRING(" |System"));

	LCD_MoveCursor(1, 0);
	LCD_DisplayString(LCD_STRING("L:"));
	LCD_intgerToString(lightLevel);
	LCD_DisplayString(LCD_STRING(" F:"));
	LCD_intgerToString(flameStatus);
	LCD_DisplayString(LCD_STRING(" |Normal"));
}
/*
 * Function: APP_handleAlerts
 *
 * Description:
 * Handles multiple alert scenarios:
 * 1. Fire: high temperature, gas leak, and flame detected.
 * 2. High Temperature Only: high temperature, no gas, no flame.
 * 3. Gas Leak Only: normal temperature, gas leak, no flame.
 * 4. Normal State: no alert condition detected.
 */
static void APP_handleAlerts(void) {
	/* Reset indicators to safe state */
	LED_off(&Red);
	Buzzer_off(&Alarm);
	LED_on(&Green);

	/* Case 1: Fire condition */
	if ((tempValue > TEMP_THRESHOLD) && gasValue && flameStatus) {
		LCD_DisplayStringRowColumn(0, 0, LCD_STRING("!!! ALERT !!!   "));
		LCD_DisplayStringRowColumn(1, 0, LCD_STRING("Fire Detected!  "));
		LED_on(&Red);
		LED_off(&Green);
		Buzzer_on(&Alarm);
		Robot_STOP();
		_delay_ms(STOPING_TIME_MS);
	}

	/* Case 2: High Temperature Only */
	else if ((tempValue > TEMP_THRESHOLD) && !gasValue && !flameStatus) {
		LCD_DisplayStringRowColumn(0, 0, LCD_STRING("High Temp!!     "));
		LCD_DisplayStringRowColumn(1, 0, LCD_STRING("Check Cooling   "));
		LED_on(&Red);
		LED_off(&Green);
		Buzzer_on(&Alarm);
		_delay_ms(STOPING_TIME_MS);
	}

	/* Case 3: Gas Leak Only */
	else if ((tempValue <= TEMP_THRESHOLD) && gasValue && !flameStatus) {
		LCD_DisplayStringRowColumn(0, 0, LCD_STRING("!! GAS LEAK !!  "));
		LCD_DisplayStringRowColumn(1, 0, LCD_STRING("Ventilate Area  "));
		LED_on(&Red);
		LED_off(&Green);
		Buzzer_on(&Alarm);
		Robot_STOP();
		_delay_ms(STOPING_TIME_MS);
	}
}
