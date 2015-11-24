#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          flag1,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          flag2,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          flag3,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     lift,          tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C1_2,     hang,          tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C2_1,     rightFront,    tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C2_2,     rightBack,     tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C3_1,     hang2,         tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C3_2,     motorI,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     leftBack,      tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C4_2,     leftFront,     tmotorTetrix, PIDControl)
#pragma config(Servo,  srvo_S2_C1_1,    autonomous,           tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_3,    hangrelease,          tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    collector,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_5,    tilt,                 tServoStandard)
#pragma config(Servo,  srvo_S2_C1_6,    clamp,                tServoStandard)
#pragma config(Servo,  srvo_S2_C2_1,    open,                 tServoStandard)
#pragma config(Servo,  srvo_S2_C2_2,    servo8,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S2_C2_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S2_C2_6,    servo12,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "Auto Header 2.11.14.h"



void initializeRobot()
{
	servo[autonomous]=255;
	servo[hangrelease]=0;
	servo[clamp]=120;
	servo[tilt]=0;
	servo[collector]=231;
	servo[open]=255;

	return;
}

task main()
{
	initializeRobot();

	waitForStart();

	while (true)
	{
		setSpeed(100 , 500);

		stopmotors(100);

		servo[autonomous]=0;

		stopmotors(2000);

		servo[autonomous]=100;

		stopmotors(100);

		setSpeed(100 , 1500);

		stopmotors(100);

		turn(-100 , 950);

		stopmotors(100);

		setSpeed(100 , 1200);

		stopmotors(200);

		wait1Msec(100000);


	}
}
