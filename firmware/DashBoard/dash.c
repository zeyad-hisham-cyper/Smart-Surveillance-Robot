/*
 * dash.c
 *
 *  Created on: May 26, 2025
 *      Author: zeyad
 */

#include "dash.h"

uint8 tempValue = 0;
uint8 gasValue = 0;
uint8 flameStatus = 0;
#define LCD_STRING(str) ((const uint8 *)(str))
void App_DisplayReadings(void);
static void APP_handleAlerts(void);
static uint8 recieve_Byte(void);
static void send_Byte(uint8 byte);

int main(void) {
	LCD_init();
	UART_init(9600);
	while (1) {
		LCD_DisplayString(LCD_STRING("Waiting Master"));
		tempValue = UART_recieveByte();
		gasValue = UART_recieveByte();
		flameStatus = UART_recieveByte();
		LED_off(&Red);
		Buzzer_off(&Alarm);
		LED_on(&Green);
		App_DisplayReadings();
		APP_handleAlerts();
	}
	return 0;
}

void App_DisplayReadings(void) {
	LCD_MoveCursor(0, 0);
	LCD_DisplayString(LCD_STRING("T:"));
	LCD_intgerToString(tempValue);
	LCD_DisplayString(LCD_STRING(" G:"));
	LCD_intgerToString(gasValue);
	LCD_DisplayString(LCD_STRING(" |System"));

	LCD_MoveCursor(1, 0);
	LCD_DisplayString(LCD_STRING(" FLame:"));
	LCD_intgerToString(flameStatus);
	LCD_DisplayString(LCD_STRING(" |Normal"));
}
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
		_delay_ms(STOPING_TIME_MS);
	}
}

static uint8 recieve_Byte(void) {
	uint8 byte;
	while (UART_recieveByte() != READY) {
	}
	UART_sendByte(READY);
	byte = UART_recieveByte();
	UART_sendByte(DONE);
	return byte;
}

static void send_Byte(uint8 byte) {
	UART_sendByte(READY);
	while (UART_recieveByte() != READY) {
	}
	UART_sendByte(byte);
	while (UART_recieveByte() != DONE) {
	}
}

