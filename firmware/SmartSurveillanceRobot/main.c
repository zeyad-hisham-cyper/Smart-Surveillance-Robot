/******************************************************************************
 * File: main.c
 * Description: Main program for the Smart Surveillance Robot.
 *              Initializes and runs the robot.
 * Author: Amr & Zeyad
 * Created: April 16, 2025
 ******************************************************************************/

#include "APP/app.h"

/*
 * Function: main
 * --------------
 * Initializes the robot and runs the main control loop.
 */
int main(void) {
	app_init();  /* Initialize the robot components */
	app_run();   /*	 Run the robot's main operations */
}
