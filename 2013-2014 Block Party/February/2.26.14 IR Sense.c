#pragma config(Hubs,  S1, HTMotor,  HTMotor,  HTMotor,  HTMotor)
#pragma config(Hubs,  S2, HTServo,  HTServo,  none,     none)
#pragma config(Sensor, S3,     SMUX,           sensorI2CCustom)
#pragma config(Motor,  mtr_S1_C1_1,     lift,          tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C1_2,     hang,          tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C2_1,     rightFront,    tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C2_2,     rightBack,     tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C3_1,     hang2,         tmotorTetrix, PIDControl)
#pragma config(Motor,  mtr_S1_C3_2,     flag,          tmotorTetrix, openLoop)
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
#include "Auto Header 2.11.14.h"
#include "C:\Program Files (x86)\Robomatter Inc\ROBOTC Development Environment\Sample Programs\NXT\3rd Party Sensor Drivers\drivers\hitechnic-sensormux.h"
#include "C:\Program Files (x86)\Robomatter Inc\ROBOTC Development Environment\Sample Programs\NXT\3rd Party Sensor Drivers\drivers\hitechnic-irseeker-v2.h"
const tMUXSensor irSMUX = msensor_S3_1;

task main()
{
while(true){
	nxtDisplayString(3,"%d",(HTIRS2readACDir(irSMUX)));
	wait10Msec(1);
}
}
