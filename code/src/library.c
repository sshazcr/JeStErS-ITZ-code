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
		if(joystickGetAnalog(JS_VEXNET, JS_Right_y)>20) { //this block of code is the drivetrain
		smartMotorSet(DRIVETRAIN_RB, joystickGetAnalog(JS_VEXNET, JS_Right_y));
		}
		else if(joystickGetAnalog(JS_VEXNET, JS_Right_y)<-20) {
		smartMotorSet(DRIVETRAIN_RB, joystickGetAnalog(JS_VEXNET, JS_Right_y));
		}
		else {
		smartMotorSet(DRIVETRAIN_RB, 0);
		}
		if(joystickGetAnalog(JS_VEXNET, JS_Right_y)>20) {
		smartMotorSet(DRIVETRAIN_RF, joystickGetAnalog(JS_VEXNET, JS_Right_y));
		}
		else if(joystickGetAnalog(JS_VEXNET, JS_Right_y)<-20) {
		smartMotorSet(DRIVETRAIN_RF, joystickGetAnalog(JS_VEXNET, JS_Right_y));
		}
		else {
		smartMotorSet(DRIVETRAIN_RF, 0);
		}
		if(joystickGetAnalog(JS_VEXNET, JS_Left_y)>20) {
		smartMotorSet(DRIVETRAIN_LB, -joystickGetAnalog(JS_VEXNET, JS_Left_y));
		}
		else if(joystickGetAnalog(JS_VEXNET, JS_Left_y)<-20) {
		smartMotorSet(DRIVETRAIN_LB, -joystickGetAnalog(JS_VEXNET, JS_Left_y));
		}
		else {
		smartMotorSet(DRIVETRAIN_LB, 0);
		}
		if(joystickGetAnalog(JS_VEXNET, JS_Left_y)>20) {
		smartMotorSet(DRIVETRAIN_LF, -joystickGetAnalog(JS_VEXNET, JS_Left_y));
		}
		else if(joystickGetAnalog(JS_VEXNET, JS_Left_y)<-20) {
		smartMotorSet(DRIVETRAIN_LF, -joystickGetAnalog(JS_VEXNET, JS_Left_y));
		}
		else {
		smartMotorSet(DRIVETRAIN_LF, 0);
		}		
		delay(20);
}
void conegrabber(void) {
	if(joystickGetDigital(1, 6, JOY_UP)) { //this block of code is for cone manipulator
			smartMotorSet(6, 64);     //have someone check this
		}
		else if(joystickGetDigital(1, 6, JOY_DOWN)) { 
			smartMotorSet(6, 64);
		}
		else {
			smartMotorSet(6, 0); //i am better than michelle lol
		}
	delay(20);	
}
void lineargear(void) {
	if(joystickGetAnalog(JS_VEXNET, JS_Right_x)>60) { //linear gear code is set for half speed
		smartMotorSet(LINEARGEAR_R, -joystickGetAnalog(JS_VEXNET, JS_Right_x)-60);
	}
	else if(joystickGetAnalog(JS_VEXNET, JS_Right_x)<-60) {
		smartMotorSet(LINEARGEAR_R, -joystickGetAnalog(JS_VEXNET, JS_Right_x)+60);
	}
	else {
		smartMotorSet(LINEARGEAR_R, 0);
	}
	if(joystickGetAnalog(JS_VEXNET, JS_Right_x)>60) {
		smartMotorSet(LINEARGEAR_L, joystickGetAnalog(JS_VEXNET, JS_Right_x)-60);
	}
	else if(joystickGetAnalog(JS_VEXNET, JS_Right_x)<-60) {
		smartMotorSet(LINEARGEAR_L, joystickGetAnalog(JS_VEXNET, JS_Right_x)+60);
	}
	else {
		smartMotorSet(LINEARGEAR_L, 0);
	}
		delay(20);
}
/*
void goalgrabber(void) {	//use buttons for this not a joystick 
}

void GOALGRAB(void) {
	if (joystickGetDigital(1,5,JOY_UP)) {
	smartMotorSet(5,20); }
	else if (joystickGetDigital(1,5,JOY_DOWN) {
	smartMotorSet (5,-20);}
	else {  
	smartMotorSet(5,0);
	}
delay(20);
}

void CHAINBAR(void) { //not partner joystivk
	if(joystickGetAnalog(JS_VEXNET, JS_Left_x)>30) { 
		smartMotorSet(CHAINBAR_R, -joystickGetAnalog(JS_VEXNET, JS_left_x)-60);
	}
	else if(joystickGetAnalog(JS_VEXNET, JS_left_x_x)<-30) {
		smartMotorSet(CHAINBAR, -joystickGetAnalog(JS_VEXNET, JS_Left_x)+60);
	}
	else {
		smartMotorSet(CHAINBAR, 0);
} 
}


void chainbar(void) {  //WILL BE FOR PARTNER JOYSTICK 
	if(joystickGetAnalog(JS_PARTNER, 3)>60) {
		smartMotorSet(CHAINBAR_MOTORPORT, joystickGetAnalog(JS_PARTNER, 3)-60);
	}
	else if(joystickGetAnalog(JS_PARTNER, 3)<-60) {
		smartMotorSet(CHAINBAR_MOTORPORT, joystickGetAnalog(JS_PARTNER, 3)+60);
	}
	else {
		smartMotorSet(CHAINBAR_MOTORPORT, 0);
	}
}
*/
void debug(void) {
	smartMotorSet(9, joystickGetAnalog(JS_VEXNET, 4)); //i am still better than michelle :D
	delay(20);
}
