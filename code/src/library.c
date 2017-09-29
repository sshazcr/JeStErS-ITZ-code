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
	if(joystickGetDigital(JS_VEXNET, SHOULDER_R, JOY_UP)) { //this block of code is for cone manipulator
		smartMotorSet(CONEGRAB, 32);    
	}
	else if(joystickGetDigital(JS_VEXNET, SHOULDER_R, JOY_DOWN)) { 
		smartMotorSet(CONEGRAB, -32);
	}
	else {
		smartMotorSet(CONEGRAB, 0); 
	}
	delay(20);	
}
void lineargear(void) { //WILL BE FOR PARTNER JOYSTICK AHHHHHHHHH
	if(joystickGetAnalog(JS_VEXNET, JS_RIGHT_X)>60) { //linear gear code is set for half speed
		smartMotorSet(LINEARGEAR_R, joystickGetAnalog(JS_VEXNET, JS_RIGHT_X)-60);
		smartMotorSet(LINEARGEAR_L, joystickGetAnalog(JS_VEXNET, JS_RIGHT_X)-60);
	}
	else if(joystickGetAnalog(JS_VEXNET, JS_RIGHT_X)<-60) {
		smartMotorSet(LINEARGEAR_R, joystickGetAnalog(JS_VEXNET, JS_RIGHT_X)+60);
		smartMotorSet(LINEARGEAR_L, joystickGetAnalog(JS_VEXNET, JS_RIGHT_X)+60);
	}
	else {
		smartMotorSet(LINEARGEAR_R, 0);
		smartMotorSet(LINEARGEAR_L, 0);
	}
		delay(20);
}
void calibrate(void) {
	if(joystickGetDigital(JS_VEXNET, DPAD_L, JOY_UP)) { //IMPORTANT!!! MUST HOLD THIS FOR AT LEAST ONE FULL SECOND
		analogCalibrate(POTGOAL);
		//analogCalibrate(POTCHAIN);
	}
}
void goalgrabber(void) {  //i have a concept for a P loop for more control this 
	if(joystickGetDigital(JS_VEXNET, SHOULDER_L, JOY_DOWN)) {
		smartMotorSet(GOALGRAB_R, 25);
		smartMotorSet(GOALGRAB_L, 25);
	}
	else if(joystickGetDigital(JS_VEXNET, SHOULDER_L, JOY_UP)) {
		smartMotorSet(GOALGRAB_L, -25);
		smartMotorSet(GOALGRAB_R, -25);
	}
	else {
		smartMotorSet(GOALGRAB_L, 0);
		smartMotorSet(GOALGRAB_R, 0);
	}
}
void ploopliftgoal(void) {
	while(joystickGetDigital(1, 5, JOY_DOWN) {
		int kP = .1;
		int loadGoal = <when mob goal lifter is dropped & can load the mob goal>
		int currValue1 = analogReadCalibrated(POTGOAL)
		int currError1 = loadGoal - currValue1
		int currSpeed1 = kP * currError1

		smartMotorSet(GOALGRAB_R, currSpeed1);
		smartMotorSet(GOALGRAB_L, currSpeed1);
	}
	while(joystickGetDigital(1, 5, JOY_UP) {
		int kP = .1;
		int moveGoal = <when mob goal lifter is carried and lifted off the ground>
		int currValue2 = analogReadCalibrated(POTGOAL)
		int currError2 = moveGoal - currValue2
		int currSpeed2 = kP * currError2

		smartMotorSet(GOALGRAB_R, currSpeed2);
		smartMotorSet(GOALGRAB_L, currSpeed2);
		}
	}

void chainbar(void) {  //WILL BE FOR PARTNER JOYSTICK REMEMBER THIS AHHHHHHHHH
	if(joystickGetAnalog(JS_VEXNET, JS_LEFT_Y)>40) {
		smartMotorSet(CHAINBAR_R, joystickGetAnalog(JS_VEXNET, JS_LEFT_Y)-40);
		smartMotorSet(CHAINBAR_L, joystickGetAnalog(JS_VEXNET, JS_LEFT_Y)-40);
	}
	else if(joystickGetAnalog(JS_VEXNET, JS_LEFT_Y)<-40) {
		smartMotorSet(CHAINBAR_R, joystickGetAnalog(JS_VEXNET, JS_LEFT_Y)+40);
		smartMotorSet(CHAINBAR_L, joystickGetAnalog(JS_VEXNET, JS_LEFT_Y)+40);
	}
	else {
		smartMotorSet(CHAINBAR_R, 0);
		smartMotorSet(CHAINBAR_L, 0);
	}
}

void debug(void) {
	smartMotorSet(9, joystickGetAnalog(JS_VEXNET, JS_LEFT_Y)); 
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
	int currValue3 = getEncoder(driveEncoderR);
	int currError3 = desiredValue - currValue3;
	int currSpeed3 = kP * currError3;

	motorSet(DRIVETRAIN_LB, CurrSpeed3);
	motorSet(DRIVETRAIN_LF, CurrSpeed3);
	motorSet(DRIVETRAIN_RB, CurrSpeed3);
	motorSet(DRIVETRAIN_RF, CurrSpeed3);
	delay(25);
}

}