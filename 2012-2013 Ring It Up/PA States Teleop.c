#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  HTServo,  none,     none)
#pragma config(Sensor, S4, HTTMUX,         sensorHiTechnicTouchMux)
#pragma config(Motor,  mtr_S1_C1_1,     ring,          tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C1_2,     finger,        tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C2_1,     up1,           tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C2_2,     up2,           tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C3_1,     frontleft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     backleft,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     frontright,      tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     backright,     tmotorTetrix, openLoop)
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

	servo[flip]=255;
	servo[IRlift]=0;

	servo[shoulder]=120;
	servo[elbow]=255;
	servo[claw]=255;

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


bool flipped = false;
bool pressedLastFrame = false;

task main()
{
	// This is the code to define the variables for direct mecanum code.
	SensorType[S4] = sensorHiTechnicTouchMux;

	initializeRobot();

	waitForStart();

	while(true)

	{
		getJoystickSettings(joystick);


		int x = thresabs(joystick.joy1_x2);
		int y = thresabs(joystick.joy1_y2);
		int z = thresabs(joystick.joy1_y1);
//if drive does not work, delete from here
		if (joy1Btn(9))
		{
			if (!pressedLastFrame)
			{
				flipped = !flipped;
				pressedLastFrame = true;
			}
		}
		else
		{
			pressedLastFrame = false;
		}

		if (!flipped)
		{// to here
			if(joystick.joy1_TopHat==0)
			{
				motor[frontleft]=100;
				motor[backleft]=100;
				motor[frontright]=-100;
				motor[backright]=-100;
			}

			else if(joystick.joy1_TopHat==2)
			{
				motor[frontleft]=100;
				motor[backleft]=-100;
				motor[frontright]=100;
				motor[backright]=-100;
			}

			else if(joystick.joy1_TopHat==4)
			{
				motor[frontleft]=-100;
				motor[backleft]=-100;
				motor[frontright]=100;
				motor[backright]=100;
			}

			else if(joystick.joy1_TopHat==6)
			{
				motor[frontleft]=-100;
				motor[backleft]=100;
				motor[frontright]=-100;
				motor[backright]=100;
			}

			else if(joy2Btn(6))
			{
				motor[frontleft]=75;
				motor[backleft]=-75;
				motor[frontright]=75;
				motor[backright]=-75;
				wait1Msec(10);
			}

			else if(joy2Btn(8))
			{
				motor[frontleft]=-75;
				motor[backleft]=75;
				motor[frontright]=-75;
				motor[backright]=75;
				wait1Msec(10);
			}

			else
			{
				motor[frontleft]=y+x+z;
				motor[backleft]=y-x+z;
				motor[frontright]=-(y-x-z);
				motor[backright]=-(y+x-z);
			}
//and also delete from here
		}
		else
		{
			if(joystick.joy1_TopHat==0)
			{
				motor[frontleft]=-100;
				motor[backleft]=-100;
				motor[frontright]=100;
				motor[backright]=100;
			}

			else if(joystick.joy1_TopHat==2)
			{
				motor[frontleft]=-100;
				motor[backleft]=100;
				motor[frontright]=-100;
				motor[backright]=100;
			}

			else if(joystick.joy1_TopHat==4)
			{
				motor[frontleft]=100;
				motor[backleft]=100;
				motor[frontright]=-100;
				motor[backright]=-100;
			}

			else if(joystick.joy1_TopHat==6)
			{
				motor[frontleft]=100;
				motor[backleft]=-100;
				motor[frontright]=100;
				motor[backright]=-100;
			}

			else if(joy2Btn(6))
			{
				motor[frontleft]=-75;
				motor[backleft]=75;
				motor[frontright]=-75;
				motor[backright]=75;
				wait1Msec(10);
			}

			else if(joy2Btn(8))
			{
				motor[frontleft]=75;
				motor[backleft]=-75;
				motor[frontright]=75;
				motor[backright]=-75;
				wait1Msec(10);
			}

			else
			{
				motor[frontleft]=-(y+x+z);
				motor[backleft]=-(y-x+z);
				motor[frontright]=(y-x-z);
				motor[backright]=(y+x-z);
			}

		}//to here



		//dispenser in and out
		if(joy1Btn(6) && !(SensorValue(HTTMUX) & 0x02))
		{//drive out
			motor[ring]=-100;
		}
		else if(joy1Btn(8) && !(SensorValue(HTTMUX) & 0x01))
		{//drive in
			motor[ring]=100;
		}
		else
		{
			motor[ring]=0;
		}

		// might ask you to change
		if(joy1Btn(7))
		{//down
			//to make the plastic piece go lower, move the number closer towards 255
			servo[rings]=150;
		}
		else if(joy1Btn(5))
		{//up
			//to make the plastic piece go higher, move the number closer towards 0
			servo[rings]=75;
		}


		// horizontal extender threshold
		if(abs(joystick.joy2_y1)>10)
		{
			motor[finger]=-joystick.joy2_y1*100/128;
		}
		else
		{
			motor[finger]=0;
		}

		if(joy2Btn(4))
		{//all the way in
			//never need to change
			servo[flip]=255;
		}
		else if(joy2Btn(7))
		{//halfway out
			//for the next 3 cases, if you need to move the flip farther down, move the number to 0
			servo[flip]=35;
		}
		else if(joy2Btn(5))
		{
			servo[flip]=60;
		}
		else if(joy2Btn(12))
		{
			servo[flip]=0;
		}

		if(joy2Btn(1))
		{//hold two rings
			servo[release]=20;
		}
		else if(joy2Btn(2))
		{//drop one ring
			servo[release]=70;
		}
		else if(joy2Btn(3))
		{//drop both rings
			servo[release]=170;
		}


		//elevator threshold up and down
		if(abs(joystick.joy2_y2)>10)
		{
			motor[up1]=joystick.joy2_y2;
			motor[up2]=joystick.joy2_y2;
		}
		else
		{
			motor[up1]=0;
			motor[up2]=0;

		}


	}
}
