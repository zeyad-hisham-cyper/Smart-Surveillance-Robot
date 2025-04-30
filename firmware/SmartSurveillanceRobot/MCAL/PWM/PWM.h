/*
 * Module: PWM
 *
 * File Name: PWM.h
 *
 * Created on: Oct 4, 2024
 *
 * Author: Zeyad Hisham
 */
#ifndef PWM_H_
#define PWM_H_

/* Includes Standard Types */
#include "../std_types.h"

#define PWM_RESET_PRESCALER_BITS 0XF8

typedef enum{
	PWM_NO_CLK,
	PWM_F_CPU_CLK,
	PWM_F_CPU_8,
	PWM_F_CPU_64,
	PWM_F_CPU_256,
	PWM_F_CPU_1024
}PWM_PreScaler_Type;
/*
 * Function to generate signal with a given duty cycle
 */
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_H_ */
