////////////////////////////////////////////
//// Macros                             ////
//// #define <identifier> <token>       ////
//// causes a literal substitution in the code - these are not variables
////////////////////////////////////////////


//joystick - analog channels
#define JS_Right_x  1
#define JS_Right_y  2
#define JS_Left_x 4
#define JS_Left_y 3

//joystick - for defining vexnet or partner joystick
#define JS_VEXNET 1
#define JS_PARTNER 2

//digital sensors
#define RSHFT_TOP 1
#define RSHFT_BOT 2
#define LSHFT_TOP 3
#define LSHFT_BOT 4

Encoder driveEncoderR
Encoder driveEncoderL

//analog sensors
#define POTGOAL 1
#define POTCHAIN 2


//joystick - digital channels
#define shoulder_l 5 //left shoulder button
#define shoulder_r 6 //right shoulder button
#define dpad_l 7 //left d-pad
#define dpad_r 8 //right d-pad
	
//Motor ports - define motor ports
#define DRIVETRAIN_RB  4        
#define DRIVETRAIN_RF  5        
#define DRIVETRAIN_LB  2     
#define DRIVETRAIN_LF  3       
#define LINEARGEAR_R  7
#define LINEARGEAR_L  8
#define CHAINBAR_L 1
#define CHAINBAR_R 10
#define CONEGRAB 9
#define GOALGRAB_R
#define GOALGRAB_L

///////////////////////////////
//// Variables             ////
//// extern <type> <name>; ////
///////////////////////////////
extern int slewTmp;
extern int slewTarget[10];

extern int lftWheelSpeed;
extern int rtWheelSpeed;


////////////////////////////////
//// Functions              ////
//// <type> <name>(<args>); ////
////////////////////////////////
int min(int i1, int i2);
int max(int i1, int i2);

//smartMotorSet & slewControlTask work together
//call slewControlTask in init.c & use smartMotorSet in place of motorSet in code
void smartMotorSet(int motor, int cmd);
void slewControlTask(void * parmeter);


//functions declared in header
//coded in library.c
//called in opcontrol.c and/or auto.c
void tankdrive(void);
void conegrabber(void);
void lineargear(void);
void goalgrabber(void);
void chainbar(void);
void debug(void);
void autotest1(void);
void plooptest1(void);
void calibrate(void);