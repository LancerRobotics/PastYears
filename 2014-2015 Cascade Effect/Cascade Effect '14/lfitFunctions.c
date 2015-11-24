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
#include "gyrofunctions.c"
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

task servoInit() {
	while(true)
		servo[dump] = 66;
}

task main()
{

	waitForStart();
	playSound(soundDownwardTones);
	wait1Msec(500);
	startTask(readPosition);
	wait1Msec(200);
	while(irPosition < 0){}
	if(irPosition == 2){
		servo[dump] = 66; //init dump
		coast(-48);
		advBrake();
		encRot(-90);
		coast(20);
		coast(-25);
		encRot(-90);
		coast(5);
		encRot(-90);
		raiseLift();
		coast(-5);
		dumpAll();
	}
	else if(irPosition == 1)
	{
		servo[dump] = 66;
		coast(-3);
		raiseLift();
		encRot(30);
		coast(-5);
		dumpAll();
	}

	else if(irPosition == 0)
	{
		coast(-20);
		encRot(90);
		coast(-10);
		encRot(-90);
		raiseLift();
		coast(-10);
		dumpAll();
	}
	wait1Msec(500000);
}
