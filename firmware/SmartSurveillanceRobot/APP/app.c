#include "app.h"

static uint8 App_ReadUltrasonic(Ultrasonic_t *sensor);
static void App_DisplayDistances(uint8 front, uint8 right, uint8 left);
static Direction_t App_getMaxDistance(uint8 front, uint8 right, uint8 left);
static void Robot_MovementControl(Direction_t direction);
static void Robot_Forward(void);
static void Robot_Right(void);
static void Robot_Left(void);
static void Robot_STOP(void);

void app_init(void) {
	LCD_init();
	Ultrasonic_init(&frontDistanceSensor);
	Ultrasonic_init(&leftDistanceSensor);
	Ultrasonic_init(&rightDistanceSensor);
	DcMotor_init(&rightMotor);
	DcMotor_init(&leftMotor);
}
void app_run(void) {
	uint8 frontDistance, rightDistance, leftDistance;
	while (1) {
		frontDistance = App_ReadUltrasonic(&frontDistanceSensor);
		rightDistance = App_ReadUltrasonic(&rightDistanceSensor);
		leftDistance = App_ReadUltrasonic(&leftDistanceSensor);
		App_DisplayDistances(frontDistance, rightDistance, leftDistance);
		Robot_MovementControl(App_getMaxDistance(frontDistance,rightDistance,leftDistance));
	}
}

static uint8 App_ReadUltrasonic(Ultrasonic_t *sensor) {
	Ultrasonic_Trigger(sensor);
	_delay_ms(SENSOR_SWITCHING_TIME);
	return Ultrasonic_readDistance(sensor);
}
static void App_DisplayDistances(uint8 front, uint8 right, uint8 left) {
	LCD_MoveCursor(0, 2);
	LCD_DisplayString(LCD_STRING("F"));
	LCD_MoveCursor(1, 0);
	LCD_intgerToString(front);
	LCD_DisplayString(LCD_STRING("cm"));

	LCD_MoveCursor(0, 7);
	LCD_DisplayString(LCD_STRING("R"));
	LCD_MoveCursor(1, 5);
	LCD_intgerToString(right);
	LCD_DisplayString(LCD_STRING("cm"));

	LCD_MoveCursor(0, 12);
	LCD_DisplayString(LCD_STRING("L"));
	LCD_MoveCursor(1, 10);
	LCD_intgerToString(left);
	LCD_DisplayString(LCD_STRING("cm"));
}

static Direction_t App_getMaxDistance(uint8 front, uint8 right, uint8 left) {
	if (front >= right && front >= left) {
		return FORWARD;
	} else if (right >= left) {
		return RIGHT;
	} else if (left > right) {
		return LEFT;
	}
	return STOP;
}

static void Robot_MovementControl(Direction_t direction) {
	switch (direction) {
	case FORWARD:
		Robot_Forward();
		break;
	case RIGHT:
		Robot_Right();
		break;
	case LEFT:
		Robot_Left();
		break;
	case STOP:
		Robot_STOP();
		break;
	default:
		Robot_Forward();
		break;
	}
}
static void Robot_Forward(void) {
	DcMotor_Rotate(&rightMotor, Anti_Clock_Wise, DCMOTOR_SPEED);
	DcMotor_Rotate(&leftMotor, Anti_Clock_Wise, DCMOTOR_SPEED);
}

static void Robot_Right(void) {
	DcMotor_Rotate(&rightMotor, Clock_Wise, DCMOTOR_SPEED);
	DcMotor_Rotate(&leftMotor, Anti_Clock_Wise, DCMOTOR_SPEED);
}
static void Robot_Left(void) {
	DcMotor_Rotate(&rightMotor, Anti_Clock_Wise, DCMOTOR_SPEED);
	DcMotor_Rotate(&leftMotor, Clock_Wise, DCMOTOR_SPEED);
}
static void Robot_STOP(void) {
	DcMotor_STOP(&rightMotor);
	DcMotor_STOP(&leftMotor);

}

