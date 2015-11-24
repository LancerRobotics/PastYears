#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     IR_LEFT,        sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     frontRight,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     backRight,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorLift1,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorLift2,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     frontLeft,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     backLeft,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     collector,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     collector2,    tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    dump,                 tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    rollingGoalLeft,      tServoNone)
#pragma config(Servo,  srvo_S2_C1_3,    rollingGoalRight,     tServoNone)
#pragma config(Servo,  srvo_S2_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S2_C1_6,    servo6,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_1,    servo2,               tServoStandard)
#pragma config(Servo,  srvo_S2_C2_2,    servo3,               tServoStandard)
#pragma config(Servo,  srvo_S2_C2_3,    servo9,               tServoNone)
#pragma config(Servo,  srvo_S2_C2_4,    servo10,              tServoNone)
#pragma config(Servo,  srvo_S2_C2_5,    servo11,              tServoNone)
#pragma config(Servo,  srvo_S2_C2_6,    servo12,              tServoNone)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "infraredSensor.c"
#include "hitechnic-gyro.h"
#include "Collector.c"
#include "RollingGoal.c"
#include "Dump.c"
#include "encoderFunctions.c"
#include "moveFunctions.c"
#include "gyrofunctions.c"

void raiseLift2() {
				motor[motorLift2]=-90;
				motor[motorLift1]=-90;
				wait1Msec(50);
				while(abs(nMotorEncoder[motorLift2])<(1440*2.4 ))
				{
				}
				motor[motorLift1] = 0;
				motor[motorLift2] = 0;
				nMotorEncoder[motorLift2] = 0;
			}
void lowerLift2() {
				motor[motorLift2]=90;
				motor[motorLift1]=90;
				wait1Msec(50);
				while(abs(nMotorEncoder[motorLift2])<(1440*2.4))
				{
				}
				motor[motorLift1] = 0;
				motor[motorLift2] = 0;
				nMotorEncoder[motorLift2] = 0;
}


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
	initializeRobot();
	StartTask(getHeading);
	servo[dump] = 66;
	irPosition = 2;
//	startTask(readPosition);
	waitForStart();
/*
	servo[dump] = 94+PI;
	coastTo(-60);
	encRot(-94)
	coastTo(-90); //move to center goal
	coastFor(-30);
	encRot(-50);
	coastTo(-60);
	coastFor(-60);
	encRot(-142);
	coastTo(-35);`
	encRot(-95);
	coastFor(-63);
	//Neccessary do not touch
*/

	wait1Msec(500);
	servo[dump] = 66;
	playSound(soundDownwardTones);
	while(irPosition < 0){}
	wait1Msec(1000);

	if(irPosition == 2)//horizontal
	{
		playSound(soundUpwardTones);
		//moveSlow(1);
		//wait1Msec(3000);
		//thats lift i think
		//moveSlow(0);

		motor[frontleft] = 30;
		motor[backleft] = 30;
		motor[frontright] = -30;
		motor[backleft] = -30;
		wait1Msec(3000);
		motor[frontleft] = 0;
		motor[backleft] = 0;
		motor[backright] = 0;
		motor[frontright] = 0;
		raiseLift2();
		advBrakeNeg();
		dumpAll();
		lowerLift2();
		while(true)
			wait1Msec(1000);
	}
	else if(irPosition == 0)//vertical
	{
		coastTo(5);
		rotateCoast(30,1);
		coastRaw(1300);
		rotateCoast(36,-1);
		wait1Msec(200);
		coastTo(25);
		coastTo(-3);
		wait1Msec(500);
		raiseLift();
		advBrakeNeg();
		dumpAll();
		wait1Msec(200);
		dumpAll();
		lowerLift();
	}

	playSound(soundUpwardTones);
	wait1Msec(5000000);

}