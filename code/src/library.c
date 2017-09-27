#include "main.h"

//declare global variables
//////////////////////////
int slewTmp;
int slewTarget[10];

//////////////////////////
//// Other Variables /////
//////////////////////////


//////////////////////////
//// Helper Functions ////
//////////////////////////
int min(int i1, int i2){
  if(i1>=i2) return i2;
  else return i1;
}

int max(int i1, int i2){
  if(i1<=i2) return i2;
  else return i1;
}

void slewControlTask (void * parameter) {
  //Slew rate control (run as task in init.c)
  //works together with smartMotorSet -- always use smartMotorSet!
  extern int slewTmp;
  extern int slewTarget[10];
  while (1) {
    //if (isEnabled ()) {//only runs if competition switch is enabled
    for (int i = 0; i < 10; i++) { //Cycle through each motor port
      slewTmp = motorGet(i+1); //returns the last speed sent to the motor
      slewTmp += min(15, abs(slewTarget[i]-slewTmp))*(slewTarget[i]-slewTmp)/abs(slewTarget[i]-slewTmp);
      motorSet (i+1, slewTmp);
    }//}
  wait (20);
}}

void smartMotorSet(int motor, int cmd){
  //uses slewControlTask, which needs to be running in the background or nothing will happen
  extern int slewTarget[10];
  if(abs(cmd)<15) cmd=0;
  slewTarget[motor-1]=cmd;
}

////////////////////////////////////////
////Functions Called by opcontrol.c ////
////////////////////////////////////////
void tankdrive(){
	if(abs(joystickGetAnalog(JS_VEXNET, JS_Right_y))>20) { //this block of code is the drivetrain
		smartMotorSet(DRIVETRAIN_RB, joystickGetAnalog(JS_VEXNET, JS_Right_y));
		smartMotorSet(DRIVETRAIN_RF, joystickGetAnalog(JS_VEXNET, JS_Right_y));
	}
	else {
		smartMotorSet(DRIVETRAIN_RB, 0);
		smartMotorSet(DRIVETRAIN_RF, 0);
	}
	if(abs(joystickGetAnalog(JS_VEXNET, JS_Left_y))>20) {
		smartMotorSet(DRIVETRAIN_LB, -joystickGetAnalog(JS_VEXNET, JS_Left_y));
		smartMotorSet(DRIVETRAIN_LF, -joystickGetAnalog(JS_VEXNET, JS_Left_y));
	}
	else {
		smartMotorSet(DRIVETRAIN_LB, 0);
		smartMotorSet(DRIVETRAIN_LF, 0);
	}                                                             
	delay(20);
}
void conegrabber(void) {
	if(joystickGetDigital(1, 6, JOY_UP)) { //this block of code is for cone manipulator
		smartMotorSet(6, 32);     //have someone check this
	}
	else if(joystickGetDigital(1, 6, JOY_DOWN)) { 
		smartMotorSet(6, -32);
	}
	else {
		smartMotorSet(6, 0); 
	}
	delay(20);	
}
void lineargear(void) {
	if(joystickGetAnalog(JS_VEXNET, JS_Right_x)>70) { //linear gear code is set for half speed
		smartMotorSet(LINEARGEAR_R, joystickGetAnalog(JS_VEXNET, JS_Right_x)-70);
		smartMotorSet(LINEARGEAR_L, joystickGetAnalog(JS_VEXNET, JS_Right_x)-70);
	}
	else if(joystickGetAnalog(JS_VEXNET, JS_Right_x)<-70) {
		smartMotorSet(LINEARGEAR_R, joystickGetAnalog(JS_VEXNET, JS_Right_x)+70);
		smartMotorSet(LINEARGEAR_L, joystickGetAnalog(JS_VEXNET, JS_Right_x)+70);
	}
	else {
		smartMotorSet(LINEARGEAR_R, 0);
		smartMotorSet(LINEARGEAR_L, 0);
	}
		delay(20);
}
void calibrate(void) {
	if(joystickGetDigital(1, 7, JOY_UP)) { //IMPORTANT!!! MUST HOLD THIS FOR AT LEAST ONE FULL SECOND
		analogCalibrate(POTGOAL);
		//analogCalibrate(POTCHAIN);
}
void goalgrabber(void) {	//use buttons for this not a joystick and PID control using potentiometer
	if(joystickGetDigital(1, 5, JOY_DOWN)) {
		
	}
}

void chainbar(void) {  //WILL BE FOR PARTNER JOYSTICK 
	if(joystickGetAnalog(JS_PARTNER, 3)>60) {
		smartMotorSet(CHAINBAR_R, joystickGetAnalog(JS_PARTNER, 3)-60); //might be two motors but this codes for one motor right now
	}
	else if(joystickGetAnalog(JS_PARTNER, 3)<-60) {
		smartMotorSet(CHAINBAR_R, joystickGetAnalog(JS_PARTNER, 3)+60);
	}
	else {
		smartMotorSet(CHAINBAR_R, 0);
	}
}

void debug(void) {
	smartMotorSet(9, joystickGetAnalog(JS_VEXNET, 4)); 
	delay(20);
}
/*
I'm just a Jester,
it's jest me.

I'm an idiota 
In a tree.

I go to Worlds
And the earth cries in shame.
-some Jester from 2016-17 (Jestme.txt)
*/
////////////////////////////////////////
//////Functions called by auto.c ///////
////////////////////////////////////////
void autotest1(void) {
	encoderReset(driveEncoderR);
	while(encoderGet(driveEncoderR)<1501) {
		smartMotorSet(2, 120);    
		smartMotorSet(3, 120);
		smartMotorSet(4, 120);
		smartMotorSet(5, 120);
		delay(50);
	}
	while(1499<encoderGet(driveEncoderR)<1801) { 
		smartMotorSet(2, 80);
		smartMotorSet(3, 80);
		smartMotorSet(4, 80);
		smartMotorSet(5, 80);
		delay(50);
	}
		smartMotorSet(2, 0);     //"i agree with josh" -elaina 9 22 17
		smartMotorSet(3, 0);
		smartMotorSet(4, 0);
		smartMotorSet(5, 0);
		encoderReset(driveEncoderR);
		delay(50);
}
void plooptest1(void) {
	int kP = .1;
	int desiredValue = 2700;

while(getEncoder(driveEncoderR) <= desiredValue) {
	int currValue = getEncoder(driveEncoderR);
	int currError = desiredValue - currValue;
	int currSpeed = kP * currError;

	motorSet(DRIVETRAIN_LB CurrSpeed);
	motorSet(DRIVETRAIN_LF, CurrSpeed);
	motorSet(DRIVETRAIN_RB, CurrSpeed);
	motorSet(DRIVETRAIN_RF, CurrSpeed);
	delay(25);
}

}