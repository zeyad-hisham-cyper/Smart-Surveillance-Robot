

#include "../MCAL/GPIO/gpio.h"
#include "../MCAL/PWM/PWM.h"
#include "../HAL/LCD/LCD.h"
#include "../HAL/Ultrasonic/Ultrasonic.h"
#include "../HAL/DcMotor/Motor.h"

#include <util/delay.h>

#define SENSOR_SWITCHING_TIME 8
#define LCD_STRING(str) ((const uint8 *)(str))

#define ULTRASONIC_TRIGGER_1_2_PORT 		PORTD_ID
#define ULTRASONIC_TRIGGER_3_PORT 			PORTB_ID

#define ULTRASONIC_ECHO_PORT 			PORTD_ID
#define ULTRASONIC_ECHO_PIN 			PIN6_ID

#define ULTRASONIC_FRONT_TRIGGER_PIN	PIN4_ID
#define ULTRASONIC_LEFT_TRIGGER_PIN		PIN5_ID
#define ULTRASONIC_RIGHT_TRIGGER_PIN	PIN0_ID


#define DCMOTORS_DIR_PORT PORTC_ID
#define DCMOTOR_R_DIR_PINA PIN2_ID
#define DCMOTOR_R_DIR_PINB PIN3_ID
#define DCMOTOR_L_DIR_PINA PIN4_ID
#define DCMOTOR_L_DIR_PINB PIN5_ID
#define DCMOTOR_PWM_PORT PORTB_ID
#define DCMOTOR_PWM_PIN PIN3_ID
#define DCMOTOR_SPEED 50

typedef enum{
	FORWARD,
	RIGHT,
	LEFT,
	STOP
}Direction_t ;

/* External declaration for ultrasonic sensor configuration */
extern Ultrasonic_t frontDistanceSensor, leftDistanceSensor, rightDistanceSensor;
extern DcMotor rightMotor, leftMotor;


void app_init(void);
void app_run(void);
