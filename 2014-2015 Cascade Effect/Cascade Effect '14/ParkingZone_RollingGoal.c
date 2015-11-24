#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     SMUX,           sensorI2CCustom9V)
#pragma config(Motor,  mtr_S1_C1_1,     frontRight,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     backRight,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorLift1,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorLift2,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     frontLeft,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     backLeft,      tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C4_1,     collector,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C4_2,     collector2,    tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S2_C1_1,    dump,                 tServoStandard)
#pragma config(Servo,  srvo_S2_C1_2,    rollingGoalPair,      tServoStandard)
#pragma config(Servo,  srvo_S2_C1_3,    flag,                 tServoStandard)
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

#include "hitechnic-sensormux.h"
#include "lego-ultrasound.h"
#include "autonUtils.c"
#include "EOPD.c"
#include "clampFlagTest.c"

//int sonarPosition;

//float sonargetter;

void parkingZoneRollingGoal()
{
		servo[rollingGoalPair] = 180;
		strafeTo(-20); //strafe clear of center goal
		coastTo((24*3.2)); //coast a little above 3 mats forward
		strafeTo(-24); //strafe in front of rolling goal
		coastTo(35); //move to rolling goal
		starttask(flagRaiser); //is the rolling goal in position? checks this continuously
		servo[rollingGoalPair] = 180;
		motor[frontLeft] = 20;
		motor[frontright] = -20;
		motor[backLeft] = 20;
		motor[backright] = -20;
		while(!breakOut){} //move until the rolling goal is in position
		servo[rollingGoalPair] = 110; //clamp onto the rolling goal
		motor[frontleft] = 0;
		motor[frontright] = 0;
		motor[backleft] = 0;
		motor[backright] = 0;
		raiseLift2();
		dumpAll();
		dumpAll();
		lowerLift2();
		//scores in the rolling goal
		coastTo(-10);
		//moves back because the rolling goals might hit each other and throw off movement
		strafeTo(28);
		//clear to move backwards
		coastTo(-80); //move all the way back to parking zone! may or may not also defend center goal
		while(true)
			wait1Msec(1000);
}