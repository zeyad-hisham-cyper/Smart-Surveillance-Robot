/*
 * main.c
 *
 *  Created on: Apr 16, 2025
 *      Author: zeyad
 */

#include "MCAL/GPIO/gpio.h"
#include "HAL/LCD/LCD.h"
#include "HAL/Ultrasonic/Ultrasonic.h"
#include <util/delay.h>

#define SENSOR_SWITCHING_TIME 8
#define LCD_STRING(str) ((const uint8 *)(str))

void HardWare_init(void);

int main(void){
	uint8 frontDistance = 0, rightDistance = 0, leftDistance = 0;
	HardWare_init();
	for(;;){
		Ultrasonic_Trigger(&frontDistanceSensor);
		_delay_ms(SENSOR_SWITCHING_TIME);
		frontDistance = Ultrasonic_readDistance(&frontDistanceSensor);
		Ultrasonic_Trigger(&rightDistanceSensor);
		_delay_ms(SENSOR_SWITCHING_TIME);
		rightDistance = Ultrasonic_readDistance(&rightDistanceSensor);
		Ultrasonic_Trigger(&leftDistanceSensor);
		_delay_ms(SENSOR_SWITCHING_TIME);
		leftDistance = Ultrasonic_readDistance(&leftDistanceSensor);
		LCD_MoveCursor(0,2);
		LCD_DisplayString(LCD_STRING("F"));
		LCD_MoveCursor(1,0);
		LCD_intgerToString(frontDistance);
		LCD_DisplayString(LCD_STRING("cm"));
		LCD_MoveCursor(0,7);
		LCD_DisplayString(LCD_STRING("R"));
		LCD_MoveCursor(1,5);
		LCD_intgerToString(rightDistance);
		LCD_DisplayString(LCD_STRING("cm"));
		LCD_MoveCursor(0,12);
		LCD_DisplayString(LCD_STRING("L"));
		LCD_MoveCursor(1,10);
		LCD_intgerToString(leftDistance);
		LCD_DisplayString(LCD_STRING("cm"));
		//_delay_ms(10);
	}
}
void HardWare_init(void){
	LCD_init();
	Ultrasonic_init(&frontDistanceSensor);
	Ultrasonic_init(&leftDistanceSensor);
	Ultrasonic_init(&rightDistanceSensor);
}
