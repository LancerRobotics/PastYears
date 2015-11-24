#include "hitechnic-sensormux.h"
#include "hitechnic-gyro.h"
#include "gyroFunctions.c"
#include "lego-ultrasound.h"
#include "RollingGoal.c"
#include "EOPD.c"
#include "Robotics (PROGRAMENG)/lego-touch.h"
//#include "clampFlagTest.c"


float low;
const tMUXSensor touchClamp = msensor_S4_1;
const tMUXSensor SonarRight = msensor_S4_4;
const tMUXSensor SonarLeft = msensor_S4_3;
float sonarVal;
float sonarRight, sonarLeft;
float ticks = 0;
int theta;
bool braked;
float frontRightPID = 1;
float frontLeftPID = 1;
float backRightPID = 1;
float backLeftPID = 1;
float leftPID = 1;
float rightPID =1;

typedef enum { left = -1, right = 1 } hDir;
typedef enum { snail = 20, slow = 35, medium = 50, fast = 65, max = 78 } speed;


/*float checkMotorEncMin() {
	float maxenc = abs(nMotorEncoder[frontLeft]);

	if(abs(nMotorEncoder[frontRight]) < maxenc)
		maxenc = abs(nMotorEncoder[frontRight]);
	if(abs(nMotorEncoder[backRight]) < maxenc)
		maxenc = abs(nMotorEncoder[backRight]);
	if(abs(nMotorEncoder[backLeft]) < maxenc)
		maxenc = abs(nMotorEncoder[backLeft]);

	return maxenc;
}*/


float checkMotorEnc() {
	float maxenc = abs(nMotorEncoder[frontLeft]);

	if(abs(nMotorEncoder[frontRight]) > maxenc)
		maxenc = abs(nMotorEncoder[frontRight]);
	if(abs(nMotorEncoder[backRight]) > maxenc)
		maxenc = abs(nMotorEncoder[backRight]);
	if(abs(nMotorEncoder[backLeft]) > maxenc)
		maxenc = abs(nMotorEncoder[backLeft]);

	return maxenc;
}

bool advBrakeNeg() {
	motor[motorLift1] = -5;
	motor[motorLift2] = -5;
	return true;
}

task checkIfBraked(){
	int initialEncoder;
	braked = false;
	while(true){
		initialEncoder = checkMotorEnc();
		wait1Msec(100);
		if(abs(initialEncoder-checkMotorEnc()) < 3)
			braked = true;
	}
}


bool lowerLift() {
	motor[motorLift2]=90;
	motor[motorLift1]=90;
	nMotorEncoder[motorLift2] = 0;
	wait1Msec(50);
	while(abs(nMotorEncoder[motorLift2])<abs(1300*3.2)) { /*until its at the top*/ }
	playSound(soundBeepBeep);
	motor[motorLift2]=0;
	motor[motorLift1]=0;
	return true;
}




bool lowerLift2() {
	motor[motorLift2]=90;
	motor[motorLift1]=90;
	nMotorEncoder[motorLift2] = 0;
	wait1Msec(50);
	while(abs(nMotorEncoder[motorLift2])<abs(1440*1.7)) { /*until its at the top*/ }
	playSound(soundBeepBeep);
	motor[motorLift2]=0;
	motor[motorLift1]=0;
	return true;
}


bool brake() {
	motor[frontLeft] = 0;
	motor[frontRight] = 0;
	motor[backLeft] = 0;
	motor[backRight] = 0;
	return true;
}

bool dumpAll() {
	//wait1Msec(2000);
	//encodedMove(-3);
	wait1Msec(100);
	servo[dump] = 180;
	wait1Msec(1000);
	servo[dump] = 70;
	//lowerLift();
	return true;
}

bool dumpAll2() {
	servo[dump] = 170;
	wait1Msec(2000);
	servo[dump] = 66;
	//lowerLift();
	return true;
}
bool raiseLift3()
{
	motor[motorLift2]=-78;
	motor[motorLift1]=-78;
	//raise lift

	nMotorEncoder[motorLift2] = 0;
	wait1Msec(50);
	while(abs(nMotorEncoder[motorLift2])<(2300*2))//2.5 rotations was 1440
	{
		//until its at the top
	}
	playSound(soundBeepBeep);
	motor[motorLift2]=0;
	motor[motorLift1]=0;
	//then stop
	//	stopTask(servoInit);
	return true;
}

bool raiseLift()
{
	motor[motorLift2]=-78;
	motor[motorLift1]=-78;
	//raise lift

	nMotorEncoder[motorLift2] = 0;
	wait1Msec(50);
	while(abs(nMotorEncoder[motorLift2])<((2100*2)-20))//2.5 rotations was 1440
	{
		//until its at the top
	}
	playSound(soundBeepBeep);
	motor[motorLift2]=0;
	motor[motorLift1]=0;
	//then stop
	//	stopTask(servoInit);
	return true;
}
bool raiseLiftCondition(int height)//arbitrary measurements
{

	motor[motorLift2]=-78;
	motor[motorLift1]=-78;
	//raise lift

	nMotorEncoder[motorLift2] = 0;
	wait1Msec(50);
	while(abs(nMotorEncoder[motorLift2])<(height*2))//2.5 rotations was 1440
	{//2100*
		//until its at the top
	}
	playSound(soundBeepBeep);
	motor[motorLift2]=0;
	motor[motorLift1]=0;
	//then stop
	//	stopTask(servoInit);
	return true;
}

bool lowerLiftCondition(int height)
{
	motor[motorLift2]=90;
	motor[motorLift1]=90;
	nMotorEncoder[motorLift2] = 0;
	wait1Msec(50);
	while(abs(nMotorEncoder[motorLift2])<abs(height*3.2)) { /*until its at the top*/ }
	playSound(soundBeepBeep);
	motor[motorLift2]=0;
	motor[motorLift1]=0;
	return true;
}
bool raiseLift2() {

	motor[motorLift2]=-78;
	motor[motorLift1]=-78;
	//raise lift

	nMotorEncoder[motorLift2] = 0;
	wait1Msec(50);
	while(abs(nMotorEncoder[motorLift2])<(1100*2))//2.5 rotations was 1440
	{
		//until its at the top
	}
	playSound(soundBeepBeep);
	motor[motorLift2]=0;
	motor[motorLift1]=0;
	//then stop
	//	stopTask(servoInit);
	return true;
}

bool startCollector(){
	motor[collector] = 65;
	motor[collector2] = -65;
	return true;
}

bool stopCollector(){
	motor[collector] = 0;
	motor[collector2] = 0;
	return true;
}

void freezeEncoders() {
	nMotorEncoder[frontLeft] = 0;
	nMotorEncoder[frontRight] = 0;
	nMotorEncoder[backLeft] = 0;
	nMotorEncoder[backRight] = 0;
	playSound(soundBeepBeep);
}


void rotPwr(int fr, int fl, int br, int bl){
	motor[frontright] = fr;
	motor[frontleft] = fl;
	motor[backright] = br;
	motor[backleft] = bl;
}
void rotPwr(int left, int right){
	rotPwr(right,left,right,left);
}
void rotPwr(int pwr) {
	if(pwr>78)pwr = 78;
	if(pwr<0) pwr = 1;
	rotPwr(pwr,pwr,pwr,pwr);
}
bool rotateCoast(float relativeAngle, int direction){
	float finalHeading = currHeading + direction*relativeAngle;

	if (finalHeading > 360) finalHeading -= 360;
	else if(finalHeading < 0) finalHeading += 360;
	//clearDebugStream();
	//writeDebugStreamLine("%d", finalHeading);
	float z=0;
	float startHeading = currHeading;
	float theta = abs(currHeading-startHeading);
	while(abs(finalHeading - currHeading) >= 0.5){
		z = -direction*(20*cos(PI*theta/relativeAngle)+75);
		motor[frontLeft] = z*.5;
		motor[frontRight] = z*.5;
		motor[backLeft] = z*.5;
		motor[backRight] = z*.5;
		theta = abs(currHeading-startHeading);
	}
	z = 0;
	motor[frontLeft] = z*.5;
	motor[frontRight] = z*.5;
	motor[backLeft] = z*.5;
	motor[backRight] = z*.5;
	playSound(soundBeepBeep);
	wait1Msec(100);
	return true;
}


bool encRot(float dist){
	if(dist<0)
	{
		float encVal = dist/(16.0*PI)*1120/180*114.5;
		freezeEncoders();
		int motorVal = 0;
		while(abs(checkMotorEnc())<abs(encVal/2))
		{
			motorVal++;
			rotPwr(motorVal);
		}
		while(abs(checkMotorEnc()) > abs(encVal/2)
			&&	abs(checkMotorEnc()) < abs(encVal))
		{
			motorVal--;
			rotPwr(motorVal);
		}
		playSound(soundDownwardTones);
		brake();
		playSound(soundBeepBeep);
	}
	else
	{
		float encVal = dist/(16.0*PI)*1120/8.0/30*45;
		freezeEncoders();
		int motorVal = 0;
		while(abs(checkMotorEnc())<abs(encVal/2))
		{
			motorVal++;
			rotPwr(-motorVal);
		}
		while(abs(checkMotorEnc()) > abs(encVal/2))
		{
			motorVal--;
			rotPwr(-motorVal);
		}
		brake();
	}
	return true;
}
/*
task pidControl{
float flInitial, flDistance, frInitial, frDistance, blInitial, blDistance, brInitial, brDistance;
while(true){
flInitial = abs(nMotorEncoder[frontLeft]);
frInitial = abs(nMotorEncoder[frontRight]);
blInitial = abs(nMotorEncoder[backLeft]);
brInitial = abs(nMotorEncoder[backRight]);
wait1Msec(100);
flDistance = abs(nMotorEncoder[frontLeft])-flInitial;
frDistance = abs(nMotorEncoder[frontRight])-frInitial;
blDistance = abs(nMotorEncoder[backLeft])-blInitial;
brDistance = abs(nMotorEncoder[backRight])-brInitial;

if(flDistance > frDistance){
frontLeftPID = frDistance/flDistance;
frontRightPID = 1;
}
else{
frontRightPID = flDistance/frDistance;
frontLeftPID = 1;
}
if(blDistance > brDistance){
backLeftPID = brDistance/blDistance;
backRightPID = 1;
}
else{
backRightPID = blDistance/brDistance;
backLeftPID = 1;
}
}
}
*/

task gyroPID{
	float pidHeading;
	pidHeading = 180 - currHeading;
	while(true){

		if((currHeading + pidHeading)%360 < 180){//left side should be faster, right side slower
			rightPID = (1-.15*abs(currHeading+pidHeading-180)/30);
			leftPID = (1+.15*abs(currHeading+pidHeading-180)/30);
		}
		else{ //right side should be faster, left side slower
			leftPID = (1-.15*abs(currHeading+pidHeading-180)/30);
			rightPID = (1+.15*abs(currHeading+pidHeading-180)/30);
		}

	}
}

bool coastToCollect(float dist)
{
	float encVal = dist/(7.25*PI)*1120;
	freezeEncoders();
	float motorVal;
	startTask(checkIfBraked);
	//startTask(gyroPID);
	if(abs(dist) < 10){
		while(abs(checkMotorEnc()) < abs(encVal))
		{
			motorVal = dist/abs(dist)*(25*cos(PI*checkMotorEnc()/encVal)+25);

			motor[frontLeft] = -motorVal*.5;
			motor[frontRight] = motorVal*.5;
			motor[backRight] = motorVal*.5;
			motor[backLeft] = -motorVal*.5;

			if(braked){
				braked = false;
				break;
			}
		}
	}
	else{
		while(abs(checkMotorEnc()) < 300){
			motorVal = .6*dist/abs(dist)*(45*sin(PI*checkMotorEnc()/500)+45);
			motor[frontLeft] = -motorVal;
			motor[frontRight] = motorVal;
			motor[backRight] = motorVal;
			motor[backLeft] = -motorVal;
			if(braked || (checkMotorEnc() > encVal/2))
				break;
		}

		while(abs(encVal)-abs(checkMotorEnc()) > 300){
			motorVal = .6*dist/abs(dist)*90;
			motor[frontLeft] = -motorVal;
			motor[frontRight] = motorVal;
			motor[backRight] = motorVal;
			motor[backLeft] = -motorVal;
			if(braked)
				break;
		}
		encVal = encVal/abs(encVal)*(abs(encVal)-abs(checkMotorEnc()));
		freezeEncoders();
		while(abs(checkMotorEnc()) < abs(encVal)){
			motorVal = .6*dist/abs(dist)*(35*cos(PI*checkMotorEnc()/encVal)+35);
			motor[frontLeft] = -motorVal;
			motor[frontRight] = motorVal;
			motor[backRight] = motorVal;
			motor[backLeft] = -motorVal;
			if(braked){
				braked = false;
				break;
			}
		}
	}
	stopTask(checkIfBraked);
	motor[frontLeft] = 0;
	motor[frontRight] = 0;
	motor[backRight] = 0;
	motor[backLeft] = 0;
	wait1Msec(500);
	return true;
}

bool coastToSlow(float dist)
{
	float encVal = dist/(7.25*PI)*1120;
	freezeEncoders();
	float motorVal;
	startTask(checkIfBraked);
	//startTask(gyroPID);
	if(abs(dist) < 10){
		while(abs(checkMotorEnc()) < abs(encVal))
		{
			motorVal = dist/abs(dist)*(25*cos(PI*checkMotorEnc()/encVal)+25);

			motor[frontLeft] = -motorVal*leftPID*.5;
			motor[frontRight] = motorVal*rightPID*.5;
			motor[backRight] = motorVal*rightPID*.5;
			motor[backLeft] = -motorVal*leftPID*.5;

			if(braked){
				braked = false;
				break;
			}
		}
	}
	else{
		/*while(abs(checkMotorEnc()) < 1000){
		motorVal = dist/abs(dist)*(45*sin(PI*checkMotorEnc()/500)+45);
		motor[frontLeft] = -motorVal*leftPID;
		motor[frontRight] = motorVal*rightPID;
		motor[backRight] = motorVal*rightPID;
		motor[backLeft] = -motorVal*leftPID;
		if(braked || (checkMotorEnc() > encVal/2))
		break;
		}*/

		while(abs(encVal)-abs(checkMotorEnc()) > 1200){
			motorVal = dist/abs(dist)*90;
			motor[frontLeft] = -motorVal*leftPID*.5;
			motor[frontRight] = motorVal*rightPID*.5;
			motor[backRight] = motorVal*rightPID*.5;
			motor[backLeft] = -motorVal*leftPID*.5;
			if(braked)
				break;
		}
		encVal = encVal/abs(encVal)*(abs(encVal)-abs(checkMotorEnc()));
		freezeEncoders();
		while(abs(checkMotorEnc()) < abs(encVal)){
			motorVal = dist/abs(dist)*(35*cos(PI*checkMotorEnc()/encVal)+35);
			motor[frontLeft] = -motorVal*leftPID*.5;
			motor[frontRight] = motorVal*rightPID*.5;
			motor[backRight] = motorVal*rightPID*.5;
			motor[backLeft] = -motorVal*leftPID*.5;
			if(braked){
				braked = false;
				break;
			}
		}
	}
	stopTask(checkIfBraked);
	//stopTask(gyroPID);
	/*
	startTask(checkIfBraked);
	while(abs(checkMotorEnc()) < abs(encVal)){
	//if(abs(encVal)-abs(checkMotorEnc()) > 600)
	//	motorVal = -dist/abs(dist)*78;
	//else
	motorVal = -dist/abs(dist)*(25*cos(pi*checkMotorEnc()/encval)+50);
	motor[frontLeft] = -motorVal;
	motor[frontRight] = motorVal;
	motor[backRight] = motorVal;
	motor[backLeft] = -motorVal;
	if(braked)
	{
	braked = false;
	break;
	}
	}
	stopTask(checkIfBraked);
	*/
	motor[frontLeft] = 0;
	motor[frontRight] = 0;
	motor[backRight] = 0;
	motor[backLeft] = 0;
	wait1Msec(500);
	return true;
}
bool coastTo(float dist){
	float encVal = dist/(7.25*PI)*1120;
	freezeEncoders();
	float motorVal;
	startTask(checkIfBraked);
	//startTask(gyroPID);
	if(abs(dist) < 10){
		while(abs(checkMotorEnc()) < abs(encVal))
		{
			motorVal = dist/abs(dist)*(25*cos(PI*checkMotorEnc()/encVal)+25);

			motor[frontLeft] = -motorVal*leftPID;
			motor[frontRight] = motorVal*rightPID;
			motor[backRight] = motorVal*rightPID;
			motor[backLeft] = -motorVal*leftPID;

			if(braked){
				braked = false;
				break;
			}
		}
	}
	else{
		/*while(abs(checkMotorEnc()) < 1000){
		motorVal = dist/abs(dist)*(45*sin(PI*checkMotorEnc()/500)+45);
		motor[frontLeft] = -motorVal*leftPID;
		motor[frontRight] = motorVal*rightPID;
		motor[backRight] = motorVal*rightPID;
		motor[backLeft] = -motorVal*leftPID;
		if(braked || (checkMotorEnc() > encVal/2))
		break;
		}*/

		while(abs(encVal)-abs(checkMotorEnc()) > 1200){
			motorVal = dist/abs(dist)*90;
			motor[frontLeft] = -motorVal*leftPID;
			motor[frontRight] = motorVal*rightPID;
			motor[backRight] = motorVal*rightPID;
			motor[backLeft] = -motorVal*leftPID;
			if(braked)
				break;
		}
		encVal = encVal/abs(encVal)*(abs(encVal)-abs(checkMotorEnc()));
		freezeEncoders();
		while(abs(checkMotorEnc()) < abs(encVal)){
			motorVal = dist/abs(dist)*(35*cos(PI*checkMotorEnc()/encVal)+35);
			motor[frontLeft] = -motorVal*leftPID;
			motor[frontRight] = motorVal*rightPID;
			motor[backRight] = motorVal*rightPID;
			motor[backLeft] = -motorVal*leftPID;
			if(braked){
				braked = false;
				break;
			}
		}
	}
	stopTask(checkIfBraked);
	//stopTask(gyroPID);
	/*
	startTask(checkIfBraked);
	while(abs(checkMotorEnc()) < abs(encVal)){
	//if(abs(encVal)-abs(checkMotorEnc()) > 600)
	//	motorVal = -dist/abs(dist)*78;
	//else
	motorVal = -dist/abs(dist)*(25*cos(pi*checkMotorEnc()/encval)+50);
	motor[frontLeft] = -motorVal;
	motor[frontRight] = motorVal;
	motor[backRight] = motorVal;
	motor[backLeft] = -motorVal;
	if(braked)
	{
	braked = false;
	break;
	}
	}
	stopTask(checkIfBraked);
	*/
	motor[frontLeft] = 0;
	motor[frontRight] = 0;
	motor[backRight] = 0;
	motor[backLeft] = 0;
	wait1Msec(500);
	return true;
}

task touchPressed{
	while(true){
		pressed = TSreadState(touchClamp);
		wait1Msec(10);
		pressed = false;
	}
}

void agitateUntilCollected()
{
	int runCounter = 0;
	startTask(runRollingGoal);
	//startTask(touchPressed);

	while(!TSreadState(touchClamp) || (runCounter < 4))
	{
		playSound(soundBeepBeep);
		//if(pressed) break;
		if(TSreadState(touchClamp) ==  true) break;
		//servo[rollingGoalPair] = DRAG;
		servo[rollingGoalPair] = CLAMPED;
		//if(pressed) break;
		//if(TSreadState(touchClamp) ==  true) break;
		wait1Msec(400);
		//coastTo(-5);
		//if(pressed) break;
		if(TSreadState(touchClamp) ==  true) break;
		servo[rollingGoalPair] = OPEN;
		wait1Msec(200);
		if(TSreadState(touchClamp) ==  true) break;
		//if(pressed) break;
		coastToCollect(8);
		//if(pressed) break;
		if(TSreadState(touchClamp) ==  true) break;
		wait1Msec(500);
		//if(pressed) break;
		if(TSreadState(touchClamp) ==  true) break;
		servo[rollingGoalPair] = CLAMPED;
		//if(pressed) break;
		runCounter++;
	}
	servo[rollingGoalPair] = CLAMPED;
	stopTask(runRollingGoal);
	playSound(soundUpwardTones);
	//stopTask(touchPressed);
	//touchClamp = false;
}
/*
task collectGoal
{
while(true)
{
if(!TSreadState(touchClamp))wait1Msec(50);//
else break agitateLoop;
}
}

bool coastRaw(int dist){
float encval = dist;
freezeEncoders();
int motorVal;
startTask(checkIfBraked);
while(abs(checkMotorEnc()) < abs(encVal)){
//if(abs(encVal)-abs(checkMotorEnc()) > 600)
//	motorVal = -dist/abs(dist)*78;
//else
motorVal = -dist/abs(dist)*(25*cos(pi*checkMotorEnc()/encval)+50);
motor[frontLeft] = -motorVal;
motor[frontRight] = motorVal;
motor[backRight] = motorVal;
motor[backLeft] = -motorVal;
if(braked){
braked = false;
break;
}
}
stopTask(checkIfBraked);
motor[frontLeft] = 0;
motor[frontRight] = 0;
motor[backRight] = 0;
motor[backLeft] = 0;
wait1Msec(500);
return true;
}
*/
bool strafe(hDir dir, speed motorVal){
	motor[frontLeft] = dir*-motorVal;
	motor[frontRight] = dir*-motorVal;
	motor[backRight] = dir*motorVal;
	motor[backLeft] = dir*motorVal;
	return true;
}

bool strafeTo(float dist){
	float encVal = dist/(7.25*PI)*1120*15/11.5;
	freezeEncoders();
	int motorVal;
	startTask(checkIfBraked);
	/*while(abs(encVal)-abs(checkMotorEnc()) > 500){
	motorVal = -dist/abs(dist)*100;
	nxtDisplayBigStringAt(0,31,"%d",motorVal);
	motor[frontLeft] = -motorVal*frontLeftPID;
	motor[frontRight] = -motorVal*frontRightPID;
	motor[backRight] = motorVal*backRightPID;
	motor[backLeft] = motorVal*backLeftPID;
	if(braked){
	braked = false;
	break;
	}
	}
	encVal = encVal/abs(encVal)*(abs(encVal) - abs(checkMotorEnc()));
	freezeEncoders();*/
	while(abs(checkMotorEnc()) < abs(encVal)){
		motorVal = -dist/abs(dist)*80;
		motor[frontLeft] = -motorVal*frontLeftPID;
		motor[frontRight] = -motorVal*frontRightPID;
		motor[backRight] = motorVal*backRightPID;
		motor[backLeft] = motorVal*backLeftPID;
		if(braked){
			braked = false;
			break;
		}
	}
	stopTask(checkIfBraked);
	/*	while(abs(checkMotorEnc()) < abs(encVal)){
	motorVal = -dist/abs(dist)*(25*cos(pi*checkMotorEnc()/encval)+50);
	motor[frontLeft] = -motorVal;
	motor[frontRight] = -motorVal;
	motor[backRight] = motorVal;
	motor[backLeft] = motorVal;
	}*/
	motor[frontLeft] = 0;
	motor[frontRight] = 0;
	motor[backRight] = 0;
	motor[backLeft] = 0;
	wait1Msec(200);
	return true;
}

bool strafeRaw(float dist){
	float encVal = dist;
	freezeEncoders();
	int motorVal;
	while(abs(checkMotorEnc()) < abs(encVal)){
		motorVal = -dist/abs(dist)*(25*cos(PI*checkMotorEnc()/encVal)+50);
		motor[frontLeft] = -motorVal;
		motor[frontRight] = -motorVal;
		motor[backRight] = motorVal;
		motor[backLeft] = motorVal;
	}
	motor[frontLeft] = 0;
	motor[frontRight] = 0;
	motor[backRight] = 0;
	motor[backLeft] = 0;
	wait1Msec(500);
	return true;
}

bool waitMsec(int a){
	wait1Msec(a);
	return true;
}

void motorTrigger(tMotor motorCall,int x,int y,int z)
{
	motor[motorCall]= (y+x+z);
}

bool diagonalTo(float dist, float angle){
	angle-=90;
	if(angle < 0) angle+=360;
	float encVal = dist/(7.25*PI)*1120*1.9;
	int power = 78;
	int x = power*128/100*cosDegrees(angle);
	int y = power*128/100*sinDegrees(angle);
	/*if(angle > 180)
	{
	x = -x;
	y = -y;
	}
	if(angle > 45 && angle < 180)
	{
	x = -x;
	y = -y;
	}	*/

	freezeEncoders();
	startTask(checkIfBraked);
	while(abs(checkMotorEnc()) < abs(encVal)){
		motorTrigger(frontRight,x,-y,0);
		motorTrigger(backRight,-x,-y,0);
		motorTrigger(frontLeft,x,y,0);
		motorTrigger(backLeft,-x,y,0);
		if(braked){
			braked = false;
			break;
		}
	}
	stopTask(checkIfBraked);
	motor[frontLeft] = 0;
	motor[frontRight] = 0;
	motor[backRight] = 0;
	motor[backLeft] = 0;
	wait1Msec(500);
	return true;
}



bool diagonalRaw(float dist, float angle){
	float encVal = dist;
	freezeEncoders();
	float x = cos(angle)*dist;
	float y = sin(angle)*dist;
	while(abs(checkMotorEnc()) < abs(encVal)){
		motor[frontLeft]=(-y+x)*(100/dist);
		motor[backLeft]= (-y-x)*(100/dist); // -y-x||x+y
		motor[frontRight]=(y+x)*(100/dist);//-y+x||-x+y
		motor[backRight]=(y-x)*(100/dist);
	}
	motor[frontLeft] = 0;
	motor[frontRight] = 0;
	motor[backRight] = 0;
	motor[backLeft] = 0;
	wait1Msec(500);
	return true;
}

task getSonarValues() {
	low=255;
	while(true){
		sonarRight = USReadDist(SonarRight);
		sonarLeft = USReadDist(SonarLeft);
		if(sonarRight < 200 && sonarLeft > 200)
			sonarVal = sonarRight;
		else if(sonarLeft < 200 && sonarRight > 200)
			sonarVal = sonarLeft;
		else
			sonarVal = (sonarRight + sonarLeft)/2;
		if(sonarVal < low) low = sonarVal;
		wait1Msec(200);
	}
}

void rotateAlign(int angle){

	if(currHeading > 180)
	{
		playSound(soundBeepBeep);
		int z = 0;
		if((currHeading + 180)%360 > angle)
		{
			while(abs(angle-currHeading) >= 0.5)
			{
				z = -40;
				motor[frontLeft] = z;
				motor[frontRight] = z;
				motor[backLeft] = z;
				motor[backRight] = z;
			}
		}
		else
		{
			while(abs(angle-currHeading) >= 0.5)
			{
				z = 40;
				motor[frontLeft] = z;
				motor[frontRight] = z;
				motor[backLeft] = z;
				motor[backRight] = z;
			}
		}
		motor[frontLeft] = 0;
		motor[frontRight] = 0;
		motor[backLeft] = 0;
		motor[backRight] = 0;
	}

	else
	{
		playSound(soundDownwardTones);
		int z = 0;
		if((currHeading + 180)%360 > angle){
			while(abs(angle-currHeading) >= 0.5){
				z = -20;
				motor[frontLeft] = -z;
				motor[frontRight] = -z;
				motor[backLeft] = -z;
				motor[backRight] = -z;
			}
		}
		else{
			while(abs(angle-currHeading) >= 0.5){
				z = 20;
				motor[frontLeft] = -z;
				motor[frontRight] = -z;
				motor[backLeft] = -z;
				motor[backRight] = -z;
			}
		}
		motor[frontLeft] = 0;
		motor[frontRight] = 0;
		motor[backLeft] = 0;
		motor[backRight] = 0;
	}

}


void rotateAlignTo(int angle){

	if(angle-currHeading < 180)
	{
		playSound(soundBeepBeep);
		int z = 0;
		if((currHeading + 180)%360 > angle)
		{
			while(abs(angle-currHeading) >= 0.5)
			{
				z = -20;
				motor[frontLeft] = z;
				motor[frontRight] = z;
				motor[backLeft] = z;
				motor[backRight] = z;
			}
		}
		else
		{
			while(abs(angle-currHeading) >= 0.5)
			{
				z =20;
				motor[frontLeft] = z;
				motor[frontRight] = z;
				motor[backLeft] = z;
				motor[backRight] = z;
			}
		}
		motor[frontLeft] = 0;
		motor[frontRight] = 0;
		motor[backLeft] = 0;
		motor[backRight] = 0;
	}

	else
	{
		playSound(soundDownwardTones);
		int z = 0;
		if((currHeading + 180)%360 > angle){
			while(abs(angle-currHeading) >= 0.5){
				z = -20;
				motor[frontLeft] = -z;
				motor[frontRight] = -z;
				motor[backLeft] = -z;
				motor[backRight] = -z;
			}
		}
		else{
			while(abs(angle-currHeading) >= 0.5){
				z = 20;
				motor[frontLeft] = -z;
				motor[frontRight] = -z;
				motor[backLeft] = -z;
				motor[backRight] = -z;
			}
		}
		motor[frontLeft] = 0;
		motor[frontRight] = 0;
		motor[backLeft] = 0;
		motor[backRight] = 0;
	}

}



int getPosition()
{
	startTask(getSonarValues);
	wait1Msec(500);
	stopTask(getSonarValues);
	if(sonarLeft < 25)
		return 0;
	else{
		rotateCoast(38, -1);
		startTask(getSonarValues);
		wait1Msec(500);
		stopTask(getSonarValues);
		wait1Msec(500);
		if(sonarLeft > 200 && sonarRight < 40){
			//rotateAlign(0);
			return 1;
		}
		else{
			return 2;
		}
	}
}

	/*
	if((sonarRight < 40  && sonarLeft < 40) && (sonarRight > 10  && sonarLeft > 10))
	{
	return 2;
	}
	else if(sonarLeft < 25 && sonarRight > 30)
	{
	return 0;
	}*/


	//else return 1;

	//
	//

	//if values are less than 20 than verticle

	// 45's should be around 30 and 26 and 26


	// Horizontal 34 and 24 and 25 and 24
	/*
	startTask(readEOPD);
	if(sonarLeft < 22 && sonarRight > 200){
	playSound(soundBeepBeep);
	wait1Msec(100);
	return 0; //vertical
	}
	else{

	coastTo(5.5);

	if(floorColor == NOTGRAY){
	return 2; //horizontal
	}
	else{
	return 1; //45
	}
	stopTask(readEOPD);
	}

	//rawSonarPosition1 = sonarVal;
	startTask(getSonarValues);
	strafeTo(5);
	stopTask(getSonarValues);
	rawSonarPosition2 = sonarVal;
	//sonarVal = low;
	//if(sonarVal<50){return 0;}//vertical
	//else if(sonarVal<64){return 2;}//horizontal
	//else if(abs(sonarVal) > 200){return 1;}//45
	//the low is already 255 so if it doesnt read values it defaults
	*/



void centerAlign(){
	startTask(readEopd);
	if(floorColor ==NOTGRAY)strafeTo(15);
	while(floorColor == NOTGRAY){
		//strafe(left, 80);
		strafeTo(-5);
	}


	brake();
	stopTask(readEOPD);
	//strafeTo(2);

}


int centerGoalPosition = -1;
float sonargetter;
task symphonize() {
	while(true){
		playSound(soundDownwardTones);
		wait1Msec(500);
		playSound(soundUpwardTones);
		wait1Msec(500);
	}
}


void hitKickstand()
{
	//		rotateAlign
	strafeTo(-10);
	startTask(getSonarValues);
	while(sonarLeft < 40){
		strafeTo(-3);
	}
	strafeTo(-8);
	if(centerGoalPosition==0)rotateAlign(0);
	playSound(soundBeepBeep);
	wait1Msec(1000);
	if(centerGoalPosition == 0)rotateAlign(0);
	/*else if(centerGoalPosition == 1);
	else ;*/
	coastTo(60);
	////tTo(20);
	startCollector();
	wait1Msec(200);
	coastTo(-40);
	if(centerGoalPosition != 2 && centerGoalPosition != 1) coastTo(60);
	//while(true)wait1Msec(300);
}



//rotateAlign(0);
//coastTo(value);
//
void resetMonty() {
	rotateAlign(0);
	coastTo(-10);
}
