#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  HTServo,  none,     none)
#pragma config(Sensor, S4, HTTMUX,         sensorHiTechnicTouchMux)
#pragma config(Motor,  mtr_S1_C1_1,     ring,          tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C1_2,     finger,        tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C2_1,     up1,           tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C2_2,     up2,           tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C3_1,     backright,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     frontright,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     backleft,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     frontleft,     tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    IRlift,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    claw,                 tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    elbow,                tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_1,    shoulder,               tServoStandard)
#pragma config(Servo,  srvo_S2_C2_2,    ,             tServoNone)
#pragma config(Servo,  srvo_S2_C2_3,    rings,                tServoStandard)
#pragma config(Servo,  srvo_S2_C2_4,    IRpivot,              tServoStandard)
#pragma config(Servo,  srvo_S2_C2_5,    release,              tServoStandard)
#pragma config(Servo,  srvo_S2_C2_6,    flip,                 tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"

#include "C:\Program Files (x86)\Robomatter Inc\ROBOTC Development Environment\Sample Programs\NXT\3rd Party Sensor Drivers\drivers\hitechnic-touchmux.h"
#include "C:\Program Files (x86)\Robomatter Inc\ROBOTC Development Environment\Sample Programs\NXT\3rd Party Sensor Drivers\drivers\lego-touch.h"

void initializeRobot()
{


	// Place code here to sinitialize servos to starting positions.
	// Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

	return;
}

//accuracy threshold for driving on joysticks
int thresabs(int n){
	if(abs(n) < 10){
		n=0;
	}
	return (100*n/128);
}

//servo toggle function
void servotoggle(short buttonname, bool Pressedornot, TServoIndex servoName, int lower, int upper)
{
	if(buttonname)
	{
		int mid = (lower + upper) / 2;

		if(!Pressedornot)
		{
			Pressedornot = true;

			if(ServoValue[servoName]>mid)
			{
				servo[servoName]=lower;
			}
			else
			{
				servo[servoName]=upper;
			}
		}
	}
	else
	{
		Pressedornot = false;
	}
}

task main()
{
	// This is the code to define the variables for direct mecanum code.
	SensorType[S4] = sensorHiTechnicTouchMux;

	bool button15 = false;
	bool button26 = false;

	bool button1 = false;
	bool button2 = false;
	bool button3 = false;
	bool button4 = false;


	//bool alreadyPressed = false;

	initializeRobot();

	waitForStart();

	while(true)

	{
		getJoystickSettings(joystick);

			motor[frontleft]=100;
			motor[backleft]=100;
			motor[frontright]=100;
			motor[backright]=100;

}
}
