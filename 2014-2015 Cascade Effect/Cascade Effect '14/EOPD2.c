#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  HTServo,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     ,               sensorI2CMuxController)
#pragma config(Sensor, S3,     Gyro,           sensorI2CHiTechnicGyro)
#pragma config(Sensor, S4,     SMUX,        sensorI2CCustom9V)
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
#include "Drivers/hitechnic-eopd.h"

float eopdVal;
const tMUXSensor eopdSensor = msensor_S4_3;

task main()
{
	while(true)
	{
		HTEOPDsetLongRange(eopdSensor);
		eopdVal = HTEOPDreadProcessed(eopdSensor);
		nxtDisplayBigTextLine(1,"V: %d", eopdVal);
	}
}
