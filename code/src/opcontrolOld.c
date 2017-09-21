/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void operatorControlDoNOTEverRun() {
	while (1) {
		joystickGetAnalog(1, 3); //analog 2 and 3 are for wheels
		joystickGetAnalog(1, 2); 
		joystickGetAnalog(1, 1); //analog 1 is for linear gear shaft
		joystickGetDigital(1, 6, JOY_UP);
		joystickGetDigital(1, 6, JOY_DOWN);
		
		/*MotorSet(2, -joystickGetAnalog(1, 2));  legacy drivetrain code
		MotorSet(3, -joystickGetAnalog(1, 2));
		MotorSet(4, joystickGetAnalog(1, 3));
		MotorSet(5, joystickGetAnalog(1, 3));
		*/
		
		if(joystickGetAnalog(1, 2)>20) { //this block of code is the real drivetrain, with deadzones
		smartMotorSet(2, -joystickGetAnalog(1, 2));
		}
		else {
			if(joystickGetAnalog(1, 2)<-20) {
				smartMotorSet(2, -joystickGetAnalog(1, 2));
			}
			else {
				smartMotorSet(2, 0);
			}
		}
		
		
		
		
		
		if(joystickGetAnalog(1, 2)>20) {
		smartMotorSet(3, -joystickGetAnalog(1, 2));
		}
		else if(joystickGetAnalog(1, 2)<-20) {
		smartMotorSet(3, -joystickGetAnalog(1, 2));
		}
		else {
		smartMotorSet(3, 0);
		}
		if(joystickGetAnalog(1, 3)>20) {
		smartMotorSet(4, joystickGetAnalog(1, 3));
		}
		else if(joystickGetAnalog(1, 3)<-20) {
		smartMotorSet(4, joystickGetAnalog(1, 3));
		}
		else {
		smartMotorSet(4, 0);
		}
		if(joystickGetAnalog(1, 3)>20) {
		smartMotorSet(5, joystickGetAnalog(1, 3));
		}
		else if(joystickGetAnalog(1, 3)<-20) {
		smartMotorSet(5, joystickGetAnalog(1, 3));
		}
		else {
		smartMotorSet(5, 0);
		}		
		
		
		if(joystickGetDigital(1, 6, JOY_UP)) { //this block of code is for cone manipulator
			smartMotorSet(6, 127);
		}
		else if(joystickGetDigital(1, 6, JOY_DOWN)) { 
			smartMotorSet(6, -127);
		}
		else {
			smartMotorSet(6, 0); //i am better than michelle lol
		}
		
		
		smartMotorSet(7, joystickGetAnalog(1, 1)); //this block of code is for linear gear shaft
		delay(20);
	}
}
