#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     SMUX,           sensorI2CCustom9V)
#pragma config(Motor,  mtr_S1_C1_1,     frontLeft,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C1_2,     backLeft,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C2_1,     motorLift1,    tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     motorLift2,    tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     frontRight,     tmotorTetrix, openLoop, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     backRight,      tmotorTetrix, openLoop, encoder)
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
//#include "clampFlagTest.c"

bool resetPos() {
	coastTo(0.5);
	strafe(left,medium);
	while(floorColor == GRAY){	}
	playSound(soundBeepBeep);
	brake();
	strafeTo(-14);
	coastTo(-5);
	return true;
}

task main()
{


		waitForStart();
	servo[dump]=75;
	servo[rollingGoalPair] = 125;
	initializeRobot();
//	startTask(autoRollingGoal);
	startTask(getHeading);
	//StartTask(gyroPID);
//DEFENSE
		strafeTo(55)//arbitrary
		strafeTo(-55)
		diagonalTo(25, 315);
		coastTo(90);
		rotateCoast(1,-80);
		coastTo(50);
		wait1Msec(500);
		coastTo(-25);
		wait1Msec(300);
		coastTo(50);
		while(true)wait1Msec(100);



//DEFENSE

		servo[rollingGoalPair] = 0;
		coastToCollect(85);// down ramp
		diagonalTo(15, 315);
		diagonalTo(13, 40);
		//strafeTo(-13);//aligns to wall
		//strafeTo(4);//comes back to center compared to goal
		//coastToCollect(18);//slowly approaches goal
		agitateUntilCollected();//loops until switch is triggered
		//stopTask(autoRollingGoal);
		raiseLift2();//the sequal to the first lift raiser
		dumpAll();//twice for agitation
		//dumpAll();
		lowerLift2();
		coastTo(-5);
		//moves back because the rolling goals might hit each other and throw off movement
		strafeTo(15);//moves to lane
		rotateCoast(1,-175);//counterclockwise
		servo[rollingGoalPair] = OPEN;//letting go
		wait1Msec(1000);
		rotateCoast(1,170);
		diagonalTo(15, 315);
		diagonalTo(13, 40);
		/*
		strafeTo(-20);//align with wall
		strafeTo(4);
		*/
		startCollector();
		//coastTo(20);
		coastToCollect(10);//arbitrary
		stopCollector();
    agitateUntilCollected();
    servo[rollingGoalPair] = CLAMPED;
    raiseLift();//score on goal
		dumpAll();
		//dumpAll();
		lowerLift();
    strafeTo(10);//moves away from wall
    rotateCoast(1,3);
    coastTo(-130);
    rotateCoast(1,180);
    playSound(soundFastUpwardTones);
		while(true)wait1Msec(1000); // kill program
	//defensive here
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//defensive close
	/*
	StartTask(readEOPD);
	resetPos();*/
//	diagonalTo((24*sqrt(2))-(13*sqrt(2)),55);


	/*
	rotateCoast(25, -1);
	coastTo(75);
	rotateCoast(25, 1);
	coastTo(-45);
	strafeTo(-40);
	coastTo(-15);
*/

	//while(true) wait1msec(1000);

//test
//coastTo(90);
	while(true)wait1Msec(1000);
	strafeTo(-18);
	coastTo(45);
	//coastTo(33)//original
	wait1Msec(500);
	centerGoalPosition = getPosition();
	//make sure smux is on and try this (if smux isnt on it nt wok

	while(true)
		wait1Msec(1000);

	if(centerGoalPosition==2) //horizontal
	{
		playSound(soundBeepBeep);
		strafeTo(30);
		coastTo(49.5);
		rotateCoast(85,1);
		coastTo(18);
		coastTo(-7);
		raiseLift();
		dumpAll();
		dumpAll();
		lowerLift();

		startTask(getSonarValues);
		while(sonarVal < 100){
			strafeTo(-5);
		}
		stopTask(getSonarValues);
		playSound(soundBeepBeep);
		wait1Msec(1000);
		strafeTo(4);
		coastTo(60);
		wait1Msec(200);
		coastTo(-50);

		/*
		strafeTo(-16);
		coastTo(50);
		wait1Msec(200);
		coastTo(-10);
		rotateCoast(90,1);
		coastTo(48);
		strafeTo(-10);*/
	}
	else if(centerGoalPosition==0) //vertical
	{
		playSound(soundFastUpwardTones);
		//strafeTo(3);
		coastTo(25);
		coastTo(-5);
		//strafeTo(3);
//		strafeTo(5);
		brake();
		wait1Msec(500);
		raiseLift();
		advBrakeNeg();
		dumpAll();
		lowerLift();
		strafeTo(-5);
		startTask(getSonarValues);
		while(sonarVal < 50){
			strafeTo(-5);
		}
		stopTask(getSonarValues);
		playSound(soundBeepBeep);
		wait1Msec(1000);
		strafeTo(4);
		coastTo(60);
		wait1Msec(200);
		coastTo(-50);

		/*
		strafeTo(-16);
		coastTo(80);
		wait1Msec(200);
		coastTo(-50);
		strafeTo(15);
		coastTo(-72);*/
	}
	else//(centerGoalPosition==1)//45
	{
		playSound(soundDownwardTones);
		rotateCoast(35,1);
		strafeTo(29);

		coastTo(10);
		coastTo(-7);
		wait1Msec(500);
		raiseLift();
		advBrakeNeg();
		dumpAll();
		lowerLift();
		startTask(getSonarValues);
		while(sonarVal < 30){
			strafeTo(-5);
		}
		stopTask(getSonarValues);
		playSound(soundBeepBeep);
		wait1Msec(1000);
		strafeTo(4);
		coastTo(60);
		wait1Msec(200);
		coastTo(-50);
	}

	while(true)wait1Msec(1000);

}
