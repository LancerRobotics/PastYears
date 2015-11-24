#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  HTServo,  none,     none)
#pragma config(Sensor, S3,     HTSPB,          sensorI2CCustom9V)
#pragma config(Sensor, S4,     SMUX,           sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     frontRight,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     backRight,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorLift1,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorLift2,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     frontLeft,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     backLeft,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     collector,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     collector2,    tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    dump,                 tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    servo2,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_3,    servo3,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_1,    rollingGoalLeft,      tServoStandard)
#pragma config(Servo,  srvo_S2_C2_2,    rollingGoalRight,     tServoStandard)
#pragma config(Servo,  srvo_S2_C2_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S2_C2_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S2_C2_6,    servo12,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard		!!*//


#include "infraredSensor.c"
#include "hitechnic-gyro.h"
#include "Collector.c"
#include "RollingGoal.c"
#include "Dump.c"
#include "encoderFunctions.c"
#include "moveFunctions.c"

/*
SMUX
1 - Gyro
2 - Accel
3 - IR right
4 - IR left
*/

task display()
{
	while (true){
		eraseDisplay();
		nxtDisplayTextLine(0,"Act:%d",nMotorEncoder[frontLeft]);
		//nxtDisplayCenteredTextLine(0, "Heading: %d", currHeading);
		//nxtDisplayCenteredTextLine(2, "Sonar: %d", sonarValue);
		wait1Msec(20);
	}
}

void initializeRobot()
{
	initial = 0;
	for(int i = 0; i < 100; i++){//Sensor
		initial += SensorValue[S4];
		wait10Msec(1);
	}
	initial = initial / 100;//Sensor
	return;
}
task servoInit() {
	while(true)
		servo[dump] = 66;
}

task main()
{
	playSound(soundDownwardTones);
	wait1Msec(500);
	startTask(readPosition);
	wait1Msec(200);
	while(irPosition < 0){}
	if(irPosition == 2){
		servo[dump] = 66; //init dump
		encodedMove(-20); //move to kickstand
		//move to center goal
		wait1Msec(1000);
		rotate(-90); //rotate to face kickstand
		//rotate -100 ccw
		//wait1Msec(1000);
		encodedMove(-3);
		encodedMovePos(10);
}

else if(irPosition == 1)
{
	servo[dump] = 66;
	encodedMove(-17);
	rotate(-200);
	rotate(-95);
	rotate(-95);
	raiseLift();
	wait1Msec(500);
	moveAll(0);
	encodedMove(-1);
	dumpAll();
}
else if(irPosition == 0)
{
	encodedMove(-15);
	rotate(-270);
	encodedMove(-7);
	rotate(-90);
	raiseLift();
	encodedMove(-3);
	dumpAll();
}

		/*
		encodedMove(-17);
		wait1Msec(1000);
		rotate(-90);
		//wait1Msec(1000);
		encodedMovePos(5);
		//
		//
		// Pls no edit before this //
		//
		//
		rotatePos(90);
		encodedMove(-1);
//		raiseLift();
}


*/



//Lancer's 8th Symphony
		playSound(soundDownwardTones);
		playSound(soundException);
		playSound(soundUpwardTones);
		playSound(soundDownwardTones);
//



		/*
		rotate(90);
		wait1Msec(1000);
		encodedMove(-13);
		wait1Msec(1000);
		rotate(90);
		wait1Msec(1000);
		raiseLift();
		dumpAll();
		lowerLift();
		wait1Msec(1000):
		rotate(90);
		wait1Msec(1000);
		encodedMove(-48); */
//	}
/*
	if(ir in first location)
		//score
	else
	{
	move to following location
		if(ir is in second location)
		//score
		else
		{
		move to last location
		score
		}
	}
	//check IR in third location
		//score

	startTask(display);
	//Use defensive tactics to create obstacles for other automated machines
	//Reset position/Recalibrate
	//Find Infrared
	//Knock down kickstand
	//Score balls in center




*/
	//Neccessary do not touch
	while(true)
	{
		wait1Msec(10000);
		//playSound(soundBeepBeep);
	}
}

/*

Move out of parking zone/ramp and scan for IR (in front of ramp) facing forward still
Then scan for IR
Move to location, mantaining no strafe
Release kickstand
Align with center structure
Move under center goal, raise lift and score

*/
//Edit Log 3/7/15:

/* *******
*        *
*        *
*        *
*        *
*        *
*        *
******* */

//1) changed mpower to 75
