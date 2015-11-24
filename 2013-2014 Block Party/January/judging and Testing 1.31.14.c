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
#pragma config(Motor,  mtr_S1_C4_1,     leftBack,      tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C4_2,     leftFront,     tmotorTetrix, PIDControl)
#pragma config(Servo,  srvo_S2_C1_1,    autonomous,           tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    hangrelease,          tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    collector,            tServoStandard)
#pragma config(Servo,  srvo_S2_C1_5,    tilt,                tServoStandard)
#pragma config(Servo,  srvo_S2_C1_6,    clamp,                 tServoStandard)
#pragma config(Servo,  srvo_S2_C2_1,    open,                 tServoStandard)
#pragma config(Servo,  srvo_S2_C2_2,    servo8,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S2_C2_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S2_C2_6,    servo12,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#define JOYSTICK_UPDATE_TIME 10


void initializeRobot()
{
	// Place code here to initialize servos to starting positions.
	// Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

	servo[autonomous]=100;
	servo[hangrelease]=0;
	servo[clamp]=0;
	servo[tilt]=120;
	servo[collector]=255;
	servo[open]=255;
	return;
}



task main()
{
	initializeRobot();

	waitForStart();   // wait for start of tele-op phase
	getJoystickSettings(joystick);

	while (true)
	{
		int NXT;
		if(nNxtButtonPressed == 3)
		{
			NXT++;

			switch(NXT)
			{
			case 1:
				servo[autonomous]=0;
				wait1Msec(200);
				servo[autonomous]=253;
				wait1Msec(200);
				break;

			case 2:
				motor[rightBack]=100;
				motor[rightFront]=100;
				motor[leftBack]=-100;
				motor[leftFront]=-100;
				wait1Msec(1000);

				motor[rightBack]=-100;
				motor[rightFront]=-100;
				motor[leftBack]=-100;
				motor[leftFront]=-100;
				wait1Msec(1000);
				break;

			case 3:
				motor[lift]=-100;
				wait1Msec(3000);
				break;

			case 4:
				servo[collector]=20;
				wait1Msec(200);
				servo[collector]=255;
				wait1Msec(200);
				servo[collector]=20;
				wait1Msec(200);
				break;

			case 5:
				servo[clamp]=70;
				wait1Msec(200);
				servo[clamp]=3;
				wait1Msec(200);
				break;

			case 6:
				servo[tilt]=255;
				wait1Msec(200);
				servo[tilt]=120;
				wait1Msec(200);
				break;

			case 7:
				motor[lift]=100;
				wait1Msec(3000);
				break;




			}
		}





	}
}