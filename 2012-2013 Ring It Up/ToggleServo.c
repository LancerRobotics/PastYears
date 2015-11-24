#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     ring,          tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C1_2,     finger,        tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C2_1,     up1,           tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C2_2,     up2,           tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C3_1,     backright,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C3_2,     frontright,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_1,     backleft,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     frontleft,     tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    IRlift,               tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    claw,                tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    elbow,                 tServoStandard)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_1,    servo7,               tServoStandard)
#pragma config(Servo,  srvo_S2_C2_2,    shoulder,             tServoStandard)
#pragma config(Servo,  srvo_S2_C2_3,    rings,                tServoStandard)
#pragma config(Servo,  srvo_S2_C2_4,    IRpivot,              tServoStandard)
#pragma config(Servo,  srvo_S2_C2_5,    release,              tServoStandard)
#pragma config(Servo,  srvo_S2_C2_6,    flip,                 tServoStandard)

#include "JoystickDriver.c"

void initializeRobot()
{
	return;
}

task main()
{
	initializeRobot();
	waitForStart();


	while(true)

	{
		getJoystickSettings(joystick);

		int mod = 0;

		if(joy2Btn(1)) // if button one is pressed
		{
			if((mod%2)==0)
			{
				servo[IRpivot]=0;
				mod = mod+1;
			}
			else if((mod%2)==1)
			{
				servo[IRpivot]=255;
				mod=mod+1;
			}
			else{

			}

		}//end if
	}//end while
}//end main
